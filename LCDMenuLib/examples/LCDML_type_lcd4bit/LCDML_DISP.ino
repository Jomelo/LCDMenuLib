/* every "disp menu function" constist of three functions *
 * - void LCDML_DISP_setup(func_name)    is called only if it is started
 * - void LCDML_DISP_loop(func_name)     is called continues if function quit on every button even or trigger event
 * - void LCDML_DISP_loop_end(func_name) is called when quit button or LCDML_DISP_funcend is called
 */

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_information)
/* ********************************************************************* */
{
  // setup function 
  lcd.setCursor(0, 0);
  lcd.print(F("Um Funktion zu"));
  lcd.setCursor(0, 1);
  lcd.print(F("schliessen eine"));
  lcd.setCursor(0, 2);
  lcd.print(F("Taste druecken oder"));
  lcd.setCursor(0, 3);
  lcd.print(F("Back Taste verwenden"));
}
void LCDML_DISP_loop(LCDML_FUNC_information) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function
  
  if(LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
    // LCDML_DISP_funcend calls the loop_end function
    LCDML_DISP_funcend();
  } 
}
void LCDML_DISP_loop_end(LCDML_FUNC_information)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing  
}  

/* ********************************************************************* */
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (globale variable)
void LCDML_DISP_setup(LCDML_FUNC_timer_info)
/* ********************************************************************* */
{
  // setup function      
  lcd.print(F("x sec warten")); // print some content on first row  
  g_func_timer_info = 10; // reset and set timer    
  LCDML_DISP_triggerMenu(100); // starts a trigger event for the loop function every 100 millisecounds
}

void LCDML_DISP_loop(LCDML_FUNC_timer_info)
{ 
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  
  // this function is called every 100 millisecounds
  
  // this timer checks every 1000 millisecounds if it is called
  if(LCDML.Timer(g_timer_1, 1000)) { 
    g_func_timer_info--;                // increment the value every secound */
    lcd.setCursor(0, 0);                // set cursor pos */
    lcd.print(g_func_timer_info);       // print the time counter value */
  }
  
  // this function can only be ended when quit button is pressed or the time is over
  // check if the function ends normaly
  if (g_func_timer_info <= 0)
  {
    // end function for callback
    LCDML_DISP_funcend();  
  }   
}

void LCDML_DISP_loop_end(LCDML_FUNC_timer_info) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

/* ********************************************************************* */
uint8_t g_button_value = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_p2)
/* ********************************************************************* */
{ 
  // setup function
  // print lcd content 
  lcd.setCursor(0, 0);
  lcd.print(F("3 mal Links drucken"));
  lcd.setCursor(0, 1);
  lcd.print(F("Anzahl: 0"));
  // Reset Button Value
  g_button_value = 0; 
}

void LCDML_DISP_loop(LCDML_FUNC_p2)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkLeft()) // check if button left is pressed
    {
      LCDML_BUTTON_resetLeft(); // reset the left button
      g_button_value++;
      
      // update lcd content
      lcd.setCursor(8, 1); // set cursor   
      lcd.print(g_button_value); // print change content
    }    
  }
  
  // check if button count is three
  if (g_button_value >= 3) {
    // end function for callback
    LCDML_DISP_funcend();   
  } 
}
void LCDML_DISP_loop_end(LCDML_FUNC_p2) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}



/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_back)
/* ********************************************************************* */
{ 
  // setup function 
  LCDML_DISP_funcend();  
}
void LCDML_DISP_loop(LCDML_FUNC_back) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function  

}
void LCDML_DISP_loop_end(LCDML_FUNC_back) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
  LCDML.goBack(); // go one layer back
}


/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_prog_disable)
/* ********************************************************************* */
{
  // setup function 
  LCDML_DISP_groupDisable(_LCDML_G2); // disable all menu items in G2
  LCDML_DISP_groupEnable(_LCDML_G3);  // enable all menu items in G3
  LCDML_DISP_funcend();  
}
void LCDML_DISP_loop(LCDML_FUNC_prog_disable) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function  

}
void LCDML_DISP_loop_end(LCDML_FUNC_prog_disable) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
  LCDML.goRoot(); // go to root element (first element of this menu with id=0)
}


/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_prog_enable)
/* ********************************************************************* */
{
  // setup function
  LCDML_DISP_groupEnable(_LCDML_G2);  // enable all menu items in G2
  LCDML_DISP_groupDisable(_LCDML_G3); // disable all menu items in G3
  LCDML_DISP_funcend();
}
void LCDML_DISP_loop(LCDML_FUNC_prog_enable) 
{ 
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function  
}
void LCDML_DISP_loop_end(LCDML_FUNC_prog_enable) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
  LCDML.goRoot(); // go to root element (first element of this menu with id=0)
}


/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_start)
/* ********************************************************************* */
{
  // setup function
  
  // with the function LCDML_BACK_...  you can control the BACKEND function system
  // LCDML_BACK_start: start a function (loop)
  // LCDML_BACK_stop: stop a function (loop)
  // LCDML_BACK_stopStable: stop a function (loop) and start the (stopStable) function
  // LCDML_BACK_restart: start a function (loop and setup)
  LCDML_BACK_start(LCDML_BACKEND_test10); // start the backend function "test10", this function is called every 10 sec
  LCDML_DISP_funcend(); // ends this function
}
void LCDML_DISP_loop(LCDML_FUNC_test10_start) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
}
void LCDML_DISP_loop_end(LCDML_FUNC_test10_start) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_restart)
/* ********************************************************************* */
{
  // setup function
  LCDML_BACK_restart(LCDML_BACKEND_test10); // restart the backend function "test10" (loop with setup)
  LCDML_DISP_funcend(); //end 
}
void LCDML_DISP_loop(LCDML_FUNC_test10_restart) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
}
void LCDML_DISP_loop_end(LCDML_FUNC_test10_restart) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_stop)
/* ********************************************************************* */
{
  // setup function
  LCDML_BACK_stop(LCDML_BACKEND_test10); // stop the backend "test10" function
  LCDML_DISP_funcend(); // end
}
void LCDML_DISP_loop(LCDML_FUNC_test10_stop) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function  
}
void LCDML_DISP_loop_end(LCDML_FUNC_test10_stop) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_stop_stable)
/* ********************************************************************* */
{
  // setup function
  LCDML_BACK_stopStable(LCDML_BACKEND_test10); // stable stop the backend "test10" function
  LCDML_DISP_funcend(); // end
}
void LCDML_DISP_loop(LCDML_FUNC_test10_stop_stable) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
}
void LCDML_DISP_loop_end(LCDML_FUNC_test10_stop_stable) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}




/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_start)
/* ********************************************************************* */
{
  // setup function
  LCDML_BACK_start(LCDML_BACKEND_test20); // start the "test20" backend function
  LCDML_DISP_funcend(); // end the menu function
}
void LCDML_DISP_loop(LCDML_FUNC_test20_start) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_start) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_stop)
/* ********************************************************************* */
{
  // setup function
  LCDML_BACK_stop(LCDML_BACKEND_test20); // stop "test20" function
  LCDML_DISP_funcend(); // end
  Serial.println(F("test 20 stopped")); // console output

}
void LCDML_DISP_loop(LCDML_FUNC_test20_stop) 
{ 
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function   
}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_stop) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing  
}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_500ms)
/* ********************************************************************* */
{
  // setup function
  
  // on dynamic backend function, you can change the loop time every time
  // the next function set the loop time to 500 milli secounds
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 500); // set loop time of "test20" to 500 ms
  LCDML_BACK_start(LCDML_BACKEND_test20); // start this backend function directly  
  LCDML_DISP_funcend(); // end display function
}
void LCDML_DISP_loop(LCDML_FUNC_test20_500ms) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function   
}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_500ms) 
{ 
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing  
}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_1s)
/* ********************************************************************* */
{
  // setup function
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 1000); // set loop time of "test20" to 1000 ms
  LCDML_BACK_start(LCDML_BACKEND_test20); // start this backend function directly
  LCDML_DISP_funcend(); // end display function
}
void LCDML_DISP_loop(LCDML_FUNC_test20_1s) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function  
}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_1s) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_10s)
/* ********************************************************************* */
{
  // setup function
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 10000); // set loop time of "test20" to 10 sec
  LCDML_BACK_start(LCDML_BACKEND_test20); // start this backend function directly 
  LCDML_DISP_funcend(); // end
}
void LCDML_DISP_loop(LCDML_FUNC_test20_10s) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function  
}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_10s) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}


/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test30_start)
/* ********************************************************************* */
{
  // setup function
  // the backend function can be defined as event
  // an event is called once when it is started
  LCDML_BACK_event_start(LCDML_BACKEND_test30); // start an event
  LCDML_DISP_funcend(); // end display function
}
void LCDML_DISP_loop(LCDML_FUNC_test30_start) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function   
}
void LCDML_DISP_loop_end(LCDML_FUNC_test30_start) 
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
}

/* ********************************************************************* */
unsigned long g_initscreen_example_counter = 0;
void LCDML_DISP_setup(LCDML_FUNC_initscreen)
/* ********************************************************************* */
{
  // setup function
  LCDML_DISP_triggerMenu(1000); // set trigger for this function to 1000 millisecounds
  lcd.print("InitScreen");  // print first line to lcd display
  g_initscreen_example_counter = 0; // reset or set example counter
}
void LCDML_DISP_loop(LCDML_FUNC_initscreen) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  g_initscreen_example_counter++; // count the example counter above
  lcd.setCursor(0,1); // clear the secound line on lcd 
  lcd.print("                ");
  lcd.setCursor(0,1); // print new value to lcd
  lcd.print(g_initscreen_example_counter);
  
  g_lcdml_initscreen = millis(); // reset initscreen timer
  
  if(LCDML_BUTTON_checkAny()) { // check if any button is pressed to left this function
    LCDML_DISP_funcend(); // function end    
  }   
}
void LCDML_DISP_loop_end(LCDML_FUNC_initscreen) 
{  
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing
  LCDML.goRoot(); // go to root element (first element of this menu with id=0)
}




