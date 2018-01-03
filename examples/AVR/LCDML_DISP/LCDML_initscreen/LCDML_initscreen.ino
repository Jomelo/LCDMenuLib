// ============================================================                                                            
// Example:     LCDML: initscreen                          
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 08.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton:     
// This example shows you how the initscreen or standbyscreen 
// works. The initscreen is a hidden menu element (example 004)
// witch it is not displayed in menu. The initscreen is called 
// when no action or trigger is set after ...cfg_initscreen_time
// milliseconds. When a other menu function is active, this function
// is stoped stable before initscreen function is started. 
// ============================================================  

  // include libs
  #include <LiquidCrystal.h>
  #include <LCDMenuLib.h>
  
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
  #define _LCDML_DISP_cfg_initscreen_time            10000  // enable initscreen time
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol 

// ********************************************************************* 
// LCDML TYPE SELECT
// *********************************************************************
  // settings for lcd 
  #define _LCDML_DISP_cols             20
  #define _LCDML_DISP_rows             4  

  // lcd object
  // liquid crystal needs (rs, e, dat4, dat5, dat6, dat7)
  LiquidCrystal lcd(4,5,6,7,8,9);
  
  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1 
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  }; 

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    12
  
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
  LCDML_DISP_add      (12 , _LCDML_G7  , LCDML_root        , 5  , "Program 2"          , LCDML_FUNC_initscreen); // in g7 => hidden
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    1  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
  LCDML_BACK_create();


// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {  
    // serial init; only be needed if serial control is used    
    Serial.begin(9600);                // start serial    
    Serial.println(F(_LCDML_VERSION)); // only for examples
    
    // LCD Begin
    lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);  
    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);
  
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
    // example for init screen   
    if((millis() - g_lcdml_initscreen) >= _LCDML_DISP_cfg_initscreen_time) {
      g_lcdml_initscreen = millis(); // reset init screen time
      LCDML_DISP_jumpToFunc(LCDML_FUNC_initscreen); // jump to initscreen     
    }  
    
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
