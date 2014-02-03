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

//# Define
//# =======================
#ifndef LCDMenu_h
#define LCDMenu_h

//# Include
//# =======================
#include "Arduino.h"
#include <avr/pgmspace.h>


class LCDMenu
{
private:
 LCDMenu * parent;//Parent Menu, NULL if this is the top
 LCDMenu * child;//First Child Menu, NULL if no children
 LCDMenu * sibling;//Next Sibling Menu, NULL if this is the last sibling

 void setParent(LCDMenu &p);//Sets the Menu's Parent to p
 void addSibling(LCDMenu &s,LCDMenu &p);//Adds a Sibling s with Parent p.  If the Menu already has a sibling, ask that sibling to add it
public:
 uint8_t name;//Name of this Menu
 boolean (*canEnter)(LCDMenu&);//Function to be called when this menu is 'used'

 LCDMenu(uint8_t n);//Constructs the Menu with a name and a NULL use function (be careful calling it)
 LCDMenu(uint8_t n,boolean (*c)(LCDMenu&));//Constructs the Menu with a specified use function
 void addChild(LCDMenu &c);//Adds the child c to the Menu.  If the menu already has a child, ask the child to add it as a sibling
 LCDMenu * getChild(uint8_t which);//Returns a pointer to the which'th child of this Menu
 LCDMenu * getSibling(uint8_t howfar);//Returns a pointer to the sibling howfar siblings away from this Menu
 LCDMenu * getParent();//Returns this Menu's parent Menu.  If no parent, returns itself
};
#endif