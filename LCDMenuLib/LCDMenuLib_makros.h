/************************************************************************/
/*																		*/
/*								LCDMenuLib								*/
/*																		*/
/************************************************************************/
/* Autor:			Nils Feldkämper										*/
/* Create:			03.02.2008											*/
/* Edit:			26.02.2014											*/
/************************************************************************/
/* License:			all Free											*/
/************************************************************************/

/************************************************************************/
/* Description:															*/
/* With this library, you can create menus with layers on base on the   */
/* Nested-Set-Model. For every menu element can be create a function    */
/* to control the content. This function is called automatical from the */
/* library and runs in a loop, without blocking other programm parts.   */
/*																		*/
/* Support:  -- englischen Link einfügen --                             */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/* Description (german):												*/
/* Mit der Lib können LCD Menüs über mehrere Ebenen mit Hilfe des   	*/
/* Nested Set Models generiert werden. Jeder Menüpunkt kann mit einer   */
/* Funktion hinterlegt werden die durch die Lib aufgerufen wird, sobald */
/* der Menüpunkt aktiviert wird.										*/
/*																		*/
/* Support (german):	http://forum.arduino.cc/index.php?topic=73816.0	*/
/************************************************************************/

/************************************************************************/
/* Features:															*/
/* - max 254 menu elements												*/
/* - max 254 menu elements per layer								    */
/* - max 6 layers from root, configurable in LCDMenuLib.h				*/
/* - max support for 6 buttons up, down, left, right, back/quit, enter  */
/* - min 3 buttons needed up, down, enter                               */
/* - separation of structural and functional level                      */
/* - support for initscreen which is shown after x secounds or at begin */
/* - scrollbar when more menu elments in a layer then rows              */
/* - last cursor pos is saved											*/
/* - possibility to jump from one menu elment directly to another       */
/* - support for many different lcd librarys in LCDMenuLib___config.h   */
/* - 4bit lcd support													*/
/* - 8bit lcd support													*/
/* - i2c lcd support													*/
/* - shift register lcd support											*/
/* - DogLcd support														*/
/*																		*/
/* - many small function for other things								*/
/*																		*/
/* - no support for gaphic displays yet									*/
/************************************************************************/

#ifndef LCDMenuLib_macros_h
#define LCDMenuLib_macros_h

#define root Item


#define FuncEnd(direct,enter,up,down,left,right)\
	checkFuncEnd(B##direct##enter##up##down##left##right)

#define FuncEndQuitButton()\
	checkFuncEnd(0)


#define LCDMenuLib_checkButtonEnter()\
	((LCDML.button & (1<<_LCDMenuLib_button_enter)) > 0)
#define LCDMenuLib_checkButtonUp()\
	((LCDML.button & (1<<_LCDMenuLib_button_up)) > 0)
#define LCDMenuLib_checkButtonDown()\
	((LCDML.button & (1<<_LCDMenuLib_button_down)) > 0)
#define LCDMenuLib_checkButtonLeft()\
	((LCDML.button & (1<<_LCDMenuLib_button_left)) > 0)
#define LCDMenuLib_checkButtonRight()\
	((LCDML.button & (1<<_LCDMenuLib_button_right)) > 0)

#define LCDMenuLib_resetButtonEnter()\
	bitWrite(LCDML.button, _LCDMenuLib_button_enter, 0)
#define LCDMenuLib_resetButtonUp()\
	bitWrite(LCDML.button, _LCDMenuLib_button_up, 0)
#define LCDMenuLib_resetButtonDown()\
	bitWrite(LCDML.button, _LCDMenuLib_button_down, 0)
#define LCDMenuLib_resetButtonLeft()\
	bitWrite(LCDML.button, _LCDMenuLib_button_left, 0)
#define LCDMenuLib_resetButtonRight()\
	bitWrite(LCDML.button, _LCDMenuLib_button_right, 0)
	
#define LCDMenuLib_callbackSetup				if(!LCDML.FuncInit())
#define LCDMenuLib_callbackLoop
#define LCDMenuLib_callbackEnd(a,b,c,d,e,f)		if(LCDML.FuncEnd(a,b,c,d,e,f))

#define LCDMenuLib_IS_reStartTime()		g_LCDMenuLib_cfg_initscreen_time = millis()+(_LCDMenuLib_cfg_initscreen_time);
#define LCDMenuLib_IS_startDirect()		g_LCDMenuLib_cfg_initscreen_time = 0;


#define LCDMenuLib_getActiveFuncId()	((bitRead(LCDML.control,_LCDMenuLib_control_funcsetup) == 1)?LCDML.getFunction():_LCDMenuLib_NO_FUNC)



/* ************************************************ */
/* LCDMenuLib_element								*/
/* ************************************************ */
#define LCDMenuLib_element(name, item_old, item_new, content, function)\
	const char g_LCDMenuLib_lang_ ## name ##_var[] PROGMEM = {content};\
	void function(void);\
	LCDMenu item_new(name); \
	void LCDMenuLib_##name##_function() { g_LCDMenuLib_functions[name] = function; item_old.addChild(item_new); } 

#define LCDMenuLib_add(name, item_old, item_new, content, function)\
	const char g_LCDMenuLib_lang_ ## name ##_var[] PROGMEM = {content};\
	void function(void);\
	LCDMenu item_old ## _ ## item_new(name); \
	void LCDMenuLib_##name##_function() { g_LCDMenuLib_functions[name] = function; item_old.addChild(item_old ## _ ## item_new); } 
	

/* ************************************************ */
/* LCDMenuLib_lang									*/
/* ************************************************ */
#define LCDMenuLib_lang(name)\
	g_LCDMenuLib_lang_ ## name ## _var

/* ************************************************ */
/* LCDMenuLib_init									*/
/* ************************************************ */
	#define LCDMenuLib_init(N)\
		LCDML_FuncPtr g_LCDMenuLib_functions[(N+1)];\
		void FUNC(void){}\
		void FUNC_init_screen(void) __attribute__((weak));\
		void LCDMenuLib_control_serial(void) __attribute__((weak));\
		void LCDMenuLib_control_analog(void) __attribute__((weak));\
		unsigned long g_LCDMenuLib_cfg_initscreen_time = millis()+_LCDMenuLib_cfg_initscreen_time;\
		unsigned long g_LCDMenuLib_press_time = 0;\
		LCDMenu Item (0)


/* ************************************************ */
/* LCDMenuLib_setup									*/
/* ************************************************ */
#define LCDMenuLib_setup(N)\
	_LCDML_lcd_begin();\
	\
	if(_LCDMenuLib_cfg_initscreen == 1) {\
		bitWrite(LCDML.control, _LCDMenuLib_control_initscreen_enable, 1);\
	} \
	\
	if(_LCDMenuLib_cfg_lcd_standard == 1) {\
		bitWrite(LCDML.control, _LCDMenuLib_control_lcd_standard, 1);\
	} \
	\
	if(_LCDMenuLib_cfg_scrollbar == 1) {\
		bitWrite(LCDML.control, _LCDMenuLib_control_scrollbar_l, 1);\
		\
		uint8_t scroll_bar[5][8] = {\
			{B10001,B10001,B10001,B10001,B10001,B10001,B10001,B10001},\
			{B11111,B11111,B10001,B10001,B10001,B10001,B10001,B10001},\
			{B10001,B10001,B11111,B11111,B10001,B10001,B10001,B10001},\
			{B10001,B10001,B10001,B10001,B11111,B11111,B10001,B10001},\
			{B10001,B10001,B10001,B10001,B10001,B10001,B11111,B11111}\
		};\
		lcd._LCDML_lcd_createChar(0, scroll_bar[0]);\
		lcd._LCDML_lcd_createChar(1, scroll_bar[1]);\
		lcd._LCDML_lcd_createChar(2, scroll_bar[2]);\
		lcd._LCDML_lcd_createChar(3, scroll_bar[3]);\
		lcd._LCDML_lcd_createChar(4, scroll_bar[4]);\
	} else if(_LCDMenuLib_cfg_scrollbar == 2) {\
		bitWrite(LCDML.control, _LCDMenuLib_control_scrollbar_h, 1);\
		\
		if(_LCDMenuLib_cfg_lcd_standard == 0) {\
			uint8_t scroll_bar[2][8] = {\
				{B00000,B00100,B01110,B10101,B00100,B00100,B00100,B00000},\
				{B00000,B00100,B00100,B00100,B10101,B01110,B00100,B00000}\
			};\
			lcd._LCDML_lcd_createChar(0, scroll_bar[0]);\
			lcd._LCDML_lcd_createChar(1, scroll_bar[1]);\
		}\
	}\
	LCDMenuLib_initFunction(N); \
	g_LCDMenuLib_cfg_initscreen_time = millis()+(_LCDMenuLib_cfg_initscreen_time);\
	LCDML.display();
	
   
     


/* ************************************************ */
/* LCDMenuLib_loop									*/
/* ************************************************ */
	#define LCDMenuLib_loop() \
		if(_LCDMenuLib_cfg_initscreen == 1) {\
			if(LCDML.getInitScreenActive() == false) {\
				if(bitRead(LCDML.button, _LCDMenuLib_button_init_screen)) {\
					bitWrite(LCDML.button, _LCDMenuLib_button_init_screen, 0);\
					g_LCDMenuLib_cfg_initscreen_time = millis()+(_LCDMenuLib_cfg_initscreen_time);\
				}\
				if(_LCDMenuLib_cfg_initscreen_time > 0) {\
					if(g_LCDMenuLib_cfg_initscreen_time < millis() && LCDML.getInitScreenActive() == false) {\
						LCDML.Button_quit(1);\
					}\
				}\
				if(LCDML.getFunction() != _LCDMenuLib_NO_FUNC && LCDML.getInitScreenActive() == false) {\
					g_LCDMenuLib_functions[LCDML.getCurFunction()]();\
				}\
			}\
			else\
			{\
				g_LCDMenuLib_cfg_initscreen_time = millis()+(_LCDMenuLib_cfg_initscreen_time);\
				FUNC_init_screen();\
			}\
		}\
		else\
		{\
			if(LCDML.getFunction() != _LCDMenuLib_NO_FUNC) {\
				g_LCDMenuLib_functions[LCDML.getCurFunction()]();\
			}\
		}

		




	
/* ************************************************ */
/* LCDMenuLib_initObjects							*/
/* ************************************************ */
#define LCDMenuLib_initObjects()\
	_LCDML_lcd_obj;\
	LCDMenuLib LCDML (Item, lcd, g_LCDMenuLib_lang_table, _LCDMenuLib_LCD_rows, _LCDMenuLib_LCD_cols);

/* ************************************************ */
/* LCDMenuLib_jumpToFunc							*/
/* ************************************************ */
#define LCDMenuLib_jumpToFunc(name)\
	for(uint8_t i=0; i<=255;i++) {\
		if(name == g_LCDMenuLib_functions[i]) {\
			LCDML.jumpToElement(i);\
			break;\
		}\
	}\
	return;

/* ************************************************ */
/* LCDMenuLib_initFunction							*/
/* ************************************************ */
#define LCDMenuLib_initFunction(N) \
	LCDMenuLib_func_repeat(N);

/* ************************************************ */
/* LCDMenuLib_createMenu							*/
/* ************************************************ */
#define LCDMenuLib_createMenu(N)\
	const char * const g_LCDMenuLib_lang_table[] PROGMEM = { LCDMenuLib_lang_repeat(N) }; LCDMenuLib_initObjects()






#define LCDMenuLib_getElementName(var, element_id) \
	if(element_id != _LCDMenuLib_NO_FUNC && (sizeof(g_LCDMenuLib_lang_table)-1) >= element_id) {\
		strcpy_P(var, (char*)pgm_read_word(&(g_LCDMenuLib_lang_table[element_id])));\
	}\

#define LCDMenuLib_getElementNameChecked(var, element_id, check) \
	if(element_id != _LCDMenuLib_NO_FUNC && (sizeof(g_LCDMenuLib_lang_table)-1) >= element_id) {\
		strcpy_P(var, (char*)pgm_read_word(&(g_LCDMenuLib_lang_table[element_id])));\
		check = true;\
	} else {\
	    check = false;\
	}
	




/* noch in arbeit */
#define LCDMenuLib_element_scrolltext
#define LCDMenuLib_element_settings_vertical
#define LCDMenuLib_element_settings_horizontal
#define LCDMenuLib_element_time
#define LCDMenuLib_element_time_setting



#endif