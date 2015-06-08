// ============================================================ 
//                                                              
// Example: (easy) LCDML Diffrent control options 
//			(serial, analog, digital, keypad, encoder)                         
//                                                              
// ============================================================ 

// include libs
#include <LiquidCrystal.h>
#include <LCDMenuLib.h>

// lib config
#define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms
#define _LCDML_DISP_cfg_scrollbar	           	   1      // 0 = no scrollbar, 1 = scrollbar with custom chars
#define _LCDML_DISP_cfg_scrollbar_custom_redefine  0      // 0 = nothing, 1 = redefine custom chars on scrolling
#define _LCDML_DISP_cfg_lcd_standard	           0      // 0 = HD44780 standard / 1 = HD44780U standard
#define _LCDML_DISP_cfg_initscreen                 0      // this screen is not implemented in this example
#define _LCDML_DISP_cfg_initscreen_time            30000  // has in this example no effekt

// ********************************************************************* 
// LCDML TYPE SELECT
// ********************************************************************* 

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
// this value must be the same as the last menu element
#define _LCDML_DISP_cnt    15


// LCDML_root        => layer 0 
// LCDML_root_X      => layer 1 
// LCDML_root_X_X    => layer 2 
// LCDML_root_X_X_X  => layer 3 
// LCDML_root_... 	 => layer ... 

// init lcdmenulib 
LCDML_DISP_init(_LCDML_DISP_cnt);

// LCDMenuLib_element(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Information"        , LCDML_FUNC_information);
LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Time info"          , LCDML_FUNC_timer_info);
LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root        , 3  , "Settings"           , LCDML_FUNC);
LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_3      , 1  , "Change value"       , LCDML_FUNC);
LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_3      , 2  , "Something"          , LCDML_FUNC);
LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root_3      , 3  , "Back"               , LCDML_FUNC_back); // to go a layer back with encoder
LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root        , 4  , "Program"            , LCDML_FUNC);
LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_4      , 1  , "Program 1"          , LCDML_FUNC);
LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_4_1    , 1  , "P1 start"           , LCDML_FUNC);
LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_4_1    , 2  , "Settings"           , LCDML_FUNC);
LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_4_1_2  , 1  , "Warm"               , LCDML_FUNC);
LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_4_1_2  , 2  , "Long"               , LCDML_FUNC);
LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root_4_1_2  , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root_4_1    , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add      (14 , _LCDML_G1  , LCDML_root_4      , 2  , "Program 2"          , LCDML_FUNC_p2);
LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root_4      , 3  , "Back"               , LCDML_FUNC_back);

LCDML_DISP_createMenu(_LCDML_DISP_cnt);


// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
// define backend function  
#define _LCDML_BACK_cnt    1  // last backend function id

LCDML_BACK_init(_LCDML_BACK_cnt);
LCDML_BACK_new_timebased_static  (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
LCDML_BACK_new_timebased_dynamic (1  , ( 1000UL )       , _LCDML_stop   , LCDML_BACKEND_menu);
LCDML_BACK_create();


// *********************************************************************
// SETUP
// *********************************************************************
void setup()
{  
  // serial init; only be needed 
  Serial.begin(9600);   // start serial
  
  LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1
  
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