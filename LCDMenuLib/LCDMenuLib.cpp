/* ******************************************************************** */
/*																		*/
/*						LCDMenuLib (LCDML)								*/
/*																		*/
/* ******************************************************************** */
/* Autor:			Nils Feldkämper										*/
/* Create:			03.02.2008											*/
/* Edit:			17.05.2015											*/
/* ******************************************************************** */

/* ******************************************************************** */
/* ============															*/
/* Description:															*/
/* ============															*/
/* With this library, you can create menus with layers on base on the   */
/* Nested-Set-Model. For every menu element can be create a function    */
/* to control the content. This function is called automatical from the */
/* library and can runs in a loop, without blocking other programm parts*/
/* ******************************************************************** */

/* ******************************************************************** */
/* ======================												*/
/* Beschreibung (german):												*/
/* ======================												*/
/* Mit der Lib können LCD Menüs über mehrere Ebenen mit Hilfe des   	*/
/* Nested Set Models generiert werden. Jeder Menüpunkt kann mit einer   */
/* Funktion hinterlegt werden die durch die Lib aufgerufen wird, sobald */
/* der Menüpunkt aktiviert wird.										*/
/* ******************************************************************** */

/* ******************************************************************** */
/* error reporting (english / german)									*/
/*	https://github.com/Jomelo/LCDMenuLib/issues							*/
/* support (german):													*/
/* 	http://forum.arduino.cc/index.php?topic=73816.0						*/
/* ******************************************************************** */

/************************************************************************/
/* Features:															*/
/* - max 254 menu elements												*/
/* - max 254 menu elements per layer								    */
/* - max 6 layers from root, configurable in LCDMenuLib___config.h		*/
/* - max support for 6 buttons up, down, left, right, back/quit, enter  */
/* - min 3 buttons needed up, down, enter                               */
/* - control over, analog buttons, digital buttons, encoder, ir, ...    */
/* - separation of structural and functional level                      */
/* - scrollbar when more menu elments in a layer then rows, configurable*/
/* - last cursor pos is saved											*/
/* - possibility to jump from one menu elment directly to another       */
/* - support for many different lcd librarys in LCDMenuLib___config.h   */
/*		4bit lcd support												*/
/* 		8bit lcd support												*/
/* 		i2c lcd support													*/
/* 		shift register lcd support										*/
/*		DogLcd support													*/
/* - max 254 simple threads can be used									*/
/*   this threads are working in the background to check temp or other  */
/*   sensors or other things											*/
/*																		*/
/*																		*/
/* - no support for gaphic displays 									*/
/************************************************************************/

#	include <LCDMenuLib.h>


/* ******************************************************************** */
/* constructor
 *	@param
 *		menu instance
 *		LCD instance
 *		flash table for menu elements
 *		lcd rows
 *		lcd colls
 *	@return
 * ******************************************************************** */
LCDMenuLib::LCDMenuLib(LCDMenu &p_r, _LCDML_lcd_type &p_d, const char * const *p_flash_table, const uint8_t p_rows, const uint8_t p_cols)
/* ******************************************************************** */
{
	// initialisation
    rootMenu        = &p_r;
    curMenu         = rootMenu;
	flash_table     = p_flash_table;
    lcd             = &p_d;		
	control			= 0; 
    cursor_pos      = 0;
    layer           = 0;
    layer_save[0]   = 0;
	child_cnt		= 0;
	rows			= p_rows;
	cols			= (p_cols-1); 	
    function		= _LCDML_NO_FUNC;
    button			= 0;	
}


/* ******************************************************************** *
 * private
 * @param
 *		menu instance (pointer)
 *		menu element (pointer)
 * @return
 *		search status (uint8)
 * ******************************************************************** */
uint8_t		LCDMenuLib::selectElementDirect(LCDMenu &p_m, uint8_t p_search)
/* ******************************************************************** */
{
	//deklaration
	LCDMenu * search = &p_m;
	LCDMenu * tmp;	
	uint8_t found	 = 0;

	bitSet(control, _LCDML_control_search_display);
			
	do 
	{
		tmp = search->getChild(0);
			
		if (tmp) {//check elements for childs					
			goEnter();					
			
			if (tmp->name == p_search) { //search elements in this layer			
				found = 1;				
				break;
			}
			else {
				function = _LCDML_NO_FUNC;
			}

			found = selectElementDirect(*tmp, p_search); //recursive search until found is true or last item reached
						
			if (found == 1) {  //check result
				//something found
				break; 
			} 
			else {
				function = _LCDML_NO_FUNC;				
				//nothing found
				//goto next root element
				goBack();
				Button_udlr(_LCDML_button_down);				
			}				
		} 
		else {			
			//no childs found				
			if (search->name == p_search) {  //search
			
				//found something
				found = 1;				
				break;
			} 
			else {
				function = _LCDML_NO_FUNC;
				//select next element			
				Button_udlr(_LCDML_button_down);				
			}
		}		
	} while ((search=search->getSibling(1)) != NULL && found == 0);

	if (found == 1) {
		bitClear(control, _LCDML_control_search_display);
	}
	//return result
	return found;	
}


/* ******************************************************************** *
 * public: go to the first element in this menu with id = 0
 * @param
 * @return
 * ******************************************************************** */
void		LCDMenuLib::goRoot()
/* ******************************************************************** */
{
	//go back to root layer
	while(layer > 0) 
	{ 
		Button_quit(); 
	}	
	//ends the last aktive function or do nothing
	Button_quit();
	
	//reset buttons and cursor position
	button = 0;
	cursor_pos = 0;
	curloc = 0;
	scroll = 0;	
	//display menu
	display();
}

/* ******************************************************************** *
 * public: jump to an item of this menu if exists
 * @param
 *		item name (uint8)
 * @return
 * ******************************************************************** */
void		LCDMenuLib::jumpToElement(uint8_t p_element)
/* ******************************************************************** */
{
	Button_quit();
	goRoot();		
	
	bitSet(control, _LCDML_control_disable_hidden);
	if(selectElementDirect(*rootMenu, p_element)) { //search element
		//open this element
		goEnter();
		//Button_enter();
	}
	bitClear(control, _LCDML_control_disable_hidden);
	bitClear(control, _LCDML_control_search_display);
}


/* ******************************************************************** *
 * public: go to the first element in this menu with id = 0
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::goBack()
/* ******************************************************************** */
{	
	if(layer > 0) {	 //check layer
		//go back
		bitWrite(control, _LCDML_control_menu_back, 1);
		goMenu(*curMenu->getParent());
	}		
}


/* ******************************************************************** *
 * private: curloc correction
 * @param
 * @return
 *	correction (uint8)
 * ******************************************************************** */
uint8_t		LCDMenuLib::curloc_correction()
{
	LCDMenu *tmp;	// declare opjects
	uint8_t	curloc_cor = 0;
	uint8_t j = 0;
	//correct function / menu element to open for hidden menu elements
	if ((tmp = curMenu->getChild(0)) != NULL) {
		do
		{
			if (bitRead(group_en, tmp->disp) || bitRead(control, _LCDML_control_disable_hidden)) {
				j++;
			}
			else {
				if (j <= curloc) {
					curloc_cor++;
				}
			}
		} while ((tmp = tmp->getSibling(1)) != NULL);
	}
	return curloc_cor;
}


/* ******************************************************************** *
 * private: go in a menu item and start function
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::goEnter()
/* ******************************************************************** */
{
	LCDMenu *tmp;	// declare opjects
	uint8_t name		= function;
	uint8_t j			= 0;
	
	if (function == _LCDML_NO_FUNC) { //check button lock		
		//check if element has childs
		if ((tmp = curMenu->getChild(curloc + curloc_correction())) != NULL) { // check child			
			goMenu(*tmp);					
			name = tmp->name;		

			//check if element has childs			
			if ((tmp = tmp->getChild(0)) != NULL) {			
				
				while ((tmp = tmp->getSibling(1)) != NULL)
				{
					if (bitRead(group_en, tmp->disp) || bitRead(control, _LCDML_control_disable_hidden)) {
						j++;
					}					
				}
			}

			if (j == 0) {				
				function = name;
				countChilds();
			}			
		}		
	}
}


/* ******************************************************************** *
 * private: go in a menu item and display next elements
 * @param
 *		pointer to next menu item
 * @return
 * ******************************************************************** */
void	LCDMenuLib::goMenu(LCDMenu &m)
/* ******************************************************************** */
{
	//declare variables
	int diff;
    scroll = 0;

	//set current menu object	
	curMenu=&m;	
		
	if(layer < _LCDML_DISP_cfg_cursor_deep) { //check layer deep		
		if(bitRead(control, _LCDML_control_menu_back) == 0) { //check back button		
			//go into the next layer
			layer_save[layer] = curloc;
			layer++;		
			curloc = 0;
		} 
		else {
			//button reset
			bitWrite(control, _LCDML_control_menu_back, 0);
			
			if(layer > 0) {				
				layer--;				
				curloc = layer_save[layer];

				if(curloc >= rows) {
					diff = curloc-(rows-1);
					for(int i=0; i<diff; i++) 
					{
						doScroll();
					}
				}
			}
		}
	}
	display();	
}


/* ******************************************************************** *
 * private: count sibling for an menu item if exists
 * @param
 * @return
 *	sibling count 0 = one 
 * ******************************************************************** */
uint8_t    LCDMenuLib::countChilds()
/* ******************************************************************** */
{
	//declaration
	LCDMenu * tmp;
	uint8_t j = 0;

	//check if element has childs
	if ((tmp = curMenu->getChild(0)) != NULL) {		
		while ((tmp = tmp->getSibling(1)) != NULL)
		{
			if (bitRead(group_en, tmp->disp) || bitRead(control, _LCDML_control_disable_hidden)) {				
				j++;
			}			
		}		
	}	
	return j;
}


/* ******************************************************************** *
 * public: display the current menu
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::display()
/* ******************************************************************** */
{

	//declaration
	LCDMenu * tmp;
	uint8_t i = scroll;
	uint8_t maxi = (rows + scroll);
	char buffer[_LCDML_DISP_cfg_max_string_length];

	child_cnt = countChilds();

	

	//check children
	if ((tmp = curMenu->getChild(i))) {
		if (!bitRead(control, _LCDML_control_search_display)) {
			//clear lcd
			lcd->_LCDML_lcd_clear();

			//show menu structure
			do
			{
				if (bitRead(group_en, tmp->disp)) {
					lcd->_LCDML_lcd_setCursor(0, i - scroll);
					lcd->_LCDML_lcd_write(0x20);
					lcd->_LCDML_lcd_setCursor(1, i - scroll);

					//get name from flash table
					strcpy_P(buffer, (char*)pgm_read_word(&(flash_table[tmp->name])));

					//check if string is to long for the lcd display with and without scrollbar				
					if (strlen(buffer) > (uint8_t)(cols - (1 << bitRead(control, _LCDML_control_scrollbar_l)))) {
						//error message
						lcd->_LCDML_lcd_print(F("too_long"));
					}
					else {
						//write string  to row
						lcd->_LCDML_lcd_print(buffer);
					}

					//select next element in flash table which is not hidden
					i++;
				}

			} while ((tmp = tmp->getSibling(1)) != NULL && i<maxi);

			//show scrollbar mode 2
			if (bitRead(control, _LCDML_control_scrollbar_l) == 1) {

				//show scrollbar
				if (child_cnt>(rows - 1)) {
					if ((curloc == child_cnt && curloc != 0) || (curloc != child_cnt && curloc != 0)) {
						lcd->_LCDML_lcd_setCursor((cols), 0);
						lcd->_LCDML_lcd_write((uint8_t)(!bitRead(control, _LCDML_control_lcd_standard) ? 0x00 : 0x18));
					}

					if ((curloc != child_cnt && curloc == 0) || (curloc != child_cnt && curloc != 0)) {
						lcd->_LCDML_lcd_setCursor((cols), (rows - 1));
						lcd->_LCDML_lcd_write((uint8_t)(!bitRead(control, _LCDML_control_lcd_standard) ? 0x01 : 0x19));
					}
				}
			}
		}
	}
	else { // no children
		goBack();
		// function can run ...
		
		
	}
	setCursor();
}


/* ******************************************************************** *
 * private: set cursor position
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::setCursor()
/* ******************************************************************** */
{
	child_cnt = countChilds();

	//reset last cursor position
	if (cursor_pos > curloc - scroll) {
		//reset cursor in row 0
		lcd->_LCDML_lcd_setCursor(0, cursor_pos);
		lcd->_LCDML_lcd_write(0x20);
	}
	else if (cursor_pos < curloc - scroll) {
		//reset cursor at row > 0
		lcd->_LCDML_lcd_setCursor(0, curloc - scroll - 1);
		lcd->_LCDML_lcd_write(0x20);
	}

	//save current cursor position
	cursor_pos = curloc - scroll;

	if (cursor_pos > child_cnt) {
		cursor_pos = child_cnt;
	}

	if (!bitRead(control, _LCDML_control_search_display)) {
		//set cursor 
		lcd->_LCDML_lcd_setCursor(0, cursor_pos);
		lcd->_LCDML_lcd_write(_LCDML_DISP_cfg_cursor);

		if (bitRead(control, _LCDML_control_scrollbar_l) == 1) { //check scrollbar mode
			//count elements in this layer
			uint8_t j = child_cnt;

			//show scrollbar
			if (j > (rows - 1)) {
				//reset row 0
				lcd->_LCDML_lcd_setCursor(cols, 0);
				lcd->_LCDML_lcd_write((uint8_t)0);
				//reset row 1
				if (rows >= 2) {
					lcd->_LCDML_lcd_setCursor(cols, 1);
					lcd->_LCDML_lcd_write((uint8_t)0);
				}
				//reset row 2
				if (rows >= 3) {
					lcd->_LCDML_lcd_setCursor(cols, 2);
					lcd->_LCDML_lcd_write((uint8_t)0);
				}
				//reset row 3
				if (rows >= 4) {
					lcd->_LCDML_lcd_setCursor(cols, 3);
					lcd->_LCDML_lcd_write((uint8_t)0);
				}

				//show scrollbar
				if (curloc == 0) {
					//first element
					lcd->_LCDML_lcd_setCursor(cols, 0);
					lcd->_LCDML_lcd_write((uint8_t)1);
				}
				else if (curloc == j) {
					//last element
					lcd->_LCDML_lcd_setCursor(cols, (rows - 1));
					lcd->_LCDML_lcd_write((uint8_t)4);
				}
				else {
					//set scroll position
					uint8_t scroll_pos = ((4.*rows) / j*curloc);
					lcd->_LCDML_lcd_setCursor(cols, scroll_pos / 4);
					lcd->_LCDML_lcd_write((scroll_pos % 4) + 1);
				}
			}
		}
	}
}


/* ******************************************************************** *
 * private: do scroll if lines in display to small to show all items
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::doScroll()
/* ******************************************************************** */
{
	//only allow it to go up to menu element   
	while (curloc>0 && !curMenu->getChild(curloc))
	{
		curloc--;
	}
	//scroll down
	if (curloc >= (rows + scroll))
	{
		scroll++;
		display();
	}
	//scroll up
	else if (curloc < scroll)
	{
		scroll--;
		display();
	}
	//do not scroll
	else
	{
		setCursor();
	}
}
  

/* ******************************************************************** *
 * public: button enter was pressed, save the state or go in an item
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::Button_enter()
/* ******************************************************************** */
{	
	if (function != _LCDML_NO_FUNC)
	{			
		//function is active		
		bitSet(button, _LCDML_button_enter);
	}
	else {
		//menu is active
		goEnter();
	}			
}


/* ******************************************************************** *
 * public: button up down left right were pressed 
 * @param
 *		(u)p (d)own (l)eft (r)ight status (uint8)
 * @return
 * ******************************************************************** */
void	LCDMenuLib::Button_udlr(uint8_t but)
/* ******************************************************************** */
{	
	if (function == _LCDML_NO_FUNC) {	//check menu lock	
		//enable up and down button for menu mode and scroll		
		switch(but)
		{
			case _LCDML_button_up:   if(curloc > 0) { curloc--; }	break;
			case _LCDML_button_down: if (curloc < child_cnt) { curloc++; } break;
		}
		doScroll();
	}
	else {
		bitSet(button, but);
	}			
}


/* ******************************************************************** *
 * public: button quit was pressed
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::Button_quit()
/* ******************************************************************** */
{
	if (function != _LCDML_NO_FUNC) {
		function = _LCDML_NO_FUNC;
		bitSet(control, _LCDML_control_funcend);
	}	
	goBack();
}
 

/* ******************************************************************** *
 * public: get the name of the active function
 * @param
 * @return
 *	active function (uint8)
 * ******************************************************************** */
uint8_t	LCDMenuLib::getFunction()
/* ******************************************************************** */
{	
	return function;	
}

/* ******************************************************************** *
 * public: return the position of the current layer
 * @param
 * @return
 *	layer (uint8)
 * ******************************************************************** */
uint8_t	LCDMenuLib::getLayer()
/* ******************************************************************** */
{
	return layer;
}


/* ******************************************************************** *
 * public: the current cursor position with correcture for hidden elements
 * @param
 * @return
 *	current corsor position
 * ******************************************************************** */
uint8_t	LCDMenuLib::getCursorPos()
/* ******************************************************************** */
{
	return (curloc + curloc_correction()); //return the current cursor position
}


/* ******************************************************************** *
 * public: redefine the special chars for scrollbar on lcd
 * @param
 * @return
 * ******************************************************************** */
void LCDMenuLib::scrollbarInit()
/* ******************************************************************** */
{
	uint8_t scroll_bar[5][8] = {
	{B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001},
	{B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, 
	{B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001},
	{B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, 
	{B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}
	}; 
	lcd->_LCDML_lcd_createChar(0, scroll_bar[0]);
	lcd->_LCDML_lcd_createChar(1, scroll_bar[1]);
	lcd->_LCDML_lcd_createChar(2, scroll_bar[2]);
	lcd->_LCDML_lcd_createChar(3, scroll_bar[3]);
	lcd->_LCDML_lcd_createChar(4, scroll_bar[4]);
}