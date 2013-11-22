
#ifndef LCDMenuLib_class_h
#	define LCDMenuLib_class_h


#	ifdef _LCDMenuLib_cfg_lcd_type
#		if(_LCDMenuLib_cfg_lcd_type >= 0 && _LCDMenuLib_cfg_lcd_type < 100)
		//LCD Function
#			define _LCDML_lcd_createChar(pos,char)		createChar(pos,char)
#			define _LCDML_lcd_setCursor(col,row)		setCursor(col,row)
#			define _LCDML_lcd_write(content)			write(content)
#			define _LCDML_lcd_clear()					clear()
#			define _LCDML_lcd_print(content)			print(content)

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
		// ================================================================================
		// LiquidCrystal SR3W
		// ================================================================================


#		endif
#	endif
#endif
