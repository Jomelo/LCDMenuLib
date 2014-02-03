/************************************************************************/
/*																		*/
/*								LCDMenuLib								*/
/*																		*/
/************************************************************************/
/* Autor:			Nils Feldkämper										*/
/* Contact:			nilsfeld@gmail.com  (kein Support)					*/
/* Create:			03.02.2008											*/
/* Edit:			03.02.2014											*/
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


#include "LCDMenuLib_menu.h"

LCDMenu::LCDMenu(uint8_t n)
{	
	name=n;
	canEnter=NULL;
}

LCDMenu::LCDMenu(uint8_t n,boolean (*c)(LCDMenu&))
{
	name=n;
	canEnter=c;
}

void LCDMenu::setParent(LCDMenu &p)
{
	parent=&p;
}

void LCDMenu::addSibling(LCDMenu &s,LCDMenu &p)
{
	if (sibling)
	{
		sibling->addSibling(s,p);
	}
	else
	{
		sibling=&s;
		sibling->setParent(p);
	}
}



void LCDMenu::addChild(LCDMenu &c)
{
	if (child)
	{
		child->addSibling(c,*this);
	}
	else
	{
		child=&c;
		child->setParent(*this);
	}
}

LCDMenu * LCDMenu::getChild(uint8_t which)
{
	if (child)
	{
		return child->getSibling(which);
	}
	else //This Menu item has no children
	{
		return NULL;
	}
}

LCDMenu * LCDMenu::getSibling(uint8_t howfar)
{
	if (howfar==0)
	{
		return this;
	}
	else if (sibling)
	{
		return sibling->getSibling(howfar-1);
	}
	else //Asking for a nonexistent sibling
	{
		return NULL;
	}
}

LCDMenu * LCDMenu::getParent()
{
	if (parent)
	{
		return parent;
	}
	else //Top Menu
	{
		return this;
	}
}