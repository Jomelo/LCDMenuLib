// ============================================================                                                            
// Example:     LCDML_serialmonitor with stepper                          
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 12.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton: 
// This examples works with a serial menu (baudrate 250000) 
// The content is a stepper control for two steppers with 
// hidden menu elements and parametern
// ============================================================ 

  // include libs
  #include <LCDMenuLib.h>
  #include <AccelStepper.h>


  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms

// ********************************************************************* 
// LCDML TYPE SELECT
// *********************************************************************
  // settings for lcd 
  #define _LCDML_DISP_cols             20
  #define _LCDML_DISP_rows             4 


// ********************************************************************* 
// Stepper Objects and global variables
// ********************************************************************* 
  AccelStepper stepper1; // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
  AccelStepper stepper2(AccelStepper::FULL4WIRE, 6, 7, 8, 9);
  char g_stepper_1_mode = 0;
  char g_stepper_2_mode = 0;
  
// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    10
  
  // LCDML_root        => layer 0 
  // LCDML_root_X      => layer 1 
  // LCDML_root_X_X    => layer 2 
  // LCDML_root_X_X_X  => layer 3 
  // LCDML_root_... 	 => layer ... 
  
  // LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  LCDML_DISP_initParam(_LCDML_DISP_cnt);
  LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Stepper"          , LCDML_FUNC);
  LCDML_DISP_addParam (1  , _LCDML_G2  , LCDML_root_1      , 1  , "Stepper 1 on"     , LCDML_FUNC_stepper_on  ,    1);
  LCDML_DISP_addParam (2  , _LCDML_G3  , LCDML_root_1      , 2  , "Stepper 1 off"    , LCDML_FUNC_stepper_off ,    1);
  LCDML_DISP_addParam (3  , _LCDML_G4  , LCDML_root_1      , 3  , "Stepper 2 on"     , LCDML_FUNC_stepper_on  ,    2);
  LCDML_DISP_addParam (4  , _LCDML_G5  , LCDML_root_1      , 4  , "Stepper 2 off"    , LCDML_FUNC_stepper_off ,    2);
  LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root        , 2  , "Stepper 1 Mode"   , LCDML_FUNC);
  LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root_2      , 1  , "Only speed"       , LCDML_FUNC);
  LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_2      , 2  , "Position"         , LCDML_FUNC);
  LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root        , 3  , "Stepper 2 Mode"   , LCDML_FUNC);
  LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_3      , 1  , "Only speed"       , LCDML_FUNC);
  LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_3      , 2  , "Position"         , LCDML_FUNC);
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    2  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_static  (0  , ( 0UL )          , _LCDML_start  , LCDML_BACKEND_stepper); // set here the time to null and use in backend loop the return value with true
  LCDML_BACK_new_timebased_dynamic (1  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (2  , ( 10000000UL )   , _LCDML_stop   , LCDML_BACKEND_menu);
  LCDML_BACK_create();

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {  
    // serial init; only be needed if serial control is used     
    Serial.begin(250000);                // start serial    
    Serial.println(F(_LCDML_VERSION)); // only for examples
      
    // Enable all items with _LCDML_G1
    LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1
    LCDML_DISP_groupEnable(_LCDML_G2); // stepper 1 off on startup
    LCDML_DISP_groupEnable(_LCDML_G4); // stepper 2 off on startup
    
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
