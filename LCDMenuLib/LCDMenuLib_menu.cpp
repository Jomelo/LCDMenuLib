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

#include "LCDMenuLib_menu.h"

/* ******************************************************************** *
 * constructor 
 *	@param
 *		name (uint8)
 *		group (uint8)
 *	@return
 *
 * ******************************************************************** */
LCDMenu::LCDMenu(uint8_t n, uint8_t group)
/* ******************************************************************** */
{	
	parent = NULL;
	sibling = NULL;
	child = NULL;
	name = n;		// element name 
	disp = group;	// element group
}


/* ******************************************************************** *
 * private: set parent to current menu eitem
 *	@param
 *		LCDMenu (pointer)
 *	@return
 *
 * ******************************************************************** */
void LCDMenu::setParent(LCDMenu &p)
/* ******************************************************************** */
{
	parent = &p;
}


/* ******************************************************************** *
 * private: add a sibling to the current menu  
 *	@param
 *		sibling before this (pointer) 
 *		parent (pointer)
 *	@return
 *
 * ******************************************************************** */
void LCDMenu::addSibling(LCDMenu &s,LCDMenu &p)
/* ******************************************************************** */
{
	if (sibling) { // add sibling if sibing exists 
		sibling->addSibling(s,p);
	} else
	{ // add sibling and parent 
		sibling =& s;
		sibling->setParent(p);
	}
}


/* ******************************************************************** *
 * public: add a child to current menu
 *	@param
 *		LCDMenu (pointer)
 *	@return
 *
 * ******************************************************************** */
void LCDMenu::addChild(LCDMenu &c)
/* ******************************************************************** */
{
	if (child) { // add sibling if child exists
		child->addSibling(c,*this);
	} else
	{ // add child  and parent
		child=&c;
		child->setParent(*this);
	}
}


/* ******************************************************************** *
 * public: returns the childs pointer if it exists
 *	@param
		which ...
 *	@return
 *
 * ******************************************************************** */
LCDMenu * LCDMenu::getChild(uint8_t which)
/* ******************************************************************** */
{
	if (child) { // return child if exists		
		return child->getSibling(which);		
	}
	else { // this menu item has no children
		return NULL;
	}
}


/* ******************************************************************** *
 * public: returns a sibling pointer if exists
 *	@param
 *
 *	@return
 *
 * ******************************************************************** */
LCDMenu * LCDMenu::getSibling(uint8_t howfar)
/* ******************************************************************** */
{
	if (howfar == 0) { // this sibling					
		return this;				
	}
	else if (sibling) {	// get next sibling	
		return sibling->getSibling(howfar - 1);
	}
	else { // asking for a nonexistent sibling	
		return NULL;
	}
}


/* ******************************************************************** *
 * public: return the parent pointer if exists
 *	@param
 *
 *	@return
 *
 * ******************************************************************** */
LCDMenu * LCDMenu::getParent()
/* ******************************************************************** */
{
	if (parent) { // get parent if exists		
		return parent;		
	}
	else { // root menu	
		return this;
	}
}