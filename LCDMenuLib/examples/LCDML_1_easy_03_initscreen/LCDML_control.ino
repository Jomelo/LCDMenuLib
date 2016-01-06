
// *********************************************************************
#if(_LCDML_DISP_cfg_control == 0)
void LCDML_CONTROL_serial()
// *********************************************************************
{  
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

// *********************************************************************
#elif (_LCDML_DISP_cfg_control == 1)
void LCDML_CONTROL_analog()
// *********************************************************************
{  
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



// *********************************************************************
#elif(_LCDML_DISP_cfg_control == 2)
void LCDML_CONTROL_digital()
// *********************************************************************
{  
  //#if(_LCDML_CONTROL_digital_low_active == 1)
  //#  define _LCDML_CONTROL_digital_a !
  //#else
  #define _LCDML_CONTROL_digital_a
  //#endif
  
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


// *********************************************************************
#elif(_LCDML_DISP_cfg_control == 3)
uint8_t  g_LCDML_CONTROL_encoder_t_prev = 0;
uint8_t  g_LCDML_CONTROL_encoder_a_prev = 0;
uint32_t g_LCDML_CONTROL_encoder_timer  = 0;
void LCDML_CONTROL_encoder()
// *********************************************************************
{  
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


// *********************************************************************
#elif(_LCDML_DISP_cfg_control == 4)
// more information under http://playground.arduino.cc/Main/KeypadTutorial
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
#endif
