// ============================================================                                                            
// Example:     LCDML: grafik display with u8g2                        
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 12.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton: 
// This example shows how to use the u8g2lib with the lcdmenulib
// The menu can placed in a box that can be placed anywhere on 
// the screen.  
// ============================================================ 

  // include libs
  #include <LCDMenuLib.h>

  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms

  
  // U8g2lib
  #include <Arduino.h>
  #include <U8g2lib.h>
  
  #ifdef U8X8_HAVE_HW_SPI
  #include <SPI.h>
  #endif
  #ifdef U8X8_HAVE_HW_I2C
  #include <Wire.h>
  #endif
  


// *********************************************************************
// U8G2LIB
// *********************************************************************
// U8g2 Contructor List (Frame Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected
  U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 12, /* reset=*/ U8X8_PIN_NONE); 
  
  // settings for u8g lib and lcd
  #define _LCDML_DISP_w                 128            // lcd width
  #define _LCDML_DISP_h                 64             // lcd height
  // font settings
  #define _LCDML_DISP_font              u8g_font_6x13  // u8glib font (more fonts under u8g.h line 1520 ...)
  #define _LCDML_DISP_font_w            6              // font width
  #define _LCDML_DISP_font_h            13             // font heigt  
  // cursor settings
  #define _LCDML_DISP_cursor_char       "X"            // cursor char
  #define _LCDML_DISP_cur_space_before  2              // cursor space between
  #define _LCDML_DISP_cur_space_behind  4              // cursor space between  
  // menu position and size
  #define _LCDML_DISP_box_x0            0              // start point (x0, y0)
  #define _LCDML_DISP_box_y0            0              // start point (x0, y0)
  #define _LCDML_DISP_box_x1            128            // width x  (x0 + width)
  #define _LCDML_DISP_box_y1            64             // hight y  (y0 + height)
  #define _LCDML_DISP_draw_frame        1              // draw a box around the menu
   // scrollbar width
  #define _LCDML_DISP_scrollbar_w       6  // scrollbar width (if this value is < 3, the scrollbar is disabled)    

  // nothing change here
  #define _LCDML_DISP_cols_max          ((_LCDML_DISP_box_x1-_LCDML_DISP_box_x0)/_LCDML_DISP_font_w) 
  #define _LCDML_DISP_rows_max          ((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0)/_LCDML_DISP_font_h))/_LCDML_DISP_font_h) 

  // rows and cols 
  // when you use more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
  // the program needs more ram with this changes
  #define _LCDML_DISP_rows              _LCDML_DISP_rows_max  // max rows 
  #define _LCDML_DISP_cols              20                   // max cols


// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    16
  
  // LCDML_root        => layer 0 
  // LCDML_root_X      => layer 1 
  // LCDML_root_X_X    => layer 2 
  // LCDML_root_X_X_X  => layer 3 
  // LCDML_root_... 	 => layer ... 
  
  // LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  LCDML_DISP_init(_LCDML_DISP_cnt);
  LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Information"        , LCDML_FUNC_information);
  LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Time info"          , LCDML_FUNC_timer_info);
  LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root        , 3  , "Settings"           , LCDML_FUNC);
  LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_3      , 1  , "Change value"       , LCDML_FUNC);
  LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_3      , 2  , "Something"          , LCDML_FUNC);
  LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root        , 4  , "Program"            , LCDML_FUNC);
  LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root_4      , 1  , "Program 1"          , LCDML_FUNC);
  LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_4_1    , 1  , "P1 start"           , LCDML_FUNC);
  LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_4_1    , 2  , "Settings"           , LCDML_FUNC);
  LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_4_1_2  , 1  , "Warm"               , LCDML_FUNC);
  LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_4_1_2  , 2  , "Long"               , LCDML_FUNC);
  LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_4      , 2  , "Program 2"          , LCDML_FUNC_p2);
  LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root        , 5  , "Mode"               , LCDML_FUNC);
  LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root        , 6  , "Serial No."         , LCDML_FUNC);
  LCDML_DISP_add      (14 , _LCDML_G1  , LCDML_root        , 7  , "Display Type"       , LCDML_FUNC);
  LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root        , 8  , "Something 1"        , LCDML_FUNC);
  LCDML_DISP_add      (16 , _LCDML_G1  , LCDML_root        , 9  , "Something 2"        , LCDML_FUNC);
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    1  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (1  , ( 10000000UL )   , _LCDML_stop   , LCDML_BACKEND_menu);
  LCDML_BACK_create();



// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {  
    u8g2.begin();
    
    // serial init; only be needed if serial control is used    
    Serial.begin(9600);                // start serial    
    Serial.println(F(_LCDML_VERSION)); // only for examples
      
    // Enable all items with _LCDML_G1
    LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1
    
    // Enable menu rollover if needed
    //LCDML.enRollover();
  
    // LCDMenu Setup
    LCDML_setup(_LCDML_BACK_cnt);  
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  { 
    // this function must called here, do not delete it
    LCDML_run(_LCDML_priority); 
  }




// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
