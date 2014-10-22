// init screen 
// this functions is called if: 
// -> _LCDMenuLib_cfg_initscreen is enable and 
// ---> quit/back button is called in layer 0 
// ---> or _LCDMenuLib_cfg_initscreen_time is larger then 0  
void FUNC_init_screen(void)
{
  // setup function 
  if(!LCDML.FuncInit())
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Init Screen"));      
  }
  
  // here you can enter the loop code
    
  //.
  //..
  //...
  //..
  //.  
  
  // end the loop code here  
  
  // check function end 
  if(LCDML.FuncEnd(0, 1, 1, 1, 1, 1)) // (direct, enter, up, down, left, right) 
  {
    // do something bevor this function is closed   
  }     
}

// callback function - FUNC_information
void FUNC_information(void)
{       
  // setup function      
  if(!LCDML.FuncInit())
  {
    // init              
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Um Funktion zu"));
    lcd.setCursor(0,1);
    lcd.print(F("schliessen eine"));
    lcd.setCursor(0,2);
    lcd.print(F("Taste druecken oder"));
    lcd.setCursor(0,3);
    lcd.print(F("Back Taste verwenden"));      
  } 
    
  // here you have to enter the loop code 
  
  //.
  //..
  //...
  //..
  //.  
  
  // end the loop code here

  // end function for callback */
  if(LCDML.FuncEnd(0, 1, 1, 1, 1, 1))  // (direct, enter, up, down, left, right) 
  {
    // do something bevor this function is closed      
  }      
}





uint8_t g_func_timer_info = 0;  // time counter
unsigned long g_timer_1 = 0;    // timer variable

// callback function - FUNC_information 
void FUNC_timer_info(void)
{
  // setup function       
  if(!LCDML.FuncInit())
  {
    // clear the display and init the time counter value          
    lcd.clear();
    lcd.print(F("x sec warten"));      
    g_func_timer_info = 10;      
  }
     
  if(LCDML.Timer(g_timer_1, 1000)) {    // init a timer with 1000ms */      
    g_func_timer_info--;                 // increment the value every secound */
    lcd.setCursor(0,0);                 // set cursor pos */
    lcd.print(g_func_timer_info);       // print the time counter value */
  }    
  
  
  // check if the function ends normaly
  if(g_func_timer_info <= 0) 
  {
    // end function for callback 
    if(LCDML.FuncEnd(1,0,0,0,0,0)) // (direct, enter, up, down, left, right)   
    {
      // do something bevor this function is closed     
    }  
  }

  // check if the function ends hard
  if(LCDML.FuncEndQuitButton()) 
  {
    // do something bevor this function is closed     
  }  
} 




uint8_t g_button_value = 0;
 
void FUNC_p2(void)
{    
  // setup function       
  if(!LCDML.FuncInit())
  {
    // Init Function            
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("3 mal Links drucken"));
    lcd.setCursor(0,1);
    lcd.print(F("Anzahl: 0")); 
    // Reset Button Value
    g_button_value = 0;      
  }
  
  
  // * --------- LOOP ----------
  // * Hier wird nur ein Ereignis ausgelöst, sobald ein Button gedrückt
  // * wurde. Die Funktion LCDML.checkButtons liefert true, wenn ein Button 
  // * seit dem letztem durchlauf betätigt wurde, ansonsten false.     
  if(LCDML.checkButtons()) 
  {
    if(LCDMenuLib_checkButtonLeft()) 
    {
      LCDMenuLib_resetButtonLeft();
      g_button_value++;
    }
    
    // Die Position des Cursor wird verschoben 
    lcd.setCursor(8,1);
    // Die Anzahl wie oft ein Button gedrückt wurde, wird angezeigt 
    lcd.print(g_button_value);
  }
  
  if(g_button_value >= 3) {    
    // end function for callback
    if(LCDML.FuncEnd(1, 0, 0, 0, 0, 0)) // (direct, enter, up, down, left, right)  
    {
      // do something bevor this function is closed normaly       
    } 
  } 
  
  if(LCDML.FuncEndQuitButton())
  {
    //* do something bevor this function is closed hard  
  }
}



void FUNC_back(void)
{        
  LCDML.FuncInit();            // setup function 
  LCDML.Button_quit(2);        // quit button   
  LCDML.FuncEnd(1,0,0,0,0,0);  // direct func end
}
  
