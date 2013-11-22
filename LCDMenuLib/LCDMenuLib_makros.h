/************************************************************************/
/*																		*/
/*								LCDMenuLib								*/
/*																		*/
/************************************************************************/
/* Autor:			Nils Feldkämper										*/
/* Contact:			nilsfeld@gmail.com  (kein Support)					*/
/* Create:			03.02.2008											*/
/* Edit:			25.08.2013											*/
/************************************************************************/
/* License:			all Free											*/
/************************************************************************/
/* Support:	
/* Ich beantworte Frage zu der Lib nur im Forum. Stellt eure Fragen in  */
/* diesem Thread:														*/
/* 			http://forum.arduino.cc/index.php?topic=73816.0				*/
/*																		*/
/************************************************************************/
/* Deutsche Beschreibung:												*/
/* Mit der Lib können LCD Menüs über mehrere Ebenen mit Hilfe des   	*/
/* Nested Set Models generiert werden. Jeder Menüpunkt kann mit einer   */
/* Funktion hinterlegt werden die durch die Lib aufgerufen wird, sobald */
/* der Menüpunkt aktiviert wird.										*/
/************************************************************************/
/************************************************************************/

#ifndef LCDMenuLib_macros_h
#define LCDMenuLib_macros_h


#define FuncEnd(direct,enter,up,down,left,right)\
	checkFuncEnd(B##direct##enter##up##down##left##right)


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
	PROGMEM prog_char g_LCDMenuLib_lang_ ## name ##_var[]  = content;\
	void function(void);\	
	LCDMenu item_new(name); \
	void LCDMenuLib_##name##_function() { g_LCDMenuLib_functions[name] = function; item_old.addChild(item_new); } 

/* ************************************************ */
/* LCDMenuLib_lang									*/
/* ************************************************ */
#define LCDMenuLib_lang(name)\
	g_LCDMenuLib_lang_ ## name ## _var

/* ************************************************ */
/* LCDMenuLib_init									*/
/* ************************************************ */
	#define LCDMenuLib_init(N)\
		FuncPtr g_LCDMenuLib_functions[(N+1)];\
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
	lcd.begin(_LCDMenuLib_LCD_rows,_LCDMenuLib_LCD_cols);\
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
	PROGMEM const char *g_LCDMenuLib_lang_table[] = { LCDMenuLib_lang_repeat(N) }; LCDMenuLib_initObjects()




#endif