/* =============================================== */
/* Example: LCD Menu with LiquidCrystal          */
/* =============================================== */

/* include libs */
#include <LiquidCrystal.h>
#include <LCDMenuLib.h>

/* settings for lcd */
#define _LCDML_DISP_cols             20
#define _LCDML_DISP_rows             4

/* pin settings */
#define _LCDML_DISP_rs               2
#define _LCDML_DISP_e                3
#define _LCDML_DISP_dat0             4
#define _LCDML_DISP_dat1             5
#define _LCDML_DISP_dat2             6
#define _LCDML_DISP_dat3             7

/* optional */
//#define _LCDML_DISP_rw			0
//#define _LCDML_DISP_backlight         7
//#define _LCDML_DISP_backlight_pol     POSITIVE // NEGATIVE
/* 8 bit mode */
//#define _LCDML_DISP_dat4          0
//#define _LCDML_DISP_dat5          0
//#define _LCDML_DISP_dat6          0
//#define _LCDML_DISP_dat7          0


/* lib config */
#define _LCDML_DISP_cfg_button_press_time          200    /* button press time in ms */
#define _LCDML_DISP_cfg_scrollbar	           1      /* 0 = no scrollbar, 1 = scrollbar with custom chars */
#define _LCDML_DISP_cfg_scrollbar_custom_redefine  0      /* 0 = nothing, 1 = redefine custom chars on scrolling */
#define _LCDML_DISP_cfg_lcd_standard	           0      /* 0 = HD44780 standard / 1 = HD44780U standard */
       
/* other configs are in LCDMenuLib___config.h
 * - max char limit per row (default is 20)
 * - cursor simbol
 * - max layer deep (default is 6)
 * - lcd type
 */

/* ********************************************************************* */
/* LCDML CONTROL
/* ********************************************************************* */
#define _LCDML_DISP_cfg_control                0      /* 0=seriell, 1=analog, 2=digital, 3=encoder */


#if(_LCDML_DISP_cfg_control == 0)
#  define _LCDML_CONTROL_serial_enter           'e'
#  define _LCDML_CONTROL_serial_up              'w'
#  define _LCDML_CONTROL_serial_down            's'
#  define _LCDML_CONTROL_serial_left            'a'
#  define _LCDML_CONTROL_serial_right           'd'
#  define _LCDML_CONTROL_serial_quit            'q'
#endif

#if(_LCDML_DISP_cfg_control == 1)
#  define _LCDML_CONTROL_analog_pin              0
#  define _LCDML_CONTROL_analog_enter_min        850     // Button Enter
#  define _LCDML_CONTROL_analog_enter_max        920  
#  define _LCDML_CONTROL_analog_up_min           520     // Button Up
#  define _LCDML_CONTROL_analog_up_max           590   
#  define _LCDML_CONTROL_analog_down_min         700     // Button Down
#  define _LCDML_CONTROL_analog_down_max         770   
//optional if menu element "back" exists, look at FUNC_back in functions tab 
#  define _LCDML_CONTROL_analog_enable_quit      1
#  define _LCDML_CONTROL_analog_back_min         950     // Button Back
#  define _LCDML_CONTROL_analog_back_max         1020   
//optional
#  define _LCDML_CONTROL_analog_enable_lr        1
#  define _LCDML_CONTROL_analog_left_min         430     // Button Left
#  define _LCDML_CONTROL_analog_left_max         500   
#  define _LCDML_CONTROL_analog_right_min        610     // Button Right
#  define _LCDML_CONTROL_analog_right_max        680 
#endif

#if(_LCDML_DISP_cfg_control == 2)
#  define _LCDML_CONTROL_digital_enter           8    
#  define _LCDML_CONTROL_digital_up              9
#  define _LCDML_CONTROL_digital_down            10
//optional
#  define _LCDML_CONTROL_digital_enable_quit     1
#  define _LCDML_CONTROL_digital_quit            11
//optional
#  define _LCDML_CONTROL_digital_enable_lr       1
#  define _LCDML_CONTROL_digital_left            12
#  define _LCDML_CONTROL_digital_right           13
#endif

#if(_LCDML_DISP_cfg_control == 3)
#  define _LCDML_CONTROL_encoder_pin_a           10   // pin encoder b
#  define _LCDML_CONTROL_encoder_pin_b           11   // pin encoder a
#  define _LCDML_CONTROL_encoder_pin_button      12   // pin taster
#  define _LCDML_CONTROL_encoder_high_active     0    // (0 = low active, 1 = high active) button
#  define _LCDML_CONTROL_encoder_time            20
#endif

#define _LCDML_DISP_cnt    37

/* create menu */
/* root           => layer 0 */
/* root_XX        => layer 1 */
/* root_XX_XX     => layer 2 */
/* root_XX_XX_XX  => layer 3 */
/* root_... 	  => layer ... */
/* menu element count - last element id */

/* init lcdmenulib */
LCDML_DISP_init(_LCDML_DISP_cnt);
/* LCDMenuLib_element(id, group, prev_layer_element, new_element_num, lang_string, callback_function) */
LCDML_DISP_add(0  , _LCDML_G1  , LCDML_root        , 1  , "Information"        , LCDML_FUNC_information);
LCDML_DISP_add(1  , _LCDML_G1  , LCDML_root        , 2  , "Time info"          , LCDML_FUNC_timer_info);
LCDML_DISP_add(2  , _LCDML_G1  , LCDML_root        , 3  , "Settings"           , LCDML_FUNC);
LCDML_DISP_add(3  , _LCDML_G1  , LCDML_root_3      , 1  , "Change value"       , LCDML_FUNC);
LCDML_DISP_add(4  , _LCDML_G1  , LCDML_root_3      , 2  , "Something"          , LCDML_FUNC);
LCDML_DISP_add(5  , _LCDML_G1  , LCDML_root_3      , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add(6  , _LCDML_G2  , LCDML_root        , 4  , "Program"            , LCDML_FUNC);
LCDML_DISP_add(7  , _LCDML_G2  , LCDML_root_4      , 1  , "Program 1"          , LCDML_FUNC);
LCDML_DISP_add(8  , _LCDML_G2  , LCDML_root_4_1    , 1  , "P1 start"           , LCDML_FUNC);
LCDML_DISP_add(9  , _LCDML_G2  , LCDML_root_4_1    , 2  , "Settings"           , LCDML_FUNC);
LCDML_DISP_add(10 , _LCDML_G2  , LCDML_root_4_1_2  , 1  , "Warm"               , LCDML_FUNC);
LCDML_DISP_add(11 , _LCDML_G2  , LCDML_root_4_1_2  , 2  , "Long"               , LCDML_FUNC);
LCDML_DISP_add(12 , _LCDML_G2  , LCDML_root_4_1_2  , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add(13 , _LCDML_G2  , LCDML_root_4_1    , 3  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add(14 , _LCDML_G2  , LCDML_root_4      , 2  , "Program 2"          , LCDML_FUNC_p2);
LCDML_DISP_add(15 , _LCDML_G2  , LCDML_root_4      , 3  , "back"               , LCDML_FUNC_back);
LCDML_DISP_add(16 , _LCDML_G1  , LCDML_root        , 5  , "Menu-Mode"          , LCDML_FUNC);
LCDML_DISP_add(17 , _LCDML_G2  , LCDML_root_5      , 1  , "disable program"    , LCDML_FUNC_prog_disable);
LCDML_DISP_add(18 , _LCDML_G3  , LCDML_root_5      , 2  , "enable program"     , LCDML_FUNC_prog_enable);
LCDML_DISP_add(19 , _LCDML_G1  , LCDML_root_5      , 3  , "back"               , LCDML_FUNC_back);
LCDML_DISP_add(20 , _LCDML_G1  , LCDML_root        , 6  , "Backend-Control"    , LCDML_FUNC);
LCDML_DISP_add(21 , _LCDML_G1  , LCDML_root_6      , 1  , "Test 10"            , LCDML_FUNC);
LCDML_DISP_add(22 , _LCDML_G1  , LCDML_root_6_1    , 1  , "Start"              , LCDML_FUNC_test10_start);
LCDML_DISP_add(23 , _LCDML_G1  , LCDML_root_6_1    , 2  , "Restart"            , LCDML_FUNC_test10_restart);
LCDML_DISP_add(24 , _LCDML_G1  , LCDML_root_6_1    , 3  , "Stop"               , LCDML_FUNC_test10_stop);
LCDML_DISP_add(25 , _LCDML_G1  , LCDML_root_6_1    , 4  , "Stop stable"        , LCDML_FUNC_test10_stop_stable);
LCDML_DISP_add(26 , _LCDML_G1  , LCDML_root_6_1    , 5  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add(27 , _LCDML_G1  , LCDML_root_6      , 2  , "Test 20"            , LCDML_FUNC);
LCDML_DISP_add(28 , _LCDML_G1  , LCDML_root_6_2    , 1  , "Start"              , LCDML_FUNC_test20_start);
LCDML_DISP_add(29 , _LCDML_G1  , LCDML_root_6_2    , 2  , "Stop"               , LCDML_FUNC_test20_stop);
LCDML_DISP_add(30 , _LCDML_G1  , LCDML_root_6_2    , 3  , "Change runtime"     , LCDML_FUNC);
LCDML_DISP_add(31 , _LCDML_G1  , LCDML_root_6_2_3  , 1  , "500 ms"             , LCDML_FUNC_test20_500ms);
LCDML_DISP_add(32 , _LCDML_G1  , LCDML_root_6_2_3  , 2  , "1 s"                , LCDML_FUNC_test20_1s);
LCDML_DISP_add(33 , _LCDML_G1  , LCDML_root_6_2_3  , 3  , "10 s"               , LCDML_FUNC_test20_10s);
LCDML_DISP_add(34 , _LCDML_G1  , LCDML_root_6_2_3  , 4  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add(35 , _LCDML_G1  , LCDML_root_6_2    , 4  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_add(36 , _LCDML_G1  , LCDML_root_6      , 3  , "Test 30"            , LCDML_FUNC_test30_start);
LCDML_DISP_add(37 , _LCDML_G1  , LCDML_root_6      , 4  , "Back"               , LCDML_FUNC_back);
LCDML_DISP_createMenu(_LCDML_DISP_cnt);



#define _LCDML_BACK_cnt    4

LCDML_BACK_init(_LCDML_BACK_cnt);
LCDML_BACK_new_timebased_static  (0  , _LCDML_millis, (20)                , _LCDML_start  , LCDML_BACKEND_control);
LCDML_BACK_new_timebased_dynamic (1  , _LCDML_millis, (1000*60)           , _LCDML_stop   , LCDML_BACKEND_menu);
/* own backend function */
//LCDML_BACK_new_timebased_dynamic (2  , _LCDML_millis, (1000*60)           , _LCDML_stop   , LCDML_BACKEND_initscreen);
LCDML_BACK_new_timebased_static  (2  , _LCDML_millis, (1000*10)           , _LCDML_start  , LCDML_BACKEND_test10);
LCDML_BACK_new_timebased_dynamic (3  , _LCDML_millis, (1000*20)           , _LCDML_stop   , LCDML_BACKEND_test20);
LCDML_BACK_new_eventbased        (4                                                       , LCDML_BACKEND_test30);





void setup()
{
  /* serial init; only be needed */
  Serial.begin(9600);   /* start serial */
  
  LCDML_DISP_groupEnable(_LCDML_G1);
  LCDML_DISP_groupEnable(_LCDML_G2);  
  
  LCDML_setup(_LCDML_BACK_cnt); 

  //LCDML_DISP_jumpToFunc(LCDML_FUNC_prog_disable);  
}

void loop()
{  
  LCDML_run(_LCDML_priority); 
}
