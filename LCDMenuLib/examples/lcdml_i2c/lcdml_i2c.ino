/* =============================================== */
/* Example: LCD Menu with LiquidCrystal_I2C      */ 
/* =============================================== */

/* include libs */
/* you have to edit the LCDMenuLib___config.h in the lib dir */
/* change the value of _LCDMenuLib_cfg_lcd_type */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LCDMenuLib.h>

/* settings for lcd */
#define _LCDMenuLib_LCD_cols             20
#define _LCDMenuLib_LCD_rows             4

/* i2c address */ 
#define _LCDMenuLib_LCD_addr             0x20

//#define _LCDMenuLib_LCD_e				  0
//#define _LCDMenuLib_LCD_rw				  1
//#define _LCDMenuLib_LCD_rs				  2
//#define _LCDMenuLib_LCD_dat4              3
//#define _LCDMenuLib_LCD_dat5              4
//#define _LCDMenuLib_LCD_dat6              5
//#define _LCDMenuLib_LCD_dat7              6
//#define _LCDMenuLib_LCD_backlight         7
//#define _LCDMenuLib_LCD_backlight_pol     POSITIVE // NEGATIVE

/* lib config */
#define _LCDMenuLib_cfg_initscreen       1      /* 0=disable, 1=enable */
#define _LCDMenuLib_cfg_initscreen_time  60000  /* 0=time disabled, >0 wait time in ms */
#define _LCDMenuLib_cfg_scrollbar	 1      /* 0=no scrollbar, 1=complex scrollbar, 2=easy scrollbar */
#define _LCDMenuLib_cfg_lcd_standard	 0      /* 0=HD44780 standard / 1=HD44780U standard */
#define _LCDMenuLib_cfg_press_time       200    /* button press time in ms */

/* menu element count - last element id */ 
#define _LCDMenuLib_cnt    17  

/* init lcdmenulib */
LCDMenuLib_init(_LCDMenuLib_cnt);

/* create menu */
/* root           => layer 0 */
/* root_XX        => layer 1 */
/* root_XX_XX     => layer 2 */
/* root_XX_XX_XX  => layer 3 */
/* root_... 	  => layer ... */
/* LCDMenuLib_element(id, prev_layer_element, new_element_num, lang_string, callback_function) */
LCDMenuLib_add(0  , root         , 1  , "Information"        , FUNC_information);
LCDMenuLib_add(1  , root         , 2  , "Zeit Info"          , FUNC_timer_info);
LCDMenuLib_add(2  , root         , 3  , "Einstellungen"      , FUNC);
LCDMenuLib_add(3  , root_3       , 1  , "Werte veraendern"   , FUNC);
LCDMenuLib_add(4  , root_3       , 2  , "Irgendwas"          , FUNC);
LCDMenuLib_add(5  , root         , 4  , "Programme"          , FUNC);
LCDMenuLib_add(6  , root_4       , 1  , "Programme 1"        , FUNC);
LCDMenuLib_add(7  , root_4_1     , 1  , "P1 Starten"         , FUNC);
LCDMenuLib_add(8  , root_4_1     , 2  , "Einstellungen"      , FUNC);
LCDMenuLib_add(9  , root_4_1_2   , 1  , "extra warm"         , FUNC);
LCDMenuLib_add(10 , root_4_1_2   , 2  , "extra lang"         , FUNC);
LCDMenuLib_add(11 , root_4_1_2   , 3  , "zurück"             , FUNC_back);
LCDMenuLib_add(12 , root_4       , 2  , "Programm 2"         , FUNC_p2);
LCDMenuLib_add(13 , root_4       , 3  , "Programm Mix"       , FUNC);
LCDMenuLib_add(14 , root_4       , 4  , "Programm Hemden"    , FUNC);
LCDMenuLib_add(15 , root_4       , 5  , "Programm Schnell"   , FUNC);
LCDMenuLib_add(16 , root_4       , 6  , "Einstellungen"      , FUNC);
LCDMenuLib_add(17 , root_4_6     , 1  , "Irgendwas"          , FUNC);
LCDMenuLib_createMenu(_LCDMenuLib_cnt);


void setup()
{    
  LCDMenuLib_setup(_LCDMenuLib_cnt);  /* Setup for LcdMenuLib */
  Serial.begin(9600);                 /* start serial */  
}

void loop()
{  
  //LCDMenuLib_control_analog();      /* lcd menu control - config in tab "LCDML_control" */
  //LCDMenuLib_control_digital();     /* lcd menu control - config in tab "LCDML_control" */ 
  LCDMenuLib_control_serial();        /* lcd menu control */  
  LCDMenuLib_loop();                  /* lcd function call */

  //other function ... for example simple threads ..   
}
