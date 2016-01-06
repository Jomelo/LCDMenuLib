// =====================================================================
//
// CONTROL
//
// =====================================================================

// *********************************************************************
// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_control)      
// *********************************************************************
{
  // setup of this backend function is called only at first start or reset
  // you can init here pins or do nothing
   
  /*
  // control digital
    pinMode(_LCDML_CONTROL_digital_enter      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_up         , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_down       , INPUT_PULLUP);  
  # if(_LCDML_CONTROL_digital_enable_quit == 1)
      pinMode(_LCDML_CONTROL_digital_quit     , INPUT_PULLUP);
  # endif
  # if(_LCDML_CONTROL_digital_enable_lr == 1)
    pinMode(_LCDML_CONTROL_digital_left       , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_right      , INPUT_PULLUP);
  # endif
  */

  /*
  // control encoder
  
    pinMode(_LCDML_CONTROL_encoder_pin_a      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_encoder_pin_b      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_encoder_pin_button , INPUT_PULLUP);
  */
      
}

boolean LCDML_BACK_loop(LCDML_BACKEND_control)
{    
   // check control settings of lcdml
  
    LCDML_CONTROL_serial();           
 
   // LCDML_CONTROL_analog();     
 
    //LCDML_CONTROL_digital();     
 
    //LCDML_CONTROL_encoder();
 
    //LCDML_CONTROL_keypad();  
  
 
  return true;  
}

void LCDML_BACK_stable(LCDML_BACKEND_control)
{
}



// *********************************************************************
void LCDML_CONTROL_serial()
// *********************************************************************
{ 
  // settings
  # define _LCDML_CONTROL_serial_enter           'e'
  # define _LCDML_CONTROL_serial_up              'w'
  # define _LCDML_CONTROL_serial_down            's'
  # define _LCDML_CONTROL_serial_left            'a'
  # define _LCDML_CONTROL_serial_right           'd'
  # define _LCDML_CONTROL_serial_quit            'q'

  
  if (Serial.available()) {   
    switch (Serial.read())
    {
      case _LCDML_CONTROL_serial_enter:  LCDML_BUTTON_enter(); break;
      case _LCDML_CONTROL_serial_up:     LCDML_BUTTON_up();    break;
      case _LCDML_CONTROL_serial_down:   LCDML_BUTTON_down();  break;
      case _LCDML_CONTROL_serial_left:   LCDML_BUTTON_left();  break;
      case _LCDML_CONTROL_serial_right:  LCDML_BUTTON_right(); break;
      case _LCDML_CONTROL_serial_quit:   LCDML_BUTTON_quit();  break;
      default: break;
    } 
  }
}





/*
// *********************************************************************
void LCDML_CONTROL_analog()
// *********************************************************************
{  
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
  
  
  if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
    g_LCDML_DISP_press_time = millis(); // reset press time
    
    uint16_t value = analogRead(_LCDML_CONTROL_analog_pin);  // analogpin for keypad
    
    if (value >= _LCDML_CONTROL_analog_enter_min && value <= _LCDML_CONTROL_analog_enter_max) { LCDML_BUTTON_enter(); }
    if (value >= _LCDML_CONTROL_analog_up_min    && value <= _LCDML_CONTROL_analog_up_max)    { LCDML_BUTTON_up();    }
    if (value >= _LCDML_CONTROL_analog_down_min  && value <= _LCDML_CONTROL_analog_down_max)  { LCDML_BUTTON_down();  }
    if (value >= _LCDML_CONTROL_analog_left_min  && value <= _LCDML_CONTROL_analog_left_max)  { LCDML_BUTTON_left();  }
    if (value >= _LCDML_CONTROL_analog_right_min && value <= _LCDML_CONTROL_analog_right_max) { LCDML_BUTTON_right(); }
    if (value >= _LCDML_CONTROL_analog_back_min  && value <= _LCDML_CONTROL_analog_back_max)  { LCDML_BUTTON_quit();  }
  }
}
*/




/*
// *********************************************************************
void LCDML_CONTROL_digital()
// *********************************************************************
{  
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
  
  #if(_LCDML_CONTROL_digital_low_active == 1)
  #  define _LCDML_CONTROL_digital_a !
  #else
  #  define _LCDML_CONTROL_digital_a
  #endif
  
  uint8_t but_stat = 0x00;
  
  bitWrite(but_stat, 0, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_enter)));
  bitWrite(but_stat, 1, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_up)));
  bitWrite(but_stat, 2, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_down)));
  #if(_LCDML_CONTROL_digital_enable_quit == 1)
  bitWrite(but_stat, 3, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_quit)));
  #endif
  #if(_LCDML_CONTROL_digital_enable_lr == 1)
  bitWrite(but_stat, 4, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_left)));
  bitWrite(but_stat, 5, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_right)));
  #endif  
  
  if (but_stat > 0) {
    if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
      g_LCDML_DISP_press_time = millis(); // reset press time
    
      if (bitRead(but_stat, 0)) { LCDML_BUTTON_enter(); }
      if (bitRead(but_stat, 1)) { LCDML_BUTTON_up();    }
      if (bitRead(but_stat, 2)) { LCDML_BUTTON_down();  }
      if (bitRead(but_stat, 3)) { LCDML_BUTTON_quit();  }
      if (bitRead(but_stat, 4)) { LCDML_BUTTON_left();  }
      if (bitRead(but_stat, 5)) { LCDML_BUTTON_right(); }        
    }    
  }
}
*/



/*
// *********************************************************************
uint8_t  g_LCDML_CONTROL_encoder_t_prev = 0;
uint8_t  g_LCDML_CONTROL_encoder_a_prev = 0;
uint32_t g_LCDML_CONTROL_encoder_timer  = 0;
void LCDML_CONTROL_encoder()
// *********************************************************************
{ 
  // settings
  #define _LCDML_CONTROL_encoder_pin_a           10 // pin encoder b
  #define _LCDML_CONTROL_encoder_pin_b           11 // pin encoder a
  #define _LCDML_CONTROL_encoder_pin_button      12 // pin taster
  #define _LCDML_CONTROL_encoder_high_active     0  // (0 = low active (pullup), 1 = high active (pulldown)) button
                                                    // // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
  #define _LCDML_CONTROL_encoder_time            20

   
  // check encoder time
  if((millis() - g_LCDML_CONTROL_encoder_timer) >= _LCDML_CONTROL_encoder_time) {
    g_LCDML_CONTROL_encoder_timer = millis(); // reset encoder time
    
    // read encoder status
    unsigned char a = digitalRead(_LCDML_CONTROL_encoder_pin_a);
    unsigned char b = digitalRead(_LCDML_CONTROL_encoder_pin_b);
    unsigned char t = digitalRead(_LCDML_CONTROL_encoder_pin_button);
    
    // change button status if high and low active are switched
    if (_LCDML_CONTROL_encoder_high_active == 1) {
      t != t;
    }
    
    // check encoder status and set control menu
    if (!a && g_LCDML_CONTROL_encoder_a_prev) {
      g_LCDML_CONTROL_encoder_t_prev = 1;
      
      if (!b) { LCDML_BUTTON_up();   }
      else    { LCDML_BUTTON_down(); }            
    } 
    else {
      // check button press time for enter
      if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
        g_LCDML_DISP_press_time = millis(); // reset button press time
        
        // press button once
        if (!t && g_LCDML_CONTROL_encoder_t_prev == 0) {          
            LCDML_BUTTON_enter();          
        } 
        else {
          g_LCDML_CONTROL_encoder_t_prev = 0;
        }
      }      
    }
    g_LCDML_CONTROL_encoder_a_prev = a;  // set new encoder status 
  }
}
*/


/*
// *********************************************************************
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
// *********************************************************************
void LCDML_CONTROL_keypad()
// *********************************************************************
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '#': LCDML_BUTTON_enter(); break;
      case '2': LCDML_BUTTON_up();    break;
      case '8': LCDML_BUTTON_down();  break;
      case '4': LCDML_BUTTON_left();  break;
      case '6': LCDML_BUTTON_right(); break;
      case '*': LCDML_BUTTON_quit();  break;
      default: break;       
    }
  }  
}
*/



