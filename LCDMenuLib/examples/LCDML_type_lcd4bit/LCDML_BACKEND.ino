/* ===================================================================== */
/* LCDMenuLib BACKEND FUNCTION - do not change here something            */
/* ===================================================================== */
/* ********************************************************************* */
void LCDML_BACK_setup(LCDML_BACKEND_control)      /* NOTHING CHANGE HERE */
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
/* ===================================================================== */
/* OWM BACKEND FUNCTION */
/* ===================================================================== */


