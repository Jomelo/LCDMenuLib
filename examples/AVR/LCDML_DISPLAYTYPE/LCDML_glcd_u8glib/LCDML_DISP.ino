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
  u8g.setFont(_LCDML_DISP_font);
  u8g.setColorIndex(1); // Instructs the display to draw with a pixel on.

  if (LCDML_DISP_update()) {

    // init vars
    uint8_t n_max = (LCDML.getChilds() >= _LCDML_DISP_rows) ? ((_LCDML_DISP_rows > _LCDML_DISP_rows_max) ? _LCDML_DISP_rows : _LCDML_DISP_rows_max) : (LCDML.getChilds());
    uint8_t gCP   = LCDML.getCursorPos();
    uint8_t gCPABS= LCDML.getCursorPosAbs();
    uint8_t gC    = LCDML.getChilds();

  
    // set page
    u8g.firstPage();

    // generate content
    do {

      // display rows and cursor
      for (uint8_t n = 0; n < n_max; n++)
      {
        // set cursor
        if (n == gCP) {
          u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_cur_space_before, _LCDML_DISP_box_y0 + _LCDML_DISP_font_h * (n + 1),  _LCDML_DISP_cursor_char);
        }
		
    		// set content
    		// with content id you can add special content to your static menu or replace the content
    		// the content_id contains the id wich is set on main tab for a menuitem
        switch(LCDML.content_id[n])
    		{		 
    			//case 0:
    			//	u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind, _LCDML_DISP_box_y0 + _LCDML_DISP_font_h * (n + 1), "var_datetime"); // or datetime or other things
    			//	break;
    		
    			default: // static content
    				u8g.drawStr( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind, _LCDML_DISP_box_y0 + _LCDML_DISP_font_h * (n + 1), LCDML.content[n]);
    				break;				
    		}
      }

      // drow a box around the menu
      if(_LCDML_DISP_draw_frame == 1) {
         u8g.drawFrame(_LCDML_DISP_box_x0, _LCDML_DISP_box_y0, (_LCDML_DISP_box_x1-_LCDML_DISP_box_x0), (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0));
      }

      // display scrollbar when more content as rows available and with > 2 
      if (gC > n_max && _LCDML_DISP_scrollbar_w > 2) {

        // set frame for scrollbar
        u8g.drawFrame(_LCDML_DISP_box_x1 - _LCDML_DISP_scrollbar_w, _LCDML_DISP_box_y0, _LCDML_DISP_scrollbar_w, _LCDML_DISP_box_y1-_LCDML_DISP_box_y0);

        // calculate scrollbar length
        uint8_t scrollbar_block_length = gC - n_max;
        scrollbar_block_length = (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0) / (scrollbar_block_length + _LCDML_DISP_rows);

        //set scrollbar
        if (gCPABS == 0) {                                   // top position     (min)
          u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y0 + 1                                                     , (_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
        } 
        else if (gCPABS == (gC-1)) {            // bottom position  (max)         
          u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y1 - scrollbar_block_length                                , (_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
        } 
        else {                                                                // between top and bottom
          u8g.drawBox(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1), _LCDML_DISP_box_y0 + (scrollbar_block_length * gCPABS + 1),(_LCDML_DISP_scrollbar_w-2)  , scrollbar_block_length);
        }       
      }
    } while ( u8g.nextPage() );
  }

  // reinit some vars
  LCDML_DISP_update_end();
}

// lcd clear
void LCDML_lcd_menu_clear()
{
}
