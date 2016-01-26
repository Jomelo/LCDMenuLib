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
