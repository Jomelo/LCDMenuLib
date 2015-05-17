
/* ********************************************************************* */
#if (_LCDML_DISP_cfg_control == 0)
void LCDML_CONTROL_serial()
/* ********************************************************************* */
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

/* ********************************************************************* */
#elif (_LCDML_DISP_cfg_control == 1)
void LCDML_CONTROL_analog()
/* ********************************************************************* */
{
  uint16_t value = analogRead(_LCDML_CONTROL_analog_pin);  // analogpin for keypad

  if (LCDML.Timer(g_LCDML_DISP_press_time, _LCDML_DISP_cfg_button_press_time)) {
    if (value >= _LCDML_CONTROL_analog_enter_min && value <= _LCDML_CONTROL_analog_enter_max) { // control enter
      LCDML_BUTTON_enter();
    }
    else if (value >= _LCDML_CONTROL_analog_up_min && value <= _LCDML_CONTROL_analog_up_max) { // control up
      LCDML_BUTTON_up();
    }
    else if (value >= _LCDML_CONTROL_analog_down_min && value <= _LCDML_CONTROL_analog_down_max) { // control down
      LCDML_BUTTON_down();
    }
    else if (value >= _LCDML_CONTROL_analog_left_min && value <= _LCDML_CONTROL_analog_left_max && _LCDML_CONTROL_analog_enable_lr == 1) { // control left
      LCDML_BUTTON_left();
    }
    else if (value >= _LCDML_CONTROL_analog_right_min && value <= _LCDML_CONTROL_analog_right_max && _LCDML_CONTROL_analog_enable_lr == 1) { // control right
      LCDML_BUTTON_right();
    }

    if (value >= _LCDML_CONTROL_analog_back_min && value <= _LCDML_CONTROL_analog_back_max && _LCDML_CONTROL_analog_enable_quit == 1) { // control quit
      LCDML_BUTTON_quit();
    }
  }
}



/* ********************************************************************* */
#elif(_LCDML_DISP_cfg_control == 2)
void LCDML_CONTROL_digital()
/* ********************************************************************* */
{
  if (digitalRead(_LCDML_CONTROL_digital_enter) || digitalRead(_LCDML_CONTROL_digital_up) || digitalRead(_LCDML_CONTROL_digital_down)
      || (digitalRead(_LCDML_CONTROL_digital_quit) && _LCDML_CONTROL_digital_enable_quit == 1)
      || ((digitalRead(_LCDML_CONTROL_digital_left) || digitalRead(_LCDML_CONTROL_digital_right)) && _LCDML_CONTROL_digital_enable_lr == 1))
  {
    if (LCDML.Timer(g_LCDML_DISP_press_time, _LCDML_DISP_cfg_button_press_time)) {
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
#elif(_LCDML_DISP_cfg_control == 3)
uint8_t  g_LCDML_CONTROL_encoder_t_prev = 0;
uint8_t  g_LCDML_CONTROL_encoder_a_prev = 0;
uint32_t g_LCDML_CONTROL_encoder_timer  = 0;
void LCDML_CONTROL_encoder()
/* ********************************************************************* */
{
  if (LCDML.Timer(g_LCDML_CONTROL_encoder_timer, _LCDML_CONTROL_encoder_time)) {    
    unsigned char a = digitalRead(_LCDML_CONTROL_encoder_pin_a);
    unsigned char b = digitalRead(_LCDML_CONTROL_encoder_pin_b);
    unsigned char t = digitalRead(_LCDML_CONTROL_encoder_pin_button);

    if (_LCDML_CONTROL_encoder_high_active == 1) {
      t != t;
    }

    if (!a && g_LCDML_CONTROL_encoder_a_prev) {
      g_LCDML_CONTROL_encoder_t_prev = 1;
      if (!t) {
        if (!b) {
          LCDML_BUTTON_right();
        }
        else {
          LCDML_BUTTON_left();
        }
      }
      else {
        if (!b) {
          LCDML_BUTTON_up();
        }
        else {
          LCDML_BUTTON_down();
        }
      }      
    } 
    else {
      if (LCDML.Timer(g_LCDML_DISP_press_time, _LCDML_DISP_cfg_button_press_time)) {
        if (!t && g_LCDML_CONTROL_encoder_t_prev == 0) {          
            LCDML_BUTTON_enter();          
        } 
        else {
          g_LCDML_CONTROL_encoder_t_prev = 0;
        }
      }      
    }
    g_LCDML_CONTROL_encoder_a_prev = a;   
  }
}
#endif







