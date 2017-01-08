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
    uint8_t scrollbar_min     = 0;
    uint8_t scrollbar_max     = LCDML.getChilds();
    uint8_t scrollbar_cur_pos = LCDML.getCursorPosAbs();
    uint8_t scroll_pos        = ((1.*n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos);


    // update content
    if (LCDML_DISP_update_content()) {
      // clear menu
      LCDML_lcd_menu_clear();

      // display rows
      for (uint8_t n = 0; n < n_max; n++)
      {
        // set cursor
        lcd.setCursor(1, n);
		// set content
		// with content id you can add special content to your static menu or replace the content
		// the content_id contains the id wich is set on main tab for a menuitem
        switch(LCDML.content_id[n])
		{		 
			//case 0:
			//	lcd.print("special"); // or datetime or other things
			//	break;
		
			default: // static content
				lcd.print(LCDML.content[n]);
				break;				
		} 
      }
    }

    // update cursor and scrollbar
    if (LCDML_DISP_update_cursor()) {

      // display rows
      for (uint8_t n = 0; n < n_max; n++)
      {
        //set cursor
        lcd.setCursor(0, n);

        //set cursor char
        if (n == LCDML.getCursorPos()) {
          lcd.write(_LCDML_DISP_cfg_cursor);
        } else {
          lcd.write(' ');
        }

        // delete or reset scrollbar
        if (_LCDML_DISP_cfg_scrollbar == 1) {
          if (scrollbar_max > n_max) {
            lcd.setCursor((_LCDML_DISP_cols - 1), n);
            lcd.write((uint8_t)0);
          }
          else {
            lcd.setCursor((_LCDML_DISP_cols - 1), n);
            lcd.print(' ');
          }
        }
      }

      // display scrollbar
      if (_LCDML_DISP_cfg_scrollbar == 1) {
        if (scrollbar_max > n_max) {
          //set scroll position
          if (scrollbar_cur_pos == scrollbar_min) {
            // min pos
            lcd.setCursor((_LCDML_DISP_cols - 1), 0);
            lcd.write((uint8_t)1);
          } else if (scrollbar_cur_pos == (scrollbar_max - 1)) {
            // max pos
            lcd.setCursor((_LCDML_DISP_cols - 1), (n_max - 1));
            lcd.write((uint8_t)4);
          } else {
            // between
            lcd.setCursor((_LCDML_DISP_cols - 1), scroll_pos / n_max);
            lcd.write((uint8_t)(scroll_pos % n_max) + 1);
          }
        }
      }
    }
  }
  // reinit some vars
  LCDML_DISP_update_end();
}


// lcd clear
void LCDML_lcd_menu_clear()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}




