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
#ifndef LCDMenuLib___config_h
#	define LCDMenuLib___config_h

/* config */
#	define _LCDML_DISP_cfg_cursor_deep				6		// save the last position of the cursor until layer xx
#	define _LCDML_DISP_cfg_cursor					0x7E	// cursor char
#	define _LCDML_DISP_cfg_max_string_length		20		// max string length witch can be display



/* **************************************************************************************************** */
/*	0:100  LiquidCrystal (orginal)																		*/
/* **************************************************************************************************** */
// =========================
// 4 bit mode and 8 bit mode
// =========================
#	define _LCDMenuLib_cfg_lcd_type	0	// 4Bit												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	1	// 4Bit with rw										(tested)
//#	define _LCDMenuLib_cfg_lcd_type	2	// 4Bit with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	3	// 4Bit with rw,backlight							(tested)
//#	define _LCDMenuLib_cfg_lcd_type	4	// 8Bit												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	5	// 8Bit with rw										(tested)
//#	define _LCDMenuLib_cfg_lcd_type	6	// 8Bit with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	7	// 8Bit with rw,backlight							(tested)


/* **************************************************************************************************** */
/*	100:200  LiquidCrystal_new Version (extern)															*/
/* **************************************************************************************************** */
// =========================
// 4 bit mode and 8 bit mode
// =========================
//#	define _LCDMenuLib_cfg_lcd_type	100	// 4Bit												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	101	// 4Bit with rw										(tested)
//#	define _LCDMenuLib_cfg_lcd_type	102	// 4Bit with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	103	// 4Bit with rw,backlight							(tested)
//#	define _LCDMenuLib_cfg_lcd_type	104	// 8Bit												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	105	// 8Bit with rw										(tested)
//#	define _LCDMenuLib_cfg_lcd_type	106	// 8Bit with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	107	// 8Bit with rw,backlight							(tested)
// =========================
// I2C
// =========================
//#	define _LCDMenuLib_cfg_lcd_type	110	// I2C												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	111	// I2C with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	112	// I2C with e,rw,rs									
//#	define _LCDMenuLib_cfg_lcd_type	113	// I2C with e,rw,rs,backlight
//#	define _LCDMenuLib_cfg_lcd_type	114	// I2C with e,rw,rs,dat4,dat5,dat6,dat7
//#	define _LCDMenuLib_cfg_lcd_type	115	// I2C with e,rw,rs,dat4,dat5,dat6,dat7,backlight 
// =========================
// shift register
// =========================
//#	define _LCDMenuLib_cfg_lcd_type	120	// SR
// =========================
// shift register 2W
// =========================
//#	define _LCDMenuLib_cfg_lcd_type	130	// SR2W
// =========================
// shift register 3W
// =========================
//#	define _LCDMenuLib_cfg_lcd_type	140	// SR3W												(tested)
//#	define _LCDMenuLib_cfg_lcd_type	141	// SR3W with backlight								(tested)
//#	define _LCDMenuLib_cfg_lcd_type	142	// SR3W with control lines							(tested)
//#	define _LCDMenuLib_cfg_lcd_type	143	// SR3W with control lines, backlight				(tested)


/* **************************************************************************************************** */
/*	200:300  DogLCD (extern)																			*/
/* **************************************************************************************************** */
// =========================
// 4 bit mode
// =========================
//#define _LCDMenuLib_cfg_lcd_type 200


#endif