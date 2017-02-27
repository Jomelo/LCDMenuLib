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
 
/* ******************************************************************** */  
void LCDML_BACK_setup(LCDML_BACKEND_sec_counter)
/* ******************************************************************** */
{
  // setup
  // is called only if it is started or restartet (reset+start)
}

boolean LCDML_BACK_loop(LCDML_BACKEND_sec_counter)
{    
  // runs in loop
  g_sec_counter++; 
      
  // Update menu if no function is running (the check is in LCDML_DISP_update_menu_direct())
  // the update function check if the parameter id is realy displayed on the screen only then 
  // the display is realy updated.  
  LCDML_DISP_update_menu_direct(0);
 
  return false;  
}

void LCDML_BACK_stable(LCDML_BACKEND_sec_counter)
{
  // stable stop
  // is called when a backend function is stopped with stopStable  
}