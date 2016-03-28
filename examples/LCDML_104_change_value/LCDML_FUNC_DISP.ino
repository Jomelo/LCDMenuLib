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


/* ===============================================
 * Set Time
 * =============================================== */
  // you can remove this part when you are using a time lib
  // this makros are only for this examples and can be delete  
  uint8_t vh, vmi, vs, vd,vmo, vy = 0;
  #define hour()    vh
  #define minute()  vmi
  #define second()  vs
  #define day()     vd
  #define month()   vmo
  #define year()    vy
  #define setTime(h,mi,s,d,mo,y) vh=h; vmi=mi; vs=s; vd=d; vmo=mo; vy=y;
  // define global variable  
  uint8_t _pos = 0;
  // define help function to set the current time
  void HELP_FUNC_set_dat(int8_t l_i)
  {
    switch(_pos)
    {
      case 0: setTime(hour()+l_i,minute(),second(),day(),month(),year());  break; // hour
      case 1: setTime(hour(),minute()+l_i,second(),day(),month(),year()); break; // min
      case 2: setTime(hour(),minute(),second(),day()+l_i,month(),year()); break; // day
      case 3: setTime(hour(),minute(),second(),day(),month()+l_i,year()); break; // month
      case 4: setTime(hour(),minute(),second(),day(),month(),year()+l_i); break; // year
    }
  }
  // define help function to display the current clock settings
  void digitalClockDisplay(){   
   
    lcd.setCursor(3,0);
    printDigits(hour());
    lcd.print(":");
    if(_pos == 1) { lcd.print(" "); }
    printDigits(minute());
    lcd.print(":");
    printDigits(second());
    lcd.setCursor(3,1);  
    lcd.print(day());
    lcd.print(".");
    if(_pos == 3) { lcd.print(" "); }
    lcd.print(month());
    lcd.print(".");
    if(_pos == 4) { lcd.print(" "); }
    lcd.print(year());
    // set cursor
    switch(_pos) {
      case 0: lcd.setCursor(2,0); lcd.blink(); break; //hour
      case 1: lcd.setCursor(6,0); lcd.blink(); break; //min
      case 2: lcd.setCursor(2,1); lcd.blink(); break; //day
      case 3: lcd.setCursor(5+((day()<10)?0:1),1); lcd.blink(); break;//month
      case 4: lcd.setCursor(7+((day()<10)?0:1)+((month()<10)?0:1),1); lcd.blink(); break; //year
      default: lcd.noBlink(); break;
     }
  }
  // define help function to display digits in front of the value
  void printDigits(int digits){
    // utility function for digital clock display: prints preceding colon and leading 0  
    if(digits < 10) {
      lcd.print('0');
	}
    lcd.print(digits);
  }
// ===============================================
// Set Time
void LCDML_DISP_setup(LCDML_FUNC_change_datetime)
// ********************************************************************* */
{
  // setup function
  //LCDML_DISP_triggerMenu(500); // set trigger for this function to 1000 millisecounds
  // print default value
  digitalClockDisplay();
}


void LCDML_DISP_loop(LCDML_FUNC_change_datetime)
{
  // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
  // the quit button works in every DISP function without any checks; it starts the loop_end function
       
  if(LCDML_BUTTON_checkAny()) { // check if any button is presed (enter, up, down, left, right)
    // LCDML_DISP_funcend calls the loop_end function

      if (LCDML_BUTTON_checkUp())    { HELP_FUNC_set_dat(+1); LCDML_BUTTON_resetUp(); }
      if (LCDML_BUTTON_checkDown())  { HELP_FUNC_set_dat(-1);  LCDML_BUTTON_resetDown(); }
      if (LCDML_BUTTON_checkRight()) { _pos=(_pos+1)%5; LCDML_BUTTON_resetRight(); }
      lcd.clear();
      digitalClockDisplay()  ;
   }   
  
}


void LCDML_DISP_loop_end(LCDML_FUNC_change_datetime) 
{  
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing

    // disable the cursor
  lcd.noBlink();  
} 

