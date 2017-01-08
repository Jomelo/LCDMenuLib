// =====================================================================
//
// Output function
//
// =====================================================================

/* ******************************************************************** */
void LCDML_lcd_menu_display()
/* ******************************************************************** */
{
  // check if menu needs an update
  if (LCDML_DISP_update()) {     
    // init vars
    uint8_t n_max             = (LCDML.getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.getChilds());

    
    
    // update content
    if (LCDML_DISP_update_content() || LCDML_DISP_update_cursor()) {
      // clear menu
      LCDML_lcd_menu_clear();

      Serial.println(F("==========================================="));
      Serial.println(F("================  Menu ===================="));
      Serial.println(F("==========================================="));

      // display rows
      for (uint8_t n = 0; n < n_max; n++)
      {
        //set cursor char
        if (n == LCDML.getCursorPos()) {
          Serial.print(F("(x) "));          
        } else {
          Serial.print(F("( ) "));
        }                
        // print content
		// with content id you can add special content to your static menu or replace the content
		// the content_id contains the id wich is set on main tab for a menuitem
        switch(LCDML.content_id[n])
		{		 
			//case 0:
			//	Serial.print("special"); // or datetime or other things
			//	break;
		
			default: // static content
				Serial.print(LCDML.content[n]);
				break;				
		}
		Serial.println();
      }
    }   
  }
  // reinit some vars
  LCDML_DISP_update_end();
}


// lcd clear
void LCDML_lcd_menu_clear()
{
  for(uint8_t i=0;i<15;i++) {
    Serial.println();
  }
}



