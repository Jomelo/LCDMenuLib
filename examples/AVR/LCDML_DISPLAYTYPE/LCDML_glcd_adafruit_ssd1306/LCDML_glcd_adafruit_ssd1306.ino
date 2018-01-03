// ============================================================                                                            
// Example:     LCDML: use adafruite i2c display ssd1306                           
// ============================================================
// Autor:       Nils Feldkämper
// Last update: 08.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton:  
// ============================================================ 

  // include libs
  #include <LCDMenuLib.h>
  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>

  
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms

// *********************************************************************
// Adufruit SSD1306
// *********************************************************************
  // http://blog.simtronyx.de/ein-096-zoll-oled-display-i%C2%B2c-mit-128x64-pixel-und-ein-arduino/
  
  #define _ADAFRUITE_I2C_ADR    0x3C
  #define _LCDML_ADAFRUITE_TEXT_COLOR WHITE 
  
  #define _LCDML_ADAFRUITE_FONT_SIZE   1   
  #define _LCDML_ADAFRUITE_FONT_W      (6*_LCDML_ADAFRUITE_FONT_SIZE)             // font width 
  #define _LCDML_ADAFRUITE_FONT_H      (8*_LCDML_ADAFRUITE_FONT_SIZE)             // font heigt 
  
  // settings for u8g lib and lcd
  #define _LCDML_ADAFRUITE_lcd_w       128            // lcd width
  #define _LCDML_ADAFRUITE_lcd_h       64             // lcd height
 
  
  
  #define OLED_RESET 4 // not used / nicht genutzt bei diesem Display
  Adafruit_SSD1306 display(OLED_RESET);
  


  // nothing change here
  #define _LCDML_ADAFRUITE_cols_max    (_LCDML_ADAFRUITE_lcd_w/_LCDML_ADAFRUITE_FONT_W)  
  #define _LCDML_ADAFRUITE_rows_max    (_LCDML_ADAFRUITE_lcd_h/_LCDML_ADAFRUITE_FONT_H) 

  // rows and cols 
  // when you use more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
  // the program needs more ram with this changes
  #define _LCDML_ADAFRUITE_cols        20                   // max cols
  #define _LCDML_ADAFRUITE_rows        _LCDML_ADAFRUITE_rows_max  // max rows 


  // scrollbar width
  #define _LCDML_ADAFRUITE_scrollbar_w 6  // scrollbar width  


  // old defines with new content
  #define _LCDML_DISP_cols      _LCDML_ADAFRUITE_cols
  #define _LCDML_DISP_rows      _LCDML_ADAFRUITE_rows  


// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // create menu
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    16
  
  // LCDML_root        => layer 0 
  // LCDML_root_X      => layer 1 
  // LCDML_root_X_X    => layer 2 
  // LCDML_root_X_X_X  => layer 3 
  // LCDML_root_... 	 => layer ... 
  
  // LCDMenuLib_add(id, group, prev_layer_element, new_element_num, lang_char_array, callback_function)
  LCDML_DISP_init(_LCDML_DISP_cnt);
  LCDML_DISP_add      (0  , _LCDML_G1  , LCDML_root        , 1  , "Information"        , LCDML_FUNC_information);
  LCDML_DISP_add      (1  , _LCDML_G1  , LCDML_root        , 2  , "Time info"          , LCDML_FUNC_timer_info);
  LCDML_DISP_add      (2  , _LCDML_G1  , LCDML_root        , 3  , "Settings"           , LCDML_FUNC);
  LCDML_DISP_add      (3  , _LCDML_G1  , LCDML_root_3      , 1  , "Change value"       , LCDML_FUNC);
  LCDML_DISP_add      (4  , _LCDML_G1  , LCDML_root_3      , 2  , "Something"          , LCDML_FUNC);
  LCDML_DISP_add      (5  , _LCDML_G1  , LCDML_root        , 4  , "Program"            , LCDML_FUNC);
  LCDML_DISP_add      (6  , _LCDML_G1  , LCDML_root_4      , 1  , "Program 1"          , LCDML_FUNC);
  LCDML_DISP_add      (7  , _LCDML_G1  , LCDML_root_4_1    , 1  , "P1 start"           , LCDML_FUNC);
  LCDML_DISP_add      (8  , _LCDML_G1  , LCDML_root_4_1    , 2  , "Settings"           , LCDML_FUNC);
  LCDML_DISP_add      (9  , _LCDML_G1  , LCDML_root_4_1_2  , 1  , "Warm"               , LCDML_FUNC);
  LCDML_DISP_add      (10 , _LCDML_G1  , LCDML_root_4_1_2  , 2  , "Long"               , LCDML_FUNC);
  LCDML_DISP_add      (11 , _LCDML_G1  , LCDML_root_4      , 2  , "Program 2"          , LCDML_FUNC_p2);
  LCDML_DISP_add      (12 , _LCDML_G1  , LCDML_root        , 5  , "Mode"               , LCDML_FUNC);
  LCDML_DISP_add      (13 , _LCDML_G1  , LCDML_root        , 6  , "Serial No."         , LCDML_FUNC);
  LCDML_DISP_add      (14 , _LCDML_G1  , LCDML_root        , 7  , "Display Type"       , LCDML_FUNC);
  LCDML_DISP_add      (15 , _LCDML_G1  , LCDML_root        , 8  , "Something 1"        , LCDML_FUNC);
  LCDML_DISP_add      (16 , _LCDML_G1  , LCDML_root        , 9  , "Something 2"        , LCDML_FUNC);
  LCDML_DISP_createMenu(_LCDML_DISP_cnt);



// ********************************************************************* 
// LCDML BACKEND (core of the menu, do not change here anything yet)
// ********************************************************************* 
  // define backend function  
  #define _LCDML_BACK_cnt    1  // last backend function id
  
  LCDML_BACK_init(_LCDML_BACK_cnt);
  LCDML_BACK_new_timebased_dynamic (0  , ( 20UL )         , _LCDML_start  , LCDML_BACKEND_control);
  LCDML_BACK_new_timebased_dynamic (1  , ( 10000000UL )   , _LCDML_stop   , LCDML_BACKEND_menu);
  LCDML_BACK_create();



// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {  
    // serial init; only be needed if serial control is used    
    Serial.begin(9600);                // start serial    
    Serial.println(F(_LCDML_VERSION)); // only for examples
      
    // Enable all items with _LCDML_G1
    LCDML_DISP_groupEnable(_LCDML_G1); // enable group 1
    
    // Enable menu rollover if needed
    //LCDML.enRollover();
  
	// initialize with the I2C addr / mit I2C-Adresse initialisieren
	display.begin(SSD1306_SWITCHCAPVCC, _ADAFRUITE_I2C_ADR);
    
    // clear lcd
    display.clearDisplay();
    // set text color / Textfarbe setzen
    display.setTextColor(_LCDML_ADAFRUITE_TEXT_COLOR);  
    // set text size / Textgroesse setzen
    display.setTextSize(_LCDML_ADAFRUITE_FONT_SIZE);
    display.setCursor(0, _LCDML_ADAFRUITE_FONT_H * (3));
    display.println("LCDMenuLib v2.1.4 alpha");
    display.display();
    delay(1000);    
  
    // LCDMenu Setup
    LCDML_setup(_LCDML_BACK_cnt);  
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  { 
    // this function must called here, do not delete it
    LCDML_run(_LCDML_priority); 
  }




// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
# if(_LCDML_DISP_rows > _LCDML_ADAFRUITE_rows_max)
# error change value of _LCDML_ADAFRUITE_rows_max in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
