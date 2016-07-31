// ============================================================ 
//                                                              
// Example: LCDML_003_glcd_u8glib                         
//                                                            
// ============================================================ 
// todo
// ============================================================ 

  // include libs
  #include <LCDMenuLib.h>
  #include <U8glib.h>
  
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms

// *********************************************************************
// U8GLIB
// *********************************************************************
  // setup u8g object, please remove comment from one of the following constructor calls
  // IMPORTANT NOTE: The following list is incomplete. The complete list of supported 
  // devices with all constructor calls is here: https://github.com/olikraus/u8glib/wiki/device
  U8GLIB_ST7920_128X64 u8g(13, 11, 12, U8G_PIN_NONE); 
  
  // settings for u8g lib and lcd
  #define _LCDML_u8g_lcd_w       128            // lcd width
  #define _LCDML_u8g_lcd_h       64             // lcd height
  #define _LCDML_u8g_font        u8g_font_6x13  // u8glib font (more fonts under u8g.h line 1520 ...)
  #define _LCDML_u8g_font_w      6              // u8glib font width
  #define _LCDML_u8g_font_h      13             // u8glib font heigt

  // nothing change here
  #define _LCDML_u8g_cols_max    (_LCDML_u8g_lcd_w/_LCDML_u8g_font_w)  
  #define _LCDML_u8g_rows_max    (_LCDML_u8g_lcd_h/_LCDML_u8g_font_h) 

  // rows and cols 
  // when you use more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
  // the program needs more ram with this changes
  #define _LCDML_u8g_rows        _LCDML_u8g_rows_max  // max rows 
  #define _LCDML_u8g_cols        20                   // max cols

  // scrollbar width
  #define _LCDML_u8g_scrollbar_w 6  // scrollbar width  


  // old defines with new content
  #define _LCDML_DISP_cols      _LCDML_u8g_cols
  #define _LCDML_DISP_rows      _LCDML_u8g_rows  


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
    // serial init; only be needed if serial control is used 
    while(!Serial);                    // wait until serial ready
    Serial.begin(9600);                // start serial    
    Serial.println(F(_LCDML_VERSION)); // only for examples
      
    // Enable all items with _LCDML_G1
    LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1
  
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