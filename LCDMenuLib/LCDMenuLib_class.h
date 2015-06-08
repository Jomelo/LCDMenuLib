/* ******************************************************************** */
/*																		*/
/*						LCDMenuLib (LCDML)								*/
/*																		*/
/* ******************************************************************** */
/* Autor:			Nils Feldkämper										*/
/* Create:			03.02.2008											*/
/* Edit:			14.05.2015											*/
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

#ifndef LCDMenuLib_class_h
#	define LCDMenuLib_class_h

//	====================================================================================================
//	check errors
//	====================================================================================================
#	ifndef _LCDMenuLib_cfg_lcd_type
#		error "not defined: _LCDMenuLib_cfg_lcd_type (LCDMenuLib___config.h)" 
#	endif

#	ifndef _LCDMenuLib_arduino_version
#		error "not defined: _LCDMenuLib_arduino_version (LCDMenuLib___config.h)"
#	endif

#	ifdef _LCDMenuLib_cfg_lcd_type


/* ******************************************************************************** */
/* LiquidCrystal (Orginal Lib)														*/
/* ******************************************************************************** */
#		if(_LCDMenuLib_cfg_lcd_type >= 0 && _LCDMenuLib_cfg_lcd_type < 100)
			//LCD Function
#			define _LCDML_lcd_createChar(pos,char)		createChar(pos,char)
#			define _LCDML_lcd_setCursor(col,row)		setCursor(col,row)
#			define _LCDML_lcd_write(content)			write(content)
#			define _LCDML_lcd_clear()					clear()
#			define _LCDML_lcd_print(content)			print(content)
#			if(_LCDMenuLib_arduino_version == 0)
#				define _LCDML_lcd_begin()					lcd.begin(_LCDML_DISP_rows,_LCDML_DISP_cols);
#			elif(_LCDMenuLib_arduino_version == 1)
#				define _LCDML_lcd_begin()					lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);
#			else
#				error "wrong value for LCDMenuLib_arduino_version (LCDMenuLib___config.h)"
#			endif

			// ====================
			// 4Bit/8Bit Mode
			// ====================	
#			if(_LCDMenuLib_cfg_lcd_type >= 0 && _LCDMenuLib_cfg_lcd_type < 10)
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal
				//LCD include
#				include <LiquidCrystal.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 0)		//4Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3);
#				elif(_LCDMenuLib_cfg_lcd_type == 1)		//4Bit	rw				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3);
#				elif(_LCDMenuLib_cfg_lcd_type == 2)		//4Bit	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 3)		//4Bit	rw	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 4)		//8Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 5)		//8Bit	rw				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 6)		//8Bit	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 7)		//8Bit	rw	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				else									//4Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3);	
#				endif
#			endif


/* ******************************************************************************** */
/* LiquidCrystal New (extern Lib)													*/
/* ******************************************************************************** */
#		elif(_LCDMenuLib_cfg_lcd_type >= 100 && _LCDMenuLib_cfg_lcd_type < 200)
			//LCD Function
#			define _LCDML_lcd_createChar(pos,char)		createChar(pos,char)
#			define _LCDML_lcd_setCursor(col,row)		setCursor(col,row)
#			define _LCDML_lcd_write(content)			write(content)
#			define _LCDML_lcd_clear()					clear()
#			define _LCDML_lcd_print(content)			print(content)			
#			define _LCDML_lcd_begin()					lcd.begin(_LCDML_DISP_rows,_LCDML_DISP_cols);
	
			// ====================
			// 4Bit/8Bit Mode
			// ====================	
#			if(_LCDMenuLib_cfg_lcd_type >= 100 && _LCDMenuLib_cfg_lcd_type < 110)
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal
				//LCD include
#				include <Wire.h>
#				include <LiquidCrystal.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 100)		//4Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3);
#				elif(_LCDMenuLib_cfg_lcd_type == 101)		//4Bit	rw				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3);
#				elif(_LCDMenuLib_cfg_lcd_type == 102)		//4Bit	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 103)		//4Bit	rw	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 104)		//8Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 105)		//8Bit	rw				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 106)		//8Bit	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 107)		//8Bit	rw	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_rw, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);			
#				else									//4Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDML_DISP_rs, _LCDML_DISP_e, _LCDML_DISP_dat0, _LCDML_DISP_dat1, _LCDML_DISP_dat2, _LCDML_DISP_dat3);	
#				endif
#			endif

			// ====================
			// I2C
			// ====================
#			if(_LCDMenuLib_cfg_lcd_type >= 110 && _LCDMenuLib_cfg_lcd_type < 120)
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_I2C
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_I2C.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 110)		//I2C				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDML_DISP_addr);
#				elif(_LCDMenuLib_cfg_lcd_type == 111)	//I2C	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDML_DISP_addr, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);
#				elif(_LCDMenuLib_cfg_lcd_type == 112)	//I2C	e	rw	rs				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDML_DISP_addr, _LCDML_DISP_e, _LCDML_DISP_rw, _LCDML_DISP_rs);
#				elif(_LCDMenuLib_cfg_lcd_type == 113)	//I2C	e	rw	rs	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDML_DISP_addr, _LCDML_DISP_e, _LCDML_DISP_rw, _LCDML_DISP_rs, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);
#				elif(_LCDMenuLib_cfg_lcd_type == 114)	//I2C	e	rw	rs	dat0	dat1	dat2	dat3				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDML_DISP_addr, _LCDML_DISP_e, _LCDML_DISP_rw, _LCDML_DISP_rs, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 115)	//I2C	e	rw	rs	dat0	dat1	dat2	dat3	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDML_DISP_addr, _LCDML_DISP_e, _LCDML_DISP_rw, _LCDML_DISP_rs, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);
#				else									//I2C				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDML_DISP_addr);
#				endif
#			endif

			// ====================
			// shift register SR
			// ====================
#			if(_LCDMenuLib_cfg_lcd_type >= 120 && _LCDMenuLib_cfg_lcd_type < 130)	
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_SR
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_SR.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 120)		//SR
#					define _LCDML_lcd_obj	LiquidCrystal_SR lcd(_LCDML_DISP_srdata, _LCDML_DISP_srclk, _LCDML_DISP_enable);
#				endif
#			endif
			// ====================
			// shift register SR2W
			// ====================
#			if(_LCDMenuLib_cfg_lcd_type >= 130 && _LCDMenuLib_cfg_lcd_type < 140)	
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_SR2W
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_SR2W.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 130)		//SR2W
#					define _LCDML_lcd_obj	LiquidCrystal_SR2W lcd(_LCDML_DISP_srdata, _LCDML_DISP_srclk, _LCDML_DISP_backlight_pol);
#				endif
#			endif

			// ====================
			// shift register SR3W
			// ====================
#			if(_LCDMenuLib_cfg_lcd_type >= 140 && _LCDMenuLib_cfg_lcd_type < 150)	
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_SR3W
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_SR3W.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 140)		//SR3W
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDML_DISP_srdata, _LCDML_DISP_srclk, _LCDML_DISP_strobe);
#				elif(_LCDMenuLib_cfg_lcd_type == 141)	//SR3W with backlight
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDML_DISP_srdata, _LCDML_DISP_srclk, _LCDML_DISP_strobe, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);
#				elif(_LCDMenuLib_cfg_lcd_type == 142)	//SR3W with control lines
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDML_DISP_srdata, _LCDML_DISP_srclk, _LCDML_DISP_strobe, _LCDML_DISP_e, _LCDML_DISP_rw, _LCDML_DISP_rs, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 143)	//SR3W with control lines, backlight
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDML_DISP_srdata, _LCDML_DISP_srclk, _LCDML_DISP_strobe, _LCDML_DISP_e, _LCDML_DISP_rw, _LCDML_DISP_rs, _LCDML_DISP_dat4, _LCDML_DISP_dat5, _LCDML_DISP_dat6, _LCDML_DISP_dat7, _LCDML_DISP_backlight, _LCDML_DISP_backlight_pol);
#				endif
#			endif


/* ******************************************************************************** */
/* DogLcd (external Lib)															*/
/* ******************************************************************************** */
#		elif(_LCDMenuLib_cfg_lcd_type >= 200 && _LCDMenuLib_cfg_lcd_type < 300)
			// LCD Function 
#			define _LCDML_lcd_createChar(pos,char)		createChar(pos,char)
#			define _LCDML_lcd_setCursor(col,row)		setCursor(col,row)
#			define _LCDML_lcd_write(content)			write(content)
#			define _LCDML_lcd_clear()					clear()
#			define _LCDML_lcd_print(content)			print(content)
#			define _LCDML_lcd_begin()					lcd.begin(_LCDMenuLib_DogLCD_type);

			// ====================
			// 4 Bit Mode
			// ====================
#			if(_LCDMenuLib_cfg_lcd_type >= 100 && _LCDMenuLib_cfg_lcd_type < 110)
				//LCD type
#				define _LCDML_lcd_type		DogLcd
				//LCD include
#				include <DogLcd.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 100)		//4Bit	
#					define _LCDML_lcd_obj	DogLcd lcd(_LCDMenuLib_DogLCD_SI, _LCDMenuLib_DogLCD_CLK, _LCDMenuLib_DogLCD_RS, _LCDMenuLib_DogLCD_CSB, _LCDMenuLib_DogLCD_RESET, _LCDMenuLib_DogLCD_LIGHT);
#				endif
#			endif
#		endif
#	endif

#endif