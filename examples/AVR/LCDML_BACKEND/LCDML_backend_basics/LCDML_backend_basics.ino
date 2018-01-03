// ============================================================                                                            
// Example:     LCDML: serialmonitor                          
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 08.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton:  
//                                                            
// ============================================================ 

  // include libs
  #include <LiquidCrystal.h>
  #include <LCDMenuLib.h>
  
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
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
  #define _LCDML_DISP_cnt    26
  
  // LCDML_root        => layer 0 
  // LCDML_root_X      => layer 1 
  // LCDML_root_X_X    => layer 2 
  // LCDML_root_X_X_X  => layer 3 
  // LCDML_root_... 	 => layer ... 
  
  // LCDMenuLib_add     (id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  // LCDMenuLib_addMenu (id, group, prev_layer_element, new_element_num, lang_char_array)
  // LCDMenuLib_addParam(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function, parameter [0-255]) // needs LCDML_DISP_initParam
  
  //LCDML_DISP_init(_LCDML_DISP_cnt);
  LCDML_DISP_initParam(_LCDML_DISP_cnt); // enbable parameters (needs one byte per menu element)
  // Menu
  LCDML_DISP_addMenu  (0  , _LCDML_G1  , LCDML_root        , 1  , "Backend Basic");
  LCDML_DISP_addMenu  (1  , _LCDML_G1  , LCDML_root_1      , 1  , "Func (static)");
  LCDML_DISP_addParam (2  , _LCDML_G1  , LCDML_root_1_1    , 1  , "Start"        , LCDML_FUNC_static, 1);
  LCDML_DISP_addParam (3  , _LCDML_G1  , LCDML_root_1_1    , 2  , "Reset"        , LCDML_FUNC_static, 2);
  LCDML_DISP_addParam (4  , _LCDML_G1  , LCDML_root_1_1    , 3  , "Stop"         , LCDML_FUNC_static, 3);
  LCDML_DISP_addParam (5  , _LCDML_G1  , LCDML_root_1_1    , 4  , "Restart"      , LCDML_FUNC_static, 4);
  LCDML_DISP_addParam (6  , _LCDML_G1  , LCDML_root_1_1    , 5  , "Stop stable"  , LCDML_FUNC_static, 5);
  LCDML_DISP_addMenu  (7  , _LCDML_G1  , LCDML_root_1      , 2  , "Func (dynamic)");
  LCDML_DISP_addParam (8  , _LCDML_G1  , LCDML_root_1_2    , 1  , "Start"        , LCDML_FUNC_dynamic, 1);
  LCDML_DISP_addParam (9  , _LCDML_G1  , LCDML_root_1_2    , 2  , "Stop Stable"  , LCDML_FUNC_dynamic, 2);
  LCDML_DISP_addParam (10 , _LCDML_G1  , LCDML_root_1_2    , 3  , "Set Time"     , LCDML_FUNC_dynamic, 3);
  LCDML_DISP_addMenu  (11 , _LCDML_G1  , LCDML_root        , 2  , "Backend Groups");
  LCDML_DISP_addParam (12 , _LCDML_G1  , LCDML_root_2      , 1  , "Group start"  , LCDML_FUNC_group, 1);
  LCDML_DISP_addParam (13 , _LCDML_G1  , LCDML_root_2      , 2  , "Group stop"   , LCDML_FUNC_group, 2);
  LCDML_DISP_addMenu  (14 , _LCDML_G1  , LCDML_root        , 3  , "Backend State-M.");
  LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_3      , 1  , "Start"        , LCDML_FUNC_state_start);
  LCDML_DISP_addMenu  (16 , _LCDML_G1  , LCDML_root        , 4  , "Backend Event");
  LCDML_DISP_add      (17 , _LCDML_G1  , LCDML_root_4      , 1  , "Trigger"      , LCDML_FUNC_trigger_event);
  LCDML_DISP_addMenu  (18 , _LCDML_G1  , LCDML_root        , 5  , "Backend Signals");
  LCDML_DISP_add      (19 , _LCDML_G1  , LCDML_root_5      , 1  , "Ping Pong"    , LCDML_FUNC_ping_pong);
  LCDML_DISP_addMenu  (20 , _LCDML_G1  , LCDML_root        , 6  , "Destroy System");
  LCDML_DISP_addMenu  (21 , _LCDML_G1  , LCDML_root_6      , 1  , "restart helps");
  LCDML_DISP_addMenu  (22 , _LCDML_G1  , LCDML_root_6      , 2  , "Kill");
  LCDML_DISP_addParam (23 , _LCDML_G1  , LCDML_root_6_2    , 1  , "stopp all"    , LCDML_FUNC_kill, 1);
  LCDML_DISP_addParam (24 , _LCDML_G1  , LCDML_root_6_2    , 2  , "restart all"  , LCDML_FUNC_kill, 2);
  LCDML_DISP_addParam (25 , _LCDML_G1  , LCDML_root_6_2    , 3  , "static init 0", LCDML_FUNC_kill, 3);
  LCDML_DISP_addParam (26 , _LCDML_G1  , LCDML_root_6_2    , 4  , "dyn set to 0" , LCDML_FUNC_kill, 4);
  // create Menu
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);


// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    16  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  // only for example - do not make this in your real program
  LCDML_BACK_new_timebased_static  (0  , ( 0UL )          , _LCDML_stop   , LCDML_BACKEND_kill_system_3);
  LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_kill_system_4);  
  // menu function and control function
  LCDML_BACK_new_timebased_dynamic (2  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (3  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);  
  // custom backend function
  // static time example
  LCDML_BACK_new_timebased_static  (4  , ( 500UL )        , _LCDML_stop   , LCDML_BACKEND_static);
  // dynamic time example
  LCDML_BACK_new_timebased_dynamic (5  , ( 4000UL )       , _LCDML_stop   , LCDML_BACKEND_dynamic);
  // groups example
  LCDML_BACK_new_timebased_static  (6  , ( 1533UL  )      , _LCDML_stop   , LCDML_BACKEND_ge1);
  LCDML_BACK_new_timebased_static  (7  , ( 2727UL  )      , _LCDML_stop   , LCDML_BACKEND_ge2);
  LCDML_BACK_new_timebased_static  (8  , ( 3918UL  )      , _LCDML_stop   , LCDML_BACKEND_ge3);
  // state maschine
  LCDML_BACK_new_timebased_static  (9  , ( 500UL  )       , _LCDML_stop   , LCDML_BACKEND_state_1);
  LCDML_BACK_new_timebased_static  (10 , ( 500UL  )       , _LCDML_stop   , LCDML_BACKEND_state_2);
  LCDML_BACK_new_timebased_static  (11 , ( 500UL  )       , _LCDML_stop   , LCDML_BACKEND_state_3);
  LCDML_BACK_new_timebased_static  (12 , ( 500UL  )       , _LCDML_stop   , LCDML_BACKEND_state_4);
  // event
  LCDML_BACK_new_eventbased        (13 ,                                    LCDML_BACKEND_event);
  // signals - ping pong
  LCDML_BACK_new_timebased_static  (14 , ( 2000UL  )      , _LCDML_stop   , LCDML_BACKEND_signals_ping);
  LCDML_BACK_new_timebased_static  (15 , ( 500UL  )       , _LCDML_stop   , LCDML_BACKEND_signals_pong);

  // this backend function is only for debug
  LCDML_BACK_new_timebased_static  (16 , ( 30000UL )      , _LCDML_start  , LCDML_BACKEND_idle);
  LCDML_BACK_create();


  // Groups
  // =========
  // for group example
  LCDML_BACK_group_init(GROUP_group_example, 3)
  {
    LCDML_BACK_group(LCDML_BACKEND_ge1),
    LCDML_BACK_group(LCDML_BACKEND_ge2),
    LCDML_BACK_group(LCDML_BACKEND_ge3),
  };
  
  // for state mashine 
  LCDML_BACK_group_init(GROUP_state_mashine, 4)
  {
    LCDML_BACK_group(LCDML_BACKEND_state_1),
    LCDML_BACK_group(LCDML_BACKEND_state_2),
    LCDML_BACK_group(LCDML_BACKEND_state_3),
    LCDML_BACK_group(LCDML_BACKEND_state_4),   
  };
  
  // for ping pong example
  LCDML_BACK_group_init(GROUP_ping_pong, 2)
  {
    LCDML_BACK_group(LCDML_BACKEND_signals_ping),
    LCDML_BACK_group(LCDML_BACKEND_signals_pong),
  };

  // Signals
  // ========
  // here are some signals defined
  /* beta 4
  LCDML_BACK_signal_init(2);
  LCDML_BACK_signal(0, signal_from_ping_to_pong);
  LCDML_BACK_signal(1, signal_from_pong_to_ping);
  */

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
  
    // Enable all items with _LCDML_G1 and _LCDML_G2
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
