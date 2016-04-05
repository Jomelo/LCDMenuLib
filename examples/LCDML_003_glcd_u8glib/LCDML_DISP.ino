// =====================================================================
//
// Output function
//
// =====================================================================

/* ******************************************************************** */
void LCDML_lcd_menu_display()
/* ******************************************************************** */
{
  // for first test set font here
  u8g.setFont(u8g_font_6x13);
  u8g.setColorIndex(1); // Instructs the display to draw with a pixel on. 

  if (LCDML_DISP_update()) { 

    // init vars
    uint8_t n_max             = (LCDML.getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.getChilds());
    //uint8_t scrollbar_min     = 0;
    //uint8_t scrollbar_max     = LCDML.getChilds();
    //uint8_t scrollbar_cur_pos = LCDML.getCursorPosAbs();
    //uint8_t scroll_pos        = ((1.*n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos);
    

    u8g.firstPage();
  
    do {
      // check if menu needs an update 

      // update content
      //if (LCDML_DISP_update_content()) {  
        // display rows
        for (uint8_t n = 0; n < n_max; n++)
        {
          if (n == LCDML.getCursorPos()) {
            u8g.drawStr( 0, 13*(n+1),  "X");
          } else {
            //lcd.write(' ');
          }
          
          // set content
          u8g.drawStr( 10, 13*(n+1), LCDML.content[n]);
        }
      //}
       
  
        // display scrollbar
        /* comming soon */
        /*
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
        */
      
    } while( u8g.nextPage() );
  }  

  // reinit some vars
  LCDML_DISP_update_end();
}

// lcd clear
void LCDML_lcd_menu_clear()
{  
}




