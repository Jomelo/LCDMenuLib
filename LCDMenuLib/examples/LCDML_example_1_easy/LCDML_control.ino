/* ******************************************************************** */
/*                      LCDMenuLib (CONTROL)				*/
/*                                                                      */
/* ******************************************************************** */


/* ********************************************************************* */
/* Control: Seriel
/* ********************************************************************* */ 
#if (_LCDML_DISP_cfg_control == 0)
void LCDML_CONTROL_serial()
/* ********************************************************************* */
{
  // check if data available
  if (Serial.available()) {  
    // read one char from buffer and set control menu
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



/* ********************************************************************* */
/* Control: Analog with one pin                                          */
/* (different resitors values are needed for any button                  */
/* ********************************************************************* */ 
#elif (_LCDML_DISP_cfg_control == 1)
void LCDML_CONTROL_analog()
/* ********************************************************************* */
{
  // read analog pin value
  uint16_t value = analogRead(_LCDML_CONTROL_analog_pin);  // analogpin for keypad  
  
  // check button press time
  if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
    g_LCDML_DISP_press_time = millis(); // reset press time
    
    // check different values and control menu
    if (value >= _LCDML_CONTROL_analog_enter_min && value <= _LCDML_CONTROL_analog_enter_max) { 
      // control enter
      LCDML_BUTTON_enter();
    }
    else if (value >= _LCDML_CONTROL_analog_up_min && value <= _LCDML_CONTROL_analog_up_max) { 
      // control up
      LCDML_BUTTON_up();
    }
    else if (value >= _LCDML_CONTROL_analog_down_min && value <= _LCDML_CONTROL_analog_down_max) { 
      // control down
      LCDML_BUTTON_down();
    }
    else if (value >= _LCDML_CONTROL_analog_left_min && value <= _LCDML_CONTROL_analog_left_max && _LCDML_CONTROL_analog_enable_lr == 1) { 
      // control left
      LCDML_BUTTON_left();
    }
    else if (value >= _LCDML_CONTROL_analog_right_min && value <= _LCDML_CONTROL_analog_right_max && _LCDML_CONTROL_analog_enable_lr == 1) { 
      // control right
      LCDML_BUTTON_right();
    }

    if (value >= _LCDML_CONTROL_analog_back_min && value <= _LCDML_CONTROL_analog_back_max && _LCDML_CONTROL_analog_enable_quit == 1) { 
      // control quit
      LCDML_BUTTON_quit();
    }
  }
}



/* ********************************************************************* */
/* Control: Digital every button need one arduino input                  */
/* ********************************************************************* */ 
#elif(_LCDML_DISP_cfg_control == 2)
void LCDML_CONTROL_digital()
/* ********************************************************************* */
{
  // check arduino inputs
  if (digitalRead(_LCDML_CONTROL_digital_enter) || digitalRead(_LCDML_CONTROL_digital_up) || digitalRead(_LCDML_CONTROL_digital_down)
      || (digitalRead(_LCDML_CONTROL_digital_quit) && _LCDML_CONTROL_digital_enable_quit == 1)
      || ((digitalRead(_LCDML_CONTROL_digital_left) || digitalRead(_LCDML_CONTROL_digital_right)) && _LCDML_CONTROL_digital_enable_lr == 1))
  {
    // check button presstime
    if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
      g_LCDML_DISP_press_time = millis(); // reset press time
      
      // check inputs and control menu
      if (digitalRead(_LCDML_CONTROL_digital_enter)) {
        LCDML_BUTTON_enter();        
      }
      else if (digitalRead(_LCDML_CONTROL_digital_up)) {
        LCDML_BUTTON_up();
      }
      else if (digitalRead(_LCDML_CONTROL_digital_down)) {
        LCDML_BUTTON_down();
      }
      else if (digitalRead(_LCDML_CONTROL_digital_quit) && _LCDML_CONTROL_digital_enable_quit == 1) {
        LCDML_BUTTON_quit();        
      }
      else if (digitalRead(_LCDML_CONTROL_digital_left) && _LCDML_CONTROL_digital_enable_lr == 1) {
        LCDML_BUTTON_left();
      }
      else if (digitalRead(_LCDML_CONTROL_digital_right) && _LCDML_CONTROL_digital_enable_lr == 1) {
        LCDML_BUTTON_right();
      }      
    }    
  }
}


/* ********************************************************************* */
/* Control: Encoder                                                      */
/* ********************************************************************* */
#elif(_LCDML_DISP_cfg_control == 3)
uint8_t  g_LCDML_CONTROL_encoder_t_prev = 0;
uint8_t  g_LCDML_CONTROL_encoder_a_prev = 0;
uint32_t g_LCDML_CONTROL_encoder_timer  = 0;
void LCDML_CONTROL_encoder()
/* ********************************************************************* */
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
      
      if (!b) {
        LCDML_BUTTON_up();
      }
      else {
        LCDML_BUTTON_down();
      }            
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
#endif







