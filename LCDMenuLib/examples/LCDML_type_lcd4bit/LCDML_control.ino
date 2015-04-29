
/* ********************************************************************* */
#if (_LCDML_DISP_cfg_control == 0)
void LCDML_control_serial()
/* ********************************************************************* */
{
  if (Serial.available())
  {
    switch (Serial.read())
    {
      case _LCDML_CONTROL_serial_enter:  LCDML.Button_enter(); LCDML_BACK_reset(LCDML_BACKEND_menu); break;
      case _LCDML_CONTROL_serial_up:     LCDML.Button_up_down_left_right(_LCDML_button_up); break;
      case _LCDML_CONTROL_serial_down:   LCDML.Button_up_down_left_right(_LCDML_button_down); break;
      case _LCDML_CONTROL_serial_left:   LCDML.Button_up_down_left_right(_LCDML_button_left); break;
      case _LCDML_CONTROL_serial_right:  LCDML.Button_up_down_left_right(_LCDML_button_right); break;
      case _LCDML_CONTROL_serial_quit:   LCDML.Button_quit(); break;
      default: break;
    }    
    LCDML_UPDATE();    
  }
}

/* ********************************************************************* */
#elif (_LCDML_DISP_cfg_control == 1)
void LCDML_control_analog()
/* ********************************************************************* */
{
  uint16_t value = analogRead(_LCDML_CONTROL_analog_pin);  // analogpin for keypad

  if (LCDML.Timer(g_LCDML_DISP_press_time, _LCDML_DISP_cfg_button_press_time))
  {
    if (value >= _LCDML_CONTROL_analog_enter_min && value <= _LCDML_CONTROL_analog_enter_max)
    { // control enter
      LCDML.Button_enter();
      LCDML_BACK_reset(LCDML_BACKEND_menu);
      LCDML_UPDATE();
    }
    else if (value >= _LCDML_CONTROL_analog_up_min && value <= _LCDML_CONTROL_analog_up_max)
    { // control up
      LCDML.Button_up_down_left_right(_LCDML_button_up);
      LCDML_UPDATE();
    }
    else if (value >= _LCDML_CONTROL_analog_down_min && value <= _LCDML_CONTROL_analog_down_max)
    { // control down
      LCDML.Button_up_down_left_right(_LCDML_button_down);
      LCDML_UPDATE();
    }
    else if (value >= _LCDML_CONTROL_analog_left_min && value <= _LCDML_CONTROL_analog_left_max && _LCDML_CONTROL_analog_enable_lr == 1)
    { // control left
      LCDML.Button_up_down_left_right(_LCDML_button_left);
      LCDML_UPDATE();
    }
    else if (value >= _LCDML_CONTROL_analog_right_min && value <= _LCDML_CONTROL_analog_right_max && _LCDML_CONTROL_analog_enable_lr == 1)
    { // control right
      LCDML.Button_up_down_left_right(_LCDML_button_right);
      LCDML_UPDATE();
    }

    if (value >= _LCDML_CONTROL_analog_back_min && value <= _LCDML_CONTROL_analog_back_max && _LCDML_CONTROL_analog_enable_quit == 1)
    { // control quit
      LCDML.Button_quit();
      LCDML_UPDATE();
    }
  }
}



/* ********************************************************************* */
#elif(_LCDML_DISP_cfg_control == 2)
void LCDML_control_digital()
/* ********************************************************************* */
{
  if (digitalRead(_LCDML_CONTROL_digital_enter) || digitalRead(_LCDML_CONTROL_digital_up) || digitalRead(_LCDML_CONTROL_digital_down)
      || (digitalRead(_LCDML_CONTROL_digital_quit) && _LCDML_CONTROL_digital_enable_quit == 1)
      || ((digitalRead(_LCDML_CONTROL_digital_left) || digitalRead(_LCDML_CONTROL_digital_right)) && _LCDML_CONTROL_digital_enable_lr == 1))
  {
    if (LCDML.Timer(g_LCDML_DISP_press_time, _LCDML_DISP_cfg_button_press_time))
    {
      if (digitalRead(_LCDML_CONTROL_digital_enter)) 
      {
        LCDML.Button_enter();
        LCDML_BACK_reset(LCDML_BACKEND_menu);
      }
      else if (digitalRead(_LCDML_CONTROL_digital_up)) 
      {
        LCDML.Button_up_down_left_right(_LCDML_button_up);
      }
      else if (digitalRead(_LCDML_CONTROL_digital_down)) 
      {
        LCDML.Button_up_down_left_right(_LCDML_button_down);
      }
      else if (digitalRead(_LCDML_CONTROL_digital_quit) && _LCDML_CONTROL_digital_enable_quit == 1) 
      {
        LCDML.Button_quit();        
      }
      else if (digitalRead(_LCDML_CONTROL_digital_left) && _LCDML_CONTROL_digital_enable_lr == 1) 
      {
        LCDML.Button_up_down_left_right(_LCDML_button_left);
      }
      else if (digitalRead(_LCDML_CONTROL_digital_right) && _LCDML_CONTROL_digital_enable_lr == 1) 
      {
        LCDML.Button_up_down_left_right(_LCDML_button_right);
      }
      LCDML_UPDATE();
    }    
  }
}
/* ********************************************************************* */
#elif(_LCDML_DISP_cfg_control == 3)
uint8_t  g_LCDML_CONTROL_encoder_t_prev = 0;
uint8_t  g_LCDML_CONTROL_encoder_a_prev = 0;
uint32_t g_LCDML_CONTROL_encoder_timer  = 0;
void LCDML_control_encoder()
/* ********************************************************************* */
{
  if (LCDML.Timer(g_LCDML_CONTROL_encoder_timer, _LCDML_CONTROL_encoder_time)) 
  {    
    unsigned char a = digitalRead(_LCDML_CONTROL_encoder_pin_a);
    unsigned char b = digitalRead(_LCDML_CONTROL_encoder_pin_b);
    unsigned char t = digitalRead(_LCDML_CONTROL_encoder_pin_button);

    if (_LCDML_CONTROL_encoder_high_active == 1) 
    {
      t != t;
    }

    if (!a && g_LCDML_CONTROL_encoder_a_prev) 
    {
      g_LCDML_CONTROL_encoder_t_prev = 1;
      if (!t) {
        if (!b)
        {
          LCDML.Button_up_down_left_right(_LCDML_button_right);
        }
        else
        {
          LCDML.Button_up_down_left_right(_LCDML_button_left);
        }
      }
      else
      {
        if (!b)
        {
          LCDML.Button_up_down_left_right(_LCDML_button_up);
        }
        else
        {
          LCDML.Button_up_down_left_right(_LCDML_button_down);
        }
      }
      LCDML_UPDATE();
    } 
    else 
    {
      if (LCDML.Timer(g_LCDML_DISP_press_time, _LCDML_DISP_cfg_button_press_time)) 
      {
        if (!t && g_LCDML_CONTROL_encoder_t_prev == 0) 
        {          
            LCDML.Button_enter();
            LCDML_BACK_reset(LCDML_BACKEND_menu);
            LCDML_UPDATE();          
        } 
        else 
        {
          g_LCDML_CONTROL_encoder_t_prev = 0;
        }
      }      
    }
    g_LCDML_CONTROL_encoder_a_prev = a;   
  }
}
#endif







