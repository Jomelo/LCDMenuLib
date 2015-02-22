/************************************************************************/
/*																		*/
/*								LCDMenuLib								*/
/*																		*/
/************************************************************************/
/* Autor:			Nils Feldkämper										*/
/* Create:			03.02.2008											*/
/* Edit:			18.10.2014											*/
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

#ifndef LCDMenuLib_h
#	define LCDMenuLib_h

/* define the no function constante */
#	define _LCDMenuLib_NO_FUNC				255

//button bit pos
#	define _LCDMenuLib_button_init_screen			7
#	define _LCDMenuLib_button						6
#	define _LCDMenuLib_button_quit					5
#	define _LCDMenuLib_button_enter					4
#	define _LCDMenuLib_button_up					3
#	define _LCDMenuLib_button_down					2
#	define _LCDMenuLib_button_left					1
#	define _LCDMenuLib_button_right					0

//control bit pos
#	define _LCDMenuLib_control_menu_back			7
#	define _LCDMenuLib_control_menu_look			6
#	define _LCDMenuLib_control_scrollbar_h			5
#	define _LCDMenuLib_control_scrollbar_l			4
#	define _LCDMenuLib_control_lcd_standard			3
#	define _LCDMenuLib_control_initscreen_enable	2
#	define _LCDMenuLib_control_initscreen_active	1
#	define _LCDMenuLib_control_funcsetup			0

//control2 bits pos
#	define _LCDMenuLib_control2_free7				7
#	define _LCDMenuLib_control2_free6				6
#	define _LCDMenuLib_control2_free5				5
#	define _LCDMenuLib_control2_free4				4
#	define _LCDMenuLib_control2_free3				3
#	define _LCDMenuLib_control2_free2				2
#	define _LCDMenuLib_control2_endFunc				1
#	define _LCDMenuLib_control2_endFuncOverExit		0


/* config */
#	define _LCDMenuLib_cfg_cursor_deep				6		// save the last position of the cursor until layer xx
#	define _LCDMenuLib_cfg_cursor					0x7E	// cursor char
#	define _LCDMenuLib_cfg_max_string_length		20		// max string length witch can be display

/* include config */
#	include <LCDMenuLib___config.h>
#	include <LCDMenuLib_class.h>

/* set pointer to function if not defined */
#	ifndef TYPEDEF_FUNCPTR
#		define TYPEDEF_FUNCPTR
		typedef void (* LCDML_FuncPtr) ();
#	endif

/* include arduino ios */
#	include "Arduino.h"

/* configure arduino flash lib */
#	ifndef __PROG_TYPES_COMPAT__
#		define __PROG_TYPES_COMPAT__
#	endif
/* include arduino flash lib */
#	include <avr/pgmspace.h>

/* include lcd menu lib, this generates the menu items */
#	include "LCDMenuLib_menu.h"

/* help macros to generate and save the menu item content */
#	include "LCDMenuLib_lang_repeat.h"

/* help macros to generate the menu item functions */ 
#	include "LCDMenuLib_func_repeat.h"

/* include macros for this lib */
#	include "LCDMenuLib_makros.h"

//# Lcd Menu Lib
//# =======================
	class LCDMenuLib
	{
		private:
			/* LCD Object */
			_LCDML_lcd_type *lcd;
			/* Menu Objects */
			LCDMenu *rootMenu;
			LCDMenu *curMenu;

			/* Saves the string position from menu elments in flash memory */
			const char * const *flash_table;
			
			/* display cols */
			uint8_t cols;
			/* display rows */
			uint8_t rows;
			/* save the last layer */
			uint8_t layer_save[_LCDMenuLib_cfg_cursor_deep];      // Speichert Cursor Position bis zur 8 Ebene

			/* current corsor position */
			uint8_t curloc;  
			/* current scroll position */
			uint8_t scroll; 
			/* save the last cursor position when a menue element is called */
			uint8_t cursor_pos;        

			/* save the last id from a menu element, when a menu elmend is called */
			uint8_t g_function;
			/* save the last id from a menu element */
			uint8_t curfuncname;     
		
			/* containes the current layer */
			uint8_t layer; 
			
			/* move to the parent menu */
			void goBack();
			/* activate the menu under the cursor */
			void goEnter();        
			/* set the cursor to the current position in the menu */
			void setCursor(); 
			/* scroll the menu */
			void doScroll(); 
			/* go to a menu element */
			void goMenu(LCDMenu &m);   
			/* works with jump to element on globale function */
			uint8_t selectElementDirect(LCDMenu &p_m, uint8_t p_search);

			uint8_t anzahl();
					
		public:			
			/* Constructor */
			LCDMenuLib(LCDMenu &p_r,_LCDML_lcd_type &p_d, const char * const *p_flash_table, const uint8_t p_rows, const uint8_t p_cols);   
			
			/* Display the current menu on the lcd */
			void		display();        			
			
			/* jump to root menu */
			void		goRoot();	
			/* jump to menu element */
			void		jumpToElement(uint8_t element);
			/* replace the delay function */
			uint8_t		Timer(unsigned long &p_var, unsigned long p_time);
			
			/* menu element function init */
			uint8_t		FuncInit();
			/* menu element function check end */
			uint8_t checkFuncEnd(uint8_t check);
			
			/* button variable */
			uint8_t button; 
			/* control bits */
			uint8_t control;
			uint8_t control2;
			
			/* check if a button was pressed and reset the globale buttonCheck bit */
			uint8_t checkButtons();
			/* go in a menu element */
			void Button_enter();
			/* go out of a menu element */
			void Button_quit(uint8_t opt=false);
			/* navigate through the menu */
			void Button_up_down_left_right(uint8_t but);
			
			/* get active function id */
			uint8_t		getFunction();
			/* get last function id */
			uint8_t		getCurFunction();
			/* get the layer where the cursor stands in the menu */
			uint8_t		getLayer();
			/* get the init screen enable bit */
			uint8_t		getInitScreenActive();	
			/* get the corrent cursor position */
			uint8_t		getCursorPos();	
			/* get the current name of an element */
			uint8_t		getElementName(char *, uint8_t element_id);
	};
#endif


