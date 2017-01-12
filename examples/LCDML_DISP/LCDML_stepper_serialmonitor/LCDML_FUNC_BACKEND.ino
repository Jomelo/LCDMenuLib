/* ===================================================================== *
 *                                                                       *
 * BACKEND SYSTEM                                                        *
 *                                                                       *
 * ===================================================================== *
 * every "backend function" needs three functions 
 * - void LCDML_BACK_setup(..func_name..)    
 * - void LCDML_BACK_loop(..func_name..)     
 * - void LCDML_BACK_stable(..func_name..)
 *
 * - every BACKEND function can be stopped and started
 * EXAMPLE CODE:
    void LCDML_BACK_setup(LCDML_BACKEND_control)
    {
      // setup
      // is called only if it is started or restartet (reset+start)
    }
    
    boolean LCDML_BACK_loop(LCDML_BACKEND_control)
    {    
      // runs in loop
      
     
      return false;  
    }
    
    void LCDML_BACK_stable(LCDML_BACKEND_control)
    {
      // stable stop
      // is called when a backend function is stopped with stopStable  
    }
 * ===================================================================== *
 */


/* ===================================================================== */ 
void LCDML_BACK_setup(LCDML_BACKEND_stepper)
/* ===================================================================== */ 
{
  // setup
  // is called only if it is started or restartet (reset+start)
 
}

boolean LCDML_BACK_loop(LCDML_BACKEND_stepper)
{    
  // runs in loop 
  // Loop for stepper 1
  // ============================================
  // check if backend task for stepper 1 is running 
  switch(g_stepper_1_mode) {
    case 'r': // speed
      stepper1.runSpeed();
      break;

    case 'p': // position
      if (stepper1.distanceToGo() > 0) {
        stepper1.run();
      }       
      break;

    case 's': // stop direct and hold
      stepper1.stop();
      break;

    default: // do nothing
      break;        
  }
  

  // Loop for stepper 2
  // ============================================
  // check if backend task for stepper 1 is running

  switch(g_stepper_2_mode) {
    case 'r': // speed
      stepper2.runSpeed();
      break;

    case 'p': // position
      if (stepper2.distanceToGo() > 0) {
        stepper2.run();
      }       
      break;

    case 's': // stop direct and hold
      stepper2.stop();
      break;

    default: // do nothing
      break;        
  }

  



   
 
  return true;  // this value have to be true because the menu is otherwise blocked  
}

void LCDML_BACK_stable(LCDML_BACKEND_stepper)
{
  // stable stop
  // is called when a backend function is stopped with stopStable  
}





