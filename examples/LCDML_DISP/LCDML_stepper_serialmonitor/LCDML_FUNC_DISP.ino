/* ===================================================================== *
 *                                                                       *
 * DISPLAY SYSTEM                                                        *
 *                                                                       *
 * ===================================================================== *
 * every "disp menu function" needs three functions 
 * - void LCDML_DISP_setup(func_name)    
 * - void LCDML_DISP_loop(func_name)     
 * - void LCDML_DISP_loop_end(func_name)
 *
 * EXAMPLE CODE:
    void LCDML_DISP_setup(..menu_func_name..) 
    {
      // setup
      // is called only if it is started

      // starts a trigger event for the loop function every 100 millisecounds
      LCDML_DISP_triggerMenu(100);  
    }
    
    void LCDML_DISP_loop(..menu_func_name..)
    { 
      // loop
      // is called when it is triggert
      // - with LCDML_DISP_triggerMenu( millisecounds ) 
      // - with every button status change

      // check if any button is presed (enter, up, down, left, right)
      if(LCDML_BUTTON_checkAny()) {         
        LCDML_DISP_funcend();
      } 
    }
    
    void LCDML_DISP_loop_end(..menu_func_name..)
    {
      // loop end
      // this functions is ever called when a DISP function is quit
      // you can here reset some global vars or do nothing  
    } 
 * ===================================================================== * 
 */

/* ===================================================================== */
void LCDML_DISP_setup(LCDML_FUNC_stepper_on) 
/* ===================================================================== */
{
  // setup  
  uint8_t param = LCDML_DISP_getParameter();
  
  switch(param) 
  {
    case 1: // stepper 1 on 
      LCDML_DISP_groupDisable(_LCDML_G2); 
      LCDML_DISP_groupEnable(_LCDML_G3);       

      stepper1.setMaxSpeed(850);
      stepper1.setSpeed(-850);
      g_stepper_1_mode = 'r';
      
      break;

    case 2: // stepper 2 on 
      LCDML_DISP_groupDisable(_LCDML_G4); 
      LCDML_DISP_groupEnable(_LCDML_G5);

      stepper2.setMaxSpeed(850);
      stepper2.setSpeed(850);
      g_stepper_2_mode = 'r';
      
      break;

    default:
      break;  
  }    
}

void LCDML_DISP_loop(LCDML_FUNC_stepper_on)
{ 
  // end function direct
  LCDML_DISP_funcend();  
}

void LCDML_DISP_loop_end(LCDML_FUNC_stepper_on)
{
  // loop end
  // this functions is ever called when a DISP function is quit
}

/* ===================================================================== */
void LCDML_DISP_setup(LCDML_FUNC_stepper_off) 
/* ===================================================================== */
{
  // setup
  uint8_t param = LCDML_DISP_getParameter();
  
  switch(param) 
  {
    case 1: // stepper 1 off
      LCDML_DISP_groupEnable(_LCDML_G2); 
      LCDML_DISP_groupDisable(_LCDML_G3);
      g_stepper_1_mode = 0;
      break;

    case 2: // stepper 2 off
      LCDML_DISP_groupEnable(_LCDML_G4); 
      LCDML_DISP_groupDisable(_LCDML_G5);
      g_stepper_2_mode = 0;
      break;

    default:
      break;  
  }    
}

void LCDML_DISP_loop(LCDML_FUNC_stepper_off)
{ 
  // end function direct     
  LCDML_DISP_funcend();   
}

void LCDML_DISP_loop_end(LCDML_FUNC_stepper_off)
{
  // loop end
  // this functions is ever called when a DISP function is quit
}

     


