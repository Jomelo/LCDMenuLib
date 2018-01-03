// =====================================================================
//
// CONTROL
//
// =====================================================================
// *********************************************************************
// *********************************************************************
// content:
// (0) Control over serial interface
// (1) Control over one analog input 
// (2) Control over 4 - 6 digital input pins (internal pullups enabled)
// (3) Control over encoder (internal pullups enabled)
// (4) Control with Keypad
// (5) Control with an ir remote
// (6) Control with a youstick
// *********************************************************************

#define _LCDML_CONTROL_cfg      0  


// therory:
// "#if" is a preprocessor directive and no error, look here:
// (english) https://en.wikipedia.org/wiki/C_preprocessor
// (german)  https://de.wikipedia.org/wiki/C-Pr%C3%A4prozessor


// *********************************************************************
// CONTROL TASK, DO NOT CHANGE
// *********************************************************************
void LCDML_BACK_setup(LCDML_BACKEND_control)      
// *********************************************************************
{
  // call setup   
  LCDML_CONTROL_setup();      
}
// backend loop
boolean LCDML_BACK_loop(LCDML_BACKEND_control)
{    
  // call loop
  LCDML_CONTROL_loop();

  // go to next backend function and do not block it
  return true;  
}
// backend stop stable
void LCDML_BACK_stable(LCDML_BACKEND_control)
{
}




// *********************************************************************
// *************** (0) CONTROL OVER SERIAL INTERFACE *******************
// *********************************************************************
#if(_LCDML_CONTROL_cfg == 0)
// settings
  # define _LCDML_CONTROL_serial_enter           'e'
  # define _LCDML_CONTROL_serial_up              'w'
  # define _LCDML_CONTROL_serial_down            's'
  # define _LCDML_CONTROL_serial_left            'a'
  # define _LCDML_CONTROL_serial_right           'd'
  # define _LCDML_CONTROL_serial_quit            'q'
// *********************************************************************
// setup
void LCDML_CONTROL_setup()
{
}
// *********************************************************************
// loop
void LCDML_CONTROL_loop()
{
  // check if new serial input is available  
  if (Serial.available()) {
    // read one char from input buffer   
    switch (Serial.read())
    {
      case _LCDML_CONTROL_serial_enter:  LCDML_BUTTON_enter(); break;
      case _LCDML_CONTROL_serial_up:     LCDML_BUTTON_up();    break;
      case _LCDML_CONTROL_serial_down:   LCDML_BUTTON_down();  break;
      case _LCDML_CONTROL_serial_left:   LCDML_BUTTON_left();  break;
      case _LCDML_CONTROL_serial_right:  LCDML_BUTTON_right(); break;
      case _LCDML_CONTROL_serial_quit:   LCDML_BUTTON_quit();  break;
      default: break;
    } 
  }
}
// *********************************************************************
// ******************************* END *********************************
// *********************************************************************





// *********************************************************************
// *************** (1) CONTROL OVER ONE ANALOG PIN *********************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 1)
// settings
  #define _LCDML_CONTROL_analog_pin              0
  // when you did not use a button set the value to zero
  #define _LCDML_CONTROL_analog_enter_min        850     // Button Enter
  #define _LCDML_CONTROL_analog_enter_max        920  
  #define _LCDML_CONTROL_analog_up_min           520     // Button Up
  #define _LCDML_CONTROL_analog_up_max           590   
  #define _LCDML_CONTROL_analog_down_min         700     // Button Down
  #define _LCDML_CONTROL_analog_down_max         770   
  #define _LCDML_CONTROL_analog_back_min         950     // Button Back
  #define _LCDML_CONTROL_analog_back_max         1020   
  #define _LCDML_CONTROL_analog_left_min         430     // Button Left
  #define _LCDML_CONTROL_analog_left_max         500   
  #define _LCDML_CONTROL_analog_right_min        610     // Button Right
  #define _LCDML_CONTROL_analog_right_max        680
// *********************************************************************
// setup
void LCDML_CONTROL_setup()
{
}
// *********************************************************************
// loop
void LCDML_CONTROL_loop()
{
  // check debounce timer  
  if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
    g_LCDML_DISP_press_time = millis(); // reset debounce timer
    
    uint16_t value = analogRead(_LCDML_CONTROL_analog_pin);  // analogpin for keypad
    
    if (value >= _LCDML_CONTROL_analog_enter_min && value <= _LCDML_CONTROL_analog_enter_max) { LCDML_BUTTON_enter(); }
    if (value >= _LCDML_CONTROL_analog_up_min    && value <= _LCDML_CONTROL_analog_up_max)    { LCDML_BUTTON_up();    }
    if (value >= _LCDML_CONTROL_analog_down_min  && value <= _LCDML_CONTROL_analog_down_max)  { LCDML_BUTTON_down();  }
    if (value >= _LCDML_CONTROL_analog_left_min  && value <= _LCDML_CONTROL_analog_left_max)  { LCDML_BUTTON_left();  }
    if (value >= _LCDML_CONTROL_analog_right_min && value <= _LCDML_CONTROL_analog_right_max) { LCDML_BUTTON_right(); }
    if (value >= _LCDML_CONTROL_analog_back_min  && value <= _LCDML_CONTROL_analog_back_max)  { LCDML_BUTTON_quit();  }
  }
}
// *********************************************************************
// ******************************* END *********************************
// *********************************************************************






// *********************************************************************
// *************** (2) CONTROL OVER DIGITAL PINS ***********************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 2)
// settings
  #define _LCDML_CONTROL_digital_low_active      0    // (1 = low active (pullup), 0 = high active (pulldown) button
                                                      // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
  #define _LCDML_CONTROL_digital_enable_quit     1
  #define _LCDML_CONTROL_digital_enable_lr       1
  #define _LCDML_CONTROL_digital_enter           8    
  #define _LCDML_CONTROL_digital_up              9
  #define _LCDML_CONTROL_digital_down            10
  #define _LCDML_CONTROL_digital_quit            11
  #define _LCDML_CONTROL_digital_left            12
  #define _LCDML_CONTROL_digital_right           13
// *********************************************************************
// setup
void LCDML_CONTROL_setup()
{
  // init buttons
  pinMode(_LCDML_CONTROL_digital_enter      , INPUT_PULLUP);
  pinMode(_LCDML_CONTROL_digital_up         , INPUT_PULLUP);
  pinMode(_LCDML_CONTROL_digital_down       , INPUT_PULLUP);  
  # if(_LCDML_CONTROL_digital_enable_quit == 1)
    pinMode(_LCDML_CONTROL_digital_quit     , INPUT_PULLUP);
  # endif
  # if(_LCDML_CONTROL_digital_enable_lr == 1)
    pinMode(_LCDML_CONTROL_digital_left     , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_right    , INPUT_PULLUP);
  # endif
}
// *********************************************************************
// loop
void LCDML_CONTROL_loop()
{
  #if(_LCDML_CONTROL_digital_low_active == 1)
  #  define _LCDML_CONTROL_digital_a !
  #else
  #  define _LCDML_CONTROL_digital_a
  #endif
  
  uint8_t but_stat = 0x00;
  
  bitWrite(but_stat, 0, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_enter)));
  bitWrite(but_stat, 1, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_up)));
  bitWrite(but_stat, 2, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_down)));
  #if(_LCDML_CONTROL_digital_enable_quit == 1)
  bitWrite(but_stat, 3, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_quit)));
  #endif
  #if(_LCDML_CONTROL_digital_enable_lr == 1)
  bitWrite(but_stat, 4, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_left)));
  bitWrite(but_stat, 5, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_right)));
  #endif  
  
  if (but_stat > 0) {
    if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
      g_LCDML_DISP_press_time = millis(); // reset press time
    
      if (bitRead(but_stat, 0)) { LCDML_BUTTON_enter(); }
      if (bitRead(but_stat, 1)) { LCDML_BUTTON_up();    }
      if (bitRead(but_stat, 2)) { LCDML_BUTTON_down();  }
      if (bitRead(but_stat, 3)) { LCDML_BUTTON_quit();  }
      if (bitRead(but_stat, 4)) { LCDML_BUTTON_left();  }
      if (bitRead(but_stat, 5)) { LCDML_BUTTON_right(); }        
    }    
  }
}
// *********************************************************************
// ******************************* END *********************************
// *********************************************************************






// *********************************************************************
// *************** (3) CONTROL WITH ENCODER ****************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 3)
// settings
  #define _LCDML_CONTROL_encoder_pin_a                  4 // pin encoder b
  #define _LCDML_CONTROL_encoder_pin_b                  5 // pin encoder a
  #define _LCDML_CONTROL_encoder_pin_button             7 // pin taster
  #define _LCDML_CONTROL_encoder_high_active            0 // (0 = low active (pullup), 1 = high active (pulldown)) button
                                                          // http://playground.arduino.cc/CommonTopics/PullUpDownResistor

  #define _LCDML_CONTROL_encoder_refresh_time           5UL  // 5ms
  #define _LCDML_CONTROL_encoder_switch_time            75UL // 75 ms 

// macros which define the functionality
  #define _LCDML_CONTROL_encoder_switch_press_short()   LCDML_BUTTON_enter()
  #define _LCDML_CONTROL_encoder_rotary_a()             LCDML_BUTTON_up()  
  #define _LCDML_CONTROL_encoder_rotary_b()             LCDML_BUTTON_down()

  #define _LCDML_CONTROL_encoder_advanced_switch        1
  #define _LCDML_CONTROL_encoder_switch_press_long()    LCDML_BUTTON_quit()

  #define _LCDML_CONTROL_encoder_advanced_rotary        1
  #define _LCDML_CONTROL_encoder_rotary_a_and_press()   LCDML_BUTTON_left()
  #define _LCDML_CONTROL_encoder_rotary_b_and_press()   LCDML_BUTTON_right()
                                                      
  #define _LCDML_CONTROL_encoder_t_long_press    1000   // maximum is 1275 (5*255)
  
// global defines
  uint8_t  g_LCDML_CONTROL_encoder_t_prev = 0;
  uint8_t  g_LCDML_CONTROL_encoder_a_prev = 0;
  uint8_t  g_LCDML_CONTROL_t_pressed = 0;
  uint8_t  g_LCDML_CONTROL_t_press_time = 0;

// *********************************************************************
// setup
void LCDML_CONTROL_setup()
{
  // set encoder update intervall time 
  LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_control, _LCDML_CONTROL_encoder_refresh_time);  // 5ms 

  // init pins
  if(_LCDML_CONTROL_encoder_high_active == 0) 
  {  
    pinMode(_LCDML_CONTROL_encoder_pin_a      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_encoder_pin_b      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_encoder_pin_button , INPUT_PULLUP);
  } 
}

// *********************************************************************
// loop
void LCDML_CONTROL_loop()
{    
  // read encoder status
  unsigned char a = digitalRead(_LCDML_CONTROL_encoder_pin_a);
  unsigned char b = digitalRead(_LCDML_CONTROL_encoder_pin_b);
  unsigned char t = digitalRead(_LCDML_CONTROL_encoder_pin_button);
  
  // change button status if high and low active are switched
  if (_LCDML_CONTROL_encoder_high_active == 1) {
    t = !t;
  }

  // check if the button was pressed and save this state
  if((millis() - g_LCDML_DISP_press_time) >= _LCDML_CONTROL_encoder_switch_time) {
    g_LCDML_DISP_press_time = millis(); // reset button press time
    
    // press button once
    if (t == false && g_LCDML_CONTROL_encoder_t_prev == 0) 
    {
      g_LCDML_CONTROL_t_pressed = 1;
    } 
    else {
      g_LCDML_CONTROL_encoder_t_prev = 0;
    }
  } 

  // check if button is currently pressed
  if(t == false) 
  {
    // check if the advanced rotary function is enabled
    if(_LCDML_CONTROL_encoder_advanced_rotary == 1)
    {
      // check if the rotary encoder was moved
      if (a == false && g_LCDML_CONTROL_encoder_a_prev ) {
        g_LCDML_CONTROL_encoder_t_prev = 1;
        
        if (b == false) 
        { 
          // switch active and rotary b moved
          _LCDML_CONTROL_encoder_rotary_b_and_press();       
        }
        else    
        { 
          // switch active and rotary a moved
          _LCDML_CONTROL_encoder_rotary_a_and_press(); 
        }
  
        g_LCDML_CONTROL_t_pressed = 0;
        g_LCDML_CONTROL_t_press_time = 0;            
      }
    } 

    // check advanced mode "long press switch"
    if(_LCDML_CONTROL_encoder_advanced_switch == 1)
    {    
      // button was pressed
      if(g_LCDML_CONTROL_t_pressed == 1) 
      {
        // check overrun and stop
        if(g_LCDML_CONTROL_t_press_time < 255) 
        {
          g_LCDML_CONTROL_t_press_time++;
        }
      }
    }
  }
  else
  {
    // switch is not active

    // check encoder
    if (a == false && g_LCDML_CONTROL_encoder_a_prev) {
      g_LCDML_CONTROL_encoder_t_prev = 1;
      
      if (b == false) 
      { 
        _LCDML_CONTROL_encoder_rotary_a();        
      }
      else    
      { 
        _LCDML_CONTROL_encoder_rotary_b(); 
      }

      g_LCDML_CONTROL_t_pressed = 0;
      g_LCDML_CONTROL_t_press_time = 0;
      g_LCDML_DISP_press_time = millis();            
    } 

    // check if an button was pressed
    if(g_LCDML_CONTROL_t_pressed == 1) 
    {
      if(g_LCDML_CONTROL_t_press_time * _LCDML_CONTROL_encoder_refresh_time >= _LCDML_CONTROL_encoder_t_long_press && _LCDML_CONTROL_encoder_advanced_switch == 1)
      {        
        _LCDML_CONTROL_encoder_switch_press_long();
      } 
      else 
      {
        _LCDML_CONTROL_encoder_switch_press_short();
      }
      
      g_LCDML_CONTROL_t_pressed = 0;
      g_LCDML_CONTROL_t_press_time = 0;
      g_LCDML_DISP_press_time = millis();
    }
  }
  
  g_LCDML_CONTROL_encoder_a_prev = a;  // set new encoder status 
  
}
// *********************************************************************
// ******************************* END *********************************
// *********************************************************************





// *********************************************************************
// *************** (4) CONTROL WITH A KEYPAD ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 4)
// include
  // more information under http://playground.arduino.cc/Main/KeypadTutorial
  #include <Keypad.h>
// settings
  #define _LCDML_CONTROL_keypad_rows 4 // Four rows
  #define _LCDML_CONTROL_keypad_cols 3 // Three columns
// global vars
  char keys[_LCDML_CONTROL_keypad_rows][_LCDML_CONTROL_keypad_cols] = { 
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'#','0','*'}
  };  
  byte rowPins[_LCDML_CONTROL_keypad_rows] = { 9, 8, 7, 6 };  // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
  byte colPins[_LCDML_CONTROL_keypad_cols] = { 12, 11, 10 };  // Create the Keypad
// objects
  Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, _LCDML_CONTROL_keypad_rows, _LCDML_CONTROL_keypad_cols );
// *********************************************************************
// setup
void LCDML_CONTROL_setup()
{
}
// *********************************************************************
// loop
void LCDML_CONTROL_loop()
{    
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch (key)
    {
      case '#': LCDML_BUTTON_enter(); break;
      case '2': LCDML_BUTTON_up();    break;
      case '8': LCDML_BUTTON_down();  break;
      case '4': LCDML_BUTTON_left();  break;
      case '6': LCDML_BUTTON_right(); break;
      case '*': LCDML_BUTTON_quit();  break;
      default: break;       
    }
  } 
}
// *********************************************************************
// ******************************* END *********************************
// *********************************************************************


// *********************************************************************
// *************** (5) CONTROL WITH IR REMOTE ***************************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 5)
	// ir include (this lib have to be installed) 
	#include <IRremote.h>
	// ir global vars
	int RECV_PIN = 11; 
	// ir objects
	IRrecv irrecv(RECV_PIN);
	decode_results results;
  
// *********************************************************************
// setup (nothing change here)
void LCDML_CONTROL_setup()
{
	irrecv.enableIRIn(); // Start the receiver
}
// *********************************************************************
// loop
// change in this function the ir values to your values
void LCDML_CONTROL_loop()
{  
	if (irrecv.decode(&results))
	{
		// comment this line out, to check the correct code 
		//Serial.println(results.value, HEX);
    
		// in this switch case you have to change the value 0x...1 to the correct ir code
		switch (results.value)
		{
			case 0x00000001: LCDML_BUTTON_enter(); break;  
			case 0x00000002: LCDML_BUTTON_up();    break;
			case 0x00000003: LCDML_BUTTON_down();  break;
			case 0x00000004: LCDML_BUTTON_left();  break;
			case 0x00000005: LCDML_BUTTON_right(); break;
			case 0x00000006: LCDML_BUTTON_quit();  break;
			default: break;       
		}
	} 
}
// *********************************************************************
// ******************************* END *********************************
// *********************************************************************



// *********************************************************************
// *************** (6) CONTROL OVER JOYSTICK *********************
// *********************************************************************
#elif(_LCDML_CONTROL_cfg == 6)
	// settings
	#define _LCDML_CONTROL_analog_pinx A0
	#define _LCDML_CONTROL_analog_piny A1
	#define _LCDML_CONTROL_digitalread 33 //don't work with u8glib

	// when you did not use a button set the value to zero
	#define _LCDML_CONTROL_analog_up_min 612 // Button Up
	#define _LCDML_CONTROL_analog_up_max 1023
	#define _LCDML_CONTROL_analog_down_min 0 // Button Down
	#define _LCDML_CONTROL_analog_down_max 412
	#define _LCDML_CONTROL_analog_left_min 612 // Button Left
	#define _LCDML_CONTROL_analog_left_max 1023
	#define _LCDML_CONTROL_analog_right_min 0 // Button Right
	#define _LCDML_CONTROL_analog_right_max 412
// *********************************************************************
// setup
void LCDML_CONTROL_setup()
{	
	pinMode (_LCDML_CONTROL_digitalread, INPUT);
}
// *********************************************************************
// loop
void LCDML_CONTROL_loop()
{
	// check debounce timer
	if((millis() - g_LCDML_DISP_press_time) >= _LCDML_DISP_cfg_button_press_time) {
		g_LCDML_DISP_press_time = millis(); // reset debounce timer

		uint16_t valuex = analogRead(_LCDML_CONTROL_analog_pinx);  // analogpinx
		uint16_t valuey = analogRead(_LCDML_CONTROL_analog_piny);  // analogpinx
		uint16_t valuee = digitalRead(_LCDML_CONTROL_digitalread);  //digitalpinenter

		
		if (valuey >= _LCDML_CONTROL_analog_up_min && valuey <= _LCDML_CONTROL_analog_up_max) { LCDML_BUTTON_up(); }		// up
		if (valuey >= _LCDML_CONTROL_analog_down_min && valuey <= _LCDML_CONTROL_analog_down_max) { LCDML_BUTTON_down(); }	// down
		if (valuex >= _LCDML_CONTROL_analog_left_min && valuex <= _LCDML_CONTROL_analog_left_max) { LCDML_BUTTON_left(); } 	// left
		if (valuex >= _LCDML_CONTROL_analog_right_min && valuex <= _LCDML_CONTROL_analog_right_max) { LCDML_BUTTON_right(); }	// right
		
		if(valuee == true) {LCDML_BUTTON_enter();}	// enter

		// back buttons have to be included as menuitem 
		// lock at the examle LCDML_back_button

	}
}
// *********************************************************************
// ******************************* END *********************************
// *********************************************************************


#else
  #error _LCDML_CONTROL_cfg is not defined or not in range
#endif

