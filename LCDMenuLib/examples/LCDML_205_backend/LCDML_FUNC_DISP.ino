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
void LCDML_DISP_setup(LCDML_FUNC_static)
// ********************************************************************* 
{
  // setup 
  // use parameter on menu init
  uint8_t param = LCDML_DISP_getParameter();
  switch(param)
  {
    case 1: // start backend
      LCDML_BACK_start(LCDML_BACKEND_static);
      break;

    case 2: // reset backend
      LCDML_BACK_reset(LCDML_BACKEND_static);
      break;

    case 3: // stop backend
      LCDML_BACK_stop(LCDML_BACKEND_static);
      break;

    case 4: // restart backend
      LCDML_BACK_reset(LCDML_BACKEND_static);
      break;

    case 5: // stop stable 
      LCDML_BACK_stopStable(LCDML_BACKEND_static);
      break;

    default:
      Serial.println(F("Wrong Parameter: LCDML_FUNC_static"));
      break;
  }
  // quit
  LCDML_DISP_funcend();
}
void LCDML_DISP_loop(LCDML_FUNC_static)
{ // loop    
}
void LCDML_DISP_loop_end(LCDML_FUNC_static)
{ // loop end  
} 




// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_dynamic)
// ********************************************************************* 
{
  // setup 
  // use parameter on menu init
  uint8_t param = LCDML_DISP_getParameter();
  switch(param)
  {
    case 1: // Start
      LCDML_BACK_start(LCDML_BACKEND_dynamic);
      break;

    case 2: // Stop Stable
      LCDML_BACK_stopStable(LCDML_BACKEND_dynamic);
      break;

    case 3:
      Serial.println(F("not implemented -> next beta 4"));
      break;

    default:
       Serial.println(F("Wrong Parameter: LCDML_FUNC_dynamic"));
      break;
  }
  // quit 
  LCDML_DISP_funcend(); 
}
void LCDML_DISP_loop(LCDML_FUNC_dynamic)
{  // loop 
}
void LCDML_DISP_loop_end(LCDML_FUNC_dynamic)
{  // loop end
}




// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_group)
// ********************************************************************* 
{
  // setup
  // use parameter on menu init
  uint8_t param = LCDML_DISP_getParameter();
  switch(param) 
  {
    case 1: // start group
      LCDML_BACK_group_start(GROUP_group_example);
      break;

    case 2: // group stop
      LCDML_BACK_group_stop(GROUP_group_example);
      break;

    default:
      Serial.println(F("Wrong Parameter: LCDML_FUNC_group"));
      break;
  }  
  // quit
  LCDML_DISP_funcend();
}
void LCDML_DISP_loop(LCDML_FUNC_group)
{  // loop
}
void LCDML_DISP_loop_end(LCDML_FUNC_group)
{  // loop end
}




// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_state_start)
// ********************************************************************* 
{
  // setup
  // start backend function with restart (setup runs again)
  LCDML_BACK_restart(LCDML_BACKEND_state_1);
  LCDML_DISP_funcend();
}
void LCDML_DISP_loop(LCDML_FUNC_state_start)
{  // loop
}

void LCDML_DISP_loop_end(LCDML_FUNC_state_start)
{  // loop end
}




// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_trigger_event)
// ********************************************************************* 
{
  // setup
  LCDML_BACK_start(LCDML_BACKEND_event);
  LCDML_DISP_funcend(); 
}

void LCDML_DISP_loop(LCDML_FUNC_trigger_event)
{  // loop
}

void LCDML_DISP_loop_end(LCDML_FUNC_trigger_event)
{  // loop end
}




// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_ping_pong)
// ********************************************************************* 
{
  // starts backend functions
  /*
  LCDML_BACK_signal_set(signal_from_ping_to_ping);
  LCDML_BACK_restart(LCDML_BACKEND_signals_ping);
  LCDML_BACK_restart(LCDML_BACKEND_signals_pong);
  */
  Serial.println(F("LCDML_FUNC_ping_pong: beta 4"));
  LCDML_DISP_funcend();
}

void LCDML_DISP_loop(LCDML_FUNC_ping_pong)
{  // loop
}

void LCDML_DISP_loop_end(LCDML_FUNC_ping_pong)
{  // loop end
}




// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_kill)
// ********************************************************************* 
{
  // setup 
  // use parameter on menu init
  uint8_t param = LCDML_DISP_getParameter();
  switch(param) 
  {
    case 1: // stop all backend function
      LCDML_BACK_all_stop();
      break;

    case 2: // restart all backend function
      LCDML_BACK_all_restart();
      break;

    case 3: // start a function with static time 0
      LCDML_BACK_start(LCDML_BACKEND_kill_system_3);
      break;

    case 4: // start a dynamic function and set loop time to 0
      LCDML_BACK_start(LCDML_BACKEND_kill_system_4);
      break;

    default:
      Serial.println(F("Wrong Parameter: LCDML_FUNC_group"));
      break;
  }
  // quit
  LCDML_DISP_funcend();
}
void LCDML_DISP_loop(LCDML_FUNC_kill)
{  // loop 
}
void LCDML_DISP_loop_end(LCDML_FUNC_kill)
{  // loop end
}
