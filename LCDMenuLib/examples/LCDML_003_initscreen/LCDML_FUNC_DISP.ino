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
void LCDML_DISP_setup(LCDML_FUNC_information)
// *********************************************************************
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


// *********************************************************************
uint8_t g_func_timer_info = 0;  // time counter (global variable)
unsigned long g_timer_1 = 0;    // timer variable (globale variable)
void LCDML_DISP_setup(LCDML_FUNC_timer_info)
// *********************************************************************
{
  // setup function   
  lcd.print(F("x sec warten")); // print some content on first row  
  g_func_timer_info = 10;       // reset and set timer    
  LCDML_DISP_triggerMenu(100);  // starts a trigger event for the loop function every 100 millisecounds
}

void LCDML_DISP_loop(LCDML_FUNC_timer_info)
{ 
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  
  // this function is called every 100 millisecounds
  
  // this timer checks every 1000 millisecounds if it is called
  if((millis() - g_timer_1) >= 1000) {
    g_timer_1 = millis();   
    g_func_timer_info--;                // increment the value every secound
    lcd.setCursor(0, 0);                // set cursor pos
    lcd.print(g_func_timer_info);       // print the time counter value
  }
  
  // reset the initscreen timer
  LCDML_DISP_resetIsTimer();
  
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

// *********************************************************************
uint8_t g_button_value = 0; // button value counter (global variable)
void LCDML_DISP_setup(LCDML_FUNC_p2)
// *********************************************************************
{ 
  // setup function
  // print lcd content
  lcd.setCursor(0, 0);
  lcd.print(F("press left or up"));  
  lcd.setCursor(0, 1);
  lcd.print(F("count: 0 of 3"));
  // Reset Button Value
  g_button_value = 0; 
}

void LCDML_DISP_loop(LCDML_FUNC_p2)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkLeft() || LCDML_BUTTON_checkUp()) // check if button left is pressed
    {
      LCDML_BUTTON_resetLeft(); // reset the left button
      LCDML_BUTTON_resetUp(); // reset the left button
      g_button_value++;
      
      // update lcd content
      lcd.setCursor(7, 1); // set cursor   
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



// *********************************************************************
unsigned long g_initscreen_example_counter = 0;
void LCDML_DISP_setup(LCDML_FUNC_initscreen)
// *********************************************************************
{
  // setup function
  LCDML_DISP_triggerMenu(1000); // set trigger for this function to 1000 millisecounds
  lcd.print(F("InitScreen"));  // print first line to lcd display
  g_initscreen_example_counter = 0; // reset or set example counter
}

void LCDML_DISP_loop(LCDML_FUNC_initscreen) 
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function 
  g_initscreen_example_counter++; // count the example counter above
  lcd.setCursor(0,1); // clear the secound line on lcd 
  lcd.print(F("      "));
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
