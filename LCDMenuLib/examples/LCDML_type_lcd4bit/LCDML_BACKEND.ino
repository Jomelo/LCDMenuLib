/* ===================================================================== */
/*
/* LCDMenuLib BACKEND FUNCTION - do not change here something            */
/*
/* ===================================================================== */

/* ********************************************************************* */
unsigned long g_lcdml_initscreen = millis();
void LCDML_BACK_setup(LCDML_BACKEND_control)      
/* ********************************************************************* */
{
  // setup of this backend function is called only at first start or reset 
  #if(_LCDML_DISP_cfg_control == 3)
  pinMode(_LCDML_CONTROL_encoder_pin_a      , INPUT_PULLUP);
  pinMode(_LCDML_CONTROL_encoder_pin_b      , INPUT_PULLUP);
  pinMode(_LCDML_CONTROL_encoder_pin_button , INPUT_PULLUP);
  #endif  
}
boolean LCDML_BACK_loop(LCDML_BACKEND_control)
{ 
  // loop of this backend function
  if(bitRead(LCDML.control, _LCDMenuLib_control_funcend)) {    
    LCDML_BACK_reset(LCDML_BACKEND_menu); // reset setup function for DISP function 
    LCDML_BACK_dynamic_setDefaultTime(LCDML_BACKEND_menu); // reset trigger settings
    LCDML_BACK_stopStable(LCDML_BACKEND_menu); // stop an menu function stable    
  } 
  
  // check control settings of lcdml
  #if(_LCDML_DISP_cfg_control == 0)  
  LCDML_control_serial();           
  #elif(_LCDML_DISP_cfg_control == 1)  
  LCDML_control_analog();     
  #elif(_LCDML_DISP_cfg_control == 2)  
  LCDML_control_digital();     
  #elif(_LCDML_DISP_cfg_control == 3)  
  LCDML_control_encoder();
  #else 
  #error "_LCDML_DISP_cfg_control is not defined correctly"  
  #endif
  
  // example for init screen
  if(g_lcdml_initscreen + 30000 < millis()) {  // set initscreen time to 30 sec
    g_lcdml_initscreen = millis(); // reset init screen time
    LCDML_DISP_jumpToFunc(LCDML_FUNC_initscreen); // jump to initscreen     
  }   
  return true;  
}
void LCDML_BACK_stable(LCDML_BACKEND_control)
{
}

/* ===================================================================== */
/*
/* OWM BACKEND FUNCTION */
/*
/* ===================================================================== */



/* ===================================================================== */
void LCDML_BACK_setup(LCDML_BACKEND_test10)
/* ===================================================================== */
{
  // setup of backend function "test10"
  Serial.println(F("T:10 start"));  
}
boolean LCDML_BACK_loop(LCDML_BACKEND_test10) 
{
  // loop fo backend function "test10"
  Serial.println(F("T:10 loop"));
}
void LCDML_BACK_stable(LCDML_BACKEND_test10) 
{
  // stop stable of backend function "test10"
  Serial.println(F("T:10 stop stable"));
}

/* ===================================================================== */
void LCDML_BACK_setup(LCDML_BACKEND_test20)
/* ===================================================================== */
{
  // setup of backend function "test20"
  Serial.println(F("T:20 start"));  
}
boolean LCDML_BACK_loop(LCDML_BACKEND_test20) 
{
  // loop of backend function "test20"
  // the loop time of this function can be changed on runtime
  Serial.println(F("T:20"));
}
void LCDML_BACK_stable(LCDML_BACKEND_test20)
{
  // stopStable
}


/* ===================================================================== */
void LCDML_BACK_setup(LCDML_BACKEND_test30)
/* ===================================================================== */
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
}
void LCDML_BACK_stable(LCDML_BACKEND_test30)
{
  // stable stop of this function
}





















