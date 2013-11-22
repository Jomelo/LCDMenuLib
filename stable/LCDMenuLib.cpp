/************************************************************************/
/*																		*/
/*								LCDMenuLib								*/
/*																		*/
/************************************************************************/
/* Autor:			Nils Feldkämper										*/
/* Contact:			nilsfeld@gmail.com  (kein Support)					*/
/* Create:			03.02.2008											*/
/* Edit:			26.08.2013											*/
/************************************************************************/
/* License:			all Free											*/
/************************************************************************/
/* Support:	
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
/*								Wichtig									*/
/************************************************************************/
/* Falls ihr die Lib mit I2C oder anderen Schnittstellen betreiben		*/
/* wollt, muss die LCDMenuLib_config.h angepasst werden. Die Datei		*/
/* befindet sich im Lib Verzeichnis. Für die Anpassung der Schnitt-		*/
/* stelle muss der Wert (_LCDMenuLib_cfg_lcd_type) verändert werden.    */
/************************************************************************/
#	include <LCDMenuLib.h>


LCDMenuLib::LCDMenuLib(LCDMenu &p_r,_LCDML_lcd_type &p_d, const char **p_flash_table, const uint8_t p_rows, const uint8_t p_cols)
{
    rootMenu        = &p_r;
    curMenu         = rootMenu;
	flash_table     = p_flash_table;
    lcd             = &p_d;	

	control = 0; 
    cursor_pos      = 0;
    layer           = 0;
    layer_save[0]   = 0;
	
	rows			= p_rows;
	cols			= (p_cols-1);    
	
    g_function      = _LCDMenuLib_NO_FUNC;

    button = 0;
}



boolean LCDMenuLib::selectElementDirect(LCDMenu &p_m, uint8_t p_search)
{	
	LCDMenu * search = &p_m;
	LCDMenu * tmp;	
	uint8_t found = 0;
			
	do {
		//Überprüfen ob das Element Kinder hat
		if(tmp=search->getChild(0)) 
		{
			//Kinder gefunden, daher kann Enter gedrückt werden
			Button_enter();

			//Überprüfen ob Übereinstimmung vorhanden ist
			if(tmp->name == p_search) 
			{
				found = 1;				
				break;
			}		
			
			//keine Übereinstimmung

			//Rekrosiv Funktion erneut aufruf um eine Ebene tiefer zu überprüfen
			found = selectElementDirect(*tmp, p_search);
			
			//Erneut Prüfen ob eine Übereinstimmung vorhanden ist
			if(found == 1) 
			{
				// gefunden
				break; 
			} 
			else 
			{
				// nicht gefunden, wieder eine Ebene nach oben und nächstes Element auswählen
				Button_quit();
				Button_up_down_left_right(_LCDMenuLib_button_down);				
			}				
		} 
		else 
		{
			// Keine Kinder gefunden, trotzdem Überprüfen ob Übereinstimmung vorhanden ist
			
			//Überprüfen ob Übereinstimmung vorhanden ist
			if(search->name == p_search) 
			{
				// passt
				found = 1;				
				break;
			} 
			else 
			{
				// nächstes Element auswählen
				//Button_down();
				Button_up_down_left_right(_LCDMenuLib_button_down);
			}
		}
		
		
	} while ((search=search->getSibling(1)) && found == 0);


	return found;
	
}

void	LCDMenuLib::goRoot()
{
	button = 0;
	while(layer > 0) { Button_quit(2); }
	Button_quit(2);
	while(cursor_pos > 0) { Button_up_down_left_right(_LCDMenuLib_button_up); }
}

void	LCDMenuLib::jumpToElement(uint8_t p_element)
{	
	goRoot();
	selectElementDirect(*rootMenu, p_element);
	Button_enter();
}



void	LCDMenuLib::setCursor()
{
	LCDMenu * tmp; 
    uint8_t j = 0;

	if(cursor_pos > curloc-scroll) 
	{
        lcd->_LCDML_lcd_setCursor(0,cursor_pos);
        lcd->_LCDML_lcd_write(0x20);
    }
    else if(cursor_pos < curloc-scroll) 
	{
       lcd->_LCDML_lcd_setCursor(0,curloc-scroll-1);
       lcd->_LCDML_lcd_write(0x20);
    }	
   
	cursor_pos = curloc-scroll;

	//setze Kurser
    lcd->_LCDML_lcd_setCursor(0,cursor_pos);
    lcd->_LCDML_lcd_write(0x7E);

	if(bitRead(control, _LCDMenuLib_control_scrollbar_l) == 1) {
		//Scrollbalken animieren
		// Anzahl ermitteln
	
		if ((tmp=curMenu->getChild(0))) 
		{
			do 
			{
				j++;
			} while ((tmp=tmp->getSibling(1)));
		}
		j--; // Korrektur

	
		if(j>(rows-1)) {

			lcd->_LCDML_lcd_setCursor(cols, 0);
			lcd->_LCDML_lcd_write((uint8_t)0);
			lcd->_LCDML_lcd_setCursor(cols, 1);
			lcd->_LCDML_lcd_write((uint8_t)0);

			if(rows == 4) {
				lcd->_LCDML_lcd_setCursor(cols, 2);
				lcd->_LCDML_lcd_write((uint8_t)0);
				lcd->_LCDML_lcd_setCursor(cols, 3);
				lcd->_LCDML_lcd_write((uint8_t)0);
			}
          
			if(curloc == 0) {
				lcd->_LCDML_lcd_setCursor(cols, 0);
				lcd->_LCDML_lcd_write((uint8_t)1);					
			} else if(curloc == j) {
				lcd->_LCDML_lcd_setCursor(cols, (rows-1));
				lcd->_LCDML_lcd_write((uint8_t)4);			
			} else {
				uint8_t scroll_pos = ((4.*rows)/j*curloc);
				lcd->_LCDML_lcd_setCursor(cols, scroll_pos/4);			
				lcd->_LCDML_lcd_write((scroll_pos%4)+1);
			}
		}
	}
	
	
}

void	LCDMenuLib::doScroll()
{
	//Only allow it to go up to Menu item (one more if back button enabled)    
	while (curloc>0 && !curMenu->getChild(curloc))
    {
		curloc--;    
    }

	//Scroll
    if (curloc >= (rows+scroll)) {
        scroll++;
        display();
    } else if (curloc < scroll) {
        scroll--;
        display();
    } else {
        setCursor();
    }
}





void	LCDMenuLib::goBack()
{
	if(bitRead(control, _LCDMenuLib_control_menu_look) == 0) 
	{
		if(layer > 0) 
		{
			bitWrite(control, _LCDMenuLib_control_menu_back, 1);
			goMenu(*curMenu->getParent());
		}
	}
	g_function      = _LCDMenuLib_NO_FUNC;
}

void	LCDMenuLib::goEnter()
{	
	if(bitRead(control, _LCDMenuLib_control_menu_look) == 0) 
	{
		LCDMenu *tmp;
		tmp=curMenu;

		if ((tmp=tmp->getChild(curloc))) //The child exists
		{
			goMenu(*tmp);				
			curfuncname = tmp->name;			
		}		
	}
}



void	LCDMenuLib::goMenu(LCDMenu &m)
{
    curMenu=&m;	

    if(layer < _LCDMenuLib_cfg_cursor_deep) 
	{
        int diff;
        scroll = 0;

        if(bitRead(control, _LCDMenuLib_control_menu_back) == 0) 
		{			
            layer_save[layer] = curloc;
            layer++;		
            curloc = 0;
        } 
		else 
		{
            bitWrite(control, _LCDMenuLib_control_menu_back, 0);

            if(layer > 0) 
			{				
                layer--;				
                curloc = layer_save[layer];

                if(curloc >= rows) 
				{
                    diff = curloc-(rows-1);
                    for(int i=0; i<diff; i++) 
					{
                        doScroll();
                    }
                }
            }
        }
    }

    display();
}

void	LCDMenuLib::display()
{
    LCDMenu * tmp;
    uint8_t i = scroll;
    uint8_t j = 0;
    uint8_t maxi=(rows+scroll);	
	char buffer[_LCDMenuLib_cfg_max_string_length];
    lcd->_LCDML_lcd_clear();

    // Anzahl ermitteln
    
	if ((tmp=curMenu->getChild(0))) 
	{
        do 
		{
            j++;
        } while ((tmp=tmp->getSibling(1)));
    }
    j--; // Korrektur	
	

    if ((tmp=curMenu->getChild(i))) 
	{
        do 
		{
			strcpy_P(buffer, (char*)pgm_read_word(&(flash_table[tmp->name])));

            lcd->_LCDML_lcd_setCursor(0,i-scroll);
            lcd->_LCDML_lcd_write(0x20);			
            lcd->_LCDML_lcd_print(buffer);			
            i++;

        } while ((tmp=tmp->getSibling(1))&&i<maxi); 

		if(bitRead(control, _LCDMenuLib_control_scrollbar_h) == 1) 
		{
		
		
			if(j>(rows-1)) 
			{
			  

				if(curloc == 0) 
				{
					lcd->_LCDML_lcd_setCursor((cols),(rows-1));
					if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 0) {
					
						lcd->_LCDML_lcd_write((uint8_t)1);
					} else if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 1) {
						lcd->_LCDML_lcd_write((uint8_t)0x19);
					}
				}
				else if(curloc == j) 
				{
					lcd->_LCDML_lcd_setCursor((cols),0);
					if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 0) {
						lcd->_LCDML_lcd_write((uint8_t)0);
					} else if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 1) {
						lcd->_LCDML_lcd_write((uint8_t)0x18);
					}
				}
				else 
				{
					lcd->_LCDML_lcd_setCursor((cols),0);
					if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 0) {
						lcd->_LCDML_lcd_write((uint8_t)0);
					} else if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 1) {
						lcd->_LCDML_lcd_write((uint8_t)0x18);
					}

					lcd->_LCDML_lcd_setCursor((cols),(rows-1));
					if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 0) {
						lcd->_LCDML_lcd_write((uint8_t)1);
					} else if(bitRead(control, _LCDMenuLib_control_lcd_standard) == 1) {
						lcd->_LCDML_lcd_write((uint8_t)0x19);
					}
				}
			}
		}
        
    }
    else 
	{ // no children
        goBack();
        // function can work
    }
    setCursor();
}


boolean LCDMenuLib::checkButtons()
{
    if(bitRead(button, _LCDMenuLib_button)) 
	{		
		bitWrite(button, _LCDMenuLib_button, 0);		
        return true;
    }
    return false;    
}


 
/* 
//button
*/
uint8_t	LCDMenuLib::checkFuncEnd(uint8_t check)
  { 
    //Bedingung zum Abbruch    
    if(bitRead(check, 5) //direct
            || (((button & check) & (1<<_LCDMenuLib_button_enter)))  
            || (((button & check) & (1<<_LCDMenuLib_button_up)))
            || (((button & check) & (1<<_LCDMenuLib_button_down)))
            || (((button & check) & (1<<_LCDMenuLib_button_left)))
            || (((button & check) & (1<<_LCDMenuLib_button_right)))
    ) 
	{       
      //Funktion beenden
      Button_quit();
      return true;
    } 
    
    //Funktion läuft noch
    return false;    
  }
  
  
  
void	LCDMenuLib::Button_enter()
{
	if(bitRead(control, _LCDMenuLib_control_initscreen_active) == true) 
	{
		Button_quit(2);
	} 
	else 
	{
  
	
		if(g_function != _LCDMenuLib_NO_FUNC) 
		{
			bitWrite(button, _LCDMenuLib_button, 1);
			bitWrite(button, _LCDMenuLib_button_enter, 1);	
		} 

		if(bitRead(control, _LCDMenuLib_control_initscreen_active) == 0) 
		{
			goEnter();
			g_function = curfuncname;
		}  
		
		bitWrite(button, _LCDMenuLib_button_init_screen, 1);
		
	}
}

void	LCDMenuLib::Button_up_down_left_right(uint8_t but)
{
	if(bitRead(control, _LCDMenuLib_control_menu_look) == 0)
	{
		switch(but)
		{
			case _LCDMenuLib_button_up:
				if(curloc > 0) 
				{
					curloc--;
				}				
			break;

			case _LCDMenuLib_button_down:
				curloc++;				
			break;
		}
		doScroll();
	}

	bitWrite(button, but, 1);
	bitWrite(button, _LCDMenuLib_button, 1);
	bitWrite(button, _LCDMenuLib_button_init_screen, 1);
}


void	LCDMenuLib::Button_quit(uint8_t opt)
{
	bitWrite(button, _LCDMenuLib_button_init_screen, 1);
 
  
  if(bitRead(control, _LCDMenuLib_control_initscreen_active) == 1) 
  {
	   //Lcd löschen      
		lcd->_LCDML_lcd_clear();

	  bitWrite(control, _LCDMenuLib_control_initscreen_active, 0);
	  bitWrite(control, _LCDMenuLib_control_menu_look, 0);
	  bitWrite(control, _LCDMenuLib_control_funcsetup, 0);
	 
	 
	 display();

	 goRoot();
	  
  } 
  else 
  { 
	  // Splash Screen überprüfen, muss vor goBack eingebunden werden
	  if(opt==1 || (g_function == _LCDMenuLib_NO_FUNC && layer == 0 && opt==0) && bitRead(control, _LCDMenuLib_control_initscreen_enable) == 1) 
	  {
		  //enable init screen		  
		  bitWrite(control, _LCDMenuLib_control_funcsetup, 0);
		  bitWrite(control, _LCDMenuLib_control_initscreen_active, 1);
		  bitWrite(control, _LCDMenuLib_control_menu_look, 1);
		
	  } 
	  else 
	  {	
		  if(g_function == _LCDMenuLib_NO_FUNC && layer == 0) {

		  } else {
			  //Lcd löschen      
			lcd->_LCDML_lcd_clear();
		
		   //Menu wieder anzeigen
			display();
  
		    goBack();  
       
		 
			//Wenn in einer Menu Funktion, Funktionsspeicher löschen
			g_function = _LCDMenuLib_NO_FUNC;                      
			//Funktionsstatus löschen          
			bitWrite(control, _LCDMenuLib_control_funcsetup, 0);
    
			//Display wieder freigeben
			bitWrite(control, _LCDMenuLib_control_menu_look, 0);

		  }		 
	  }	  
  }
  
  button = 0;
}






boolean	LCDMenuLib::FuncInit(void)
{
    //Funktionsstatus überprüfen
    
	if(bitRead(control, _LCDMenuLib_control_funcsetup) == false) 
	{
		//Funktion aktive estzen
		bitWrite(control, _LCDMenuLib_control_funcsetup, 1);
		//Funktionsnamen festlegen, damit diese Funktion immer wieder aufgerufen werden kann
		if(bitRead(control, _LCDMenuLib_control_initscreen_active) == 0) 
		{
			g_function  = curfuncname;
		}
		//Buttons zurücksetzen
		button = 0;
		//Menu sperren
		bitWrite(control, _LCDMenuLib_control_menu_look, 1);    
     
		return false;
	}
	
    return true;    
} 
  
uint8_t	LCDMenuLib::getFunction()
{	
	return g_function;	
}

uint8_t	LCDMenuLib::getCurFunction()
{
	return curfuncname;
}

uint8_t	LCDMenuLib::getLayer()
{
	return layer;
}

uint8_t	LCDMenuLib::getInitScreenActive()
{
	return bitRead(control, _LCDMenuLib_control_initscreen_active);
}

boolean LCDMenuLib::Timer(unsigned long &p_var, unsigned long p_time)
{	
	if(p_var > millis()) 
	{  
		return false; 
	}
	p_var = millis() + p_time;
	return true;
}


