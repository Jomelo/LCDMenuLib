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
/* Support:																*/
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
/* Driver																*/
/*  - Orginal LiquidCrystal												*/
/*  --- 4 Bit Mode														*/
/*  --- 8 Bit Mode														*/
/*	- New LiquidCrystal													*/
/*  --- 4 Bit Mode														*/
/*  --- 8 Bit Mode														*/
/*  --- I2C																*/
/*  --- SR																*/
/*  --- SR2W (74LS164)													*/
/*  --- SR3W (74HC595N)													*/
/* - LiquidCrystal_I2C													*/
/*	--- I2C																*/
/************************************************************************/
#ifndef LCDMenuLib___config_h
#	define LCDMenuLib___config_h
//
//	====================================================================================================
//	0:10  LiquidCrystal (orginal) or LiquidCrystal_new Version 1.2.1			(normal)
//	====================================================================================================
#	define _LCDMenuLib_cfg_lcd_type	0	// 4Bit												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	1	// 4Bit with rw										(tested)
//#	define _LCDMenuLib_cfg_lcd_type	2	// 4Bit with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	3	// 4Bit with rw,backlight							(tested)
//#	define _LCDMenuLib_cfg_lcd_type	4	// 8Bit												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	5	// 8Bit with rw										(tested)
//#	define _LCDMenuLib_cfg_lcd_type	6	// 8Bit with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	7	// 8Bit with rw,backlight							(tested)
//	====================================================================================================
//	10:20  LiquidCrystal_I2C from LiquidCrystal_new Version 1.2.1				(I2C)
//	====================================================================================================
//#	define _LCDMenuLib_cfg_lcd_type	10	// I2C												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	11	// I2C with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	12	// I2C with e,rw,rs									
//#	define _LCDMenuLib_cfg_lcd_type	13	// I2C with e,rw,rs,backlight
//#	define _LCDMenuLib_cfg_lcd_type	14	// I2C with e,rw,rs,dat0,dat1,dat2,dat3
//#	define _LCDMenuLib_cfg_lcd_type	15	// I2C with e,rw,rs,dat0,dat1,dat2,dat3,backlight 
//	====================================================================================================
//	20:30	LiquidCrystal_SR from LiquidCrystal_new Version 1.2.1				(ShiftRegister)
//	====================================================================================================
//#	define _LCDMenuLib_cfg_lcd_type	20	// SR

#endif









