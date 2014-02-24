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
//#	define _LCDMenuLib_cfg_lcd_type	14	// I2C with e,rw,rs,dat4,dat5,dat6,dat7
//#	define _LCDMenuLib_cfg_lcd_type	15	// I2C with e,rw,rs,dat4,dat5,dat6,dat7,backlight 

//	====================================================================================================
//	20:30	LiquidCrystal_SR from LiquidCrystal_new Version 1.2.1				(ShiftRegister)
//	====================================================================================================
//#	define _LCDMenuLib_cfg_lcd_type	20	// SR

//	====================================================================================================
//	30:40	LiquidCrystal_SR from LiquidCrystal_new Version 1.2.1				(ShiftRegister 2W)
//	====================================================================================================
//#	define _LCDMenuLib_cfg_lcd_type	30	// SR2W

//	====================================================================================================
//	40:50	LiquidCrystal_SR from LiquidCrystal_new Version 1.2.1				(ShiftRegister 3W)
//	====================================================================================================
//#	define _LCDMenuLib_cfg_lcd_type	40	// SR3W												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	41	// SR3W with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	42	// SR3W with control lines							(tested)
//#	define _LCDMenuLib_cfg_lcd_type	43	// SR3W with control lines, backlight				(tested)

//	====================================================================================================
//	100:110	DogLcd
//	====================================================================================================
//#define _LCDMenuLib_cfg_lcd_type 100


#endif