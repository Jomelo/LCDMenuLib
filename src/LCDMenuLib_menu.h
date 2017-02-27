/*
 * MIT License
 * 
 * Copyright (c) [2017] [Nils Feldkämper]
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// ********************************************************************
//																		
//						LCDMenuLib (LCDML)								
//																		
// ********************************************************************
//
// Autor:			Nils Feldkaemper				
// Create:			03.02.2008											
// Edit:			31.07.2016											
// License:			MIT License											
//
// ********************************************************************
//
// error reporting: 									
//	https://github.com/Jomelo/LCDMenuLib/issues							
//
// forum thread:													
// 	http://forum.arduino.cc/index.php?topic=73816.0						
//
// ********************************************************************

#ifndef LCDMenu_h
#	define LCDMenu_h

#	include "Arduino.h"

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