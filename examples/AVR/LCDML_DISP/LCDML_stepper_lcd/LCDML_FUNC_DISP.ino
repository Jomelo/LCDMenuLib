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
//LCDML_FUNC_MANUAL LCD UPDATE 
void menu_manual_on_lcd_update() {
  lcd.setCursor(11, 1); // set cursor   
  lcd.print(g_button_value); // print change content
  lcd.print("  ");
  lcd.setCursor(6, 3); //
  lcd.print(stepper1TimeArray[abs(g_button_value)]);
  lcd.print("    ");        
  lcd.setCursor(10, 1); 
}

// *********************************************************************
// CHECK ENCODER g_button_value_interval_check 
int g_button_value_interval_check() {
  if ( g_button_value > 0 ){
    stepper1.moveTo(sliderTotalSteps);
    if (  g_button_value >= 23){
      g_button_value = 23; 
    }
  }

  else if ( g_button_value < 0 ){
    stepper1.moveTo(sliderHomePosition);
    if (  g_button_value <= -23){
      g_button_value = -23; 
    }
  }
  
  else if ( g_button_value = 0 ){
    stepper1.stop();
  }
        
  return g_button_value;
}
     
 
// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_SET_SPEED)
// *********************************************************************
{
  g_button_value = 0;
   
  // lcd setup content 
  lcd.setCursor(0, 0);
  lcd.print(F("Automatic Set Speed"));
  lcd.setCursor(0, 1);
  lcd.print(F("INDEX SPD:"));
  lcd.setCursor(0, 3);
  lcd.print(F("TIME:"));
  lcd.setCursor(6, 3);
  lcd.print(F("0.00"));
  lcd.setCursor(16, 3);
  lcd.print(F("m.s"));
  lcd.setCursor(11, 1);
  lcd.print(g_button_value);
  lcd.setCursor(10, 1);

  LCDML_BACK_start(LCDML_BACKEND_stepper1);
  LCDML_DISP_triggerMenu(500);

}

void LCDML_DISP_loop(LCDML_FUNC_SET_SPEED) 
{  
  
  Serial.println("LCDML_DISP_loop(LCDML_FUNC_SET_SPEED)");
  
  if (LCDML_BUTTON_checkAny()) // check if any button is pressed (enter, up, down, left, right)
  {
    if (LCDML_BUTTON_checkLeft() || LCDML_BUTTON_checkUp()) 
      {
      LCDML_BUTTON_resetLeft(); // reset
      LCDML_BUTTON_resetUp(); // reset  
      --g_button_value;
      g_button_value_interval_check();
      menu_manual_on_lcd_update();
      }    

    if (LCDML_BUTTON_checkRight() || LCDML_BUTTON_checkDown()) 
      {
      LCDML_BUTTON_resetRight(); // reset
      LCDML_BUTTON_resetDown(); // reset 
      ++g_button_value;
      g_button_value_interval_check();
      menu_manual_on_lcd_update();
      }
  }

  if(LCDML_BUTTON_checkEnter()) {         
        LCDML_DISP_funcend();
    } 
   
}

void LCDML_DISP_loop_end(LCDML_FUNC_SET_SPEED)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 
  int g_button_value = 0;
  float stepper1CurrentSpeed = 0; 
  stepper1.stop();  
  LCDML_BACK_stop(LCDML_BACKEND_stepper1);
 
}  

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_back)
// *********************************************************************
{
  // setup
  // is called only if it is started
}
   
void LCDML_DISP_loop(LCDML_FUNC_back)
{
  // loop
  // is called when it is triggert
  LCDML_DISP_resetIsTimer(); // reset the initscreen timer
  LCDML.goBack();            // go back
  LCDML_DISP_funcend();      // LCDML_DISP_funcend calls the loop_end function
}
   
void LCDML_DISP_loop_end(LCDML_FUNC_back)
{
  // loop end
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 
}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_MANUAL)
// *********************************************************************
{

  lcd.setCursor(0, 0);
  lcd.print(F("Press reset to exit Manual Mode"));
  
  LCDML_BACK_stop(LCDML_BACKEND_control);
  LCDML_BACK_stop(LCDML_BACKEND_menu);
  
  stepper1.stop();
  LCDML_BACK_start(LCDML_BACKEND_stepper1);

}
   
void LCDML_DISP_loop(LCDML_FUNC_MANUAL)
{


}
   
void LCDML_DISP_loop_end(LCDML_FUNC_MANUAL)
{
  // loop end
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 

}

// *********************************************************************
void LCDML_DISP_setup(LCDML_FUNC_DISPLAY_RUN)
// *********************************************************************
{
  g_button_value = 0;
   
  // lcd setup content 
  lcd.setCursor(0, 0);
  lcd.print(F("Display Running"));
  lcd.setCursor(0, 1);
  lcd.print(F("INDEX SPD:"));
  lcd.setCursor(0, 2);
  lcd.print(F("POSITION:"));
  lcd.setCursor(10, 2);
  lcd.print(F("0"));

  lcd.setCursor(11, 1);
  lcd.print(g_button_value);
 

  LCDML_BACK_start(LCDML_BACKEND_stepper1);
  LCDML_DISP_triggerMenu(500);

}

void LCDML_DISP_loop(LCDML_FUNC_DISPLAY_RUN) 
{  
  lcd.setCursor(11, 1); // set cursor   
  lcd.print(g_button_value); // print change content
  lcd.print("  ");
  lcd.setCursor(10, 2); //
  lcd.print(stepper1.currentPosition());
  lcd.print("     ");        
  
  if(LCDML_BUTTON_checkEnter()) {         
        LCDML_DISP_funcend();
    } 
   
}

void LCDML_DISP_loop_end(LCDML_FUNC_DISPLAY_RUN)
{
  // this functions is ever called when a DISP function is quit
  // you can here reset some global vars or do nothing 
  int g_button_value = 0;
  float stepper1CurrentSpeed = 0; 
  stepper1.stop();  
  LCDML_BACK_stop(LCDML_BACKEND_stepper1);
 
}  

