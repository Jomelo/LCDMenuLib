
// ===================================================================== 
//
// LCDMenuLib BACKEND FUNCTION           
//
// =====================================================================

// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_control)      
// *********************************************************************
{
  // setup of this backend function is called only at first start or reset 
  #if(_LCDML_DISP_cfg_control == 2)
  
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
  
  #elif(_LCDML_DISP_cfg_control == 3)
  
    pinMode(_LCDML_CONTROL_encoder_pin_a      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_encoder_pin_b      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_encoder_pin_button , INPUT_PULLUP);
    
  #endif  
}

boolean LCDML_BACK_loop(LCDML_BACKEND_control)
{  
  // check control settings of lcdml
  #if(_LCDML_DISP_cfg_control == 0)  
  LCDML_CONTROL_serial();           
  #elif(_LCDML_DISP_cfg_control == 1)  
  LCDML_CONTROL_analog();     
  #elif(_LCDML_DISP_cfg_control == 2)  
  LCDML_CONTROL_digital();     
  #elif(_LCDML_DISP_cfg_control == 3)  
  LCDML_CONTROL_encoder();
  #elif(_LCDML_DISP_cfg_control == 4)
  LCDML_CONTROL_keypad();  
  #endif  
 
  return true;  
}

void LCDML_BACK_stable(LCDML_BACKEND_control)
{
}

// =====================================================================
//
// OWM BACKEND FUNCTION */
//
// =====================================================================



// =====================================================================
void LCDML_BACK_setup(LCDML_BACKEND_test10)
// =====================================================================
{
  // setup of backend function "test10"
  Serial.println(F("T:10 start"));  
}

boolean LCDML_BACK_loop(LCDML_BACKEND_test10) 
{
  // loop fo backend function "test10"
  Serial.println(F("T:10 loop"));
  return false;
}

void LCDML_BACK_stable(LCDML_BACKEND_test10) 
{
  // stop stable of backend function "test10"
  Serial.println(F("T:10 stop stable"));
}

// =====================================================================
void LCDML_BACK_setup(LCDML_BACKEND_test20)
// =====================================================================
{
  // setup of backend function "test20"
  Serial.println(F("T:20 start"));  
}

boolean LCDML_BACK_loop(LCDML_BACKEND_test20) 
{
  // loop of backend function "test20"
  // the loop time of this function can be changed on runtime
  Serial.println(F("T:20"));
  return false;
}

void LCDML_BACK_stable(LCDML_BACKEND_test20)
{
  // stopStable
}


// =====================================================================
void LCDML_BACK_setup(LCDML_BACKEND_test30)
// =====================================================================
{
  // setup of function "test30"
  Serial.println(F("T:30 event start"));  
}

boolean LCDML_BACK_loop(LCDML_BACKEND_test30) 
{
  // loop of function "test30"
  // this backend function is defined as event an the loop 
  // of an event is called once, then it stops
  Serial.println(F("T:30 event loop"));
  return false;
}

void LCDML_BACK_stable(LCDML_BACKEND_test30)
{
  // stable stop of this function
}
