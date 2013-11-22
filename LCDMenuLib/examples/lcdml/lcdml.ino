/* =============================================== */
/* Example 1: LCD Menu with LiquidCrystal          */ 
/* =============================================== */

/* include libs */
#include <LiquidCrystal.h>
#include <LCDMenuLib.h>

/* settings for lcd */
#define _LCDMenuLib_LCD_cols             20
#define _LCDMenuLib_LCD_rows             4

/* pin settings */  
#define _LCDMenuLib_LCD_rs               4
#define _LCDMenuLib_LCD_e                5
#define _LCDMenuLib_LCD_dat0             8
#define _LCDMenuLib_LCD_dat1             9
#define _LCDMenuLib_LCD_dat2             7
#define _LCDMenuLib_LCD_dat3             11 

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

/* create lcdmenulib */
/* Item           => layer 0 */
/* Item_XX        => layer 1 */
/* Item_XX_XX     => layer 2 */
/* Item_XX_XX_XX  => layer 3 */
/* LCDMenuLib_element(id, prev_layer_element, current_layer_element, lang_string, callback_function) */
LCDMenuLib_element(0  , Item         , Item_1        , "Information"        , FUNC_information);
LCDMenuLib_element(1  , Item         , Item_2        , "Zeit Info"          , FUNC_timer_info);
LCDMenuLib_element(2  , Item         , Item_3        , "Einstellungen"      , FUNC);
LCDMenuLib_element(3  , Item_3       , Item_3_1      , "Werte veraendern"   , FUNC);
LCDMenuLib_element(4  , Item_3       , Item_3_2      , "Irgendwas"          , FUNC);
LCDMenuLib_element(5  , Item         , Item_4        , "Programme"          , FUNC);
LCDMenuLib_element(6  , Item_4       , Item_4_1      , "Programme 1"        , FUNC);
LCDMenuLib_element(7  , Item_4_1     , Item_4_1_1    , "P1 Starten"         , FUNC);
LCDMenuLib_element(8  , Item_4_1     , Item_4_1_2    , "Einstellungen"      , FUNC);
LCDMenuLib_element(9  , Item_4_1_2   , Item_4_1_2_1  , "extra warm"         , FUNC);
LCDMenuLib_element(10 , Item_4_1_2   , Item_4_1_2_2  , "extra lang"         , FUNC);
LCDMenuLib_element(11 , Item_4_1_2   , Item_4_1_2_3  , "zurück"             , FUNC_back);
LCDMenuLib_element(12 , Item_4       , Item_4_2      , "Programm 2"         , FUNC_p2);
LCDMenuLib_element(13 , Item_4       , Item_4_3      , "Programm Mix"       , FUNC);
LCDMenuLib_element(14 , Item_4       , Item_4_4      , "Programm Hemden"    , FUNC);
LCDMenuLib_element(15 , Item_4       , Item_4_5      , "Programm Schnell"   , FUNC);
LCDMenuLib_element(16 , Item_4       , Item_4_6      , "Einstellungen"      , FUNC);
LCDMenuLib_element(17 , Item_4_6     , Item_4_6_1    , "Irgendwas"          , FUNC);
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
