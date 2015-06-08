// ============================================================ 
//                                                              
// Example: LCD Menu with LiquidCrystal                         
//                                                              
// for Arduino 1.0.x and 1.6.x with orginal Liquid Crystal Lib  
// ============================================================ 

// lib config
#define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
#define _LCDML_DISP_cfg_scrollbar	           1      // 0 = no scrollbar, 1 = scrollbar with custom chars
#define _LCDML_DISP_cfg_scrollbar_custom_redefine  0      // 0 = nothing, 1 = redefine custom chars on scrolling
#define _LCDML_DISP_cfg_lcd_standard	           0      // 0 = HD44780 standard / 1 = HD44780U standard
#define _LCDML_DISP_cfg_initscreen                 1
#define _LCDML_DISP_cfg_initscreen_time            30000

// ********************************************************************* 
// LCDML TYPE SELECT
// ********************************************************************* 

// include libs
// some extern libs needs this libs 
//#include <Wire.h>
//#include <DogLCD.h>
#include <LiquidCrystal.h>
#include <LCDMenuLib.h>


/* settings for lcd */
#define _LCDML_DISP_cols             20
#define _LCDML_DISP_rows             4

// pin settings
// when you are using an i2c display please load the i2c example
// (on beta v2 it is coming soon, on stable v2 it is included
#define _LCDML_DISP_rs               2
#define _LCDML_DISP_e                3
#define _LCDML_DISP_dat0             4
#define _LCDML_DISP_dat1             5
#define _LCDML_DISP_dat2             6
#define _LCDML_DISP_dat3             7

// optional 
//#define _LCDML_DISP_rw	     0
//#define _LCDML_DISP_backlight      7
//#define _LCDML_DISP_backlight_pol     POSITIVE // NEGATIVE
// 8 bit mode
//#define _LCDML_DISP_dat4          0
//#define _LCDML_DISP_dat5          0
//#define _LCDML_DISP_dat6          0
//#define _LCDML_DISP_dat7          0




     

// *********************************************************************
// LCDML CONTROL
// *********************************************************************  
// ======================
// serial lcdml control
// ======================
  // nothing change here
  #define _LCDML_DISP_cfg_control                0  // seriell
  void LCDML_CONTROL_serial(); 
  // settings
  #define _LCDML_CONTROL_serial_enter           'e'
  #define _LCDML_CONTROL_serial_up              'w'
  #define _LCDML_CONTROL_serial_down            's'
  #define _LCDML_CONTROL_serial_left            'a'
  #define _LCDML_CONTROL_serial_right           'd'
  #define _LCDML_CONTROL_serial_quit            'q'
  
/* 
// ======================
// analog lcdml control
// ======================
// nothing change here
#define _LCDML_DISP_cfg_control                1  // analog
void LCDML_CONTROL_analog();
// settings
#define _LCDML_CONTROL_analog_pin              0
// when you did not use a button set the value to zero
#define _LCDML_CONTROL_analog_enter_min        850     // Button Enter
#define _LCDML_CONTROL_analog_enter_max        920  
#define _LCDML_CONTROL_analog_up_min           520     // Button Up
#define _LCDML_CONTROL_analog_up_max           590   
#define _LCDML_CONTROL_analog_down_min         700     // Button Down
#define _LCDML_CONTROL_analog_down_max         770   
#define _LCDML_CONTROL_analog_back_min         950     // Button Back
#define _LCDML_CONTROL_analog_back_max         1020   
#define _LCDML_CONTROL_analog_left_min         430     // Button Left
#define _LCDML_CONTROL_analog_left_max         500   
#define _LCDML_CONTROL_analog_right_min        610     // Button Right
#define _LCDML_CONTROL_analog_right_max        680 
*/
  
/*
// ======================
// digital lcdml control
// ======================
// nothing change here
#define _LCDML_DISP_cfg_control                2  // digital
void LCDML_CONTROL_digital();
// settings
#define _LCDML_CONTROL_digital_low_active      0    // (0 = low active (pullup), 1 = high active (pulldown) button
                                                    // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
#define _LCDML_CONTROL_digital_enable_quit     1
#define _LCDML_CONTROL_digital_enable_lr       1

#define _LCDML_CONTROL_digital_enter           8    
#define _LCDML_CONTROL_digital_up              9
#define _LCDML_CONTROL_digital_down            10
#define _LCDML_CONTROL_digital_quit            11
#define _LCDML_CONTROL_digital_left            12
#define _LCDML_CONTROL_digital_right           13
*/
  
/*
// ======================
// encoder lcdml control
// ======================
// nothing change here 
void LCDML_CONTROL_encoder();
#define _LCDML_DISP_cfg_control                3  // encoder
// settings
#define _LCDML_CONTROL_encoder_pin_a           10 // pin encoder b
#define _LCDML_CONTROL_encoder_pin_b           11 // pin encoder a
#define _LCDML_CONTROL_encoder_pin_button      12 // pin taster
#define _LCDML_CONTROL_encoder_high_active     0  // (0 = low active (pullup), 1 = high active (pulldown)) button
                                                  // // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
#define _LCDML_CONTROL_encoder_time            20
*/
  
/*
// ======================
// keypad example lcdml control
// ======================
// nothing change here
void LCDML_CONTROL_keypad();
#define _LCDML_DISP_cfg_control                4  // encoder
// settings
// more information under http://playground.arduino.cc/Main/KeypadTutorial
#include <Keypad.h>
#define _LCDML_CONTROL_keypad_rows = 4; // Four rows
#define _LCDML_CONTROL_keypad_cols = 3; // Three columns
char keys[_LCDML_CONTROL_keypad_rows][_LCDML_CONTROL_keypad_cols] = { 
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};  
byte rowPins[_LCDML_CONTROL_keypad_rows] = { 9, 8, 7, 6 };  // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[_LCDML_CONTROL_keypad_cols] = { 12, 11, 10 };  // Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, _LCDML_CONTROL_keypad_rows, _LCDML_CONTROL_keypad_cols );
*/




// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************


// create menu
// menu element count - last element id
#define _LCDML_DISP_cnt    39


// root           => layer 0 
// root_XX        => layer 1 
// root_XX_XX     => layer 2 
// root_XX_XX_XX  => layer 3 
// root_... 	  => layer ... 
// init lcdmenulib 


//LCDML_DISP_init(_LCDML_DISP_cnt);    // 
LCDML_DISP_initParam(_LCDML_DISP_cnt); // can save flash memory on big menus, needs _LCDML_DISP_cnt Bytes more ram
                                       // it is usefull to reduce the code

// LCDMenuLib_element(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Information"        , LCDML_FUNC_information);
LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Time info"          , LCDML_FUNC_timer_info);
LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root        , 3  , "Settings"           , LCDML_FUNC);
LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_3      , 1  , "Change value"       , LCDML_FUNC);
LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_3      , 2  , "Something"          , LCDML_FUNC);
LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root_3      , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (6  , _LCDML_G2  , LCDML_root        , 4  , "Program"            , LCDML_FUNC);
LCDML_DISP_add      (7  , _LCDML_G2  , LCDML_root_4      , 1  , "Program 1"          , LCDML_FUNC);
LCDML_DISP_add      (8  , _LCDML_G2  , LCDML_root_4_1    , 1  , "P1 start"           , LCDML_FUNC);
LCDML_DISP_add      (9  , _LCDML_G2  , LCDML_root_4_1    , 2  , "Settings"           , LCDML_FUNC);
LCDML_DISP_add      (10 , _LCDML_G2  , LCDML_root_4_1_2  , 1  , "Warm"               , LCDML_FUNC);
LCDML_DISP_add      (11 , _LCDML_G2  , LCDML_root_4_1_2  , 2  , "Long"               , LCDML_FUNC);
LCDML_DISP_add      (12 , _LCDML_G2  , LCDML_root_4_1_2  , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (13 , _LCDML_G2  , LCDML_root_4_1    , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (14 , _LCDML_G2  , LCDML_root_4      , 2  , "Program 2"          , LCDML_FUNC_p2);
LCDML_DISP_add      (15 , _LCDML_G2  , LCDML_root_4      , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (16 , _LCDML_G1  , LCDML_root        , 5  , "Menu-Mode"          , LCDML_FUNC);
LCDML_DISP_add      (17 , _LCDML_G2  , LCDML_root_5      , 1  , "disable program"    , LCDML_FUNC_prog_disable);
LCDML_DISP_add      (18 , _LCDML_G3  , LCDML_root_5      , 2  , "enable program"     , LCDML_FUNC_prog_enable);
LCDML_DISP_add      (19 , _LCDML_G1  , LCDML_root_5      , 3  , "back"               , LCDML_FUNC_back);
LCDML_DISP_add      (20 , _LCDML_G1  , LCDML_root        , 6  , "Set Clock"          , LCDML_FUNC_set_date);
LCDML_DISP_add      (21 , _LCDML_G7  , LCDML_root        , 7  , "InitScreen"         , LCDML_FUNC_initscreen); 
LCDML_DISP_add      (22 , _LCDML_G1  , LCDML_root        , 8  , "Backend-Control"    , LCDML_FUNC);
LCDML_DISP_add      (23 , _LCDML_G1  , LCDML_root_8      , 1  , "Test 10"            , LCDML_FUNC);
LCDML_DISP_addParam (24 , _LCDML_G1  , LCDML_root_8_1    , 1  , "Start"              , LCDML_FUNC_backend_control, 1);
LCDML_DISP_addParam (25 , _LCDML_G1  , LCDML_root_8_1    , 2  , "Restart"            , LCDML_FUNC_backend_control, 2);
LCDML_DISP_addParam (26 , _LCDML_G1  , LCDML_root_8_1    , 3  , "Stop"               , LCDML_FUNC_backend_control, 3);
LCDML_DISP_addParam (27 , _LCDML_G1  , LCDML_root_8_1    , 4  , "Stop stable"        , LCDML_FUNC_backend_control, 4);
LCDML_DISP_add      (28 , _LCDML_G1  , LCDML_root_8_1    , 5  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (29 , _LCDML_G1  , LCDML_root_8      , 2  , "Test 20"            , LCDML_FUNC);
LCDML_DISP_addParam (30 , _LCDML_G1  , LCDML_root_8_2    , 1  , "Start"              , LCDML_FUNC_backend_control, 10);
LCDML_DISP_addParam (31 , _LCDML_G1  , LCDML_root_8_2    , 2  , "Stop"               , LCDML_FUNC_backend_control, 11);
LCDML_DISP_add      (32 , _LCDML_G1  , LCDML_root_8_2    , 3  , "Change runtime"     , LCDML_FUNC);
LCDML_DISP_addParam (33 , _LCDML_G1  , LCDML_root_8_2_3  , 1  , "500 ms"             , LCDML_FUNC_backend_control, 12);
LCDML_DISP_addParam (34 , _LCDML_G1  , LCDML_root_8_2_3  , 2  , "1 s"                , LCDML_FUNC_backend_control, 13);
LCDML_DISP_addParam (35 , _LCDML_G1  , LCDML_root_8_2_3  , 3  , "10 s"               , LCDML_FUNC_backend_control, 14);
LCDML_DISP_add      (36 , _LCDML_G1  , LCDML_root_8_2_3  , 4  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (37 , _LCDML_G1  , LCDML_root_8_2    , 4  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_addParam (38 , _LCDML_G1  , LCDML_root_8      , 3  , "Test 30"            , LCDML_FUNC_backend_control, 20);
LCDML_DISP_add      (39 , _LCDML_G1  , LCDML_root_8      , 4  , "Back"               , LCDML_FUNC_back);

LCDML_DISP_createMenu(_LCDML_DISP_cnt);


// ********************************************************************* 
// LCDML BACKEND
// ********************************************************************* 
// define backend function 
// to do:  add documentation and comments 
#define _LCDML_BACK_cnt    4  // last backend function id

LCDML_BACK_init(_LCDML_BACK_cnt);
LCDML_BACK_new_timebased_static  (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
/* own backend function */
LCDML_BACK_new_timebased_static  (2  , ( 1000UL * 10UL ), _LCDML_start  , LCDML_BACKEND_test10);
LCDML_BACK_new_timebased_dynamic (3  , ( 1000UL * 20UL ), _LCDML_stop   , LCDML_BACKEND_test20);
LCDML_BACK_new_eventbased        (4                                     , LCDML_BACKEND_test30);
LCDML_BACK_create();


// *********************************************************************
// SETUP
// *********************************************************************

void setup()
{  
  // serial init; only be needed 
  Serial.begin(9600);   // start serial
  
  LCDML_DISP_groupEnable(_LCDML_G1);
  LCDML_DISP_groupEnable(_LCDML_G2);  
  
  LCDML_setup(_LCDML_BACK_cnt);    
}

// *********************************************************************
// LOOP
// *********************************************************************

void loop()
{ 
  // example for init screen
  #if (_LCDML_DISP_cfg_initscreen == 1)
  if((millis() - g_lcdml_initscreen) >= _LCDML_DISP_cfg_initscreen_time) {
    g_lcdml_initscreen = millis(); // reset init screen time
    LCDML_DISP_jumpToFunc(LCDML_FUNC_initscreen); // jump to initscreen     
  }  
  #endif
 

  // this function must called here, do not delete it
  LCDML_run(_LCDML_priority); 
}
