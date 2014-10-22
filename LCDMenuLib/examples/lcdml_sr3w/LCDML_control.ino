/* =============================================== */
/* Example 1: LCD Menu with LiquidCrystal          */ 
/* =============================================== */
/* file content:                                   */
/* - LCDMenuLib_control_analog()                   */
/* - LCDMenuLib_control_digital()                  */
/* - LCDMenuLib_control_seriel()                   */
/* =============================================== */

/* analog menu control */
void LCDMenuLib_control_analog()
{
  uint16_t value = analogRead(0);  // analogpin for keypad

  #define _BUTTON_analog_enter_min     850     // Button Enter
  #define _BUTTON_analog_enter_max     920  
  #define _BUTTON_analog_up_min        520     // Button Up
  #define _BUTTON_analog_up_max        590   
  #define _BUTTON_analog_down_min      700     // Button Down
  #define _BUTTON_analog_down_max      770   
  //optional if menu element "back" exists, look at FUNC_back in functions tab 
  #define _BUTTON_analog_enable_quit   1
  #define _BUTTON_analog_back_min      950     // Button Back
  #define _BUTTON_analog_back_max      1020   
  //optional if needed
  #define _BUTTON_analog_enable_lr     1
  #define _BUTTON_analog_left_min      430     // Button Left
  #define _BUTTON_analog_left_max      500   
  #define _BUTTON_analog_right_min     610     // Button Right
  #define _BUTTON_analog_right_max     680   
      
  if(LCDML.Timer(g_LCDMenuLib_press_time, _LCDMenuLib_cfg_press_time)) {
    if(value >= _BUTTON_analog_enter_min && value <= _BUTTON_analog_enter_max) {        // control enter
      LCDML.Button_enter();
    }  
    else if(value >= _BUTTON_analog_up_min && value <= _BUTTON_analog_up_max) {      // control up
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_up);
    } 
    else if(value >= _BUTTON_analog_down_min && value <= _BUTTON_analog_down_max) {   // control down
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_down);
    }    
    else if(value >= _BUTTON_analog_left_min && value <= _BUTTON_analog_left_max && _BUTTON_analog_enable_lr == 1) {   // control left
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_left);
    } 
    else if(value >= _BUTTON_analog_right_min && value <= _BUTTON_analog_right_max && _BUTTON_analog_enable_lr == 1) { // control right
      LCDML.Button_up_down_left_right(_LCDMenuLib_button_right);
    }
        
    if(value >= _BUTTON_analog_back_min && value <= _BUTTON_analog_back_max && _BUTTON_analog_enable_quit == 1) {          // control quit
      LCDML.Button_quit();
    }
  }
}

void LCDMenuLib_control_digital()
{
  #define _BUTTON_digital_enter         8    
  #define _BUTTON_digital_up            9
  #define _BUTTON_digital_down          10
  //optional
  #define _BUTTON_digital_enable_quit   1
  #define _BUTTON_digital_quit          11
  //optional
  #define _BUTTON_digital_enable_lr     1
  #define _BUTTON_digital_left          12
  #define _BUTTON_digital_right         13
  
  if(digitalRead(_BUTTON_digital_enter) || digitalRead(_BUTTON_digital_up) || digitalRead(_BUTTON_digital_down)
    || (digitalRead(_BUTTON_digital_quit) && _BUTTON_digital_enable_quit == 1)
    || ((digitalRead(_BUTTON_digital_left) || digitalRead(_BUTTON_digital_right)) && _BUTTON_digital_enable_lr == 1))
  {
     if(LCDML.Timer(g_LCDMenuLib_press_time, _LCDMenuLib_cfg_press_time)) 
     {
       if(digitalRead(_BUTTON_digital_enter)) { LCDML.Button_enter(); }
       else if(digitalRead(_BUTTON_digital_up)) { LCDML.Button_up_down_left_right(_LCDMenuLib_button_up); }
       else if(digitalRead(_BUTTON_digital_down)) { LCDML.Button_up_down_left_right(_LCDMenuLib_button_down); }
       else if(digitalRead(_BUTTON_digital_quit) && _BUTTON_digital_enable_quit == 1) {LCDML.Button_quit(); }
       else if(digitalRead(_BUTTON_digital_left) && _BUTTON_digital_enable_lr == 1) { LCDML.Button_up_down_left_right(_LCDMenuLib_button_left);}
       else if(digitalRead(_BUTTON_digital_right) && _BUTTON_digital_enable_lr == 1) { LCDML.Button_up_down_left_right(_LCDMenuLib_button_right);}       
     }
  }  
}


/* serial menu control */
void LCDMenuLib_control_serial()
{
  if(Serial.available()) {
    if(LCDML.Timer(g_LCDMenuLib_press_time, _LCDMenuLib_cfg_press_time)) {
      switch(Serial.read()) {
        case 'e': LCDML.Button_enter(); break;
        case 'w': LCDML.Button_up_down_left_right(_LCDMenuLib_button_up); break;
        case 's': LCDML.Button_up_down_left_right(_LCDMenuLib_button_down); break;
        case 'a': LCDML.Button_up_down_left_right(_LCDMenuLib_button_left); break;
        case 'd': LCDML.Button_up_down_left_right(_LCDMenuLib_button_right); break;       
        case 'q': LCDML.Button_quit(); break;
        default: break; 
      }
    }
  }
}



