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



// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_static)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_static"));
  Serial.println(F("==========================="));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_static)
{
  Serial.println(F("Loop: LCDML_BACKEND_static"));    
  
  // return false = go to first backend function and check time
  return false;
  // return true = go to next backend function and check time
  // return true;  
}
void LCDML_BACK_stable(LCDML_BACKEND_static)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
  Serial.println(F("Stop Stable: LCDML_BACKEND_static"));
  Serial.println(F("================================="));  
}





// *********************************************************************
unsigned long g_dynamic_counter = 1;
void LCDML_BACK_setup(LCDML_BACKEND_dynamic)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_dynamic"));
  Serial.println(F("============================"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_dynamic)
{    
  // runs in loop with different times 
  Serial.print(F("Loop: LCDML_BACKEND_dynamic - last loop time: "));
  Serial.println(LCDML_BACK_dynamic_getLoopTime(LCDML_BACKEND_dynamic));
  
  // set next loop time
  g_dynamic_counter++;

  // read old loop time and div it through g_dynamic_counter
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_dynamic,  (LCDML_BACK_dynamic_setDefaultTime(LCDML_BACKEND_dynamic) / g_dynamic_counter));

  if(g_dynamic_counter > 30) {
    // reset counter after 8 steps
    g_dynamic_counter = 1;
    // set loop time to default
    LCDML_BACK_dynamic_setDefaultTime(LCDML_BACKEND_dynamic);    
  }   
   
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_dynamic)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
  Serial.println(F("Stop Stable: LCDML_BACKEND_dynamic"));
  Serial.println(F("=================================="));   
}






// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_ge1)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_ge1"));
  Serial.println(F("============================")); 
}
boolean LCDML_BACK_loop(LCDML_BACKEND_ge1)
{    
  // runs in loop
  Serial.println(F("Loop: LCDML_BACKEND_ge1"));   
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_ge1)
{
  // stable stop
  // is called when a backend function is stopped with stopStable 
  Serial.println(F("Stop Stable: LCDML_BACKEND_ge1"));
  Serial.println(F("=================================="));   
}
// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_ge2)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_ge2"));
  Serial.println(F("============================")); 
}
boolean LCDML_BACK_loop(LCDML_BACKEND_ge2)
{    
  // runs in loop 
  Serial.println(F("Loop: LCDML_BACKEND_ge2"));  
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_ge2)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
  Serial.println(F("Stop Stable: LCDML_BACKEND_ge2"));
  Serial.println(F("=================================="));   
}
// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_ge3)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_ge3"));
  Serial.println(F("============================"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_ge3)
{    
  // runs in loop
  Serial.println(F("Loop: LCDML_BACKEND_ge3"));  
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_ge3)
{
  // stable stop
  // is called when a backend function is stopped with stopStable 
  Serial.println(F("Stop Stable: LCDML_BACKEND_ge3"));
  Serial.println(F("=================================="));  
}





// *********************************************************************
uint8_t g_state_counter = 0;
void LCDML_BACK_setup(LCDML_BACKEND_state_1)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_state_1"));
  Serial.println(F("============================"));
  Serial.println(F("count until 5"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_state_1)
{    
  // runs in loop
  if(g_state_counter == 5) {
     // stopStable this function 
     LCDML_BACK_stopStable(LCDML_BACKEND_state_1);
     // go to next state with restart (runs setup again)
     LCDML_BACK_restart(LCDML_BACKEND_state_2);
  } else {
    // increment
    g_state_counter++;
    Serial.print(F("Loop: LCDML_BACKEND_state_1 - counter: "));
    Serial.println(g_state_counter);
  }
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_state_1)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
  Serial.println(F("Stop Stable: LCDML_BACKEND_state_1"));
  Serial.println(F("==================================")); 

  // reset counter
  g_state_counter = 0;    
}

// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_state_2)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_state_2"));
  Serial.println(F("============================"));
  Serial.println(F("count until 10"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_state_2)
{    
  // runs in loop
  if(g_state_counter == 10) {
     // stopStable this function 
     LCDML_BACK_stopStable(LCDML_BACKEND_state_2);
     // go to next state with restart (runs setup again)
     LCDML_BACK_restart(LCDML_BACKEND_state_3);
  } else {
    // increment
    g_state_counter++;
    Serial.print(F("Loop: LCDML_BACKEND_state_2 - counter: "));
    Serial.println(g_state_counter);
  } 
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_state_2)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
   Serial.println(F("Stop Stable: LCDML_BACKEND_state_2"));
  Serial.println(F("==================================")); 

  // reset counter
  g_state_counter = 0;    
}

// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_state_3)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_state_3"));
  Serial.println(F("============================"));
  Serial.println(F("count until 2"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_state_3)
{    
  // runs in loop
  if(g_state_counter == 2) {
     // stopStable this function 
     LCDML_BACK_stopStable(LCDML_BACKEND_state_3);
     // go to next state with restart (runs setup again)
     LCDML_BACK_restart(LCDML_BACKEND_state_4);
  } else {
    // increment
    g_state_counter++;
    Serial.print(F("Loop: LCDML_BACKEND_state_3 - counter: "));
    Serial.println(g_state_counter);
  }  
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_state_3)
{
  // stable stop
  // is called when a backend function is stopped with stopStable 
  Serial.println(F("Stop Stable: LCDML_BACKEND_state_3"));
  Serial.println(F("==================================")); 

  // reset counter
  g_state_counter = 0;   
}

// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_state_4)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_state_4"));
  Serial.println(F("============================"));
  Serial.println(F("count until 5 and destroy itself"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_state_4)
{    
  // runs in loop
  if(g_state_counter == 5) {
     // stopStable this function 
     LCDML_BACK_stopStable(LCDML_BACKEND_state_4);    
  } else {
    // increment
    g_state_counter++;
    Serial.print(F("Loop: LCDML_BACKEND_state_4 - counter: "));
    Serial.println(g_state_counter);
  }  
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_state_4)
{
  // stable stop
  // is called when a backend function is stopped with stopStable 
  Serial.println(F("Stop Stable: LCDML_BACKEND_state_4"));
  Serial.println(F("==================================")); 

  // reset counter
  g_state_counter = 0;   
}






// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_event)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_event"));
  Serial.println(F("============================"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_event)
{    
  // runs in loop
  Serial.println(F("Loop: LCDML_BACKEND_event - only loop is called and stopped once again")); 
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_event)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
  Serial.println(F("Stop Stable: LCDML_BACKEND_event"));
  Serial.println(F("=================================="));   
}






// *********************************************************************
uint8_t g_ping_pong_counter = 0;
void LCDML_BACK_setup(LCDML_BACKEND_signals_ping)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_signals_ping"));
  Serial.println(F("============================"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_signals_ping)
{    
  // runs in loop 
  /*
  if(LCDML_BACK_signal_get(signal_from_ping_to_ping)) {
    if(g_ping_pong_counter >= 10) {
      LCDML_BACK_stopStable(LCDML_BACKEND_signals_ping);
      LCDML_BACK_stopStable(LCDML_BACKEND_signals_pong);
      g_ping_pong_counter = 0;
      LCDML_BACK_signal_clear(signal_from_ping_to_ping);
      LCDML_BACK_signal_clear(signal_from_ping_to_pong);      
    }
    LCDML_BACK_signal_clear(signal_from_ping_to_ping);
    LCDML_BACK_signal_set(signal_from_ping_to_pong);
    Serial.println(F("Loop: LCDML_BACKEND_signals_ping - get signal"));
    g_ping_pong_counter++;
  } else {
    Serial.println(F("Loop: LCDML_BACKEND_signals_ping - no signal"));
  }
  */ 
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_signals_ping)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
  Serial.println(F("Stop Stable: LCDML_BACKEND_signals_ping"));
  Serial.println(F("=================================="));   
}

// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_signals_pong)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_signals_pong"));
  Serial.println(F("============================"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_signals_pong)
{    
  // runs in loop 
  /*
  if(LCDML_BACK_signal_get(signal_from_ping_to_pong)) {
    LCDML_BACK_signal_clear(signal_from_ping_to_pong);
    LCDML_BACK_signal_set(signal_from_ping_to_ping);
    Serial.println(F("Loop: LCDML_BACKEND_signals_pong - get signal"));
    g_ping_pong_counter++;
  } else {
    Serial.println(F("Loop: LCDML_BACKEND_signals_pong - no signal"));
  }
  */
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_signals_pong)
{
  // stable stop
  // is called when a backend function is stopped with stopStable
  Serial.println(F("Stop Stable: LCDML_BACKEND_signals_pong"));
  Serial.println(F("=================================="));   
}






// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_kill_system_3)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_kill_system_3"));
  Serial.println(F("============================"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_kill_system_3)
{    
  // runs in loop
  Serial.println(F("Loop: LCDML_BACKEND_kill_system_3")); 
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_kill_system_3)
{
  // stable stop
  // is called when a backend function is stopped with stopStable 
  Serial.println(F("Stop Stable: LCDML_BACKEND_kill_system_3"));
  Serial.println(F("=================================="));   
}





// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_kill_system_4)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_kill_system_4"));
  Serial.println(F("============================"));
  // set loop time to zero
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_kill_system_4, 0);
}
boolean LCDML_BACK_loop(LCDML_BACKEND_kill_system_4)
{    
  // runs in loop 
  Serial.println(F("Loop: LCDML_BACKEND_kill_system_4")); 
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_kill_system_4)
{
  // stable stop
  // is called when a backend function is stopped with stopStable  
  Serial.println(F("Setup: LCDML_BACKEND_kill_system_4"));
  Serial.println(F("============================"));
}








// *********************************************************************
unsigned long g_real_loop_time_old = millis();
void LCDML_BACK_setup(LCDML_BACKEND_idle)
// *********************************************************************
{
  // setup
  // is called only if it is started or restartet (reset+start)
  Serial.println(F("Setup: LCDML_BACKEND_idle"));
  Serial.println(F("============================"));
  Serial.println(F("This function is called every 30 secounds"));
  Serial.println(F("If this function is not called, the loop time of other threads was set wrong"));
}
boolean LCDML_BACK_loop(LCDML_BACKEND_idle)
{    
  // runs in loop
  Serial.print(F("Loop: LCDML_BACKEND_idle - real loop time: "));
  Serial.print((float)((millis() - g_real_loop_time_old)/1000.));
  Serial.println(" [s]");
  g_real_loop_time_old = millis();  
  return false;  
}
void LCDML_BACK_stable(LCDML_BACKEND_idle)
{
  // stable stop
  // is called when a backend function is stopped with stopStable 
  Serial.println(F("Stop Stable: LCDML_BACKEND_event"));
  Serial.println(F("=================================="));  
}




