/* ******************************************************************** */
/*																		*/
/*						LCDMenuLib (LCDML)								*/
/*																		*/
/* ******************************************************************** */
/* Autor:			Jomelo												*/
/* Create:			03.02.2008											*/
/* Edit:			10.05.2015											*/
/* ******************************************************************** */
/* support (german):													*/
/* 	http://forum.arduino.cc/index.php?topic=73816.0						*/
/* support (english / german)											*/
/*	https://github.com/Jomelo/LCDMenuLib/issues							*/
/* ******************************************************************** */

#include "LCDMenuLib_menu.h"

/* ******************************************************************** */
/* constructor 
 *	@param
 *		name (uint8)
 *		group (uint8)
 *	@return
 */
/* ******************************************************************** */
LCDMenu::LCDMenu(uint8_t n, uint8_t group)
/* ******************************************************************** */
{	
	name = n;		// element name 
	disp = group;	// element group
}


/* ******************************************************************** */
/* private
 *	@param
 *		LCDMenu (pointer)
 *	@return
 */
/* ******************************************************************** */
void LCDMenu::setParent(LCDMenu &p)
/* ******************************************************************** */
{
	parent = &p;
}


/* ******************************************************************** */
/* private 
 *	@param
 *		sibling before this (pointer) 
 *		parent (pointer)
 *	@return
 */
/* ******************************************************************** */
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


/* ******************************************************************** */
/* public:
 *	@param
 *		LCDMenu (pointer)
 *	@return
 */
/* ******************************************************************** */
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


/* ******************************************************************** */
/* public
 *	@param
		which ...
 *	@return
 */
/* ******************************************************************** */
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


/* ******************************************************************** */
/* public
 *	@param
 *	@return
 */
/* ******************************************************************** */
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


/* ******************************************************************** */
/* public
 *	@param
 *	@return
 */
/* ******************************************************************** */
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