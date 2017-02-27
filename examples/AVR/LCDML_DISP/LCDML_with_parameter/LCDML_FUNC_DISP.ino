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

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_program_change)
// *********************************************************************
{
  // setup function 

  // use parameter on menu init
  uint8_t param = LCDML_DISP_getParameter();
  switch(param) 
  {
    case 0:   // enable program
      LCDML_DISP_groupDisable(_LCDML_G2); // disable group 2
      LCDML_DISP_groupEnable(_LCDML_G3); // enable group 3
      break;

    case 1:
      LCDML_DISP_groupEnable(_LCDML_G2); // enable group 2
      LCDML_DISP_groupDisable(_LCDML_G3); // disable group 3
      break;

    default:
      //get parameter errors
      break;
  } 
  LCDML.goRoot(); // go to root element (first element of this menu with id=0) 
}

void LCDML_DISP_loop(LCDML_FUNC_program_change) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
}

void LCDML_DISP_loop_end(LCDML_FUNC_program_change)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing   
}  





