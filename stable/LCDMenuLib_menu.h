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