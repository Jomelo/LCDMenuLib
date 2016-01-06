
// every "disp menu function" constist of three functions 
// - void LCDML_DISP_setup(func_name)    is called only if it is started
// - void LCDML_DISP_loop(func_name)     is called continues if function quit on every button even or trigger event
// - void LCDML_DISP_loop_end(func_name) is called when quit button or LCDML_DISP_funcend is called


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
void LCDML_DISP_setup(LCDML_FUNC_back)
// *********************************************************************
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


// *********************************************************************
// *********************************************************************
// the next code is a little bit complexer, i remove all known comments, only new things have a commentar
// when you have questions to the setup, loop and loop_end function, look to the examples above
// *********************************************************************
// *********************************************************************


// *********************************************************************
// Set Date
// *********************************************************************
// this example to set a datetime is a little bit complexer as the first examples

// you can remove this part when you are using a time lib
// this makros are only for this examples and can be delete 
// begin block
uint8_t vh, vmi, vs, vd,vmo, vy = 0;
#define hour() (vh%24)
#define minute() (vmi%60)
#define second() (vs%60)
#define day() (vd%32)
#define month() (vmo%13)
#define year() vy
#define setTime(h,mi,s,d,mo,y) vh=((h==-1)?23:h); vmi=((mi==-1)?59:mi); vs=((s==-1)?59:s); vd=((d==-1)?31:d); vmo=((mo==-1)?12:mo); vy=y;
// end block to remove when an extern class is used
  
// define global variable  
uint8_t g_setDate_cursorPos = 0;
// define help function to set the current time
void HELP_FUNC_set_dat(int8_t l_i)
{
  switch(g_setDate_cursorPos) {
    case 0: setTime(hour()+l_i,minute(),second(),day(),month(),year());  break; // hour
    case 1: setTime(hour(),minute()+l_i,second(),day(),month(),year()); break; // min
    case 2: setTime(hour(),minute(),second(),day()+l_i,month(),year()); break; // day
    case 3: setTime(hour(),minute(),second(),day(),month()+l_i,year()); break; // month
    case 4: setTime(hour(),minute(),second(),day(),month(),year()+l_i); break; // year
  }
}
// define help function to display the current clock settings
void digitalClockDisplay()
{
  // init display
  lcd.clear();  
  lcd.setCursor(3,0); 
  
  // display hour value
  printDigits(hour());  lcd.print(F(":"));
  
  // display minute value, move output when this value is edit
  if(g_setDate_cursorPos == 1) { lcd.print(F(" ")); }
  printDigits(minute());  lcd.print(F(":"));
  
  // display second value
  printDigits(second());
  // set cursor to next row
  lcd.setCursor(3,1);  
  
  // display day value
  lcd.print(day());  lcd.print(F("."));
  
  // print month value, move output when this value is edit
  if(g_setDate_cursorPos == 3) { lcd.print(F(" ")); }
  lcd.print(month()); lcd.print(F("."));
  
  // print year value, move output when this value is edit  
  if(g_setDate_cursorPos == 4) { lcd.print(F(" ")); }
  lcd.print(year());
  
  // set cursor blink on the correct possion
  switch(g_setDate_cursorPos) {
    case 0: lcd.setCursor(2,0); lcd.print(F("H")); lcd.setCursor(2,0); lcd.blink(); break; //hour
    case 1: lcd.setCursor(6,0); lcd.print(F("M")); lcd.setCursor(6,0); lcd.blink(); break; //min
    case 2: lcd.setCursor(2,1); lcd.print(F("D")); lcd.setCursor(2,1); lcd.blink(); break; //day
    case 3: lcd.setCursor(5+((day()<10)?0:1),1); lcd.print(F("M")); lcd.setCursor(5+((day()<10)?0:1),1); lcd.blink(); break;//month
    case 4: lcd.setCursor(7+((day()<10)?0:1)+((month()<10)?0:1),1); lcd.print(F("Y")); lcd.setCursor(7+((day()<10)?0:1)+((month()<10)?0:1),1); lcd.blink(); break; //year
    default: lcd.noBlink(); break;
   }
}
// define help function to display digits in front of the value
void printDigits(int digits)
{
  // utility function for digital clock display: prints preceding colon and leading 0  
  if(digits < 10) {
    lcd.print(F("0"));
    lcd.print(digits);
  }
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_set_date)
// *********************************************************************
{
  // setup function
  LCDML_DISP_triggerMenu(500); // set trigger for this function to 1000 millisecounds
  // print default value
  digitalClockDisplay();
}
void LCDML_DISP_loop(LCDML_FUNC_set_date)
{       
  if(LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
    // LCDML_DISP_funcend calls the loop_end function

    if (LCDML_BUTTON_checkUp())    { HELP_FUNC_set_dat(+1); LCDML_BUTTON_resetUp(); }
    if (LCDML_BUTTON_checkDown())  { HELP_FUNC_set_dat(-1);  LCDML_BUTTON_resetDown(); }
    if (LCDML_BUTTON_checkRight()) { g_setDate_cursorPos=(g_setDate_cursorPos+1)%5; LCDML_BUTTON_resetRight(); }
    if (LCDML_BUTTON_checkLeft())  { g_setDate_cursorPos=(((g_setDate_cursorPos-1)>=0)?(g_setDate_cursorPos-1):4)%5; LCDML_BUTTON_resetLeft(); }      
    // only update display when its needed
    digitalClockDisplay()  ;
  }   
    
  // reset initscreenloop
  LCDML_DISP_resetIsTimer();
}

void LCDML_DISP_loop_end(LCDML_FUNC_set_date) 
{  
  // disable the cursor
  lcd.noBlink();  
}




// *********************************************************************
// *********************************************************************
// the next code is a little bit complexer, i remove all known comments, only new things have a commentar
// *********************************************************************
// *********************************************************************

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_prog_disable)
// *********************************************************************
{
  LCDML_DISP_groupDisable(_LCDML_G2); // disable all menu items in G2
  LCDML_DISP_groupEnable(_LCDML_G3);  // enable all menu items in G3
  LCDML_DISP_funcend();  
}
void LCDML_DISP_loop(LCDML_FUNC_prog_disable) 
{
}
void LCDML_DISP_loop_end(LCDML_FUNC_prog_disable) {
  LCDML.goRoot(); // go to root element (first element of this menu with id=0)
}


// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_prog_enable)
// *********************************************************************
{
  LCDML_DISP_groupEnable(_LCDML_G2);  // enable all menu items in G2
  LCDML_DISP_groupDisable(_LCDML_G3); // disable all menu items in G3
  LCDML_DISP_funcend();
}
void LCDML_DISP_loop(LCDML_FUNC_prog_enable) 
{
}
void LCDML_DISP_loop_end(LCDML_FUNC_prog_enable) 
{ 
  LCDML.goRoot(); // go to root element (first element of this menu with id=0)
}



// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_backend_control)
// *********************************************************************
{  
  // with the function LCDML_BACK_...  you can control the BACKEND function system
  // LCDML_BACK_start: start a function (loop)
  // LCDML_BACK_stop: stop a function (loop)
  // LCDML_BACK_stopStable: stop a function (loop) and start the (stopStable) function
  // LCDML_BACK_restart: start a function (loop and setup)
  switch(LCDML_DISP_getParameter()) {
    case 0: 
      LCDML_BACK_start(LCDML_BACKEND_test10); 
      break; // start the backend function "test10", this function is called every 10 sec
    case 1: 
      LCDML_BACK_restart(LCDML_BACKEND_test10); 
      break;// restart the backend function "test10" (loop with setup)
    case 2: 
      LCDML_BACK_stop(LCDML_BACKEND_test10); 
      break; // stop the backend "test10" function
    case 3: 
      LCDML_BACK_stopStable(LCDML_BACKEND_test10); 
      break; // stable stop the backend "test10" function
    
    case 10: 
      LCDML_BACK_start(LCDML_BACKEND_test20); // start the "test20" backend functionb;
      break;
    case 11: 
      LCDML_BACK_stop(LCDML_BACKEND_test20); // stop the "test20" backend functionb;
      break;
    case 12: 
      // on dynamic backend function, you can change the loop time every time
      // the next function set the loop time to 500 milli secounds
      LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 500); // set loop time of "test20" to 500 ms
      LCDML_BACK_start(LCDML_BACKEND_test20); // start this backend function directly
      // you can get the current loop time with this function
      Serial.println(  LCDML_BACK_dynamic_getLoopTime(LCDML_BACKEND_test20)  );      
      break;
    case 13:
      LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 500); // set loop time of "test20" to 500 ms
      LCDML_BACK_start(LCDML_BACKEND_test20); // start this backend function directly    
      break;
    
    case 14:
      // setup function
      LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 10000); // set loop time of "test20" to 10 sec
      LCDML_BACK_start(LCDML_BACKEND_test20); // start this backend function directly
      break; 
    
    case 20:
      LCDML_BACK_event_start(LCDML_BACKEND_test30); // start an ev
      break;
    
    default: 
      break;
  }
  LCDML_DISP_funcend(); // ends this function
}
void LCDML_DISP_loop(LCDML_FUNC_backend_control) 
{
}
void LCDML_DISP_loop_end(LCDML_FUNC_backend_control) 
{
}
