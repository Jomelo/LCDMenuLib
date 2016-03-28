/* ===================================================================== *
 *                                                                       *
 * DISPLAY SYSTEM                                                        *
 *                                                                       *
 * ===================================================================== *
 * every "disp menu function" needs three functions 
 * - void LCDML_DISP_setup(func_name)    
 * - void LCDML_DISP_loop(func_name)     
 * - void LCDML_DISP_loop_end(func_name)
 *
 * EXAMPLE CODE:
    void LCDML_DISP_setup(..menu_func_name..) 
    {
      // setup
      // is called only if it is started

      // starts a trigger event for the loop function every 100 millisecounds
      LCDML_DISP_triggerMenu(100);  
    }
    
    void LCDML_DISP_loop(..menu_func_name..)
    { 
      // loop
      // is called when it is triggert
      // - with LCDML_DISP_triggerMenu( millisecounds ) 
      // - with every button status change

      // check if any button is presed (enter, up, down, left, right)
      if(LCDML_BUTTON_checkAny()) {         
        LCDML_DISP_funcend();
      } 
    }
    
    void LCDML_DISP_loop_end(..menu_func_name..)
    {
      // loop end
      // this functions is ever called when a DISP function is quit
      // you can here reset some global vars or do nothing  
    } 
 * ===================================================================== *
 */


// this needs some bytes in ram
#define MAX_FILES_IN_LIST 20

// scroll row position
uint8_t scroll_row;
// cursor real position on lcd lines (0 - _LCDML_DISP_rows - 1)
uint8_t cursor_real_pos;
// max filelist count
uint8_t current_max_list_count;
// cursor position to file list entry
uint8_t cursor_position_cur;
// filelist
static char filelist[MAX_FILES_IN_LIST][20];
 

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_dyn_filelist)
// *********************************************************************
{
  // use this to init some vars 
  
  // set max file counter
  current_max_list_count = 0;
  // set current cursor position
  cursor_position_cur = 0;
  // 
  scroll_row = 0;
  cursor_real_pos = 0;


  // for example read sd card files here 
 
  // for example here only with a dummy list
  // with 12 dummyfiles
  // subfolders are not supported

  // generate file names
  for(uint8_t i = 0; i<13; i++) {
    if(i < MAX_FILES_IN_LIST) { 
      // copy dummy string to new position
      memcpy(filelist[i], "File   .txt", 11);
      
      if(i<10) {                    // filenames < 10
        filelist[i][5] = 0+48;      // number + '0'     '0' = 48
        filelist[i][6] = i+48;      // number
      } else {                      // filenames >= 10
        filelist[i][5] = i/10+48;  
        filelist[i][6] = i%10+48;
      }      
      current_max_list_count++;     
    }
  } 
}

void LCDML_DISP_loop(LCDML_FUNC_dyn_filelist) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function

  // init some vars for scrollbar
  uint8_t n_max             = (current_max_list_count >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (current_max_list_count);;
  uint8_t scrollbar_min     = 0;
  uint8_t scrollbar_max     = current_max_list_count;
  //uint8_t scrollbar_cur_pos = cursor_position_cur;
  uint8_t scroll_pos        = ((1.*n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * cursor_position_cur);


  // clear display
  // ================
  lcd.clear();

  // display content
  // ==================
  for (uint8_t n = scroll_row; n < (scroll_row+_LCDML_DISP_rows); n++)
  {   
    // set cursor
    lcd.setCursor(1, n-scroll_row);
    // set content
    lcd.print(filelist[n]);
  }

  // set cursor and scrollbar
  // =============================
  for (uint8_t n = scroll_row; n <(scroll_row+_LCDML_DISP_rows); n++)
  {
    lcd.setCursor(0, n-scroll_row);
      
    // set cursor
    // =====================
    if (n == cursor_position_cur) {
      lcd.write(_LCDML_DISP_cfg_cursor);
      cursor_real_pos = n-scroll_row;
    } else {
      lcd.write(' ');
    }    

    // display scrollbar
    // ==============================
    // delete or reset scrollbar
    if (scrollbar_max > n_max) {
      lcd.setCursor((_LCDML_DISP_cols - 1), n-scroll_row);
      lcd.write((uint8_t)0);
    }
    else {
      lcd.setCursor((_LCDML_DISP_cols - 1), n-scroll_row);
      lcd.print(' ');
    }

    // set scrollbar
    if (scrollbar_max > n_max) {
      //set scroll position
      if (cursor_position_cur == scrollbar_min) {
        // min pos
        lcd.setCursor((_LCDML_DISP_cols - 1), 0);
        lcd.write((uint8_t)1);
      } else if (cursor_position_cur == (scrollbar_max - 1)) {
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


  // control
  // =====================================
  
  // move up in list
  if(LCDML_BUTTON_checkUp()) {
    LCDML_BUTTON_resetAll();
    // scroll up   
    if(cursor_position_cur > 0) { // check minimum cursor
      cursor_position_cur--;      // scroll up
      if(cursor_real_pos == 0) {  
        scroll_row--;             // scroll display rows
      }      
    }
    // update content above or remove this line and copy button checks on top of this function
    LCDML_BACK_start(LCDML_BACKEND_menu);    
  }

  // move down in list
  if(LCDML_BUTTON_checkDown()) {
    LCDML_BUTTON_resetAll();   
    // scroll down
    if(cursor_position_cur < (current_max_list_count-1)) {    // check list end   
      cursor_position_cur++;                                  // go to next element
      if(cursor_real_pos == (_LCDML_DISP_rows-1)) {           // check if current cursor is in last display line
        scroll_row++;                                         // scroll content
      } 
    }
    // update content above or remove this line and copy button checks on top of this function
    LCDML_BACK_start(LCDML_BACKEND_menu);             
  }

  // enter file name
  if(LCDML_BUTTON_checkEnter()) {
    LCDML_BUTTON_resetAll();   
    // save selected file (serial.print)
    LCDML_DISP_funcend();
    // output of current line
    Serial.println(filelist[cursor_position_cur]);  
  }  
}

void LCDML_DISP_loop_end(LCDML_FUNC_dyn_filelist)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 

  // Display selected file name
 
}  

