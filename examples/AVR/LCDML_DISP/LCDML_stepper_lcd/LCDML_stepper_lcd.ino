// ============================================================                                                            
// Example:     LCDML: display liquid crystal                         
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 08.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton:  
// This example shows you, how to use this lib with LiquidCrystal
// lib. The LCD object have to create in this tab. In "LCDML_DISO"
// you can edit the layout of the menu. (content, cursor, scrollbar)
//
// When you rewrite this function, you can use every other LCD 
// or graphic LCD Lib with this menu.
// ============================================================ 

  // include libs
  #include <LiquidCrystal.h>
  #include <LCDMenuLib.h>
  #include <AccelStepper.h>
  
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
  LiquidCrystal lcd(16, 17, 23, 25 , 27, 29);  
  
  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1 
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  }; 
  
// ********************************************************************* 
// Stepper Objects and global variables
// ********************************************************************* 
AccelStepper stepper1(AccelStepper::DRIVER, 54, 55); // RAMPS PINS 54 STEP 55 DIRECTION
const int enableDriver = 38; // enable driver pin

char g_stepper_1_mode = 0;
char g_stepper_2_mode = 0;

const float stepper1SetAcceleration = 2000;
const int stepper1SpeedArray[24]={0,1,2,4,8,16,32,64,128,256,512,768,1024,1280,1536,1792,2048,2304,2560,2816,3072,3328,3584,3840};
const char *stepper1TimeArray[24]={"0.00","450.00","225.00","112.30","56.15","28.07","14.03","7.10","3.30","1.45","00.53","00.35",
                                   "00.26","00.21","00.18","00.15","00.13","00.12","00.11","00.10","00.09","00.08","00.07","00.07"};
const long sliderHomePosition = 0;
const long sliderTotalSteps = 27000;

int g_button_value = 0; // button value counter (global variable)
float stepper1CurrentSpeed = 0;

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    4
  
  // LCDML_root        => layer 0 
  // LCDML_root_X      => layer 1 
  // LCDML_root_X_X    => layer 2 
  // LCDML_root_X_X_X  => layer 3 
  // LCDML_root_... 	 => layer ... 
  
  // LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  LCDML_DISP_init(_LCDML_DISP_cnt);
  LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Manual"             , LCDML_FUNC_MANUAL);
  LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Automatic"          , LCDML_FUNC);
  LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root_2      , 1  , "Display Running"    , LCDML_FUNC_DISPLAY_RUN);
  LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_2      , 2  , "Set Speed"          , LCDML_FUNC_SET_SPEED);
  LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_2      , 3  , "Back     "          , LCDML_FUNC_back);

  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    2  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_static  (0  , ( 0UL )          , _LCDML_stop   , LCDML_BACKEND_stepper1);  
  LCDML_BACK_new_timebased_dynamic (1  , ( 10UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (2  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
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
  
    // LCDMenu Setup
    LCDML_setup(_LCDML_BACK_cnt); 

    // Stepper Motor Setup
    stepper1.setCurrentPosition(sliderHomePosition);

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
