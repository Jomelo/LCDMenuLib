/************************************************************************/
/*																		*/
/*							LCDMenuLib									*/
/*																		*/
/************************************************************************/
/* Autor:			Nils Feldk�mper										*/
/* Create:			03.02.2008											*/
/* Edit:			05.09.2013											*/
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
/* Mit der Lib k�nnen LCD Men�s �ber mehrere Ebenen mit Hilfe des   	*/
/* Nested Set Models generiert werden. Jeder Men�punkt kann mit einer   */
/* Funktion hinterlegt werden die durch die Lib aufgerufen wird, sobald */
/* der Men�punkt aktiviert wird.										*/
/************************************************************************/
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

/* config */
#	define _LCDMenuLib_cfg_cursor_deep				6		// Speichert die Position des Kursors bis zur x-ten Ebene
#	define _LCDMenuLib_cfg_max_string_length		20		// Maximale L�nge eines Strings der auf dem Display ausgegeben werden kann


/* include config */
#	include <LCDMenuLib___config.h>
#	include <LCDMenuLib_class.h>

/* set pointer to function if not defined */
#	ifndef TYPEDEF_FUNCPTR
#		define TYPEDEF_FUNCPTR
		typedef void (* FuncPtr) ();
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
			const char **flash_table;
			
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
			boolean selectElementDirect(LCDMenu &p_m, uint8_t p_search);
					
		public:			
			/* Constructor */
			LCDMenuLib(LCDMenu &p_r,_LCDML_lcd_type &p_d, const char **p_flash_table, const uint8_t p_rows, const uint8_t p_cols);   
			
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
	};
#endif


