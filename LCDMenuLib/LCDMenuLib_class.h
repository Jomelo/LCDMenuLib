/************************************************************************/
/*																		*/
/*								LCDMenuLib								*/
/*																		*/
/************************************************************************/
/* Autor:			Nils Feldkämper										*/
/* Create:			03.02.2008											*/
/* Edit:			23.02.2014											*/
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
#		if(_LCDMenuLib_cfg_lcd_type >= 0 && _LCDMenuLib_cfg_lcd_type < 100)
		//LCD Function
#			define _LCDML_lcd_createChar(pos,char)		createChar(pos,char)
#			define _LCDML_lcd_setCursor(col,row)		setCursor(col,row)
#			define _LCDML_lcd_write(content)			write(content)
#			define _LCDML_lcd_clear()					clear()
#			define _LCDML_lcd_print(content)			print(content)
#			if(_LCDMenuLib_arduino_version == 0)
#				define _LCDML_lcd_begin()					lcd.begin(_LCDMenuLib_LCD_rows,_LCDMenuLib_LCD_cols);
#			elif(_LCDMenuLib_arduino_version == 1)
#				define _LCDML_lcd_begin()					lcd.begin(_LCDMenuLib_LCD_cols,_LCDMenuLib_LCD_rows);
#			else
#				error "wrong value for LCDMenuLib_arduino_version (LCDMenuLib___config.h)"
#			endif
				

	// ================================================================================
	// LiquidCrystal
	// ================================================================================
#			if(_LCDMenuLib_cfg_lcd_type >= 0 && _LCDMenuLib_cfg_lcd_type < 10)
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal
				//LCD include
#				include <LiquidCrystal.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 0)		//4Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3);
#				elif(_LCDMenuLib_cfg_lcd_type == 1)		//4Bit	rw				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3);
#				elif(_LCDMenuLib_cfg_lcd_type == 2)		//4Bit	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 3)		//4Bit	rw	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 4)		//8Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 5)		//8Bit	rw				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 6)		//8Bit	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#				elif(_LCDMenuLib_cfg_lcd_type == 7)		//8Bit	rw	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);			
#				else									//4Bit				
#					define _LCDML_lcd_obj	LiquidCrystal lcd(_LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_dat0, _LCDMenuLib_LCD_dat1, _LCDMenuLib_LCD_dat2, _LCDMenuLib_LCD_dat3);	
#				endif
#			endif
	// ================================================================================
	// LiquidCrystal I2C
	// ================================================================================
#			if(_LCDMenuLib_cfg_lcd_type >= 10 && _LCDMenuLib_cfg_lcd_type < 20)
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_I2C
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_I2C.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 10)		//I2C				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr);
#				elif(_LCDMenuLib_cfg_lcd_type == 11)	//I2C	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#				elif(_LCDMenuLib_cfg_lcd_type == 12)	//I2C	e	rw	rs				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs);
#				elif(_LCDMenuLib_cfg_lcd_type == 13)	//I2C	e	rw	rs	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#				elif(_LCDMenuLib_cfg_lcd_type == 14)	//I2C	e	rw	rs	dat0	dat1	dat2	dat3				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 15)	//I2C	e	rw	rs	dat0	dat1	dat2	dat3	backlight				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#				else									//I2C				
#					define _LCDML_lcd_obj	LiquidCrystal_I2C lcd(_LCDMenuLib_LCD_addr);
#				endif
#			endif
		// ================================================================================
		// LiquidCrystal SR
		// ================================================================================
#			if(_LCDMenuLib_cfg_lcd_type >= 20 && _LCDMenuLib_cfg_lcd_type < 30)	
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_SR
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_SR.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 20)		//SR
#					define _LCDML_lcd_obj	LiquidCrystal_SR lcd(_LCDMenuLib_LCD_srdata, _LCDMenuLib_LCD_srclk, _LCDMenuLib_LCD_enable);
#				endif
#			endif
		// ================================================================================
		// LiquidCrystal SR2W
		// ================================================================================
#			if(_LCDMenuLib_cfg_lcd_type >= 30 && _LCDMenuLib_cfg_lcd_type < 40)	
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_SR2W
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_SR2W.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 30)		//SR2W
#					define _LCDML_lcd_obj	LiquidCrystal_SR2W lcd(_LCDMenuLib_LCD_srdata, _LCDMenuLib_LCD_srclk, _LCDMenuLib_LCD_backlight_pol);
#				endif
#			endif
		// ================================================================================
		// LiquidCrystal SR3W
		// ================================================================================
#			if(_LCDMenuLib_cfg_lcd_type >= 40 && _LCDMenuLib_cfg_lcd_type < 50)	
				//LCD type
#				define _LCDML_lcd_type		LiquidCrystal_SR3W
				//LCD includes
#				include <Wire.h>
#				include <LiquidCrystal_SR3W.h>
				//LCD objects
#				if(_LCDMenuLib_cfg_lcd_type == 40)		//SR3W
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDMenuLib_LCD_srdata, _LCDMenuLib_LCD_srclk, _LCDMenuLib_LCD_strobe);
#				elif(_LCDMenuLib_cfg_lcd_type == 41)	//SR3W with backlight
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDMenuLib_LCD_srdata, _LCDMenuLib_LCD_srclk, _LCDMenuLib_LCD_strobe, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#				elif(_LCDMenuLib_cfg_lcd_type == 42)	//SR3W with control lines
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDMenuLib_LCD_srdata, _LCDMenuLib_LCD_srclk, _LCDMenuLib_LCD_strobe, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7);
#				elif(_LCDMenuLib_cfg_lcd_type == 43)	//SR3W with control lines, backlight
#					define _LCDML_lcd_obj	LiquidCrystal_SR3W lcd(_LCDMenuLib_LCD_srdata, _LCDMenuLib_LCD_srclk, _LCDMenuLib_LCD_strobe, _LCDMenuLib_LCD_e, _LCDMenuLib_LCD_rw, _LCDMenuLib_LCD_rs, _LCDMenuLib_LCD_dat4, _LCDMenuLib_LCD_dat5, _LCDMenuLib_LCD_dat6, _LCDMenuLib_LCD_dat7, _LCDMenuLib_LCD_backlight, _LCDMenuLib_LCD_backlight_pol);
#				endif
#			endif
#		elif(_LCDMenuLib_cfg_lcd_type >= 100 && _LCDMenuLib_cfg_lcd_type < 200)
		//LCD Function
#			define _LCDML_lcd_createChar(pos,char)		createChar(pos,char)
#			define _LCDML_lcd_setCursor(col,row)		setCursor(col,row)
#			define _LCDML_lcd_write(content)			write(content)
#			define _LCDML_lcd_clear()					clear()
#			define _LCDML_lcd_print(content)			print(content)
#			define _LCDML_lcd_begin()					lcd.begin(_LCDMenuLib_DogLCD_type);

	// ================================================================================
	// DogLcd
	// ================================================================================
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