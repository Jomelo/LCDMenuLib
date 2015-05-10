
/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_information)
/* ********************************************************************* */
{
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
  LCDML.FuncEnd(0,1,1,1,1,1); 
}
void LCDML_DISP_loop_end(LCDML_FUNC_information)
{
}

  

/* ********************************************************************* */
uint8_t g_func_timer_info = 0;  // time counter
unsigned long g_timer_1 = 0;    // timer variable
void LCDML_DISP_setup(LCDML_FUNC_timer_info)
/* ********************************************************************* */
{  
  // clear the display and init the time counter value    
  lcd.print(F("x sec warten"));
  g_func_timer_info = 10;    
  
  LCDML_TRIGGER(100); 
}

void LCDML_DISP_loop(LCDML_FUNC_timer_info)
{   
  if(LCDML.Timer(g_timer_1, 1000)) { 
    g_func_timer_info--;                 // increment the value every secound */
    lcd.setCursor(0, 0);                // set cursor pos */
    lcd.print(g_func_timer_info);       // print the time counter value */
  }

  // check if the function ends normaly
  if (g_func_timer_info <= 0)
  {
    // end function for callback
    LCDML.FuncEnd(1,0,0,0,0,0);  
  }   
}

void LCDML_DISP_loop_end(LCDML_FUNC_timer_info) {}






/* ********************************************************************* */
uint8_t g_button_value = 0;
void LCDML_DISP_setup(LCDML_FUNC_p2)
/* ********************************************************************* */
{ 
  lcd.setCursor(0, 0);
  lcd.print(F("3 mal Links drucken"));
  lcd.setCursor(0, 1);
  lcd.print(F("Anzahl: 0"));
  // Reset Button Value
  g_button_value = 0; 
}

void LCDML_DISP_loop(LCDML_FUNC_p2)
{
  // * --------- LOOP ----------
  // * Hier wird nur ein Ereignis ausgelöst, sobald ein Button gedrückt
  // * wurde. Die Funktion LCDML.checkButtons liefert true, wenn ein Button
  // * seit dem letztem durchlauf betätigt wurde, ansonsten false.
  if (LCDML.checkButtons())
  {
    if (LCDML_checkButtonLeft())
    {
      LCDML_resetButtonLeft();
      g_button_value++;
    }

    // Die Position des Cursor wird verschoben
    lcd.setCursor(8, 1);
    // Die Anzahl wie oft ein Button gedrückt wurde, wird angezeigt
    lcd.print(g_button_value);
  }

  if (g_button_value >= 3) {
    // end function for callback
    LCDML.FuncEnd(1,0,0,0,0,0);   
  } 
}
void LCDML_DISP_loop_end(LCDML_FUNC_p2) {}



/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_back)
/* ********************************************************************* */
{ }
void LCDML_DISP_loop(LCDML_FUNC_back) { LCDML.FuncEnd(1,0,0,0,0,0); LCDML.Button_quit(); }
void LCDML_DISP_loop_end(LCDML_FUNC_back) {}


/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_prog_disable)
/* ********************************************************************* */
{
  Serial.println("disable");
  LCDML_DISP_groupDisable(_LCDML_G2);
  LCDML_DISP_groupEnable(_LCDML_G3);  
  LCDML.goRoot();  
}
void LCDML_DISP_loop(LCDML_FUNC_prog_disable) { LCDML.FuncEnd(1,0,0,0,0,0); LCDML.Button_quit(); }
void LCDML_DISP_loop_end(LCDML_FUNC_prog_disable) {}


/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_prog_enable)
/* ********************************************************************* */
{
  Serial.println("enable");
  LCDML_DISP_groupEnable(_LCDML_G2);
  LCDML_DISP_groupDisable(_LCDML_G3);
  LCDML.goRoot(); 
}
void LCDML_DISP_loop(LCDML_FUNC_prog_enable) { LCDML.FuncEnd(1,0,0,0,0,0); LCDML.Button_quit(); }
void LCDML_DISP_loop_end(LCDML_FUNC_prog_enable) {}


/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_start)
/* ********************************************************************* */
{
  LCDML_BACK_start(LCDML_BACKEND_test10);  
}
void LCDML_DISP_loop(LCDML_FUNC_test10_start) { LCDML.FuncEnd(1,0,0,0,0,0); LCDML.Button_quit(); }
void LCDML_DISP_loop_end(LCDML_FUNC_test10_start) {}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_restart)
/* ********************************************************************* */
{
  LCDML_BACK_restart(LCDML_BACKEND_test10);  
}
void LCDML_DISP_loop(LCDML_FUNC_test10_restart) { LCDML.FuncEnd(1,0,0,0,0,0); LCDML.Button_quit(); }
void LCDML_DISP_loop_end(LCDML_FUNC_test10_restart) {}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_stop)
/* ********************************************************************* */
{
  LCDML_BACK_stop(LCDML_BACKEND_test10);  
}
void LCDML_DISP_loop(LCDML_FUNC_test10_stop) { LCDML.FuncEnd(1,0,0,0,0,0); LCDML.Button_quit(); }
void LCDML_DISP_loop_end(LCDML_FUNC_test10_stop) {}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test10_stop_stable)
/* ********************************************************************* */
{
  LCDML_BACK_stopStable(LCDML_BACKEND_test10);  
}
void LCDML_DISP_loop(LCDML_FUNC_test10_stop_stable) { LCDML.FuncEnd(1,0,0,0,0,0); LCDML.Button_quit(); }
void LCDML_DISP_loop_end(LCDML_FUNC_test10_stop_stable) {}




/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_start)
/* ********************************************************************* */
{
  LCDML_BACK_start(LCDML_BACKEND_test20);  
  LCDML_DISP_setFuncEnd(1,0,0,0,0,0);// (direct,enter, up, down, left, right)
}
void LCDML_DISP_loop(LCDML_FUNC_test20_start) {}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_start) {}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_stop)
/* ********************************************************************* */
{
  LCDML_BACK_stop(LCDML_BACKEND_test20);  
  LCDML_DISP_setFuncEnd(1,0,0,0,0,0);// (direct,enter, up, down, left, right)
}
void LCDML_DISP_loop(LCDML_FUNC_test20_stop) {}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_stop) {}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_500ms)
/* ********************************************************************* */
{
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 500);  
  LCDML_DISP_setFuncEnd(1,0,0,0,0,0);// (direct,enter, up, down, left, right)
}
void LCDML_DISP_loop(LCDML_FUNC_test20_500ms) {}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_500ms) {}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_1s)
/* ********************************************************************* */
{
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 1000);  
  LCDML_DISP_setFuncEnd(1,0,0,0,0,0);// (direct,enter, up, down, left, right)
}
void LCDML_DISP_loop(LCDML_FUNC_test20_1s) {}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_1s) {}

/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test20_10s)
/* ********************************************************************* */
{
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_test20, 100000);  
  LCDML_DISP_setFuncEnd(1,0,0,0,0,0);// (direct,enter, up, down, left, right)
}
void LCDML_DISP_loop(LCDML_FUNC_test20_10s) {}
void LCDML_DISP_loop_end(LCDML_FUNC_test20_10s) {}



/* ********************************************************************* */
void LCDML_DISP_setup(LCDML_FUNC_test30_start)
/* ********************************************************************* */
{
  LCDML_BACK_event_start(LCDML_BACKEND_test30);
  LCDML_DISP_setFuncEnd(1,0,0,0,0,0);// (direct,enter, up, down, left, right)
}
void LCDML_DISP_loop(LCDML_FUNC_test30_start) {}
void LCDML_DISP_loop_end(LCDML_FUNC_test30_start) {}





