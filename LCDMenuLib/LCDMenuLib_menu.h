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

#ifndef LCDMenu_h
#	define LCDMenu_h

#	include "Arduino.h"
#	include <avr/pgmspace.h>

	class LCDMenu
	{
		private:
			LCDMenu * parent;					// Parent menu, NULL if this is the top
			LCDMenu * child;						// First child menu, NULL if no children
			LCDMenu * sibling;					// Next sibling menu, NULL if this is the last sibling

			void setParent(LCDMenu &p);					// Sets the menu's parent to p
			void addSibling(LCDMenu &s,LCDMenu &p);		// Adds a sibling s with parent p.  If the menu already has a sibling, ask that sibling to add it

		public:
			uint8_t name;								// Name of this menu
			uint8_t disp;								// Set element group

			LCDMenu(uint8_t n, uint8_t group);			// Constructs the menu with a name and a NULL use function (be careful calling it)
			
			void addChild(LCDMenu &c);					// Adds the child c to the menu.  
														// If the menu already has a child, ask the child to add it as a sibling
			LCDMenu * getChild(uint8_t which);			// Returns a pointer to the which'th child of this menu
			LCDMenu * getSibling(uint8_t howfar);		// Returns a pointer to the sibling howfar siblings away from this menu
			LCDMenu * getParent();						// Returns this menu's parent menu.  If no parent, returns itself
	};
#endif