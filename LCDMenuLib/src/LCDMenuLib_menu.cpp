/* ******************************************************************** */
/*																		*/
/*						LCDMenuLib (LCDML)								*/
/*																		*/
/* ******************************************************************** */
/* Autor:			Nils Feldkämper										*/
/* Create:			03.02.2008											*/
/* Edit:			05.01.2016											*/
/* ******************************************************************** */
/* error reporting (english / german)									*/
/*	https://github.com/Jomelo/LCDMenuLib/issues							*/
/* support (german):													*/
/* 	http://forum.arduino.cc/index.php?topic=73816.0						*/
/* ******************************************************************** */

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