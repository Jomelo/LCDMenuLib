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

/* ******************************************************************** */
/*																		*/
/*						LCDMenuLib (LCDML)								*/
/*																		*/
/* ******************************************************************** */
/* Autor:			Nils Feldkämper										*/
/* Create:			03.02.2008											*/
/* Edit:			27.02.2017											*/
/* ******************************************************************** */
/* error reporting (english / german)									*/
/*	https://github.com/Jomelo/LCDMenuLib/issues							*/
/* support (german):													*/
/* 	http://forum.arduino.cc/index.php?topic=73816.0						*/
/* ******************************************************************** */

#ifndef LCDMenuLib_h
#	define LCDMenuLib_h

#	define _LCDML_VERSION							"LCDML v2.3.5"

/* config */
#	define _LCDML_DISP_cfg_cursor_deep				6		// save the last position of the cursor until layer xx
#	define _LCDML_DISP_cfg_max_string_length		20		// max string length witch can be display
#	define _LCDML_DISP_cfg_max_rows					10


/* include arduino ios */
#	include "Arduino.h"


#if ARDUINO >= 160
#	define _LCDMenuLib_arduino_version	1	// for new arduino version like 1.6.0 or higher
#else
#	define _LCDMenuLib_arduino_version	0	// for old arduino version like 1.0.6 or 1.0.5
#endif


/* define the no function constante */
#	define _LCDML_NO_FUNC					255

//button bit pos
#	define _LCDML_button_free					7
#	define _LCDML_button						6
#	define _LCDML_button_quit					5
#	define _LCDML_button_enter					4
#	define _LCDML_button_up						3
#	define _LCDML_button_down					2
#	define _LCDML_button_left					1
#	define _LCDML_button_right					0

//control bit pos
#	define _LCDML_control_menu_back				7
#	define _LCDML_control_disp_update			6
#	define _LCDML_control_cursor_update			5
#	define _LCDML_control_go_root				4
#	define _LCDML_control_update_direct			3
#	define _LCDML_control_search_display		2
#	define _LCDML_control_funcend				1
#	define _LCDML_control_disable_hidden		0

//control 2
#	define _LCDML_control2_free7                7
#	define _LCDML_control2_free6                6
#	define _LCDML_control2_free5                5
#	define _LCDML_control2_free4                4
#	define _LCDML_control2_free3                3
#	define _LCDML_control2_free2                2
#	define _LCDML_control2_free1                1
#	define _LCDML_control2_rollover  		    0


// groups
#	define _LCDML_G8							7
#	define _LCDML_G7							6
#	define _LCDML_G6							5
#	define _LCDML_G5							4
#	define _LCDML_G4							3
#	define _LCDML_G3							2
#	define _LCDML_G2							1
#	define _LCDML_G1							0

/* configure arduino flash lib and load it*/
#	ifndef __PROG_TYPES_COMPAT__
#		define __PROG_TYPES_COMPAT__
#	endif

#	if defined ( ESP8266 ) || defined ( ESP32 )
#	else
#		include <avr/pgmspace.h>
#	endif

/* include lcd menu lib, this generates the menu items */
#	include "LCDMenuLib_menu.h"

/* include macros for this lib */
#	include "LCDMenuLib_makros.h"

//# Lcd Menu Lib
//# =======================
	class LCDMenuLib
	{
	private:
		/* Menu Objects */
		LCDMenu		*rootMenu;
		LCDMenu		*curMenu;	
		/* Saves the string position from menu elments in flash memory */
		const char * const *flash_table;
		/* display cols */
		uint8_t		cols;
		/* display rows */
		uint8_t		rows;
		/* save the last layer */
		uint8_t		layer_save[_LCDML_DISP_cfg_cursor_deep];      // Speichert Cursor Position bis zur 8 Ebene
		/* current corsor position */
		uint8_t		curloc;			
		/* current scroll position */
		uint8_t		scroll;
		/* save the last cursor position when a menue element is called */
		uint8_t		cursor_pos;
		/* how many childs exists on next layer */
		uint8_t		child_cnt;
		/* containes the current layer */
		uint8_t		layer;
		/* correction of the cursor position with hidden button */
		uint8_t		curloc_correction();
		/* activate the menu under the cursor */
		void		goEnter();
		/* set the cursor to the current position in the menu */
		void		setCursor();
		/* scroll the menu */
		void		doScroll();
		/* go to a menu element */
		void		goMenu(LCDMenu &m);	
		/* works with jump to element on globale function */
		uint8_t		selectElementDirect(LCDMenu &p_m, uint8_t p_search);
		/* how many childs exists on next layer */
		uint8_t		countChilds();

	public:
		/* button variable */
		uint8_t		button;
		/* control bits */
		uint8_t		control;
        /* control2 bits */
        uint8_t     control2;
		/* save group_hidden_status */
		uint8_t		group_en;
		/* save the last id from a menu element, when a menu elmend is called */
		uint8_t		function;
		
		char content[_LCDML_DISP_cfg_max_rows][_LCDML_DISP_cfg_max_string_length];	
		uint8_t content_id[_LCDML_DISP_cfg_max_rows];
		
		/* Constructor */
		LCDMenuLib(LCDMenu &p_r, const char * const *p_flash_table, const uint8_t p_rows, const uint8_t p_cols);

		/* Display the current menu on the lcd */
		void		display();
		/* jump to root menu */
		void		goRoot();
		/* move to the parent menu */
		void		goBack();
		/* update display content */
		void 		display_update();
		/* clear display content */
		void		display_clear();
		/* jump to menu element */
		void		jumpToElement(uint8_t element);		
		/* go in a menu element */
		void		Button_enter();
		/* go out of a menu element */
		void		Button_quit();
		/* navigate through the menu */
		void		Button_udlr(uint8_t but);
		/* get active function id */
		uint8_t		getFunction();
		/* get the layer where the cursor stands in the menu */
		uint8_t		getLayer();
		/* get the corrent cursor position */
		uint8_t		getCursorPos();	
		/* get the corrent cursor position */
		uint8_t		getCursorPosAbs();	
		/* get childs of an element */
		uint8_t 	getChilds();
        /* get parent */
        uint8_t     getParent();
        /* enable rollover */
        void        enRollover();
        /* disable rollover */
        void        disRollover();
        /* return the object of the current menu position */
        LCDMenu *   getMenuObject();
	};
#endif


