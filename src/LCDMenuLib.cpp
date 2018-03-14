/*
 * MIT License
 * 
 * Copyright (c) [2017] [Nils Feldkämper]
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
// ********************************************************************
//																		
//						LCDMenuLib (LCDML)								
//																		
// ********************************************************************
//
// Autor:			Nils Feldkaemper				
// Create:			03.02.2008											
// Edit:			27.02.2017											
// License:			MIT License											
//
// ********************************************************************
//
// error reporting: 									
//	https://github.com/Jomelo/LCDMenuLib/issues							
//
// forum thread:													
// 	http://forum.arduino.cc/index.php?topic=73816.0						
//
// ********************************************************************

#	include <LCDMenuLib.h>

// ********************************************************************
// constructor
// @param
// 		menu instance
//		LCD instance
//		flash table for menu elements
//		lcd rows
//		lcd colls
// @return
//		---
// ********************************************************************
LCDMenuLib::LCDMenuLib(LCDMenu &p_r, const char * const *p_flash_table, const uint8_t p_rows, const uint8_t p_cols)
// ********************************************************************
{
	// initialisation
    rootMenu        = &p_r;
    curMenu         = rootMenu;
	flash_table     = p_flash_table;
	control			= 0; 
    control2        = 0;
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
	if(function != _LCDML_NO_FUNC) {
		bitSet(control, _LCDML_control_go_root);
		Button_quit();
	} else {
		bitClear(control, _LCDML_control_go_root);
		//go back to root layer
		while(layer > 0) 
		{ 
			goBack(); 
		}			
		cursor_pos = 0;
		curloc = 0;
		scroll = 0;
			
		//reset buttons and cursor position
		button = 0;
	}		
	//display menu
	display();
	bitSet(control, _LCDML_control_disp_update);
	
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
	// check if function is active
	if(function == p_element) {
		return;
	}
	Button_quit();
	function = _LCDML_NO_FUNC;	
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
		do
		{				
			if (bitRead(group_en, tmp->disp) || bitRead(control, _LCDML_control_disable_hidden)) {				
				j++;
			} 
		} while ((tmp = tmp->getSibling(1)) != NULL);		
	}	

	if(j == 0) {
		return 0;
	} else {	
		return --j;
	}
}

/* ******************************************************************** *
 * private: clear content
 * @param
 * @return
 * ******************************************************************** */
void LCDMenuLib::display_clear()
{		
	for(uint8_t n=0; n<_LCDML_DISP_cfg_max_rows;n++) {
		for(uint8_t nc=0; nc<_LCDML_DISP_cfg_max_string_length;nc++) {
			content[n][nc] = ' ';			
		}
		content_id[n] = _LCDML_NO_FUNC;
	}	
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
			display_clear();			
			//show menu structure
			do
			{				
				if (bitRead(group_en, tmp->disp)) {	
					#if defined ( ESP8266 ) || defined ( ESP32 )
						strcpy_P(content[i-scroll], (char*)(flash_table[tmp->name]));
					#else
						strcpy_P(content[i-scroll], (char*)pgm_read_word(&(flash_table[tmp->name])));
					#endif
					content_id[i-scroll] = tmp->name;
					i++;					
				}

			} while ((tmp = tmp->getSibling(1)) != NULL && i<maxi);
			bitSet(control, _LCDML_control_disp_update);			
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

	//save current cursor position
	cursor_pos = curloc - scroll;

	
	
	if (cursor_pos > child_cnt) {
		cursor_pos = child_cnt;
	}	
	
	bitSet(control, _LCDML_control_cursor_update);
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
 * public: button quit was pressed
 * @param
 * @return
 * ******************************************************************** */
void	LCDMenuLib::Button_quit()
/* ******************************************************************** */
{
	if (function != _LCDML_NO_FUNC) {
		bitSet(control, _LCDML_control_funcend);
		bitSet(button,  _LCDML_button_quit);
	} else {
		goBack();
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
			case _LCDML_button_up:   
                if (curloc > 0) 		 
                { 
                    curloc--; 
                    doScroll();
                } 
                else 
                {
                    if(bitRead(control2, _LCDML_control2_rollover))
                    {
                        // jump to the end of the menu
                        curloc = child_cnt;
                        if(child_cnt-rows < 0) {
                            scroll = 0;
                        } else {
                            scroll = child_cnt-rows;
                        }                    
                        doScroll();
                        display();
                    }
                }
                break;
			case _LCDML_button_down: 
                if (curloc < child_cnt) 
                { 
                    curloc++; 
                    doScroll();
                } else {
                    if(bitRead(control2, _LCDML_control2_rollover))
                    {
                        // jump to the first line
                        curloc = 0;
                        scroll = 0;                
                        doScroll();
                        display();                
                    }
                }
                break;
		}		
	}
	else {
		bitSet(button, but);
	}			
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
	return (cursor_pos); //return the current cursor position
}

/* ******************************************************************** *
 * public: the current cursor position with correcture for hidden elements
 * @param
 * @return
 *	current corsor position
 * ******************************************************************** */
uint8_t	LCDMenuLib::getCursorPosAbs()
/* ******************************************************************** */
{	
	return (curloc + curloc_correction()); //return the current cursor position
}

/* ******************************************************************** */
uint8_t LCDMenuLib::getChilds()
/* ******************************************************************** */
{
	return child_cnt+1;
}

/* ******************************************************************** */
uint8_t LCDMenuLib::getParent()
/* ******************************************************************** */
{ 
    //if(curMenu->getParent() != NULL)
    //{
        return curMenu->name;
    //}   
   
    //return 0;
}

/* ******************************************************************** */
void    LCDMenuLib::enRollover()
/* ******************************************************************** */
{
    bitSet(control2, _LCDML_control2_rollover);
}

/* ******************************************************************** */
void    LCDMenuLib::disRollover()
/* ******************************************************************** */
{
    bitClear(control2, _LCDML_control2_rollover);
}

/* ******************************************************************** */
LCDMenu *   LCDMenuLib::getMenuObject()
/* ******************************************************************** */
{
    return curMenu;
}




