/* ===================================================================== */
/*
/* LCDMenuLib BACKEND FUNCTION - do not change here something            */
/*
/* ===================================================================== */

/* ********************************************************************* */
void LCDML_BACK_setup(LCDML_BACKEND_menu)         /* NOTHING CHANGE HERE */
/* ********************************************************************* */
{  
  g_LCDML_BACK_lastFunc = LCDML.getFunction();
  if(g_LCDML_DISP_functions_loop_setup[g_LCDML_BACK_lastFunc] == LCDML_FUNC_loop_setup) {
    bitSet(LCDML.control, _LCDMenuLib_control_funcend);
  } 
  else if(g_LCDML_BACK_lastFunc != _LCDMenuLib_NO_FUNC) {   
    lcd.clear();
    LCDML_BUTTON_resetAll(); 
    g_LCDML_DISP_functions_loop_setup[g_LCDML_BACK_lastFunc]();      			
  } 
}
boolean LCDML_BACK_loop(LCDML_BACKEND_menu)
{   
  if(LCDML.getFunction() != _LCDMenuLib_NO_FUNC) {    				
    g_LCDML_DISP_functions_loop[LCDML.getFunction()]();			
  }  
  return true;
}

void LCDML_BACK_stable(LCDML_BACKEND_menu)
{  
  if (g_LCDML_BACK_lastFunc != _LCDMenuLib_NO_FUNC) {					
    g_LCDML_DISP_functions_loop_end[g_LCDML_BACK_lastFunc]();
    g_LCDML_BACK_lastFunc = _LCDMenuLib_NO_FUNC;    
    lcd.clear();
    LCDML.display();
    LCDML_BUTTON_resetAll(); 
    LCDML.function = _LCDMenuLib_NO_FUNC;    
    bitClear(LCDML.control, _LCDMenuLib_control_funcend);  
  } 
}



/* ********************************************************************* */
void LCDML_BACK_setup(LCDML_BACKEND_control)      
/* ********************************************************************* */
{
  #if(_LCDML_DISP_cfg_control == 3)
  pinMode(_LCDML_CONTROL_encoder_pin_a      , INPUT_PULLUP);
  pinMode(_LCDML_CONTROL_encoder_pin_b      , INPUT_PULLUP);
  pinMode(_LCDML_CONTROL_encoder_pin_button , INPUT_PULLUP);
  #endif  
}
boolean LCDML_BACK_loop(LCDML_BACKEND_control)
{ 
  if(bitRead(LCDML.control, _LCDMenuLib_control_funcend)) {    
    LCDML_BACK_reset(LCDML_BACKEND_menu);
    LCDML_BACK_dynamic_setDefaultTime(LCDML_BACKEND_menu);
    LCDML_BACK_stopStable(LCDML_BACKEND_menu);    
  }
  
  #if(_LCDML_DISP_cfg_control == 0)  
  LCDML_control_serial();           
  #elif(_LCDML_DISP_cfg_control == 1)  
  LCDML_control_analog();     
  #elif(_LCDML_DISP_cfg_control == 2)  
  LCDML_control_digital();     
  #elif(_LCDML_DISP_cfg_control == 3)  
  LCDML_control_encoder();
  #else    
  #endif
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
  Serial.println(F("10 start"));  
}
boolean LCDML_BACK_loop(LCDML_BACKEND_test10) {
  Serial.println(F("10 loop"));
}
void LCDML_BACK_stable(LCDML_BACKEND_test10) {
  Serial.println(F("10 stop stable"));
}

/* ===================================================================== */
void LCDML_BACK_setup(LCDML_BACKEND_test20)
/* ===================================================================== */
{
  Serial.println(F("20 start"));  
}
boolean LCDML_BACK_loop(LCDML_BACKEND_test20) {
  Serial.println(F("20"));
}
void LCDML_BACK_stable(LCDML_BACKEND_test20){}


/* ===================================================================== */
void LCDML_BACK_setup(LCDML_BACKEND_test30)
/* ===================================================================== */
{
  Serial.println(F("30 event start"));  
}
boolean LCDML_BACK_loop(LCDML_BACKEND_test30) {
  Serial.println(F("30 event loop"));
}
void LCDML_BACK_stable(LCDML_BACKEND_test30){}


uint8_t g_initscreen_firststart = 0;
/* ********************************************************************* */
//void LCDML_BACK_setup(LCDML_BACKEND_initscreen)      
/* ********************************************************************* */
/*
{
  Serial.println(F("initscreen started")); 
}
boolean LCDML_BACK_loop(LCDML_BACKEND_initscreen)
{
  Serial.println(F("initscreen updated"));  
}
void LCDML_BACK_stable(LCDML_BACKEND_initscreen)
{  
}
*/

















