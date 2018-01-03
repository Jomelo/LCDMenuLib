// ============================================================                                                            
// Example:     LCDML: use adafruit i2c display ssd1306                           
// ============================================================
// Autor:       Nils Feldkämper, Markus Rudel
// Last update: 18.01.2017
// License:     MIT                                     
// ============================================================ 
// Descripton:  
// ============================================================ 

  // include libs
  #include <LCDMenuLib.h>
  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>    // Core graphics library
  #include <Adafruit_ST7735.h> // Hardware-specific library

  
  // lib config
  #define _LCDML_DISP_cfg_button_press_time          200    // button press time in ms

// *********************************************************************
// Adafruit TFT_ST7735
// *********************************************************************
// https://learn.adafruit.com/1-8-tft-display/graphics-library
  
  #define _LCDML_ADAFRUIT_TEXT_COLOR       ST7735_WHITE
  #define _LCDML_ADAFRUIT_BACKGROUND_COLOR ST7735_BLACK 
  
  #define _LCDML_ADAFRUIT_FONT_SIZE   1   
  #define _LCDML_ADAFRUIT_FONT_W      (6*_LCDML_ADAFRUIT_FONT_SIZE)             // font width 
  #define _LCDML_ADAFRUIT_FONT_H      (8*_LCDML_ADAFRUIT_FONT_SIZE)             // font heigt 
  
  // settings for u8g lib and lcd
  #define _LCDML_ADAFRUIT_lcd_w       128            // lcd width
  #define _LCDML_ADAFRUIT_lcd_h       160             // lcd height
 
  
  
  // TFT display and SD card will share the hardware SPI interface.
  // Hardware SPI pins are specific to the Arduino board type and
  // cannot be remapped to alternate pins.  For Arduino Uno,
  // Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
  #define TFT_CS  10  // Chip select line for TFT display
  #define TFT_RST  9  // Reset line for TFT (or see below...)
  #define TFT_DC   8  // Data/command line for TFT

  #define SD_CS    4  // Chip select line for SD card
  Adafruit_ST7735 display = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
  


  // nothing change here
  #define _LCDML_ADAFRUIT_cols_max    (_LCDML_ADAFRUIT_lcd_w/_LCDML_ADAFRUIT_FONT_W)  
  #define _LCDML_ADAFRUIT_rows_max    (_LCDML_ADAFRUIT_lcd_h/_LCDML_ADAFRUIT_FONT_H) 

  // rows and cols 
  // when you use more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
  // the program needs more ram with this changes
  #define _LCDML_ADAFRUIT_cols        20                   // max cols
  #define _LCDML_ADAFRUIT_rows        _LCDML_ADAFRUIT_rows_max  // max rows 


  // scrollbar width
  #define _LCDML_ADAFRUIT_scrollbar_w 6  // scrollbar width  


  // old defines with new content
  #define _LCDML_DISP_cols      _LCDML_ADAFRUIT_cols
  #define _LCDML_DISP_rows      _LCDML_ADAFRUIT_rows  


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

    SPI.begin();

    // Our supplier changed the 1.8" display slightly after Jan 10, 2012
    // so that the alignment of the TFT had to be shifted by a few pixels
    // this just means the init code is slightly different. Check the
    // color of the tab to see which init code to try. If the display is
    // cut off or has extra 'random' pixels on the top & left, try the
    // other option!
    // If you are seeing red and green color inversion, use Black Tab
  
    // If your TFT's plastic wrap has a Black Tab, use the following:
    display.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
    // If your TFT's plastic wrap has a Red Tab, use the following:
    //tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab
    // If your TFT's plastic wrap has a Green Tab, use the following:
    //tft.initR(INITR_GREENTAB); // initialize a ST7735R chip, green tab

    // clear lcd
    display.fillScreen(_LCDML_ADAFRUIT_BACKGROUND_COLOR);
    
    // set text color / Textfarbe setzen
    display.setTextColor(_LCDML_ADAFRUIT_TEXT_COLOR);  
    // set text size / Textgroesse setzen
    display.setTextSize(_LCDML_ADAFRUIT_FONT_SIZE);
    display.setCursor(0, _LCDML_ADAFRUIT_FONT_H * (3));
    display.println("LCDMenuLib v2.1.4 alpha");
    
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
# if(_LCDML_DISP_rows > _LCDML_ADAFRUIT_rows_max)
# error change value of _LCDML_ADAFRUIT_rows_max in LCDMenuLib.h
# endif
# if(_LCDML_DISP_cols > _LCDML_DISP_cfg_max_string_length)
# error change value of _LCDML_DISP_cfg_max_string_length in LCDMenuLib.h
# endif
