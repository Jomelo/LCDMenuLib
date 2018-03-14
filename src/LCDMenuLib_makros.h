/*
 * MIT License
 * 
 * Copyright (c) [2017] [Nils Feldkämper]
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// ********************************************************************
//																		
//						LCDMenuLib (LCDML)								
//																		
// ********************************************************************
//
// Autor:			Nils Feldkaemper				
// Create:			03.02.2008											
// Edit:			27.02.2017											
// License:			MIT License											
//
// ********************************************************************
//
// error reporting: 									
//	https://github.com/Jomelo/LCDMenuLib/issues							
//
// forum thread:													
// 	http://forum.arduino.cc/index.php?topic=73816.0						
//
// ********************************************************************

#ifndef _LCDML_DISP_macros_h
#	define _LCDML_DISP_macros_h

/* ******************************************************************** */
/* Includes 															*/
/* ******************************************************************** */
#	include <Arduino.h>

/* ******************************************************************** */
/* DISPLAY UPDATE MENU													*/
/* ******************************************************************** */
#	define LCDML_DISP_update() 			(LCDML.getFunction() == _LCDML_NO_FUNC || bitRead(LCDML.control, _LCDML_control_funcend) || bitRead(LCDML.control, _LCDML_control_update_direct))
#	define LCDML_DISP_update_content() 	(bitRead(LCDML.control, _LCDML_control_disp_update) || bitRead(LCDML.control, _LCDML_control_update_direct))
#	define LCDML_DISP_update_cursor()  	(bitRead(LCDML.control, _LCDML_control_cursor_update))

#	define LCDML_DISP_update_end() \
		bitClear(LCDML.control, _LCDML_control_disp_update); \
		bitClear(LCDML.control, _LCDML_control_cursor_update); \
		bitClear(LCDML.control, _LCDML_control_update_direct)

#	define LCDML_DISP_update_menu_direct(id) \
		if(LCDML.getFunction() == _LCDML_NO_FUNC) { \
			for(int i=0; i < ((LCDML.getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.getChilds())); i++) { \
				if(LCDML.content_id[i] == id) { \
					bitSet(LCDML.control, _LCDML_control_update_direct); \
					LCDML_lcd_menu_display(); \
					break; \
				} \
			} \
		}

/* ******************************************************************** */
/* CONTROL / BUTTONS													*/
/* ******************************************************************** */
#	define LCDML_BUTTON_enter()	LCDML.Button_enter();					LCDML_DISP_update_menu()
#	define LCDML_BUTTON_up()	LCDML.Button_udlr(_LCDML_button_up);	LCDML_DISP_update_menu()
#	define LCDML_BUTTON_down()	LCDML.Button_udlr(_LCDML_button_down);	LCDML_DISP_update_menu()
#	define LCDML_BUTTON_left()	LCDML.Button_udlr(_LCDML_button_left);	LCDML_DISP_update_menu()
#	define LCDML_BUTTON_right()	LCDML.Button_udlr(_LCDML_button_right);	LCDML_DISP_update_menu()
#	define LCDML_BUTTON_quit()	LCDML.Button_quit();					LCDML_DISP_update_menu()

#	define LCDML_BUTTON_checkAny()		((LCDML.button > 0) ? true : false)		
#	define LCDML_BUTTON_checkEnter()	bitRead(LCDML.button, _LCDML_button_enter)		
#	define LCDML_BUTTON_checkUp()		bitRead(LCDML.button, _LCDML_button_up)		
#	define LCDML_BUTTON_checkDown()		bitRead(LCDML.button, _LCDML_button_down)
#	define LCDML_BUTTON_checkLeft()		bitRead(LCDML.button, _LCDML_button_left)
#	define LCDML_BUTTON_checkRight()	bitRead(LCDML.button, _LCDML_button_right)

#	define LCDML_BUTTON_resetAll()		LCDML.button = 0
#	define LCDML_BUTTON_resetEnter()	bitClear(LCDML.button, _LCDML_button_enter)
#	define LCDML_BUTTON_resetUp()		bitClear(LCDML.button, _LCDML_button_up)
#	define LCDML_BUTTON_resetDown()		bitClear(LCDML.button, _LCDML_button_down)
#	define LCDML_BUTTON_resetLeft()		bitClear(LCDML.button, _LCDML_button_left)
#	define LCDML_BUTTON_resetRight()	bitClear(LCDML.button, _LCDML_button_right)


/* ******************************************************************** */
/* DISP / MENU															*/
/* ******************************************************************** */
#	define LCDML_root 					LCDML_Item

#	define LCDML_DISP_setup(name)		name ##_loop_setup(void)
#	define LCDML_DISP_loop(name)		name ##_loop(void)
#	define LCDML_DISP_loop_end(name)	name ##_loop_end(void)

#	define LCDML_DISP_funcend()			bitSet(LCDML.control, _LCDML_control_funcend)
#	define LCDML_DISP_lang(name)		g_LCDML_DISP_lang_ ## name ## _var

#	define LCDML_DISP_initFunction(N) 	LCDML_DISP_func_repeat(N);

#	define LCDML_DISP_groupEnable(g)	bitSet(LCDML.group_en, g)
#	define LCDML_DISP_groupDisable(g)	bitClear(LCDML.group_en, g)

#	define LCDML_DISP_resetIsTimer()\
	g_lcdml_initscreen = millis();

#	define LCDML_DISP_update_menu()\
	g_lcdml_initscreen = millis();\
	if (LCDML.getFunction() != _LCDML_NO_FUNC){\
		LCDML_BACK_start(LCDML_BACKEND_menu);\
	} \
	if (!bitRead(LCDML.button,  _LCDML_button_quit)) {\
		bitClear(LCDML.button,  _LCDML_button_quit);\
		LCDML_lcd_menu_display(); \
	}
	
	
	
	
# 	define LCDML_DISP_triggerMenu(time)\
		LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_menu, time);\
		LCDML_BACK_start(LCDML_BACKEND_menu)

# 	define LCDML_DISP_triggerControl(time)\
		LCDML_BACK_dynamic_setLoopTime(LCDML_BACKEND_control, time);\
		LCDML_BACK_start(LCDML_BACKEND_control)			

		
		
		
#	define LCDML_DISP_init(N)\
		typedef void(* LCDML_FuncPtr)();\
		LCDML_FuncPtr g_LCDML_DISP_functions_loop_setup[(N+1)];\
		LCDML_FuncPtr g_LCDML_DISP_functions_loop[(N+1)];\
		LCDML_FuncPtr g_LCDML_DISP_functions_loop_end[(N+1)];\
		void LCDML_FUNC_loop_setup(){}\
		void LCDML_FUNC_loop(){}\
		void LCDML_FUNC_loop_end(){}\
		unsigned long g_LCDML_DISP_press_time = 0;\
		unsigned long g_lcdml_initscreen = millis();\
		LCDMenu LCDML_Item (255, true);\
		void LCDML_lcd_menu_display(); \
		void LCDML_lcd_menu_clear();\
		uint8_t g_lcdml_jump_func = _LCDML_NO_FUNC
		

#	define LCDML_DISP_initParam(N)\
		uint8_t g_lcdml_param[(N + 1)]; \
		typedef void(* LCDML_FuncPtr)();\
		LCDML_FuncPtr g_LCDML_DISP_functions_loop_setup[(N+1)];\
		LCDML_FuncPtr g_LCDML_DISP_functions_loop[(N+1)];\
		LCDML_FuncPtr g_LCDML_DISP_functions_loop_end[(N+1)];\
		void LCDML_FUNC_loop_setup(){}\
		void LCDML_FUNC_loop(){}\
		void LCDML_FUNC_loop_end(){}\
		unsigned long g_LCDML_DISP_press_time = 0;\
		unsigned long g_lcdml_initscreen = millis();\
		LCDMenu LCDML_Item (0, true);\
		void LCDML_lcd_menu_display(); \
		void LCDML_lcd_menu_clear();\
		uint8_t g_lcdml_jump_func = _LCDML_NO_FUNC
		
		

			
#	if defined ( ESP8266 ) || defined ( ESP32 )

#		define LCDML_DISP_add(name, disp, item_parent, item_child, content, function)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] = {content};\
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = function##_loop_setup;  g_LCDML_DISP_functions_loop[name] = function##_loop; g_LCDML_DISP_functions_loop_end[name] = function##_loop_end; item_parent.addChild(item_parent ## _ ## item_child); }

#		define LCDML_DISP_addMenu(name, disp, item_parent, item_child, content)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] = {content};\
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = LCDML_FUNC_loop_setup;  g_LCDML_DISP_functions_loop[name] = LCDML_FUNC_loop; g_LCDML_DISP_functions_loop_end[name] = LCDML_FUNC_loop_end; item_parent.addChild(item_parent ## _ ## item_child); }

#		define LCDML_DISP_addFunc(name, disp, item_parent, item_child, content, function)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] = {content};\
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = function##_loop_setup;  g_LCDML_DISP_functions_loop[name] = function##_loop; g_LCDML_DISP_functions_loop_end[name] = function##_loop_end; item_parent.addChild(item_parent ## _ ## item_child); }
			

#		define LCDML_DISP_addParam(name, disp, item_parent, item_child, content, function, para)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] = { content }; \
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = function##_loop_setup;  g_LCDML_DISP_functions_loop[name] = function##_loop; g_LCDML_DISP_functions_loop_end[name] = function##_loop_end; item_parent.addChild(item_parent ## _ ## item_child); g_lcdml_param[name] = para;  }

#		define LCDML_DISP_createMenu(N)\
			const char * const g_LCDML_DISP_lang_table[] = { LCDML_DISP_lang_repeat(N) }; LCDML_DISP_initObjects()
		
#		define LCDML_DISP_getElementName(var, element_id) \
			if(element_id != _LCDML_NO_FUNC && (sizeof(g_LCDML_DISP_lang_table)-1) >= element_id) {\
				strcpy_P(var, (char*)(g_LCDML_DISP_lang_table[element_id]));\
			}\

#		define LCDML_DISP_getElementNameCheck(var, element_id, check) \
			if(element_id != _LCDML_NO_FUNC && (sizeof(g_LCDML_DISP_lang_table)-1) >= element_id) {\
				strcpy_P(var, (char*)(g_LCDML_DISP_lang_table[element_id]));\
				check = true;\
			} else {\
				check = false;\
			}			
			
#	else

#		define LCDML_DISP_add(name, disp, item_parent, item_child, content, function)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] PROGMEM = {content};\
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = function##_loop_setup;  g_LCDML_DISP_functions_loop[name] = function##_loop; g_LCDML_DISP_functions_loop_end[name] = function##_loop_end; item_parent.addChild(item_parent ## _ ## item_child); }

#		define LCDML_DISP_addMenu(name, disp, item_parent, item_child, content)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] PROGMEM = {content};\
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = LCDML_FUNC_loop_setup;  g_LCDML_DISP_functions_loop[name] = LCDML_FUNC_loop; g_LCDML_DISP_functions_loop_end[name] = LCDML_FUNC_loop_end; item_parent.addChild(item_parent ## _ ## item_child); }

#		define LCDML_DISP_addFunc(name, disp, item_parent, item_child, content, function)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] PROGMEM = {content};\
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = function##_loop_setup;  g_LCDML_DISP_functions_loop[name] = function##_loop; g_LCDML_DISP_functions_loop_end[name] = function##_loop_end; item_parent.addChild(item_parent ## _ ## item_child); }
			

#		define LCDML_DISP_addParam(name, disp, item_parent, item_child, content, function, para)\
			const char g_LCDML_DISP_lang_ ## name ##_var[] PROGMEM = { content }; \
			void function ## _loop_setup(); \
			void function ## _loop(); \
			void function ## _loop_end(); \
			LCDMenu item_parent ## _ ## item_child(name, disp); \
			void LCDML_DISP_##name##_function() { g_LCDML_DISP_functions_loop_setup[name] = function##_loop_setup;  g_LCDML_DISP_functions_loop[name] = function##_loop; g_LCDML_DISP_functions_loop_end[name] = function##_loop_end; item_parent.addChild(item_parent ## _ ## item_child); g_lcdml_param[name] = para;  }

#		define LCDML_DISP_createMenu(N)\
			const char * const g_LCDML_DISP_lang_table[] PROGMEM = { LCDML_DISP_lang_repeat(N) }; LCDML_DISP_initObjects()
		
#		define LCDML_DISP_getElementName(var, element_id) \
			if(element_id != _LCDML_NO_FUNC && (sizeof(g_LCDML_DISP_lang_table)-1) >= element_id) {\
				strcpy_P(var, (char*)pgm_read_word(&(g_LCDML_DISP_lang_table[element_id])));\
			}\

#		define LCDML_DISP_getElementNameCheck(var, element_id, check) \
			if(element_id != _LCDML_NO_FUNC && (sizeof(g_LCDML_DISP_lang_table)-1) >= element_id) {\
				strcpy_P(var, (char*)pgm_read_word(&(g_LCDML_DISP_lang_table[element_id])));\
				check = true;\
			} else {\
				check = false;\
			}	

#	endif

		

#	define	LCDML_DISP_getParameter()\
	g_lcdml_param[LCDML.getFunction()]


#	define LCDML_DISP_initSetup(N)\
		LCDML_DISP_initFunction(N); \
		LCDML.display();\
		LCDML_lcd_menu_display()
		
	
#	define LCDML_DISP_initObjects()\
		LCDMenuLib LCDML(LCDML_Item, g_LCDML_DISP_lang_table, _LCDML_DISP_rows, _LCDML_DISP_cols);

#	define LCDML_DISP_jumpToFunc(name)\
		for(uint8_t i=0; i<=254;i++) {\
			if (name##_loop_setup == g_LCDML_DISP_functions_loop_setup[i]) { \
				if(LCDML.getFunction() != _LCDML_NO_FUNC) {\
					bitSet(LCDML.control, _LCDML_control_funcend);\
					g_lcdml_jump_func = i;\
				} else {\
					LCDML.jumpToElement(i);\
					LCDML_DISP_update_menu(); \
				}\
				break;\
			}\
		}\
		LCDML_BUTTON_resetAll()
		
		
	
/* ******************************************************************** */
/* BACKEND																*/
/* ******************************************************************** */
#define LCDML_BACK_create() 											\
	void LCDML_BACK_setup(LCDML_BACKEND_menu) 							\
	{ 																	\
		g_LCDML_BACK_lastFunc = LCDML.getFunction(); 					\
		if (g_LCDML_DISP_functions_loop_setup[g_LCDML_BACK_lastFunc] == LCDML_FUNC_loop_setup) {\
			bitSet(LCDML.control, _LCDML_control_funcend);              \
		}																\
		else if (g_LCDML_BACK_lastFunc != _LCDML_NO_FUNC) {      		\
			LCDML_lcd_menu_clear();										\
			LCDML_BUTTON_resetAll();                                    \
			g_LCDML_DISP_functions_loop_setup[g_LCDML_BACK_lastFunc](); \
		}																\
	}																	\
	boolean LCDML_BACK_loop(LCDML_BACKEND_menu)							\
	{																	\
		if (LCDML.getFunction() != _LCDML_NO_FUNC) {					\
			g_LCDML_DISP_functions_loop[LCDML.getFunction()]();         \
		} 																\
		return true;													\
	}																	\
	void LCDML_BACK_stable(LCDML_BACKEND_menu)							\
	{																	\
		if (g_LCDML_BACK_lastFunc != _LCDML_NO_FUNC) {   				\
			g_LCDML_DISP_functions_loop_end[g_LCDML_BACK_lastFunc]();   \
			g_LCDML_BACK_lastFunc = _LCDML_NO_FUNC;                     \
			LCDML_lcd_menu_clear();										\
			LCDML.display();                                            \
			LCDML_lcd_menu_display();                                   \
			LCDML_BUTTON_resetAll();                                    \
			LCDML.function = _LCDML_NO_FUNC;                            \
			bitClear(LCDML.control, _LCDML_control_funcend);            \
			if(g_lcdml_jump_func != _LCDML_NO_FUNC) {					\
				LCDML.jumpToElement(g_lcdml_jump_func);					\
				LCDML_DISP_update_menu(); 								\
				g_lcdml_jump_func = _LCDML_NO_FUNC;						\
			}															\
			if(bitRead(LCDML.control, _LCDML_control_go_root)) {		\
				LCDML.goRoot();											\
				LCDML.display();                                        \
				LCDML_lcd_menu_display();                               \
			}															\
		}																\
	}

// define loop modes
#	define _LCDML_no_priority		0
#	define _LCDML_priority			1

#	define _LCDML_stop				0
#	define _LCDML_start				1
#	define _LCDML_stable			2


//non thread id
#	define     _LCDML_BACK_default_id				255		


//init for threads
	// macro: setup function
#	define LCDML_BACK_setup(name)\
		LCDML_BACK_setup_##name(void)
	// macro: loop function
#	define LCDML_BACK_loop(name)\
		LCDML_BACK_loop_##name(void)
	// macro: stableState function
#	define LCDML_BACK_stable(name)\
		LCDML_BACK_stable_##name(void)



// init thread system
	// macro: creates the LCDML_BACK name pointer on a function
#	define LCDML_BACK(name)\
		LCDML_BACK_function_##name
	// macro: creates the LCDML_BACK managemand variables
	
#	if defined ( ESP8266 )	
	
#		define LCDML_BACK_init(cnt)\
			LCDML_FuncPtr g_LCDML_BACK_priority[cnt+1];\
			const uint8_t g_LCDML_BACK_cnt = cnt+1;\
			uint8_t g_LCDML_BACK_start_stop[((cnt+1)/7)+1];\
			uint8_t g_LCDML_BACK_reset[((cnt+1)/7)+1];\
			uint8_t g_LCDML_BACK_loop_status = true;\
			uint8_t g_LCDML_BACK_lastFunc = _LCDML_NO_FUNC;\
			unsigned long g_LCDML_BACK_timer[(cnt+1)];\
			void LCDML_CONTROL_setup();\
			void LCDML_CONTROL_loop()
		
#	else
	
#		define LCDML_BACK_init(cnt)\
			LCDML_FuncPtr g_LCDML_BACK_priority[cnt+1];\
			const PROGMEM uint8_t g_LCDML_BACK_cnt = cnt+1;\
			uint8_t g_LCDML_BACK_start_stop[((cnt+1)/7)+1];\
			uint8_t g_LCDML_BACK_reset[((cnt+1)/7)+1];\
			uint8_t g_LCDML_BACK_loop_status = true;\
			uint8_t g_LCDML_BACK_lastFunc = _LCDML_NO_FUNC;\
			unsigned long g_LCDML_BACK_timer[(cnt+1)];\
			void LCDML_CONTROL_setup();\
			void LCDML_CONTROL_loop()
	
#	endif
		
	// macro: loop function  
#	define LCDML_run(mode)\
		if (bitRead(LCDML.control, _LCDML_control_funcend)) {\
			LCDML_BACK_reset(LCDML_BACKEND_menu); \
			LCDML_BACK_dynamic_setDefaultTime(LCDML_BACKEND_menu); \
			LCDML_BACK_stopStable(LCDML_BACKEND_menu); \
		}\
		for(uint8_t l_LCDML_BACK_i = 0; l_LCDML_BACK_i<g_LCDML_BACK_cnt;l_LCDML_BACK_i++) {\
			g_LCDML_BACK_priority[(l_LCDML_BACK_i)]();\
			if (mode == true && g_LCDML_BACK_loop_status == false)\
			{\
				g_LCDML_BACK_loop_status = true;\
				break;\
			}\
		}



#	if defined ( ESP8266 )
// thread create
	// macro: help to create a new thread: generate weak functions
#		define LCDML_BACK_help_new_thread(id, name, status)\
			const uint8_t g_LCDML_BACK_id__##name  = id;\
			void LCDML_BACK_setup_##name(void);\
			boolean LCDML_BACK_loop_##name(void);\
			void LCDML_BACK_stable_##name(void);\
			void LCDML_BACK_function_##name(void);\
			void LCDML_BACK_setupInit_##id(void){ g_LCDML_BACK_priority[id] = LCDML_BACK_function_##name; if(status == 1) {LCDML_BACK_start(name);} else if(status == 2) { LCDML_BACK_stopStable(name); }}

	// macro: create a new thread with dynamc times
#		define LCDML_BACK_new_timebased_dynamic(id, init_time, status, name)\
			LCDML_BACK_help_new_thread(id, name, status);\
			const uint32_t   _LCDML_BACK_time_default__##name  = (uint32_t)(init_time);\
			unsigned long g_LCDML_BACK_dynTime_##name = (uint32_t)(init_time); \
			LCDML_BACK_THREAD_FUNCTION_TIME_BASED(name, g_LCDML_BACK_dynTime_##name); 

#	else
	// thread create
	// macro: help to create a new thread: generate weak functions
#		define LCDML_BACK_help_new_thread(id, name, status)\
			const PROGMEM uint8_t g_LCDML_BACK_id__##name  = id;\
			void LCDML_BACK_setup_##name(void);\
			boolean LCDML_BACK_loop_##name(void);\
			void LCDML_BACK_stable_##name(void);\
			void LCDML_BACK_function_##name(void);\
			void LCDML_BACK_setupInit_##id(void){ g_LCDML_BACK_priority[id] = LCDML_BACK_function_##name; if(status == 1) {LCDML_BACK_start(name);} else if(status == 2) { LCDML_BACK_stopStable(name); }}

	// macro: create a new thread with dynamc times
#		define LCDML_BACK_new_timebased_dynamic(id, init_time, status, name)\
			LCDML_BACK_help_new_thread(id, name, status);\
			const PROGMEM uint32_t   _LCDML_BACK_time_default__##name  = (uint32_t)(init_time);\
			unsigned long g_LCDML_BACK_dynTime_##name = (uint32_t)(init_time); \
			LCDML_BACK_THREAD_FUNCTION_TIME_BASED(name, g_LCDML_BACK_dynTime_##name); 	
#	endif
		
		
	// macro: create a new thread with static times
#	define LCDML_BACK_new_timebased_static(id, init_time, status, name)\
		LCDML_BACK_help_new_thread(id, name, status);\
		LCDML_BACK_THREAD_FUNCTION_TIME_BASED(name, init_time);
		

	// macro: create a event based thread
#	define LCDML_BACK_new_eventbased(id, name)\
		LCDML_BACK_help_new_thread(id, name, false);\
		LCDML_BACK_THREAD_FUNCTION_EVENT_BASED(name);		



// thread control
	// macro: thread start single
#	define LCDML_BACK_start(name)\
		LCDML_BACK_dynamic_timeToZero(name);\
		bitWrite(g_LCDML_BACK_start_stop[g_LCDML_BACK_id__##name / 7], g_LCDML_BACK_id__##name%7, true)
	// macro: thread stop
#	define LCDML_BACK_stop(name)\
		bitWrite(g_LCDML_BACK_start_stop[g_LCDML_BACK_id__##name / 7], g_LCDML_BACK_id__##name%7, false) 
	// macro: thread stop stable => calls a function at the end
#	define LCDML_BACK_stopStable(name)\
		LCDML_BACK_stop(name);\
		LCDML_BACK_stable_##name()
	// macro: thread reset
#	define LCDML_BACK_reset(name)\
		bitWrite(g_LCDML_BACK_reset[g_LCDML_BACK_id__##name / 7], g_LCDML_BACK_id__##name%7, false); \
		g_LCDML_BACK_timer[g_LCDML_BACK_id__##name] = 0
	//macro: thread reStart 
#	define LCDML_BACK_restart(name)\
		LCDML_BACK_reset(name);\
		LCDML_BACK_start(name)

// thread control event
#	define LCDML_BACK_event_start(name)\
		LCDML_BACK_start(name)
#	define LCDML_BACK_event_reset(name)\
		LCDML_BACK_reset(name)
#	define LCDML_BACK_event_restart(name)\
		LCDML_BACK_restart(name)


//all
	// macro: thread start all
#	define LCDML_BACK_all_start()\
		for(uint8_t l_LCDML_BACK_i = 0; l_LCDML_BACK_i<g_LCDML_BACK_cnt;l_LCDML_BACK_i++) { \
			bitWrite(g_LCDML_BACK_start_stop[l_LCDML_BACK_i/7], l_LCDML_BACK_i%7, true); \
		}
	// macro: thread stop all
#	define LCDML_BACK_all_stop()\
		for(uint8_t l_LCDML_BACK_i = 0; l_LCDML_BACK_i<g_LCDML_BACK_cnt;l_LCDML_BACK_i++) { \
			bitWrite(g_LCDML_BACK_start_stop[l_LCDML_BACK_i/7], l_LCDML_BACK_i%7, false); \
		}
	// macro: thread reset all
#	define LCDML_BACK_all_reset()\
		for(uint8_t l_LCDML_BACK_i = 0; l_LCDML_BACK_i<g_LCDML_BACK_cnt;l_LCDML_BACK_i++) { \
			bitWrite(g_LCDML_BACK_reset[l_LCDML_BACK_i/7], l_LCDML_BACK_i%7, false); \
		}
	//macro: thread reStart all 
#	define LCDML_BACK_all_restart()\
		LCDML_BACK_all_reset();\
		LCDML_BACK_all_start()


//group
	// macro: add group elements
#	define LCDML_BACK_group(name)\
		{g_LCDML_BACK_id__##name/7, g_LCDML_BACK_id__##name%7} 
	// macro: create a new group
#	define LCDML_BACK_group_init(name, thread_cnt)\
		uint8_t g_LCDML_BACK_group__##name##_cnt = thread_cnt;\
		uint8_t g_LCDML_BACK_group__##name[thread_cnt][2] = 
	// macro: thread start group
#	define LCDML_BACK_group_start(group_name)\
		for(uint8_t l_LCDML_BACK_i = 0; l_LCDML_BACK_i<(g_LCDML_BACK_group__##group_name##_cnt);l_LCDML_BACK_i++) {\
			bitWrite(g_LCDML_BACK_start_stop[g_LCDML_BACK_group__##group_name[l_LCDML_BACK_i][0]], g_LCDML_BACK_group__##group_name[l_LCDML_BACK_i][1], true);\
		}
	// macro: thread stop group
#	define LCDML_BACK_group_stop(group_name)\
		for(uint8_t l_LCDML_BACK_i = 0; l_LCDML_BACK_i<(g_LCDML_BACK_group__##group_name##_cnt);l_LCDML_BACK_i++) {\
			bitWrite(g_LCDML_BACK_start_stop[g_LCDML_BACK_group__##group_name[l_LCDML_BACK_i][0]], g_LCDML_BACK_group__##group_name[l_LCDML_BACK_i][1], false);\
		}
	// macro: thread reset group
#	define LCDML_BACK_group_reset(group_name)\
		for(uint8_t l_LCDML_BACK_i = 0; l_LCDML_BACK_i<(g_LCDML_BACK_group__##group_name##_cnt);l_LCDML_BACK_i++) {\
			bitWrite(g_LCDML_BACK_reset[g_LCDML_BACK_group__##group_name[l_LCDML_BACK_i][0]], g_LCDML_BACK_group__##group_name[l_LCDML_BACK_i][1], false);\
		}
	// macro: thread start group
#	define LCDML_BACK_group_restart(group_name)\
		LCDML_BACK_group_reset(group_name);\
		LCDML_BACK_group_start(group_name)
	


//signals
	// macro:
#	define LCDML_BACK_signal(id, name)\
		uint8_t  g_simpleSignal_id__##name  = id	
	// macro: creates the LCDML_BACK managemand variables
#	define LCDML_BACK_signal_init(cnt)\
		uint8_t g_simpleSignal_status[(cnt/7)+1]
	// macro:
#	define LCDML_BACK_signal_set(name)\
		bitSet(g_simpleSignal_status[g_simpleSignal_id__##name/7], g_simpleSignal_id__##name%7)
	// macro:	
#	define LCDML_BACK_signal_get(name)\
		bitRead(g_simpleSignal_status[g_simpleSignal_id__##name/7], g_simpleSignal_id__##name%7)
	// macro:
#	define LCDML_BACK_signal_clear(name)\
		bitClear(g_simpleSignal_status[g_simpleSignal_id__##name/7], g_simpleSignal_id__##name%7)


//is run
	//macro: thread is running ? 
#	define LCDML_BACK_isRun(name)\
		bitRead(g_LCDML_BACK_start_stop[g_LCDML_BACK_id__##name/7], g_LCDML_BACK_id__##name%7)
	
	
// dynamic times	
	//macro: edit thread loop time
#	define LCDML_BACK_dynamic_setLoopTime(name, time)\
		g_LCDML_BACK_dynTime_##name = time
	//macro: get thread loop time
#	define LCDML_BACK_dynamic_getLoopTime(name)\
		g_LCDML_BACK_dynTime_##name	
	// macro: reset a dynamic thread to default settings
#	define LCDML_BACK_dynamic_setDefaultTime(name)\
		g_LCDML_BACK_dynTime_##name =_LCDML_BACK_time_default__##name
	// macro: restart dynamic thread time
#	define LCDML_BACK_dynamic_restartTimer(name)\
		g_LCDML_BACK_timer[g_LCDML_BACK_id__##name] = millis()
	// macro: setTime 0
#	define LCDML_BACK_dynamic_timeToZero(name)\
		g_LCDML_BACK_timer[g_LCDML_BACK_id__##name] = (millis()+1)



//direct call
	// macro: call a thread
#	define LCDML_BACK_call(name)\
		LCDML_BACK_function_##name()
	// macro: call a thread loop function
#	define LCDML_BACK_call_loop(name)\
		LCDML_BACK_loop_##name()
	// macro: call a thread setup function
#	define LCDML_BACK_call_setup(name)\
		LCDML_BACK_setup_##name()
	// macro: call a thread stable function
#	define LCDML_BACK_call_stable(name)\
		LCDML_BACK_stable_##name()	
	


//help macros
	// macro: thread timer with return
	// attention: when the wait_time is bigger then millis on startup the result ist true 
	// to fix this, the timer_var have to be initialise with the waittime 
	#define LCDML_BACK_TIMER(timer_var, wait_time)\
		if(!((millis() - timer_var) >= wait_time)) {  return; }\
		timer_var = millis();
	//macro: thread is running with return !
#	define LCDML_BACK_THREAD_isRun(name)\
	if(!bitRead(g_LCDML_BACK_start_stop[g_LCDML_BACK_id__##name/7], g_LCDML_BACK_id__##name%7)) { return; } 

	//macro: reset the reset bin from a thread
#	define LCDML_BACK_UNSET_reset(name)\
		bitWrite(g_LCDML_BACK_reset[g_LCDML_BACK_id__##name/7], g_LCDML_BACK_id__##name%7, true)

	//macro: get the reset bit from a thread
#	define LCDML_BACK_GET_reset(name)\
		bitRead(g_LCDML_BACK_reset[g_LCDML_BACK_id__##name/7], g_LCDML_BACK_id__##name%7)

	//macro: create the thread setup function 
#	define LCDML_BACK_THREAD_FUNCTION_TIME_BASED(name, time)\
		void LCDML_BACK_function_##name(void)\
		{\
			LCDML_BACK_THREAD_isRun(name);\
			if(LCDML_BACK_GET_reset(name) == false) {\
				LCDML_BACK_UNSET_reset(name);\
				LCDML_BACK_setup_##name();\
				g_LCDML_BACK_timer[g_LCDML_BACK_id__##name] = time; \
			}\
			LCDML_BACK_TIMER(g_LCDML_BACK_timer[g_LCDML_BACK_id__##name], time);\
			g_LCDML_BACK_loop_status = (LCDML_BACK_loop_##name()) ? true : false;\
		}

	//macro: create the thread setup function 
#	define LCDML_BACK_THREAD_FUNCTION_EVENT_BASED(name)\
		void LCDML_BACK_function_##name(void)\
		{\
			LCDML_BACK_THREAD_isRun(name);\
			if(LCDML_BACK_GET_reset(name) == true) {\
				LCDML_BACK_UNSET_reset(name);\
				LCDML_BACK_setup_##name();\
			}\
			g_LCDML_BACK_loop_status = (LCDML_BACK_loop_##name()) ? true : false;\
			LCDML_BACK_stop(name);\
		}

#	define LCDML_BACK_help_setup(id)   LCDML_BACK_setupInit_##id();

#	define LCDML_setup(N)\
		LCDML_DISP_initSetup(_LCDML_DISP_cnt);\
		LCDML_BACK_help_setupInit(N)













	













	






#	define LCDML_BACK_help_setup_repeat_255() LCDML_BACK_help_setup_repeat_254() LCDML_BACK_help_setup(255)
#	define LCDML_BACK_help_setup_repeat_254() LCDML_BACK_help_setup_repeat_253() LCDML_BACK_help_setup(254)
#	define LCDML_BACK_help_setup_repeat_253() LCDML_BACK_help_setup_repeat_252() LCDML_BACK_help_setup(253)
#	define LCDML_BACK_help_setup_repeat_252() LCDML_BACK_help_setup_repeat_251() LCDML_BACK_help_setup(252)
#	define LCDML_BACK_help_setup_repeat_251() LCDML_BACK_help_setup_repeat_250() LCDML_BACK_help_setup(251)
#	define LCDML_BACK_help_setup_repeat_250() LCDML_BACK_help_setup_repeat_249() LCDML_BACK_help_setup(250)
#	define LCDML_BACK_help_setup_repeat_249() LCDML_BACK_help_setup_repeat_248() LCDML_BACK_help_setup(249)
#	define LCDML_BACK_help_setup_repeat_248() LCDML_BACK_help_setup_repeat_247() LCDML_BACK_help_setup(248)
#	define LCDML_BACK_help_setup_repeat_247() LCDML_BACK_help_setup_repeat_246() LCDML_BACK_help_setup(247)
#	define LCDML_BACK_help_setup_repeat_246() LCDML_BACK_help_setup_repeat_245() LCDML_BACK_help_setup(246)
#	define LCDML_BACK_help_setup_repeat_245() LCDML_BACK_help_setup_repeat_244() LCDML_BACK_help_setup(245)
#	define LCDML_BACK_help_setup_repeat_244() LCDML_BACK_help_setup_repeat_243() LCDML_BACK_help_setup(244)
#	define LCDML_BACK_help_setup_repeat_243() LCDML_BACK_help_setup_repeat_242() LCDML_BACK_help_setup(243)
#	define LCDML_BACK_help_setup_repeat_242() LCDML_BACK_help_setup_repeat_241() LCDML_BACK_help_setup(242)
#	define LCDML_BACK_help_setup_repeat_241() LCDML_BACK_help_setup_repeat_240() LCDML_BACK_help_setup(241)
#	define LCDML_BACK_help_setup_repeat_240() LCDML_BACK_help_setup_repeat_239() LCDML_BACK_help_setup(240)
#	define LCDML_BACK_help_setup_repeat_239() LCDML_BACK_help_setup_repeat_238() LCDML_BACK_help_setup(239)
#	define LCDML_BACK_help_setup_repeat_238() LCDML_BACK_help_setup_repeat_237() LCDML_BACK_help_setup(238)
#	define LCDML_BACK_help_setup_repeat_237() LCDML_BACK_help_setup_repeat_236() LCDML_BACK_help_setup(237)
#	define LCDML_BACK_help_setup_repeat_236() LCDML_BACK_help_setup_repeat_235() LCDML_BACK_help_setup(236)
#	define LCDML_BACK_help_setup_repeat_235() LCDML_BACK_help_setup_repeat_234() LCDML_BACK_help_setup(235)
#	define LCDML_BACK_help_setup_repeat_234() LCDML_BACK_help_setup_repeat_233() LCDML_BACK_help_setup(234)
#	define LCDML_BACK_help_setup_repeat_233() LCDML_BACK_help_setup_repeat_232() LCDML_BACK_help_setup(233)
#	define LCDML_BACK_help_setup_repeat_232() LCDML_BACK_help_setup_repeat_231() LCDML_BACK_help_setup(232)
#	define LCDML_BACK_help_setup_repeat_231() LCDML_BACK_help_setup_repeat_230() LCDML_BACK_help_setup(231)
#	define LCDML_BACK_help_setup_repeat_230() LCDML_BACK_help_setup_repeat_229() LCDML_BACK_help_setup(230)
#	define LCDML_BACK_help_setup_repeat_229() LCDML_BACK_help_setup_repeat_228() LCDML_BACK_help_setup(229)
#	define LCDML_BACK_help_setup_repeat_228() LCDML_BACK_help_setup_repeat_227() LCDML_BACK_help_setup(228)
#	define LCDML_BACK_help_setup_repeat_227() LCDML_BACK_help_setup_repeat_226() LCDML_BACK_help_setup(227)
#	define LCDML_BACK_help_setup_repeat_226() LCDML_BACK_help_setup_repeat_225() LCDML_BACK_help_setup(226)
#	define LCDML_BACK_help_setup_repeat_225() LCDML_BACK_help_setup_repeat_224() LCDML_BACK_help_setup(225)
#	define LCDML_BACK_help_setup_repeat_224() LCDML_BACK_help_setup_repeat_223() LCDML_BACK_help_setup(224)
#	define LCDML_BACK_help_setup_repeat_223() LCDML_BACK_help_setup_repeat_222() LCDML_BACK_help_setup(223)
#	define LCDML_BACK_help_setup_repeat_222() LCDML_BACK_help_setup_repeat_221() LCDML_BACK_help_setup(222)
#	define LCDML_BACK_help_setup_repeat_221() LCDML_BACK_help_setup_repeat_220() LCDML_BACK_help_setup(221)
#	define LCDML_BACK_help_setup_repeat_220() LCDML_BACK_help_setup_repeat_219() LCDML_BACK_help_setup(220)
#	define LCDML_BACK_help_setup_repeat_219() LCDML_BACK_help_setup_repeat_218() LCDML_BACK_help_setup(219)
#	define LCDML_BACK_help_setup_repeat_218() LCDML_BACK_help_setup_repeat_217() LCDML_BACK_help_setup(218)
#	define LCDML_BACK_help_setup_repeat_217() LCDML_BACK_help_setup_repeat_216() LCDML_BACK_help_setup(217)
#	define LCDML_BACK_help_setup_repeat_216() LCDML_BACK_help_setup_repeat_215() LCDML_BACK_help_setup(216)
#	define LCDML_BACK_help_setup_repeat_215() LCDML_BACK_help_setup_repeat_214() LCDML_BACK_help_setup(215)
#	define LCDML_BACK_help_setup_repeat_214() LCDML_BACK_help_setup_repeat_213() LCDML_BACK_help_setup(214)
#	define LCDML_BACK_help_setup_repeat_213() LCDML_BACK_help_setup_repeat_212() LCDML_BACK_help_setup(213)
#	define LCDML_BACK_help_setup_repeat_212() LCDML_BACK_help_setup_repeat_211() LCDML_BACK_help_setup(212)
#	define LCDML_BACK_help_setup_repeat_211() LCDML_BACK_help_setup_repeat_210() LCDML_BACK_help_setup(211)
#	define LCDML_BACK_help_setup_repeat_210() LCDML_BACK_help_setup_repeat_209() LCDML_BACK_help_setup(210)
#	define LCDML_BACK_help_setup_repeat_209() LCDML_BACK_help_setup_repeat_208() LCDML_BACK_help_setup(209)
#	define LCDML_BACK_help_setup_repeat_208() LCDML_BACK_help_setup_repeat_207() LCDML_BACK_help_setup(208)
#	define LCDML_BACK_help_setup_repeat_207() LCDML_BACK_help_setup_repeat_206() LCDML_BACK_help_setup(207)
#	define LCDML_BACK_help_setup_repeat_206() LCDML_BACK_help_setup_repeat_205() LCDML_BACK_help_setup(206)
#	define LCDML_BACK_help_setup_repeat_205() LCDML_BACK_help_setup_repeat_204() LCDML_BACK_help_setup(205)
#	define LCDML_BACK_help_setup_repeat_204() LCDML_BACK_help_setup_repeat_203() LCDML_BACK_help_setup(204)
#	define LCDML_BACK_help_setup_repeat_203() LCDML_BACK_help_setup_repeat_202() LCDML_BACK_help_setup(203)
#	define LCDML_BACK_help_setup_repeat_202() LCDML_BACK_help_setup_repeat_201() LCDML_BACK_help_setup(202)
#	define LCDML_BACK_help_setup_repeat_201() LCDML_BACK_help_setup_repeat_200() LCDML_BACK_help_setup(201)
#	define LCDML_BACK_help_setup_repeat_200() LCDML_BACK_help_setup_repeat_199() LCDML_BACK_help_setup(200)
#	define LCDML_BACK_help_setup_repeat_199() LCDML_BACK_help_setup_repeat_198() LCDML_BACK_help_setup(199)
#	define LCDML_BACK_help_setup_repeat_198() LCDML_BACK_help_setup_repeat_197() LCDML_BACK_help_setup(198)
#	define LCDML_BACK_help_setup_repeat_197() LCDML_BACK_help_setup_repeat_196() LCDML_BACK_help_setup(197)
#	define LCDML_BACK_help_setup_repeat_196() LCDML_BACK_help_setup_repeat_195() LCDML_BACK_help_setup(196)
#	define LCDML_BACK_help_setup_repeat_195() LCDML_BACK_help_setup_repeat_194() LCDML_BACK_help_setup(195)
#	define LCDML_BACK_help_setup_repeat_194() LCDML_BACK_help_setup_repeat_193() LCDML_BACK_help_setup(194)
#	define LCDML_BACK_help_setup_repeat_193() LCDML_BACK_help_setup_repeat_192() LCDML_BACK_help_setup(193)
#	define LCDML_BACK_help_setup_repeat_192() LCDML_BACK_help_setup_repeat_191() LCDML_BACK_help_setup(192)
#	define LCDML_BACK_help_setup_repeat_191() LCDML_BACK_help_setup_repeat_190() LCDML_BACK_help_setup(191)
#	define LCDML_BACK_help_setup_repeat_190() LCDML_BACK_help_setup_repeat_189() LCDML_BACK_help_setup(190)
#	define LCDML_BACK_help_setup_repeat_189() LCDML_BACK_help_setup_repeat_188() LCDML_BACK_help_setup(189)
#	define LCDML_BACK_help_setup_repeat_188() LCDML_BACK_help_setup_repeat_187() LCDML_BACK_help_setup(188)
#	define LCDML_BACK_help_setup_repeat_187() LCDML_BACK_help_setup_repeat_186() LCDML_BACK_help_setup(187)
#	define LCDML_BACK_help_setup_repeat_186() LCDML_BACK_help_setup_repeat_185() LCDML_BACK_help_setup(186)
#	define LCDML_BACK_help_setup_repeat_185() LCDML_BACK_help_setup_repeat_184() LCDML_BACK_help_setup(185)
#	define LCDML_BACK_help_setup_repeat_184() LCDML_BACK_help_setup_repeat_183() LCDML_BACK_help_setup(184)
#	define LCDML_BACK_help_setup_repeat_183() LCDML_BACK_help_setup_repeat_182() LCDML_BACK_help_setup(183)
#	define LCDML_BACK_help_setup_repeat_182() LCDML_BACK_help_setup_repeat_181() LCDML_BACK_help_setup(182)
#	define LCDML_BACK_help_setup_repeat_181() LCDML_BACK_help_setup_repeat_180() LCDML_BACK_help_setup(181)
#	define LCDML_BACK_help_setup_repeat_180() LCDML_BACK_help_setup_repeat_179() LCDML_BACK_help_setup(180)
#	define LCDML_BACK_help_setup_repeat_179() LCDML_BACK_help_setup_repeat_178() LCDML_BACK_help_setup(179)
#	define LCDML_BACK_help_setup_repeat_178() LCDML_BACK_help_setup_repeat_177() LCDML_BACK_help_setup(178)
#	define LCDML_BACK_help_setup_repeat_177() LCDML_BACK_help_setup_repeat_176() LCDML_BACK_help_setup(177)
#	define LCDML_BACK_help_setup_repeat_176() LCDML_BACK_help_setup_repeat_175() LCDML_BACK_help_setup(176)
#	define LCDML_BACK_help_setup_repeat_175() LCDML_BACK_help_setup_repeat_174() LCDML_BACK_help_setup(175)
#	define LCDML_BACK_help_setup_repeat_174() LCDML_BACK_help_setup_repeat_173() LCDML_BACK_help_setup(174)
#	define LCDML_BACK_help_setup_repeat_173() LCDML_BACK_help_setup_repeat_172() LCDML_BACK_help_setup(173)
#	define LCDML_BACK_help_setup_repeat_172() LCDML_BACK_help_setup_repeat_171() LCDML_BACK_help_setup(172)
#	define LCDML_BACK_help_setup_repeat_171() LCDML_BACK_help_setup_repeat_170() LCDML_BACK_help_setup(171)
#	define LCDML_BACK_help_setup_repeat_170() LCDML_BACK_help_setup_repeat_169() LCDML_BACK_help_setup(170)
#	define LCDML_BACK_help_setup_repeat_169() LCDML_BACK_help_setup_repeat_168() LCDML_BACK_help_setup(169)
#	define LCDML_BACK_help_setup_repeat_168() LCDML_BACK_help_setup_repeat_167() LCDML_BACK_help_setup(168)
#	define LCDML_BACK_help_setup_repeat_167() LCDML_BACK_help_setup_repeat_166() LCDML_BACK_help_setup(167)
#	define LCDML_BACK_help_setup_repeat_166() LCDML_BACK_help_setup_repeat_165() LCDML_BACK_help_setup(166)
#	define LCDML_BACK_help_setup_repeat_165() LCDML_BACK_help_setup_repeat_164() LCDML_BACK_help_setup(165)
#	define LCDML_BACK_help_setup_repeat_164() LCDML_BACK_help_setup_repeat_163() LCDML_BACK_help_setup(164)
#	define LCDML_BACK_help_setup_repeat_163() LCDML_BACK_help_setup_repeat_162() LCDML_BACK_help_setup(163)
#	define LCDML_BACK_help_setup_repeat_162() LCDML_BACK_help_setup_repeat_161() LCDML_BACK_help_setup(162)
#	define LCDML_BACK_help_setup_repeat_161() LCDML_BACK_help_setup_repeat_160() LCDML_BACK_help_setup(161)
#	define LCDML_BACK_help_setup_repeat_160() LCDML_BACK_help_setup_repeat_159() LCDML_BACK_help_setup(160)
#	define LCDML_BACK_help_setup_repeat_159() LCDML_BACK_help_setup_repeat_158() LCDML_BACK_help_setup(159)
#	define LCDML_BACK_help_setup_repeat_158() LCDML_BACK_help_setup_repeat_157() LCDML_BACK_help_setup(158)
#	define LCDML_BACK_help_setup_repeat_157() LCDML_BACK_help_setup_repeat_156() LCDML_BACK_help_setup(157)
#	define LCDML_BACK_help_setup_repeat_156() LCDML_BACK_help_setup_repeat_155() LCDML_BACK_help_setup(156)
#	define LCDML_BACK_help_setup_repeat_155() LCDML_BACK_help_setup_repeat_154() LCDML_BACK_help_setup(155)
#	define LCDML_BACK_help_setup_repeat_154() LCDML_BACK_help_setup_repeat_153() LCDML_BACK_help_setup(154)
#	define LCDML_BACK_help_setup_repeat_153() LCDML_BACK_help_setup_repeat_152() LCDML_BACK_help_setup(153)
#	define LCDML_BACK_help_setup_repeat_152() LCDML_BACK_help_setup_repeat_151() LCDML_BACK_help_setup(152)
#	define LCDML_BACK_help_setup_repeat_151() LCDML_BACK_help_setup_repeat_150() LCDML_BACK_help_setup(151)
#	define LCDML_BACK_help_setup_repeat_150() LCDML_BACK_help_setup_repeat_149() LCDML_BACK_help_setup(150)
#	define LCDML_BACK_help_setup_repeat_149() LCDML_BACK_help_setup_repeat_148() LCDML_BACK_help_setup(149)
#	define LCDML_BACK_help_setup_repeat_148() LCDML_BACK_help_setup_repeat_147() LCDML_BACK_help_setup(148)
#	define LCDML_BACK_help_setup_repeat_147() LCDML_BACK_help_setup_repeat_146() LCDML_BACK_help_setup(147)
#	define LCDML_BACK_help_setup_repeat_146() LCDML_BACK_help_setup_repeat_145() LCDML_BACK_help_setup(146)
#	define LCDML_BACK_help_setup_repeat_145() LCDML_BACK_help_setup_repeat_144() LCDML_BACK_help_setup(145)
#	define LCDML_BACK_help_setup_repeat_144() LCDML_BACK_help_setup_repeat_143() LCDML_BACK_help_setup(144)
#	define LCDML_BACK_help_setup_repeat_143() LCDML_BACK_help_setup_repeat_142() LCDML_BACK_help_setup(143)
#	define LCDML_BACK_help_setup_repeat_142() LCDML_BACK_help_setup_repeat_141() LCDML_BACK_help_setup(142)
#	define LCDML_BACK_help_setup_repeat_141() LCDML_BACK_help_setup_repeat_140() LCDML_BACK_help_setup(141)
#	define LCDML_BACK_help_setup_repeat_140() LCDML_BACK_help_setup_repeat_139() LCDML_BACK_help_setup(140)
#	define LCDML_BACK_help_setup_repeat_139() LCDML_BACK_help_setup_repeat_138() LCDML_BACK_help_setup(139)
#	define LCDML_BACK_help_setup_repeat_138() LCDML_BACK_help_setup_repeat_137() LCDML_BACK_help_setup(138)
#	define LCDML_BACK_help_setup_repeat_137() LCDML_BACK_help_setup_repeat_136() LCDML_BACK_help_setup(137)
#	define LCDML_BACK_help_setup_repeat_136() LCDML_BACK_help_setup_repeat_135() LCDML_BACK_help_setup(136)
#	define LCDML_BACK_help_setup_repeat_135() LCDML_BACK_help_setup_repeat_134() LCDML_BACK_help_setup(135)
#	define LCDML_BACK_help_setup_repeat_134() LCDML_BACK_help_setup_repeat_133() LCDML_BACK_help_setup(134)
#	define LCDML_BACK_help_setup_repeat_133() LCDML_BACK_help_setup_repeat_132() LCDML_BACK_help_setup(133)
#	define LCDML_BACK_help_setup_repeat_132() LCDML_BACK_help_setup_repeat_131() LCDML_BACK_help_setup(132)
#	define LCDML_BACK_help_setup_repeat_131() LCDML_BACK_help_setup_repeat_130() LCDML_BACK_help_setup(131)
#	define LCDML_BACK_help_setup_repeat_130() LCDML_BACK_help_setup_repeat_129() LCDML_BACK_help_setup(130)
#	define LCDML_BACK_help_setup_repeat_129() LCDML_BACK_help_setup_repeat_128() LCDML_BACK_help_setup(129)
#	define LCDML_BACK_help_setup_repeat_128() LCDML_BACK_help_setup_repeat_127() LCDML_BACK_help_setup(128)
#	define LCDML_BACK_help_setup_repeat_127() LCDML_BACK_help_setup_repeat_126() LCDML_BACK_help_setup(127)
#	define LCDML_BACK_help_setup_repeat_126() LCDML_BACK_help_setup_repeat_125() LCDML_BACK_help_setup(126)
#	define LCDML_BACK_help_setup_repeat_125() LCDML_BACK_help_setup_repeat_124() LCDML_BACK_help_setup(125)
#	define LCDML_BACK_help_setup_repeat_124() LCDML_BACK_help_setup_repeat_123() LCDML_BACK_help_setup(124)
#	define LCDML_BACK_help_setup_repeat_123() LCDML_BACK_help_setup_repeat_122() LCDML_BACK_help_setup(123)
#	define LCDML_BACK_help_setup_repeat_122() LCDML_BACK_help_setup_repeat_121() LCDML_BACK_help_setup(122)
#	define LCDML_BACK_help_setup_repeat_121() LCDML_BACK_help_setup_repeat_120() LCDML_BACK_help_setup(121)
#	define LCDML_BACK_help_setup_repeat_120() LCDML_BACK_help_setup_repeat_119() LCDML_BACK_help_setup(120)
#	define LCDML_BACK_help_setup_repeat_119() LCDML_BACK_help_setup_repeat_118() LCDML_BACK_help_setup(119)
#	define LCDML_BACK_help_setup_repeat_118() LCDML_BACK_help_setup_repeat_117() LCDML_BACK_help_setup(118)
#	define LCDML_BACK_help_setup_repeat_117() LCDML_BACK_help_setup_repeat_116() LCDML_BACK_help_setup(117)
#	define LCDML_BACK_help_setup_repeat_116() LCDML_BACK_help_setup_repeat_115() LCDML_BACK_help_setup(116)
#	define LCDML_BACK_help_setup_repeat_115() LCDML_BACK_help_setup_repeat_114() LCDML_BACK_help_setup(115)
#	define LCDML_BACK_help_setup_repeat_114() LCDML_BACK_help_setup_repeat_113() LCDML_BACK_help_setup(114)
#	define LCDML_BACK_help_setup_repeat_113() LCDML_BACK_help_setup_repeat_112() LCDML_BACK_help_setup(113)
#	define LCDML_BACK_help_setup_repeat_112() LCDML_BACK_help_setup_repeat_111() LCDML_BACK_help_setup(112)
#	define LCDML_BACK_help_setup_repeat_111() LCDML_BACK_help_setup_repeat_110() LCDML_BACK_help_setup(111)
#	define LCDML_BACK_help_setup_repeat_110() LCDML_BACK_help_setup_repeat_109() LCDML_BACK_help_setup(110)
#	define LCDML_BACK_help_setup_repeat_109() LCDML_BACK_help_setup_repeat_108() LCDML_BACK_help_setup(109)
#	define LCDML_BACK_help_setup_repeat_108() LCDML_BACK_help_setup_repeat_107() LCDML_BACK_help_setup(108)
#	define LCDML_BACK_help_setup_repeat_107() LCDML_BACK_help_setup_repeat_106() LCDML_BACK_help_setup(107)
#	define LCDML_BACK_help_setup_repeat_106() LCDML_BACK_help_setup_repeat_105() LCDML_BACK_help_setup(106)
#	define LCDML_BACK_help_setup_repeat_105() LCDML_BACK_help_setup_repeat_104() LCDML_BACK_help_setup(105)
#	define LCDML_BACK_help_setup_repeat_104() LCDML_BACK_help_setup_repeat_103() LCDML_BACK_help_setup(104)
#	define LCDML_BACK_help_setup_repeat_103() LCDML_BACK_help_setup_repeat_102() LCDML_BACK_help_setup(103)
#	define LCDML_BACK_help_setup_repeat_102() LCDML_BACK_help_setup_repeat_101() LCDML_BACK_help_setup(102)
#	define LCDML_BACK_help_setup_repeat_101() LCDML_BACK_help_setup_repeat_100() LCDML_BACK_help_setup(101)
#	define LCDML_BACK_help_setup_repeat_100() LCDML_BACK_help_setup_repeat_99() LCDML_BACK_help_setup(100)
#	define LCDML_BACK_help_setup_repeat_99() LCDML_BACK_help_setup_repeat_98() LCDML_BACK_help_setup(99)
#	define LCDML_BACK_help_setup_repeat_98() LCDML_BACK_help_setup_repeat_97() LCDML_BACK_help_setup(98)
#	define LCDML_BACK_help_setup_repeat_97() LCDML_BACK_help_setup_repeat_96() LCDML_BACK_help_setup(97)
#	define LCDML_BACK_help_setup_repeat_96() LCDML_BACK_help_setup_repeat_95() LCDML_BACK_help_setup(96)
#	define LCDML_BACK_help_setup_repeat_95() LCDML_BACK_help_setup_repeat_94() LCDML_BACK_help_setup(95)
#	define LCDML_BACK_help_setup_repeat_94() LCDML_BACK_help_setup_repeat_93() LCDML_BACK_help_setup(94)
#	define LCDML_BACK_help_setup_repeat_93() LCDML_BACK_help_setup_repeat_92() LCDML_BACK_help_setup(93)
#	define LCDML_BACK_help_setup_repeat_92() LCDML_BACK_help_setup_repeat_91() LCDML_BACK_help_setup(92)
#	define LCDML_BACK_help_setup_repeat_91() LCDML_BACK_help_setup_repeat_90() LCDML_BACK_help_setup(91)
#	define LCDML_BACK_help_setup_repeat_90() LCDML_BACK_help_setup_repeat_89() LCDML_BACK_help_setup(90)
#	define LCDML_BACK_help_setup_repeat_89() LCDML_BACK_help_setup_repeat_88() LCDML_BACK_help_setup(89)
#	define LCDML_BACK_help_setup_repeat_88() LCDML_BACK_help_setup_repeat_87() LCDML_BACK_help_setup(88)
#	define LCDML_BACK_help_setup_repeat_87() LCDML_BACK_help_setup_repeat_86() LCDML_BACK_help_setup(87)
#	define LCDML_BACK_help_setup_repeat_86() LCDML_BACK_help_setup_repeat_85() LCDML_BACK_help_setup(86)
#	define LCDML_BACK_help_setup_repeat_85() LCDML_BACK_help_setup_repeat_84() LCDML_BACK_help_setup(85)
#	define LCDML_BACK_help_setup_repeat_84() LCDML_BACK_help_setup_repeat_83() LCDML_BACK_help_setup(84)
#	define LCDML_BACK_help_setup_repeat_83() LCDML_BACK_help_setup_repeat_82() LCDML_BACK_help_setup(83)
#	define LCDML_BACK_help_setup_repeat_82() LCDML_BACK_help_setup_repeat_81() LCDML_BACK_help_setup(82)
#	define LCDML_BACK_help_setup_repeat_81() LCDML_BACK_help_setup_repeat_80() LCDML_BACK_help_setup(81)
#	define LCDML_BACK_help_setup_repeat_80() LCDML_BACK_help_setup_repeat_79() LCDML_BACK_help_setup(80)
#	define LCDML_BACK_help_setup_repeat_79() LCDML_BACK_help_setup_repeat_78() LCDML_BACK_help_setup(79)
#	define LCDML_BACK_help_setup_repeat_78() LCDML_BACK_help_setup_repeat_77() LCDML_BACK_help_setup(78)
#	define LCDML_BACK_help_setup_repeat_77() LCDML_BACK_help_setup_repeat_76() LCDML_BACK_help_setup(77)
#	define LCDML_BACK_help_setup_repeat_76() LCDML_BACK_help_setup_repeat_75() LCDML_BACK_help_setup(76)
#	define LCDML_BACK_help_setup_repeat_75() LCDML_BACK_help_setup_repeat_74() LCDML_BACK_help_setup(75)
#	define LCDML_BACK_help_setup_repeat_74() LCDML_BACK_help_setup_repeat_73() LCDML_BACK_help_setup(74)
#	define LCDML_BACK_help_setup_repeat_73() LCDML_BACK_help_setup_repeat_72() LCDML_BACK_help_setup(73)
#	define LCDML_BACK_help_setup_repeat_72() LCDML_BACK_help_setup_repeat_71() LCDML_BACK_help_setup(72)
#	define LCDML_BACK_help_setup_repeat_71() LCDML_BACK_help_setup_repeat_70() LCDML_BACK_help_setup(71)
#	define LCDML_BACK_help_setup_repeat_70() LCDML_BACK_help_setup_repeat_69() LCDML_BACK_help_setup(70)
#	define LCDML_BACK_help_setup_repeat_69() LCDML_BACK_help_setup_repeat_68() LCDML_BACK_help_setup(69)
#	define LCDML_BACK_help_setup_repeat_68() LCDML_BACK_help_setup_repeat_67() LCDML_BACK_help_setup(68)
#	define LCDML_BACK_help_setup_repeat_67() LCDML_BACK_help_setup_repeat_66() LCDML_BACK_help_setup(67)
#	define LCDML_BACK_help_setup_repeat_66() LCDML_BACK_help_setup_repeat_65() LCDML_BACK_help_setup(66)
#	define LCDML_BACK_help_setup_repeat_65() LCDML_BACK_help_setup_repeat_64() LCDML_BACK_help_setup(65)
#	define LCDML_BACK_help_setup_repeat_64() LCDML_BACK_help_setup_repeat_63() LCDML_BACK_help_setup(64)
#	define LCDML_BACK_help_setup_repeat_63() LCDML_BACK_help_setup_repeat_62() LCDML_BACK_help_setup(63)
#	define LCDML_BACK_help_setup_repeat_62() LCDML_BACK_help_setup_repeat_61() LCDML_BACK_help_setup(62)
#	define LCDML_BACK_help_setup_repeat_61() LCDML_BACK_help_setup_repeat_60() LCDML_BACK_help_setup(61)
#	define LCDML_BACK_help_setup_repeat_60() LCDML_BACK_help_setup_repeat_59() LCDML_BACK_help_setup(60)
#	define LCDML_BACK_help_setup_repeat_59() LCDML_BACK_help_setup_repeat_58() LCDML_BACK_help_setup(59)
#	define LCDML_BACK_help_setup_repeat_58() LCDML_BACK_help_setup_repeat_57() LCDML_BACK_help_setup(58)
#	define LCDML_BACK_help_setup_repeat_57() LCDML_BACK_help_setup_repeat_56() LCDML_BACK_help_setup(57)
#	define LCDML_BACK_help_setup_repeat_56() LCDML_BACK_help_setup_repeat_55() LCDML_BACK_help_setup(56)
#	define LCDML_BACK_help_setup_repeat_55() LCDML_BACK_help_setup_repeat_54() LCDML_BACK_help_setup(55)
#	define LCDML_BACK_help_setup_repeat_54() LCDML_BACK_help_setup_repeat_53() LCDML_BACK_help_setup(54)
#	define LCDML_BACK_help_setup_repeat_53() LCDML_BACK_help_setup_repeat_52() LCDML_BACK_help_setup(53)
#	define LCDML_BACK_help_setup_repeat_52() LCDML_BACK_help_setup_repeat_51() LCDML_BACK_help_setup(52)
#	define LCDML_BACK_help_setup_repeat_51() LCDML_BACK_help_setup_repeat_50() LCDML_BACK_help_setup(51)
#	define LCDML_BACK_help_setup_repeat_50() LCDML_BACK_help_setup_repeat_49() LCDML_BACK_help_setup(50)
#	define LCDML_BACK_help_setup_repeat_49() LCDML_BACK_help_setup_repeat_48() LCDML_BACK_help_setup(49)
#	define LCDML_BACK_help_setup_repeat_48() LCDML_BACK_help_setup_repeat_47() LCDML_BACK_help_setup(48)
#	define LCDML_BACK_help_setup_repeat_47() LCDML_BACK_help_setup_repeat_46() LCDML_BACK_help_setup(47)
#	define LCDML_BACK_help_setup_repeat_46() LCDML_BACK_help_setup_repeat_45() LCDML_BACK_help_setup(46)
#	define LCDML_BACK_help_setup_repeat_45() LCDML_BACK_help_setup_repeat_44() LCDML_BACK_help_setup(45)
#	define LCDML_BACK_help_setup_repeat_44() LCDML_BACK_help_setup_repeat_43() LCDML_BACK_help_setup(44)
#	define LCDML_BACK_help_setup_repeat_43() LCDML_BACK_help_setup_repeat_42() LCDML_BACK_help_setup(43)
#	define LCDML_BACK_help_setup_repeat_42() LCDML_BACK_help_setup_repeat_41() LCDML_BACK_help_setup(42)
#	define LCDML_BACK_help_setup_repeat_41() LCDML_BACK_help_setup_repeat_40() LCDML_BACK_help_setup(41)
#	define LCDML_BACK_help_setup_repeat_40() LCDML_BACK_help_setup_repeat_39() LCDML_BACK_help_setup(40)
#	define LCDML_BACK_help_setup_repeat_39() LCDML_BACK_help_setup_repeat_38() LCDML_BACK_help_setup(39)
#	define LCDML_BACK_help_setup_repeat_38() LCDML_BACK_help_setup_repeat_37() LCDML_BACK_help_setup(38)
#	define LCDML_BACK_help_setup_repeat_37() LCDML_BACK_help_setup_repeat_36() LCDML_BACK_help_setup(37)
#	define LCDML_BACK_help_setup_repeat_36() LCDML_BACK_help_setup_repeat_35() LCDML_BACK_help_setup(36)
#	define LCDML_BACK_help_setup_repeat_35() LCDML_BACK_help_setup_repeat_34() LCDML_BACK_help_setup(35)
#	define LCDML_BACK_help_setup_repeat_34() LCDML_BACK_help_setup_repeat_33() LCDML_BACK_help_setup(34)
#	define LCDML_BACK_help_setup_repeat_33() LCDML_BACK_help_setup_repeat_32() LCDML_BACK_help_setup(33)
#	define LCDML_BACK_help_setup_repeat_32() LCDML_BACK_help_setup_repeat_31() LCDML_BACK_help_setup(32)
#	define LCDML_BACK_help_setup_repeat_31() LCDML_BACK_help_setup_repeat_30() LCDML_BACK_help_setup(31)
#	define LCDML_BACK_help_setup_repeat_30() LCDML_BACK_help_setup_repeat_29() LCDML_BACK_help_setup(30)
#	define LCDML_BACK_help_setup_repeat_29() LCDML_BACK_help_setup_repeat_28() LCDML_BACK_help_setup(29)
#	define LCDML_BACK_help_setup_repeat_28() LCDML_BACK_help_setup_repeat_27() LCDML_BACK_help_setup(28)
#	define LCDML_BACK_help_setup_repeat_27() LCDML_BACK_help_setup_repeat_26() LCDML_BACK_help_setup(27)
#	define LCDML_BACK_help_setup_repeat_26() LCDML_BACK_help_setup_repeat_25() LCDML_BACK_help_setup(26)
#	define LCDML_BACK_help_setup_repeat_25() LCDML_BACK_help_setup_repeat_24() LCDML_BACK_help_setup(25)
#	define LCDML_BACK_help_setup_repeat_24() LCDML_BACK_help_setup_repeat_23() LCDML_BACK_help_setup(24)
#	define LCDML_BACK_help_setup_repeat_23() LCDML_BACK_help_setup_repeat_22() LCDML_BACK_help_setup(23)
#	define LCDML_BACK_help_setup_repeat_22() LCDML_BACK_help_setup_repeat_21() LCDML_BACK_help_setup(22)
#	define LCDML_BACK_help_setup_repeat_21() LCDML_BACK_help_setup_repeat_20() LCDML_BACK_help_setup(21)
#	define LCDML_BACK_help_setup_repeat_20() LCDML_BACK_help_setup_repeat_19() LCDML_BACK_help_setup(20)
#	define LCDML_BACK_help_setup_repeat_19() LCDML_BACK_help_setup_repeat_18() LCDML_BACK_help_setup(19)
#	define LCDML_BACK_help_setup_repeat_18() LCDML_BACK_help_setup_repeat_17() LCDML_BACK_help_setup(18)
#	define LCDML_BACK_help_setup_repeat_17() LCDML_BACK_help_setup_repeat_16() LCDML_BACK_help_setup(17)
#	define LCDML_BACK_help_setup_repeat_16() LCDML_BACK_help_setup_repeat_15() LCDML_BACK_help_setup(16)
#	define LCDML_BACK_help_setup_repeat_15() LCDML_BACK_help_setup_repeat_14() LCDML_BACK_help_setup(15)
#	define LCDML_BACK_help_setup_repeat_14() LCDML_BACK_help_setup_repeat_13() LCDML_BACK_help_setup(14)
#	define LCDML_BACK_help_setup_repeat_13() LCDML_BACK_help_setup_repeat_12() LCDML_BACK_help_setup(13)
#	define LCDML_BACK_help_setup_repeat_12() LCDML_BACK_help_setup_repeat_11() LCDML_BACK_help_setup(12)
#	define LCDML_BACK_help_setup_repeat_11() LCDML_BACK_help_setup_repeat_10() LCDML_BACK_help_setup(11)
#	define LCDML_BACK_help_setup_repeat_10() LCDML_BACK_help_setup_repeat_9() LCDML_BACK_help_setup(10)
#	define LCDML_BACK_help_setup_repeat_9() LCDML_BACK_help_setup_repeat_8() LCDML_BACK_help_setup(9)
#	define LCDML_BACK_help_setup_repeat_8() LCDML_BACK_help_setup_repeat_7() LCDML_BACK_help_setup(8)
#	define LCDML_BACK_help_setup_repeat_7() LCDML_BACK_help_setup_repeat_6() LCDML_BACK_help_setup(7)
#	define LCDML_BACK_help_setup_repeat_6() LCDML_BACK_help_setup_repeat_5() LCDML_BACK_help_setup(6)
#	define LCDML_BACK_help_setup_repeat_5() LCDML_BACK_help_setup_repeat_4() LCDML_BACK_help_setup(5)
#	define LCDML_BACK_help_setup_repeat_4() LCDML_BACK_help_setup_repeat_3() LCDML_BACK_help_setup(4)
#	define LCDML_BACK_help_setup_repeat_3() LCDML_BACK_help_setup_repeat_2() LCDML_BACK_help_setup(3)
#	define LCDML_BACK_help_setup_repeat_2() LCDML_BACK_help_setup_repeat_1() LCDML_BACK_help_setup(2)
#	define LCDML_BACK_help_setup_repeat_1() LCDML_BACK_help_setup_repeat_0() LCDML_BACK_help_setup(1) 
#	define LCDML_BACK_help_setup_repeat_0() LCDML_BACK_help_setup(0) 
#	define LCDML_BACK_help_setupInit(N)	 LCDML_BACK_help_setup_repeat_##N()

	







/* ************************************************ */
/* LCDMenuLib_lang_repeat									*/
/* ************************************************ */
#	define LCDML_DISP_lang_repeat_255() LCDML_DISP_lang_repeat_254() LCDML_DISP_lang(255),
#	define LCDML_DISP_lang_repeat_254() LCDML_DISP_lang_repeat_253() LCDML_DISP_lang(254),
#	define LCDML_DISP_lang_repeat_253() LCDML_DISP_lang_repeat_252() LCDML_DISP_lang(253),
#	define LCDML_DISP_lang_repeat_252() LCDML_DISP_lang_repeat_251() LCDML_DISP_lang(252),
#	define LCDML_DISP_lang_repeat_251() LCDML_DISP_lang_repeat_250() LCDML_DISP_lang(251),
#	define LCDML_DISP_lang_repeat_250() LCDML_DISP_lang_repeat_249() LCDML_DISP_lang(250),
#	define LCDML_DISP_lang_repeat_249() LCDML_DISP_lang_repeat_248() LCDML_DISP_lang(249),
#	define LCDML_DISP_lang_repeat_248() LCDML_DISP_lang_repeat_247() LCDML_DISP_lang(248),
#	define LCDML_DISP_lang_repeat_247() LCDML_DISP_lang_repeat_246() LCDML_DISP_lang(247),
#	define LCDML_DISP_lang_repeat_246() LCDML_DISP_lang_repeat_245() LCDML_DISP_lang(246),
#	define LCDML_DISP_lang_repeat_245() LCDML_DISP_lang_repeat_244() LCDML_DISP_lang(245),
#	define LCDML_DISP_lang_repeat_244() LCDML_DISP_lang_repeat_243() LCDML_DISP_lang(244),
#	define LCDML_DISP_lang_repeat_243() LCDML_DISP_lang_repeat_242() LCDML_DISP_lang(243),
#	define LCDML_DISP_lang_repeat_242() LCDML_DISP_lang_repeat_241() LCDML_DISP_lang(242),
#	define LCDML_DISP_lang_repeat_241() LCDML_DISP_lang_repeat_240() LCDML_DISP_lang(241),
#	define LCDML_DISP_lang_repeat_240() LCDML_DISP_lang_repeat_239() LCDML_DISP_lang(240),
#	define LCDML_DISP_lang_repeat_239() LCDML_DISP_lang_repeat_238() LCDML_DISP_lang(239),
#	define LCDML_DISP_lang_repeat_238() LCDML_DISP_lang_repeat_237() LCDML_DISP_lang(238),
#	define LCDML_DISP_lang_repeat_237() LCDML_DISP_lang_repeat_236() LCDML_DISP_lang(237),
#	define LCDML_DISP_lang_repeat_236() LCDML_DISP_lang_repeat_235() LCDML_DISP_lang(236),
#	define LCDML_DISP_lang_repeat_235() LCDML_DISP_lang_repeat_234() LCDML_DISP_lang(235),
#	define LCDML_DISP_lang_repeat_234() LCDML_DISP_lang_repeat_233() LCDML_DISP_lang(234),
#	define LCDML_DISP_lang_repeat_233() LCDML_DISP_lang_repeat_232() LCDML_DISP_lang(233),
#	define LCDML_DISP_lang_repeat_232() LCDML_DISP_lang_repeat_231() LCDML_DISP_lang(232),
#	define LCDML_DISP_lang_repeat_231() LCDML_DISP_lang_repeat_230() LCDML_DISP_lang(231),
#	define LCDML_DISP_lang_repeat_230() LCDML_DISP_lang_repeat_229() LCDML_DISP_lang(230),
#	define LCDML_DISP_lang_repeat_229() LCDML_DISP_lang_repeat_228() LCDML_DISP_lang(229),
#	define LCDML_DISP_lang_repeat_228() LCDML_DISP_lang_repeat_227() LCDML_DISP_lang(228),
#	define LCDML_DISP_lang_repeat_227() LCDML_DISP_lang_repeat_226() LCDML_DISP_lang(227),
#	define LCDML_DISP_lang_repeat_226() LCDML_DISP_lang_repeat_225() LCDML_DISP_lang(226),
#	define LCDML_DISP_lang_repeat_225() LCDML_DISP_lang_repeat_224() LCDML_DISP_lang(225),
#	define LCDML_DISP_lang_repeat_224() LCDML_DISP_lang_repeat_223() LCDML_DISP_lang(224),
#	define LCDML_DISP_lang_repeat_223() LCDML_DISP_lang_repeat_222() LCDML_DISP_lang(223),
#	define LCDML_DISP_lang_repeat_222() LCDML_DISP_lang_repeat_221() LCDML_DISP_lang(222),
#	define LCDML_DISP_lang_repeat_221() LCDML_DISP_lang_repeat_220() LCDML_DISP_lang(221),
#	define LCDML_DISP_lang_repeat_220() LCDML_DISP_lang_repeat_219() LCDML_DISP_lang(220),
#	define LCDML_DISP_lang_repeat_219() LCDML_DISP_lang_repeat_218() LCDML_DISP_lang(219),
#	define LCDML_DISP_lang_repeat_218() LCDML_DISP_lang_repeat_217() LCDML_DISP_lang(218),
#	define LCDML_DISP_lang_repeat_217() LCDML_DISP_lang_repeat_216() LCDML_DISP_lang(217),
#	define LCDML_DISP_lang_repeat_216() LCDML_DISP_lang_repeat_215() LCDML_DISP_lang(216),
#	define LCDML_DISP_lang_repeat_215() LCDML_DISP_lang_repeat_214() LCDML_DISP_lang(215),
#	define LCDML_DISP_lang_repeat_214() LCDML_DISP_lang_repeat_213() LCDML_DISP_lang(214),
#	define LCDML_DISP_lang_repeat_213() LCDML_DISP_lang_repeat_212() LCDML_DISP_lang(213),
#	define LCDML_DISP_lang_repeat_212() LCDML_DISP_lang_repeat_211() LCDML_DISP_lang(212),
#	define LCDML_DISP_lang_repeat_211() LCDML_DISP_lang_repeat_210() LCDML_DISP_lang(211),
#	define LCDML_DISP_lang_repeat_210() LCDML_DISP_lang_repeat_209() LCDML_DISP_lang(210),
#	define LCDML_DISP_lang_repeat_209() LCDML_DISP_lang_repeat_208() LCDML_DISP_lang(209),
#	define LCDML_DISP_lang_repeat_208() LCDML_DISP_lang_repeat_207() LCDML_DISP_lang(208),
#	define LCDML_DISP_lang_repeat_207() LCDML_DISP_lang_repeat_206() LCDML_DISP_lang(207),
#	define LCDML_DISP_lang_repeat_206() LCDML_DISP_lang_repeat_205() LCDML_DISP_lang(206),
#	define LCDML_DISP_lang_repeat_205() LCDML_DISP_lang_repeat_204() LCDML_DISP_lang(205),
#	define LCDML_DISP_lang_repeat_204() LCDML_DISP_lang_repeat_203() LCDML_DISP_lang(204),
#	define LCDML_DISP_lang_repeat_203() LCDML_DISP_lang_repeat_202() LCDML_DISP_lang(203),
#	define LCDML_DISP_lang_repeat_202() LCDML_DISP_lang_repeat_201() LCDML_DISP_lang(202),
#	define LCDML_DISP_lang_repeat_201() LCDML_DISP_lang_repeat_200() LCDML_DISP_lang(201),
#	define LCDML_DISP_lang_repeat_200() LCDML_DISP_lang_repeat_199() LCDML_DISP_lang(200),
#	define LCDML_DISP_lang_repeat_199() LCDML_DISP_lang_repeat_198() LCDML_DISP_lang(199),
#	define LCDML_DISP_lang_repeat_198() LCDML_DISP_lang_repeat_197() LCDML_DISP_lang(198),
#	define LCDML_DISP_lang_repeat_197() LCDML_DISP_lang_repeat_196() LCDML_DISP_lang(197),
#	define LCDML_DISP_lang_repeat_196() LCDML_DISP_lang_repeat_195() LCDML_DISP_lang(196),
#	define LCDML_DISP_lang_repeat_195() LCDML_DISP_lang_repeat_194() LCDML_DISP_lang(195),
#	define LCDML_DISP_lang_repeat_194() LCDML_DISP_lang_repeat_193() LCDML_DISP_lang(194),
#	define LCDML_DISP_lang_repeat_193() LCDML_DISP_lang_repeat_192() LCDML_DISP_lang(193),
#	define LCDML_DISP_lang_repeat_192() LCDML_DISP_lang_repeat_191() LCDML_DISP_lang(192),
#	define LCDML_DISP_lang_repeat_191() LCDML_DISP_lang_repeat_190() LCDML_DISP_lang(191),
#	define LCDML_DISP_lang_repeat_190() LCDML_DISP_lang_repeat_189() LCDML_DISP_lang(190),
#	define LCDML_DISP_lang_repeat_189() LCDML_DISP_lang_repeat_188() LCDML_DISP_lang(189),
#	define LCDML_DISP_lang_repeat_188() LCDML_DISP_lang_repeat_187() LCDML_DISP_lang(188),
#	define LCDML_DISP_lang_repeat_187() LCDML_DISP_lang_repeat_186() LCDML_DISP_lang(187),
#	define LCDML_DISP_lang_repeat_186() LCDML_DISP_lang_repeat_185() LCDML_DISP_lang(186),
#	define LCDML_DISP_lang_repeat_185() LCDML_DISP_lang_repeat_184() LCDML_DISP_lang(185),
#	define LCDML_DISP_lang_repeat_184() LCDML_DISP_lang_repeat_183() LCDML_DISP_lang(184),
#	define LCDML_DISP_lang_repeat_183() LCDML_DISP_lang_repeat_182() LCDML_DISP_lang(183),
#	define LCDML_DISP_lang_repeat_182() LCDML_DISP_lang_repeat_181() LCDML_DISP_lang(182),
#	define LCDML_DISP_lang_repeat_181() LCDML_DISP_lang_repeat_180() LCDML_DISP_lang(181),
#	define LCDML_DISP_lang_repeat_180() LCDML_DISP_lang_repeat_179() LCDML_DISP_lang(180),
#	define LCDML_DISP_lang_repeat_179() LCDML_DISP_lang_repeat_178() LCDML_DISP_lang(179),
#	define LCDML_DISP_lang_repeat_178() LCDML_DISP_lang_repeat_177() LCDML_DISP_lang(178),
#	define LCDML_DISP_lang_repeat_177() LCDML_DISP_lang_repeat_176() LCDML_DISP_lang(177),
#	define LCDML_DISP_lang_repeat_176() LCDML_DISP_lang_repeat_175() LCDML_DISP_lang(176),
#	define LCDML_DISP_lang_repeat_175() LCDML_DISP_lang_repeat_174() LCDML_DISP_lang(175),
#	define LCDML_DISP_lang_repeat_174() LCDML_DISP_lang_repeat_173() LCDML_DISP_lang(174),
#	define LCDML_DISP_lang_repeat_173() LCDML_DISP_lang_repeat_172() LCDML_DISP_lang(173),
#	define LCDML_DISP_lang_repeat_172() LCDML_DISP_lang_repeat_171() LCDML_DISP_lang(172),
#	define LCDML_DISP_lang_repeat_171() LCDML_DISP_lang_repeat_170() LCDML_DISP_lang(171),
#	define LCDML_DISP_lang_repeat_170() LCDML_DISP_lang_repeat_169() LCDML_DISP_lang(170),
#	define LCDML_DISP_lang_repeat_169() LCDML_DISP_lang_repeat_168() LCDML_DISP_lang(169),
#	define LCDML_DISP_lang_repeat_168() LCDML_DISP_lang_repeat_167() LCDML_DISP_lang(168),
#	define LCDML_DISP_lang_repeat_167() LCDML_DISP_lang_repeat_166() LCDML_DISP_lang(167),
#	define LCDML_DISP_lang_repeat_166() LCDML_DISP_lang_repeat_165() LCDML_DISP_lang(166),
#	define LCDML_DISP_lang_repeat_165() LCDML_DISP_lang_repeat_164() LCDML_DISP_lang(165),
#	define LCDML_DISP_lang_repeat_164() LCDML_DISP_lang_repeat_163() LCDML_DISP_lang(164),
#	define LCDML_DISP_lang_repeat_163() LCDML_DISP_lang_repeat_162() LCDML_DISP_lang(163),
#	define LCDML_DISP_lang_repeat_162() LCDML_DISP_lang_repeat_161() LCDML_DISP_lang(162),
#	define LCDML_DISP_lang_repeat_161() LCDML_DISP_lang_repeat_160() LCDML_DISP_lang(161),
#	define LCDML_DISP_lang_repeat_160() LCDML_DISP_lang_repeat_159() LCDML_DISP_lang(160),
#	define LCDML_DISP_lang_repeat_159() LCDML_DISP_lang_repeat_158() LCDML_DISP_lang(159),
#	define LCDML_DISP_lang_repeat_158() LCDML_DISP_lang_repeat_157() LCDML_DISP_lang(158),
#	define LCDML_DISP_lang_repeat_157() LCDML_DISP_lang_repeat_156() LCDML_DISP_lang(157),
#	define LCDML_DISP_lang_repeat_156() LCDML_DISP_lang_repeat_155() LCDML_DISP_lang(156),
#	define LCDML_DISP_lang_repeat_155() LCDML_DISP_lang_repeat_154() LCDML_DISP_lang(155),
#	define LCDML_DISP_lang_repeat_154() LCDML_DISP_lang_repeat_153() LCDML_DISP_lang(154),
#	define LCDML_DISP_lang_repeat_153() LCDML_DISP_lang_repeat_152() LCDML_DISP_lang(153),
#	define LCDML_DISP_lang_repeat_152() LCDML_DISP_lang_repeat_151() LCDML_DISP_lang(152),
#	define LCDML_DISP_lang_repeat_151() LCDML_DISP_lang_repeat_150() LCDML_DISP_lang(151),
#	define LCDML_DISP_lang_repeat_150() LCDML_DISP_lang_repeat_149() LCDML_DISP_lang(150),
#	define LCDML_DISP_lang_repeat_149() LCDML_DISP_lang_repeat_148() LCDML_DISP_lang(149),
#	define LCDML_DISP_lang_repeat_148() LCDML_DISP_lang_repeat_147() LCDML_DISP_lang(148),
#	define LCDML_DISP_lang_repeat_147() LCDML_DISP_lang_repeat_146() LCDML_DISP_lang(147),
#	define LCDML_DISP_lang_repeat_146() LCDML_DISP_lang_repeat_145() LCDML_DISP_lang(146),
#	define LCDML_DISP_lang_repeat_145() LCDML_DISP_lang_repeat_144() LCDML_DISP_lang(145),
#	define LCDML_DISP_lang_repeat_144() LCDML_DISP_lang_repeat_143() LCDML_DISP_lang(144),
#	define LCDML_DISP_lang_repeat_143() LCDML_DISP_lang_repeat_142() LCDML_DISP_lang(143),
#	define LCDML_DISP_lang_repeat_142() LCDML_DISP_lang_repeat_141() LCDML_DISP_lang(142),
#	define LCDML_DISP_lang_repeat_141() LCDML_DISP_lang_repeat_140() LCDML_DISP_lang(141),
#	define LCDML_DISP_lang_repeat_140() LCDML_DISP_lang_repeat_139() LCDML_DISP_lang(140),
#	define LCDML_DISP_lang_repeat_139() LCDML_DISP_lang_repeat_138() LCDML_DISP_lang(139),
#	define LCDML_DISP_lang_repeat_138() LCDML_DISP_lang_repeat_137() LCDML_DISP_lang(138),
#	define LCDML_DISP_lang_repeat_137() LCDML_DISP_lang_repeat_136() LCDML_DISP_lang(137),
#	define LCDML_DISP_lang_repeat_136() LCDML_DISP_lang_repeat_135() LCDML_DISP_lang(136),
#	define LCDML_DISP_lang_repeat_135() LCDML_DISP_lang_repeat_134() LCDML_DISP_lang(135),
#	define LCDML_DISP_lang_repeat_134() LCDML_DISP_lang_repeat_133() LCDML_DISP_lang(134),
#	define LCDML_DISP_lang_repeat_133() LCDML_DISP_lang_repeat_132() LCDML_DISP_lang(133),
#	define LCDML_DISP_lang_repeat_132() LCDML_DISP_lang_repeat_131() LCDML_DISP_lang(132),
#	define LCDML_DISP_lang_repeat_131() LCDML_DISP_lang_repeat_130() LCDML_DISP_lang(131),
#	define LCDML_DISP_lang_repeat_130() LCDML_DISP_lang_repeat_129() LCDML_DISP_lang(130),
#	define LCDML_DISP_lang_repeat_129() LCDML_DISP_lang_repeat_128() LCDML_DISP_lang(129),
#	define LCDML_DISP_lang_repeat_128() LCDML_DISP_lang_repeat_127() LCDML_DISP_lang(128),
#	define LCDML_DISP_lang_repeat_127() LCDML_DISP_lang_repeat_126() LCDML_DISP_lang(127),
#	define LCDML_DISP_lang_repeat_126() LCDML_DISP_lang_repeat_125() LCDML_DISP_lang(126),
#	define LCDML_DISP_lang_repeat_125() LCDML_DISP_lang_repeat_124() LCDML_DISP_lang(125),
#	define LCDML_DISP_lang_repeat_124() LCDML_DISP_lang_repeat_123() LCDML_DISP_lang(124),
#	define LCDML_DISP_lang_repeat_123() LCDML_DISP_lang_repeat_122() LCDML_DISP_lang(123),
#	define LCDML_DISP_lang_repeat_122() LCDML_DISP_lang_repeat_121() LCDML_DISP_lang(122),
#	define LCDML_DISP_lang_repeat_121() LCDML_DISP_lang_repeat_120() LCDML_DISP_lang(121),
#	define LCDML_DISP_lang_repeat_120() LCDML_DISP_lang_repeat_119() LCDML_DISP_lang(120),
#	define LCDML_DISP_lang_repeat_119() LCDML_DISP_lang_repeat_118() LCDML_DISP_lang(119),
#	define LCDML_DISP_lang_repeat_118() LCDML_DISP_lang_repeat_117() LCDML_DISP_lang(118),
#	define LCDML_DISP_lang_repeat_117() LCDML_DISP_lang_repeat_116() LCDML_DISP_lang(117),
#	define LCDML_DISP_lang_repeat_116() LCDML_DISP_lang_repeat_115() LCDML_DISP_lang(116),
#	define LCDML_DISP_lang_repeat_115() LCDML_DISP_lang_repeat_114() LCDML_DISP_lang(115),
#	define LCDML_DISP_lang_repeat_114() LCDML_DISP_lang_repeat_113() LCDML_DISP_lang(114),
#	define LCDML_DISP_lang_repeat_113() LCDML_DISP_lang_repeat_112() LCDML_DISP_lang(113),
#	define LCDML_DISP_lang_repeat_112() LCDML_DISP_lang_repeat_111() LCDML_DISP_lang(112),
#	define LCDML_DISP_lang_repeat_111() LCDML_DISP_lang_repeat_110() LCDML_DISP_lang(111),
#	define LCDML_DISP_lang_repeat_110() LCDML_DISP_lang_repeat_109() LCDML_DISP_lang(110),
#	define LCDML_DISP_lang_repeat_109() LCDML_DISP_lang_repeat_108() LCDML_DISP_lang(109),
#	define LCDML_DISP_lang_repeat_108() LCDML_DISP_lang_repeat_107() LCDML_DISP_lang(108),
#	define LCDML_DISP_lang_repeat_107() LCDML_DISP_lang_repeat_106() LCDML_DISP_lang(107),
#	define LCDML_DISP_lang_repeat_106() LCDML_DISP_lang_repeat_105() LCDML_DISP_lang(106),
#	define LCDML_DISP_lang_repeat_105() LCDML_DISP_lang_repeat_104() LCDML_DISP_lang(105),
#	define LCDML_DISP_lang_repeat_104() LCDML_DISP_lang_repeat_103() LCDML_DISP_lang(104),
#	define LCDML_DISP_lang_repeat_103() LCDML_DISP_lang_repeat_102() LCDML_DISP_lang(103),
#	define LCDML_DISP_lang_repeat_102() LCDML_DISP_lang_repeat_101() LCDML_DISP_lang(102),
#	define LCDML_DISP_lang_repeat_101() LCDML_DISP_lang_repeat_100() LCDML_DISP_lang(101),
#	define LCDML_DISP_lang_repeat_100() LCDML_DISP_lang_repeat_99()  LCDML_DISP_lang(100),
#	define LCDML_DISP_lang_repeat_99()  LCDML_DISP_lang_repeat_98()  LCDML_DISP_lang(99),
#	define LCDML_DISP_lang_repeat_98()  LCDML_DISP_lang_repeat_97()  LCDML_DISP_lang(98),
#	define LCDML_DISP_lang_repeat_97()  LCDML_DISP_lang_repeat_96()  LCDML_DISP_lang(97),
#	define LCDML_DISP_lang_repeat_96()  LCDML_DISP_lang_repeat_95()  LCDML_DISP_lang(96),
#	define LCDML_DISP_lang_repeat_95()  LCDML_DISP_lang_repeat_94()  LCDML_DISP_lang(95),
#	define LCDML_DISP_lang_repeat_94()  LCDML_DISP_lang_repeat_93()  LCDML_DISP_lang(94),
#	define LCDML_DISP_lang_repeat_93()  LCDML_DISP_lang_repeat_92()  LCDML_DISP_lang(93),
#	define LCDML_DISP_lang_repeat_92()  LCDML_DISP_lang_repeat_91()  LCDML_DISP_lang(92),
#	define LCDML_DISP_lang_repeat_91()  LCDML_DISP_lang_repeat_90()  LCDML_DISP_lang(91),
#	define LCDML_DISP_lang_repeat_90()  LCDML_DISP_lang_repeat_89()  LCDML_DISP_lang(90),
#	define LCDML_DISP_lang_repeat_89()  LCDML_DISP_lang_repeat_88()  LCDML_DISP_lang(89),
#	define LCDML_DISP_lang_repeat_88()  LCDML_DISP_lang_repeat_87()  LCDML_DISP_lang(88),
#	define LCDML_DISP_lang_repeat_87()  LCDML_DISP_lang_repeat_86()  LCDML_DISP_lang(87),
#	define LCDML_DISP_lang_repeat_86()  LCDML_DISP_lang_repeat_85()  LCDML_DISP_lang(86),
#	define LCDML_DISP_lang_repeat_85()  LCDML_DISP_lang_repeat_84()  LCDML_DISP_lang(85),
#	define LCDML_DISP_lang_repeat_84()  LCDML_DISP_lang_repeat_83()  LCDML_DISP_lang(84),
#	define LCDML_DISP_lang_repeat_83()  LCDML_DISP_lang_repeat_82()  LCDML_DISP_lang(83),
#	define LCDML_DISP_lang_repeat_82()  LCDML_DISP_lang_repeat_81()  LCDML_DISP_lang(82),
#	define LCDML_DISP_lang_repeat_81()  LCDML_DISP_lang_repeat_80()  LCDML_DISP_lang(81),
#	define LCDML_DISP_lang_repeat_80()  LCDML_DISP_lang_repeat_79()  LCDML_DISP_lang(80),
#	define LCDML_DISP_lang_repeat_79()  LCDML_DISP_lang_repeat_78()  LCDML_DISP_lang(79),
#	define LCDML_DISP_lang_repeat_78()  LCDML_DISP_lang_repeat_77()  LCDML_DISP_lang(78),
#	define LCDML_DISP_lang_repeat_77()  LCDML_DISP_lang_repeat_76()  LCDML_DISP_lang(77),
#	define LCDML_DISP_lang_repeat_76()  LCDML_DISP_lang_repeat_75()  LCDML_DISP_lang(76),
#	define LCDML_DISP_lang_repeat_75()  LCDML_DISP_lang_repeat_74()  LCDML_DISP_lang(75),
#	define LCDML_DISP_lang_repeat_74()  LCDML_DISP_lang_repeat_73()  LCDML_DISP_lang(74),
#	define LCDML_DISP_lang_repeat_73()  LCDML_DISP_lang_repeat_72()  LCDML_DISP_lang(73),
#	define LCDML_DISP_lang_repeat_72()  LCDML_DISP_lang_repeat_71()  LCDML_DISP_lang(72),
#	define LCDML_DISP_lang_repeat_71()  LCDML_DISP_lang_repeat_70()  LCDML_DISP_lang(71),
#	define LCDML_DISP_lang_repeat_70()  LCDML_DISP_lang_repeat_69()  LCDML_DISP_lang(70),
#	define LCDML_DISP_lang_repeat_69()  LCDML_DISP_lang_repeat_68()  LCDML_DISP_lang(69),
#	define LCDML_DISP_lang_repeat_68()  LCDML_DISP_lang_repeat_67()  LCDML_DISP_lang(68),
#	define LCDML_DISP_lang_repeat_67()  LCDML_DISP_lang_repeat_66()  LCDML_DISP_lang(67),
#	define LCDML_DISP_lang_repeat_66()  LCDML_DISP_lang_repeat_65()  LCDML_DISP_lang(66),
#	define LCDML_DISP_lang_repeat_65()  LCDML_DISP_lang_repeat_64()  LCDML_DISP_lang(65),
#	define LCDML_DISP_lang_repeat_64()  LCDML_DISP_lang_repeat_63()  LCDML_DISP_lang(64),
#	define LCDML_DISP_lang_repeat_63()  LCDML_DISP_lang_repeat_62()  LCDML_DISP_lang(63),
#	define LCDML_DISP_lang_repeat_62()  LCDML_DISP_lang_repeat_61()  LCDML_DISP_lang(62),
#	define LCDML_DISP_lang_repeat_61()  LCDML_DISP_lang_repeat_60()  LCDML_DISP_lang(61),
#	define LCDML_DISP_lang_repeat_60()  LCDML_DISP_lang_repeat_59()  LCDML_DISP_lang(60),
#	define LCDML_DISP_lang_repeat_59()  LCDML_DISP_lang_repeat_58()  LCDML_DISP_lang(59),
#	define LCDML_DISP_lang_repeat_58()  LCDML_DISP_lang_repeat_57()  LCDML_DISP_lang(58),
#	define LCDML_DISP_lang_repeat_57()  LCDML_DISP_lang_repeat_56()  LCDML_DISP_lang(57),
#	define LCDML_DISP_lang_repeat_56()  LCDML_DISP_lang_repeat_55()  LCDML_DISP_lang(56),
#	define LCDML_DISP_lang_repeat_55()  LCDML_DISP_lang_repeat_54()  LCDML_DISP_lang(55),
#	define LCDML_DISP_lang_repeat_54()  LCDML_DISP_lang_repeat_53()  LCDML_DISP_lang(54),
#	define LCDML_DISP_lang_repeat_53()  LCDML_DISP_lang_repeat_52()  LCDML_DISP_lang(53),
#	define LCDML_DISP_lang_repeat_52()  LCDML_DISP_lang_repeat_51()  LCDML_DISP_lang(52),
#	define LCDML_DISP_lang_repeat_51()  LCDML_DISP_lang_repeat_50()  LCDML_DISP_lang(51),
#	define LCDML_DISP_lang_repeat_50()  LCDML_DISP_lang_repeat_49()  LCDML_DISP_lang(50),
#	define LCDML_DISP_lang_repeat_49()  LCDML_DISP_lang_repeat_48()  LCDML_DISP_lang(49),
#	define LCDML_DISP_lang_repeat_48()  LCDML_DISP_lang_repeat_47()  LCDML_DISP_lang(48),
#	define LCDML_DISP_lang_repeat_47()  LCDML_DISP_lang_repeat_46()  LCDML_DISP_lang(47),
#	define LCDML_DISP_lang_repeat_46()  LCDML_DISP_lang_repeat_45()  LCDML_DISP_lang(46),
#	define LCDML_DISP_lang_repeat_45()  LCDML_DISP_lang_repeat_44()  LCDML_DISP_lang(45),
#	define LCDML_DISP_lang_repeat_44()  LCDML_DISP_lang_repeat_43()  LCDML_DISP_lang(44),
#	define LCDML_DISP_lang_repeat_43()  LCDML_DISP_lang_repeat_42()  LCDML_DISP_lang(43),
#	define LCDML_DISP_lang_repeat_42()  LCDML_DISP_lang_repeat_41()  LCDML_DISP_lang(42),
#	define LCDML_DISP_lang_repeat_41()  LCDML_DISP_lang_repeat_40()  LCDML_DISP_lang(41),
#	define LCDML_DISP_lang_repeat_40()  LCDML_DISP_lang_repeat_39()  LCDML_DISP_lang(40),
#	define LCDML_DISP_lang_repeat_39()  LCDML_DISP_lang_repeat_38()  LCDML_DISP_lang(39),
#	define LCDML_DISP_lang_repeat_38()  LCDML_DISP_lang_repeat_37()  LCDML_DISP_lang(38),
#	define LCDML_DISP_lang_repeat_37()  LCDML_DISP_lang_repeat_36()  LCDML_DISP_lang(37),
#	define LCDML_DISP_lang_repeat_36()  LCDML_DISP_lang_repeat_35()  LCDML_DISP_lang(36),
#	define LCDML_DISP_lang_repeat_35()  LCDML_DISP_lang_repeat_34()  LCDML_DISP_lang(35),
#	define LCDML_DISP_lang_repeat_34()  LCDML_DISP_lang_repeat_33()  LCDML_DISP_lang(34),
#	define LCDML_DISP_lang_repeat_33()  LCDML_DISP_lang_repeat_32()  LCDML_DISP_lang(33),
#	define LCDML_DISP_lang_repeat_32()  LCDML_DISP_lang_repeat_31()  LCDML_DISP_lang(32),
#	define LCDML_DISP_lang_repeat_31()  LCDML_DISP_lang_repeat_30()  LCDML_DISP_lang(31),
#	define LCDML_DISP_lang_repeat_30()  LCDML_DISP_lang_repeat_29()  LCDML_DISP_lang(30),
#	define LCDML_DISP_lang_repeat_29()  LCDML_DISP_lang_repeat_28()  LCDML_DISP_lang(29),
#	define LCDML_DISP_lang_repeat_28()  LCDML_DISP_lang_repeat_27()  LCDML_DISP_lang(28),
#	define LCDML_DISP_lang_repeat_27()  LCDML_DISP_lang_repeat_26()  LCDML_DISP_lang(27),
#	define LCDML_DISP_lang_repeat_26()  LCDML_DISP_lang_repeat_25()  LCDML_DISP_lang(26),
#	define LCDML_DISP_lang_repeat_25()  LCDML_DISP_lang_repeat_24()  LCDML_DISP_lang(25),
#	define LCDML_DISP_lang_repeat_24()  LCDML_DISP_lang_repeat_23()  LCDML_DISP_lang(24),
#	define LCDML_DISP_lang_repeat_23()  LCDML_DISP_lang_repeat_22()  LCDML_DISP_lang(23),
#	define LCDML_DISP_lang_repeat_22()  LCDML_DISP_lang_repeat_21()  LCDML_DISP_lang(22),
#	define LCDML_DISP_lang_repeat_21()  LCDML_DISP_lang_repeat_20()  LCDML_DISP_lang(21),
#	define LCDML_DISP_lang_repeat_20()  LCDML_DISP_lang_repeat_19()  LCDML_DISP_lang(20),
#	define LCDML_DISP_lang_repeat_19()  LCDML_DISP_lang_repeat_18()  LCDML_DISP_lang(19),
#	define LCDML_DISP_lang_repeat_18()  LCDML_DISP_lang_repeat_17()  LCDML_DISP_lang(18),
#	define LCDML_DISP_lang_repeat_17()  LCDML_DISP_lang_repeat_16()  LCDML_DISP_lang(17),
#	define LCDML_DISP_lang_repeat_16()  LCDML_DISP_lang_repeat_15()  LCDML_DISP_lang(16),
#	define LCDML_DISP_lang_repeat_15()  LCDML_DISP_lang_repeat_14()  LCDML_DISP_lang(15),
#	define LCDML_DISP_lang_repeat_14()  LCDML_DISP_lang_repeat_13()  LCDML_DISP_lang(14),
#	define LCDML_DISP_lang_repeat_13()  LCDML_DISP_lang_repeat_12()  LCDML_DISP_lang(13),
#	define LCDML_DISP_lang_repeat_12()  LCDML_DISP_lang_repeat_11()  LCDML_DISP_lang(12),
#	define LCDML_DISP_lang_repeat_11()  LCDML_DISP_lang_repeat_10()  LCDML_DISP_lang(11),
#	define LCDML_DISP_lang_repeat_10()  LCDML_DISP_lang_repeat_9()   LCDML_DISP_lang(10),
#	define LCDML_DISP_lang_repeat_9()   LCDML_DISP_lang_repeat_8()   LCDML_DISP_lang(9),
#	define LCDML_DISP_lang_repeat_8()   LCDML_DISP_lang_repeat_7()   LCDML_DISP_lang(8),
#	define LCDML_DISP_lang_repeat_7()   LCDML_DISP_lang_repeat_6()   LCDML_DISP_lang(7),
#	define LCDML_DISP_lang_repeat_6()   LCDML_DISP_lang_repeat_5()   LCDML_DISP_lang(6),
#	define LCDML_DISP_lang_repeat_5()   LCDML_DISP_lang_repeat_4()   LCDML_DISP_lang(5),
#	define LCDML_DISP_lang_repeat_4()   LCDML_DISP_lang_repeat_3()   LCDML_DISP_lang(4),
#	define LCDML_DISP_lang_repeat_3()   LCDML_DISP_lang_repeat_2()   LCDML_DISP_lang(3),
#	define LCDML_DISP_lang_repeat_2()   LCDML_DISP_lang_repeat_1()   LCDML_DISP_lang(2),
#	define LCDML_DISP_lang_repeat_1()   LCDML_DISP_lang_repeat_0()   LCDML_DISP_lang(1), 
#	define LCDML_DISP_lang_repeat_0()   LCDML_DISP_lang(0), 
#	define LCDML_DISP_lang_repeat(N)	 LCDML_DISP_lang_repeat_##N ()


/* ************************************************ */
/* LCDMenuLib_function_repeat						*/
/* ************************************************ */
#	define LCDML_DISP_func_repeat_255() LCDML_DISP_func_repeat_254() LCDML_DISP_255_function();
#	define LCDML_DISP_func_repeat_254() LCDML_DISP_func_repeat_253() LCDML_DISP_254_function();
#	define LCDML_DISP_func_repeat_253() LCDML_DISP_func_repeat_252() LCDML_DISP_253_function();
#	define LCDML_DISP_func_repeat_252() LCDML_DISP_func_repeat_251() LCDML_DISP_252_function();
#	define LCDML_DISP_func_repeat_251() LCDML_DISP_func_repeat_250() LCDML_DISP_251_function();
#	define LCDML_DISP_func_repeat_250() LCDML_DISP_func_repeat_249() LCDML_DISP_250_function();
#	define LCDML_DISP_func_repeat_249() LCDML_DISP_func_repeat_248() LCDML_DISP_249_function();
#	define LCDML_DISP_func_repeat_248() LCDML_DISP_func_repeat_247() LCDML_DISP_248_function();
#	define LCDML_DISP_func_repeat_247() LCDML_DISP_func_repeat_246() LCDML_DISP_247_function();
#	define LCDML_DISP_func_repeat_246() LCDML_DISP_func_repeat_245() LCDML_DISP_246_function();
#	define LCDML_DISP_func_repeat_245() LCDML_DISP_func_repeat_244() LCDML_DISP_245_function();
#	define LCDML_DISP_func_repeat_244() LCDML_DISP_func_repeat_243() LCDML_DISP_244_function();
#	define LCDML_DISP_func_repeat_243() LCDML_DISP_func_repeat_242() LCDML_DISP_243_function();
#	define LCDML_DISP_func_repeat_242() LCDML_DISP_func_repeat_241() LCDML_DISP_242_function();
#	define LCDML_DISP_func_repeat_241() LCDML_DISP_func_repeat_240() LCDML_DISP_241_function();
#	define LCDML_DISP_func_repeat_240() LCDML_DISP_func_repeat_239() LCDML_DISP_240_function();
#	define LCDML_DISP_func_repeat_239() LCDML_DISP_func_repeat_238() LCDML_DISP_239_function();
#	define LCDML_DISP_func_repeat_238() LCDML_DISP_func_repeat_237() LCDML_DISP_238_function();
#	define LCDML_DISP_func_repeat_237() LCDML_DISP_func_repeat_236() LCDML_DISP_237_function();
#	define LCDML_DISP_func_repeat_236() LCDML_DISP_func_repeat_235() LCDML_DISP_236_function();
#	define LCDML_DISP_func_repeat_235() LCDML_DISP_func_repeat_234() LCDML_DISP_235_function();
#	define LCDML_DISP_func_repeat_234() LCDML_DISP_func_repeat_233() LCDML_DISP_234_function();
#	define LCDML_DISP_func_repeat_233() LCDML_DISP_func_repeat_232() LCDML_DISP_233_function();
#	define LCDML_DISP_func_repeat_232() LCDML_DISP_func_repeat_231() LCDML_DISP_232_function();
#	define LCDML_DISP_func_repeat_231() LCDML_DISP_func_repeat_230() LCDML_DISP_231_function();
#	define LCDML_DISP_func_repeat_230() LCDML_DISP_func_repeat_229() LCDML_DISP_230_function();
#	define LCDML_DISP_func_repeat_229() LCDML_DISP_func_repeat_228() LCDML_DISP_229_function();
#	define LCDML_DISP_func_repeat_228() LCDML_DISP_func_repeat_227() LCDML_DISP_228_function();
#	define LCDML_DISP_func_repeat_227() LCDML_DISP_func_repeat_226() LCDML_DISP_227_function();
#	define LCDML_DISP_func_repeat_226() LCDML_DISP_func_repeat_225() LCDML_DISP_226_function();
#	define LCDML_DISP_func_repeat_225() LCDML_DISP_func_repeat_224() LCDML_DISP_225_function();
#	define LCDML_DISP_func_repeat_224() LCDML_DISP_func_repeat_223() LCDML_DISP_224_function();
#	define LCDML_DISP_func_repeat_223() LCDML_DISP_func_repeat_222() LCDML_DISP_223_function();
#	define LCDML_DISP_func_repeat_222() LCDML_DISP_func_repeat_221() LCDML_DISP_222_function();
#	define LCDML_DISP_func_repeat_221() LCDML_DISP_func_repeat_220() LCDML_DISP_221_function();
#	define LCDML_DISP_func_repeat_220() LCDML_DISP_func_repeat_219() LCDML_DISP_220_function();
#	define LCDML_DISP_func_repeat_219() LCDML_DISP_func_repeat_218() LCDML_DISP_219_function();
#	define LCDML_DISP_func_repeat_218() LCDML_DISP_func_repeat_217() LCDML_DISP_218_function();
#	define LCDML_DISP_func_repeat_217() LCDML_DISP_func_repeat_216() LCDML_DISP_217_function();
#	define LCDML_DISP_func_repeat_216() LCDML_DISP_func_repeat_215() LCDML_DISP_216_function();
#	define LCDML_DISP_func_repeat_215() LCDML_DISP_func_repeat_214() LCDML_DISP_215_function();
#	define LCDML_DISP_func_repeat_214() LCDML_DISP_func_repeat_213() LCDML_DISP_214_function();
#	define LCDML_DISP_func_repeat_213() LCDML_DISP_func_repeat_212() LCDML_DISP_213_function();
#	define LCDML_DISP_func_repeat_212() LCDML_DISP_func_repeat_211() LCDML_DISP_212_function();
#	define LCDML_DISP_func_repeat_211() LCDML_DISP_func_repeat_210() LCDML_DISP_211_function();
#	define LCDML_DISP_func_repeat_210() LCDML_DISP_func_repeat_209() LCDML_DISP_210_function();
#	define LCDML_DISP_func_repeat_209() LCDML_DISP_func_repeat_208() LCDML_DISP_209_function();
#	define LCDML_DISP_func_repeat_208() LCDML_DISP_func_repeat_207() LCDML_DISP_208_function();
#	define LCDML_DISP_func_repeat_207() LCDML_DISP_func_repeat_206() LCDML_DISP_207_function();
#	define LCDML_DISP_func_repeat_206() LCDML_DISP_func_repeat_205() LCDML_DISP_206_function();
#	define LCDML_DISP_func_repeat_205() LCDML_DISP_func_repeat_204() LCDML_DISP_205_function();
#	define LCDML_DISP_func_repeat_204() LCDML_DISP_func_repeat_203() LCDML_DISP_204_function();
#	define LCDML_DISP_func_repeat_203() LCDML_DISP_func_repeat_202() LCDML_DISP_203_function();
#	define LCDML_DISP_func_repeat_202() LCDML_DISP_func_repeat_201() LCDML_DISP_202_function();
#	define LCDML_DISP_func_repeat_201() LCDML_DISP_func_repeat_200() LCDML_DISP_201_function();
#	define LCDML_DISP_func_repeat_200() LCDML_DISP_func_repeat_199() LCDML_DISP_200_function();
#	define LCDML_DISP_func_repeat_199() LCDML_DISP_func_repeat_198() LCDML_DISP_199_function();
#	define LCDML_DISP_func_repeat_198() LCDML_DISP_func_repeat_197() LCDML_DISP_198_function();
#	define LCDML_DISP_func_repeat_197() LCDML_DISP_func_repeat_196() LCDML_DISP_197_function();
#	define LCDML_DISP_func_repeat_196() LCDML_DISP_func_repeat_195() LCDML_DISP_196_function();
#	define LCDML_DISP_func_repeat_195() LCDML_DISP_func_repeat_194() LCDML_DISP_195_function();
#	define LCDML_DISP_func_repeat_194() LCDML_DISP_func_repeat_193() LCDML_DISP_194_function();
#	define LCDML_DISP_func_repeat_193() LCDML_DISP_func_repeat_192() LCDML_DISP_193_function();
#	define LCDML_DISP_func_repeat_192() LCDML_DISP_func_repeat_191() LCDML_DISP_192_function();
#	define LCDML_DISP_func_repeat_191() LCDML_DISP_func_repeat_190() LCDML_DISP_191_function();
#	define LCDML_DISP_func_repeat_190() LCDML_DISP_func_repeat_189() LCDML_DISP_190_function();
#	define LCDML_DISP_func_repeat_189() LCDML_DISP_func_repeat_188() LCDML_DISP_189_function();
#	define LCDML_DISP_func_repeat_188() LCDML_DISP_func_repeat_187() LCDML_DISP_188_function();
#	define LCDML_DISP_func_repeat_187() LCDML_DISP_func_repeat_186() LCDML_DISP_187_function();
#	define LCDML_DISP_func_repeat_186() LCDML_DISP_func_repeat_185() LCDML_DISP_186_function();
#	define LCDML_DISP_func_repeat_185() LCDML_DISP_func_repeat_184() LCDML_DISP_185_function();
#	define LCDML_DISP_func_repeat_184() LCDML_DISP_func_repeat_183() LCDML_DISP_184_function();
#	define LCDML_DISP_func_repeat_183() LCDML_DISP_func_repeat_182() LCDML_DISP_183_function();
#	define LCDML_DISP_func_repeat_182() LCDML_DISP_func_repeat_181() LCDML_DISP_182_function();
#	define LCDML_DISP_func_repeat_181() LCDML_DISP_func_repeat_180() LCDML_DISP_181_function();
#	define LCDML_DISP_func_repeat_180() LCDML_DISP_func_repeat_179() LCDML_DISP_180_function();
#	define LCDML_DISP_func_repeat_179() LCDML_DISP_func_repeat_178() LCDML_DISP_179_function();
#	define LCDML_DISP_func_repeat_178() LCDML_DISP_func_repeat_177() LCDML_DISP_178_function();
#	define LCDML_DISP_func_repeat_177() LCDML_DISP_func_repeat_176() LCDML_DISP_177_function();
#	define LCDML_DISP_func_repeat_176() LCDML_DISP_func_repeat_175() LCDML_DISP_176_function();
#	define LCDML_DISP_func_repeat_175() LCDML_DISP_func_repeat_174() LCDML_DISP_175_function();
#	define LCDML_DISP_func_repeat_174() LCDML_DISP_func_repeat_173() LCDML_DISP_174_function();
#	define LCDML_DISP_func_repeat_173() LCDML_DISP_func_repeat_172() LCDML_DISP_173_function();
#	define LCDML_DISP_func_repeat_172() LCDML_DISP_func_repeat_171() LCDML_DISP_172_function();
#	define LCDML_DISP_func_repeat_171() LCDML_DISP_func_repeat_170() LCDML_DISP_171_function();
#	define LCDML_DISP_func_repeat_170() LCDML_DISP_func_repeat_169() LCDML_DISP_170_function();
#	define LCDML_DISP_func_repeat_169() LCDML_DISP_func_repeat_168() LCDML_DISP_169_function();
#	define LCDML_DISP_func_repeat_168() LCDML_DISP_func_repeat_167() LCDML_DISP_168_function();
#	define LCDML_DISP_func_repeat_167() LCDML_DISP_func_repeat_166() LCDML_DISP_167_function();
#	define LCDML_DISP_func_repeat_166() LCDML_DISP_func_repeat_165() LCDML_DISP_166_function();
#	define LCDML_DISP_func_repeat_165() LCDML_DISP_func_repeat_164() LCDML_DISP_165_function();
#	define LCDML_DISP_func_repeat_164() LCDML_DISP_func_repeat_163() LCDML_DISP_164_function();
#	define LCDML_DISP_func_repeat_163() LCDML_DISP_func_repeat_162() LCDML_DISP_163_function();
#	define LCDML_DISP_func_repeat_162() LCDML_DISP_func_repeat_161() LCDML_DISP_162_function();
#	define LCDML_DISP_func_repeat_161() LCDML_DISP_func_repeat_160() LCDML_DISP_161_function();
#	define LCDML_DISP_func_repeat_160() LCDML_DISP_func_repeat_159() LCDML_DISP_160_function();
#	define LCDML_DISP_func_repeat_159() LCDML_DISP_func_repeat_158() LCDML_DISP_159_function();
#	define LCDML_DISP_func_repeat_158() LCDML_DISP_func_repeat_157() LCDML_DISP_158_function();
#	define LCDML_DISP_func_repeat_157() LCDML_DISP_func_repeat_156() LCDML_DISP_157_function();
#	define LCDML_DISP_func_repeat_156() LCDML_DISP_func_repeat_155() LCDML_DISP_156_function();
#	define LCDML_DISP_func_repeat_155() LCDML_DISP_func_repeat_154() LCDML_DISP_155_function();
#	define LCDML_DISP_func_repeat_154() LCDML_DISP_func_repeat_153() LCDML_DISP_154_function();
#	define LCDML_DISP_func_repeat_153() LCDML_DISP_func_repeat_152() LCDML_DISP_153_function();
#	define LCDML_DISP_func_repeat_152() LCDML_DISP_func_repeat_151() LCDML_DISP_152_function();
#	define LCDML_DISP_func_repeat_151() LCDML_DISP_func_repeat_150() LCDML_DISP_151_function();
#	define LCDML_DISP_func_repeat_150() LCDML_DISP_func_repeat_149() LCDML_DISP_150_function();
#	define LCDML_DISP_func_repeat_149() LCDML_DISP_func_repeat_148() LCDML_DISP_149_function();
#	define LCDML_DISP_func_repeat_148() LCDML_DISP_func_repeat_147() LCDML_DISP_148_function();
#	define LCDML_DISP_func_repeat_147() LCDML_DISP_func_repeat_146() LCDML_DISP_147_function();
#	define LCDML_DISP_func_repeat_146() LCDML_DISP_func_repeat_145() LCDML_DISP_146_function();
#	define LCDML_DISP_func_repeat_145() LCDML_DISP_func_repeat_144() LCDML_DISP_145_function();
#	define LCDML_DISP_func_repeat_144() LCDML_DISP_func_repeat_143() LCDML_DISP_144_function();
#	define LCDML_DISP_func_repeat_143() LCDML_DISP_func_repeat_142() LCDML_DISP_143_function();
#	define LCDML_DISP_func_repeat_142() LCDML_DISP_func_repeat_141() LCDML_DISP_142_function();
#	define LCDML_DISP_func_repeat_141() LCDML_DISP_func_repeat_140() LCDML_DISP_141_function();
#	define LCDML_DISP_func_repeat_140() LCDML_DISP_func_repeat_139() LCDML_DISP_140_function();
#	define LCDML_DISP_func_repeat_139() LCDML_DISP_func_repeat_138() LCDML_DISP_139_function();
#	define LCDML_DISP_func_repeat_138() LCDML_DISP_func_repeat_137() LCDML_DISP_138_function();
#	define LCDML_DISP_func_repeat_137() LCDML_DISP_func_repeat_136() LCDML_DISP_137_function();
#	define LCDML_DISP_func_repeat_136() LCDML_DISP_func_repeat_135() LCDML_DISP_136_function();
#	define LCDML_DISP_func_repeat_135() LCDML_DISP_func_repeat_134() LCDML_DISP_135_function();
#	define LCDML_DISP_func_repeat_134() LCDML_DISP_func_repeat_133() LCDML_DISP_134_function();
#	define LCDML_DISP_func_repeat_133() LCDML_DISP_func_repeat_132() LCDML_DISP_133_function();
#	define LCDML_DISP_func_repeat_132() LCDML_DISP_func_repeat_131() LCDML_DISP_132_function();
#	define LCDML_DISP_func_repeat_131() LCDML_DISP_func_repeat_130() LCDML_DISP_131_function();
#	define LCDML_DISP_func_repeat_130() LCDML_DISP_func_repeat_129() LCDML_DISP_130_function();
#	define LCDML_DISP_func_repeat_129() LCDML_DISP_func_repeat_128() LCDML_DISP_129_function();
#	define LCDML_DISP_func_repeat_128() LCDML_DISP_func_repeat_127() LCDML_DISP_128_function();
#	define LCDML_DISP_func_repeat_127() LCDML_DISP_func_repeat_126() LCDML_DISP_127_function();
#	define LCDML_DISP_func_repeat_126() LCDML_DISP_func_repeat_125() LCDML_DISP_126_function();
#	define LCDML_DISP_func_repeat_125() LCDML_DISP_func_repeat_124() LCDML_DISP_125_function();
#	define LCDML_DISP_func_repeat_124() LCDML_DISP_func_repeat_123() LCDML_DISP_124_function();
#	define LCDML_DISP_func_repeat_123() LCDML_DISP_func_repeat_122() LCDML_DISP_123_function();
#	define LCDML_DISP_func_repeat_122() LCDML_DISP_func_repeat_121() LCDML_DISP_122_function();
#	define LCDML_DISP_func_repeat_121() LCDML_DISP_func_repeat_120() LCDML_DISP_121_function();
#	define LCDML_DISP_func_repeat_120() LCDML_DISP_func_repeat_119() LCDML_DISP_120_function();
#	define LCDML_DISP_func_repeat_119() LCDML_DISP_func_repeat_118() LCDML_DISP_119_function();
#	define LCDML_DISP_func_repeat_118() LCDML_DISP_func_repeat_117() LCDML_DISP_118_function();
#	define LCDML_DISP_func_repeat_117() LCDML_DISP_func_repeat_116() LCDML_DISP_117_function();
#	define LCDML_DISP_func_repeat_116() LCDML_DISP_func_repeat_115() LCDML_DISP_116_function();
#	define LCDML_DISP_func_repeat_115() LCDML_DISP_func_repeat_114() LCDML_DISP_115_function();
#	define LCDML_DISP_func_repeat_114() LCDML_DISP_func_repeat_113() LCDML_DISP_114_function();
#	define LCDML_DISP_func_repeat_113() LCDML_DISP_func_repeat_112() LCDML_DISP_113_function();
#	define LCDML_DISP_func_repeat_112() LCDML_DISP_func_repeat_111() LCDML_DISP_112_function();
#	define LCDML_DISP_func_repeat_111() LCDML_DISP_func_repeat_110() LCDML_DISP_111_function();
#	define LCDML_DISP_func_repeat_110() LCDML_DISP_func_repeat_109() LCDML_DISP_110_function();
#	define LCDML_DISP_func_repeat_109() LCDML_DISP_func_repeat_108() LCDML_DISP_109_function();
#	define LCDML_DISP_func_repeat_108() LCDML_DISP_func_repeat_107() LCDML_DISP_108_function();
#	define LCDML_DISP_func_repeat_107() LCDML_DISP_func_repeat_106() LCDML_DISP_107_function();
#	define LCDML_DISP_func_repeat_106() LCDML_DISP_func_repeat_105() LCDML_DISP_106_function();
#	define LCDML_DISP_func_repeat_105() LCDML_DISP_func_repeat_104() LCDML_DISP_105_function();
#	define LCDML_DISP_func_repeat_104() LCDML_DISP_func_repeat_103() LCDML_DISP_104_function();
#	define LCDML_DISP_func_repeat_103() LCDML_DISP_func_repeat_102() LCDML_DISP_103_function();
#	define LCDML_DISP_func_repeat_102() LCDML_DISP_func_repeat_101() LCDML_DISP_102_function();
#	define LCDML_DISP_func_repeat_101() LCDML_DISP_func_repeat_100() LCDML_DISP_101_function();
#	define LCDML_DISP_func_repeat_100() LCDML_DISP_func_repeat_99()  LCDML_DISP_100_function();
#	define LCDML_DISP_func_repeat_99() LCDML_DISP_func_repeat_98() LCDML_DISP_99_function();
#	define LCDML_DISP_func_repeat_98() LCDML_DISP_func_repeat_97() LCDML_DISP_98_function();
#	define LCDML_DISP_func_repeat_97() LCDML_DISP_func_repeat_96() LCDML_DISP_97_function();
#	define LCDML_DISP_func_repeat_96() LCDML_DISP_func_repeat_95() LCDML_DISP_96_function();
#	define LCDML_DISP_func_repeat_95() LCDML_DISP_func_repeat_94() LCDML_DISP_95_function();
#	define LCDML_DISP_func_repeat_94() LCDML_DISP_func_repeat_93() LCDML_DISP_94_function();
#	define LCDML_DISP_func_repeat_93() LCDML_DISP_func_repeat_92() LCDML_DISP_93_function();
#	define LCDML_DISP_func_repeat_92() LCDML_DISP_func_repeat_91() LCDML_DISP_92_function();
#	define LCDML_DISP_func_repeat_91() LCDML_DISP_func_repeat_90() LCDML_DISP_91_function();
#	define LCDML_DISP_func_repeat_90() LCDML_DISP_func_repeat_89() LCDML_DISP_90_function();
#	define LCDML_DISP_func_repeat_89() LCDML_DISP_func_repeat_88() LCDML_DISP_89_function();
#	define LCDML_DISP_func_repeat_88() LCDML_DISP_func_repeat_87() LCDML_DISP_88_function();
#	define LCDML_DISP_func_repeat_87() LCDML_DISP_func_repeat_86() LCDML_DISP_87_function();
#	define LCDML_DISP_func_repeat_86() LCDML_DISP_func_repeat_85() LCDML_DISP_86_function();
#	define LCDML_DISP_func_repeat_85() LCDML_DISP_func_repeat_84() LCDML_DISP_85_function();
#	define LCDML_DISP_func_repeat_84() LCDML_DISP_func_repeat_83() LCDML_DISP_84_function();
#	define LCDML_DISP_func_repeat_83() LCDML_DISP_func_repeat_82() LCDML_DISP_83_function();
#	define LCDML_DISP_func_repeat_82() LCDML_DISP_func_repeat_81() LCDML_DISP_82_function();
#	define LCDML_DISP_func_repeat_81() LCDML_DISP_func_repeat_80() LCDML_DISP_81_function();
#	define LCDML_DISP_func_repeat_80() LCDML_DISP_func_repeat_79() LCDML_DISP_80_function();
#	define LCDML_DISP_func_repeat_79() LCDML_DISP_func_repeat_78() LCDML_DISP_79_function();
#	define LCDML_DISP_func_repeat_78() LCDML_DISP_func_repeat_77() LCDML_DISP_78_function();
#	define LCDML_DISP_func_repeat_77() LCDML_DISP_func_repeat_76() LCDML_DISP_77_function();
#	define LCDML_DISP_func_repeat_76() LCDML_DISP_func_repeat_75() LCDML_DISP_76_function();
#	define LCDML_DISP_func_repeat_75() LCDML_DISP_func_repeat_74() LCDML_DISP_75_function();
#	define LCDML_DISP_func_repeat_74() LCDML_DISP_func_repeat_73() LCDML_DISP_74_function();
#	define LCDML_DISP_func_repeat_73() LCDML_DISP_func_repeat_72() LCDML_DISP_73_function();
#	define LCDML_DISP_func_repeat_72() LCDML_DISP_func_repeat_71() LCDML_DISP_72_function();
#	define LCDML_DISP_func_repeat_71() LCDML_DISP_func_repeat_70() LCDML_DISP_71_function();
#	define LCDML_DISP_func_repeat_70() LCDML_DISP_func_repeat_69() LCDML_DISP_70_function();
#	define LCDML_DISP_func_repeat_69() LCDML_DISP_func_repeat_68() LCDML_DISP_69_function();
#	define LCDML_DISP_func_repeat_68() LCDML_DISP_func_repeat_67() LCDML_DISP_68_function();
#	define LCDML_DISP_func_repeat_67() LCDML_DISP_func_repeat_66() LCDML_DISP_67_function();
#	define LCDML_DISP_func_repeat_66() LCDML_DISP_func_repeat_65() LCDML_DISP_66_function();
#	define LCDML_DISP_func_repeat_65() LCDML_DISP_func_repeat_64() LCDML_DISP_65_function();
#	define LCDML_DISP_func_repeat_64() LCDML_DISP_func_repeat_63() LCDML_DISP_64_function();
#	define LCDML_DISP_func_repeat_63() LCDML_DISP_func_repeat_62() LCDML_DISP_63_function();
#	define LCDML_DISP_func_repeat_62() LCDML_DISP_func_repeat_61() LCDML_DISP_62_function();
#	define LCDML_DISP_func_repeat_61() LCDML_DISP_func_repeat_60() LCDML_DISP_61_function();
#	define LCDML_DISP_func_repeat_60() LCDML_DISP_func_repeat_59() LCDML_DISP_60_function();
#	define LCDML_DISP_func_repeat_59() LCDML_DISP_func_repeat_58() LCDML_DISP_59_function();
#	define LCDML_DISP_func_repeat_58() LCDML_DISP_func_repeat_57() LCDML_DISP_58_function();
#	define LCDML_DISP_func_repeat_57() LCDML_DISP_func_repeat_56() LCDML_DISP_57_function();
#	define LCDML_DISP_func_repeat_56() LCDML_DISP_func_repeat_55() LCDML_DISP_56_function();
#	define LCDML_DISP_func_repeat_55() LCDML_DISP_func_repeat_54() LCDML_DISP_55_function();
#	define LCDML_DISP_func_repeat_54() LCDML_DISP_func_repeat_53() LCDML_DISP_54_function();
#	define LCDML_DISP_func_repeat_53() LCDML_DISP_func_repeat_52() LCDML_DISP_53_function();
#	define LCDML_DISP_func_repeat_52() LCDML_DISP_func_repeat_51() LCDML_DISP_52_function();
#	define LCDML_DISP_func_repeat_51() LCDML_DISP_func_repeat_50() LCDML_DISP_51_function();
#	define LCDML_DISP_func_repeat_50() LCDML_DISP_func_repeat_49() LCDML_DISP_50_function();
#	define LCDML_DISP_func_repeat_49() LCDML_DISP_func_repeat_48() LCDML_DISP_49_function();
#	define LCDML_DISP_func_repeat_48() LCDML_DISP_func_repeat_47() LCDML_DISP_48_function();
#	define LCDML_DISP_func_repeat_47() LCDML_DISP_func_repeat_46() LCDML_DISP_47_function();
#	define LCDML_DISP_func_repeat_46() LCDML_DISP_func_repeat_45() LCDML_DISP_46_function();
#	define LCDML_DISP_func_repeat_45() LCDML_DISP_func_repeat_44() LCDML_DISP_45_function();
#	define LCDML_DISP_func_repeat_44() LCDML_DISP_func_repeat_43() LCDML_DISP_44_function();
#	define LCDML_DISP_func_repeat_43() LCDML_DISP_func_repeat_42() LCDML_DISP_43_function();
#	define LCDML_DISP_func_repeat_42() LCDML_DISP_func_repeat_41() LCDML_DISP_42_function();
#	define LCDML_DISP_func_repeat_41() LCDML_DISP_func_repeat_40() LCDML_DISP_41_function();
#	define LCDML_DISP_func_repeat_40() LCDML_DISP_func_repeat_39() LCDML_DISP_40_function();
#	define LCDML_DISP_func_repeat_39() LCDML_DISP_func_repeat_38() LCDML_DISP_39_function();
#	define LCDML_DISP_func_repeat_38() LCDML_DISP_func_repeat_37() LCDML_DISP_38_function();
#	define LCDML_DISP_func_repeat_37() LCDML_DISP_func_repeat_36() LCDML_DISP_37_function();
#	define LCDML_DISP_func_repeat_36() LCDML_DISP_func_repeat_35() LCDML_DISP_36_function();
#	define LCDML_DISP_func_repeat_35() LCDML_DISP_func_repeat_34() LCDML_DISP_35_function();
#	define LCDML_DISP_func_repeat_34() LCDML_DISP_func_repeat_33() LCDML_DISP_34_function();
#	define LCDML_DISP_func_repeat_33() LCDML_DISP_func_repeat_32() LCDML_DISP_33_function();
#	define LCDML_DISP_func_repeat_32() LCDML_DISP_func_repeat_31() LCDML_DISP_32_function();
#	define LCDML_DISP_func_repeat_31() LCDML_DISP_func_repeat_30() LCDML_DISP_31_function();
#	define LCDML_DISP_func_repeat_30() LCDML_DISP_func_repeat_29() LCDML_DISP_30_function();
#	define LCDML_DISP_func_repeat_29() LCDML_DISP_func_repeat_28() LCDML_DISP_29_function();
#	define LCDML_DISP_func_repeat_28() LCDML_DISP_func_repeat_27() LCDML_DISP_28_function();
#	define LCDML_DISP_func_repeat_27() LCDML_DISP_func_repeat_26() LCDML_DISP_27_function();
#	define LCDML_DISP_func_repeat_26() LCDML_DISP_func_repeat_25() LCDML_DISP_26_function();
#	define LCDML_DISP_func_repeat_25() LCDML_DISP_func_repeat_24() LCDML_DISP_25_function();
#	define LCDML_DISP_func_repeat_24() LCDML_DISP_func_repeat_23() LCDML_DISP_24_function();
#	define LCDML_DISP_func_repeat_23() LCDML_DISP_func_repeat_22() LCDML_DISP_23_function();
#	define LCDML_DISP_func_repeat_22() LCDML_DISP_func_repeat_21() LCDML_DISP_22_function();
#	define LCDML_DISP_func_repeat_21() LCDML_DISP_func_repeat_20() LCDML_DISP_21_function();
#	define LCDML_DISP_func_repeat_20() LCDML_DISP_func_repeat_19() LCDML_DISP_20_function();
#	define LCDML_DISP_func_repeat_19() LCDML_DISP_func_repeat_18() LCDML_DISP_19_function();
#	define LCDML_DISP_func_repeat_18() LCDML_DISP_func_repeat_17() LCDML_DISP_18_function();
#	define LCDML_DISP_func_repeat_17() LCDML_DISP_func_repeat_16() LCDML_DISP_17_function();
#	define LCDML_DISP_func_repeat_16() LCDML_DISP_func_repeat_15() LCDML_DISP_16_function();
#	define LCDML_DISP_func_repeat_15() LCDML_DISP_func_repeat_14() LCDML_DISP_15_function();
#	define LCDML_DISP_func_repeat_14() LCDML_DISP_func_repeat_13() LCDML_DISP_14_function();
#	define LCDML_DISP_func_repeat_13() LCDML_DISP_func_repeat_12() LCDML_DISP_13_function();
#	define LCDML_DISP_func_repeat_12() LCDML_DISP_func_repeat_11() LCDML_DISP_12_function();
#	define LCDML_DISP_func_repeat_11() LCDML_DISP_func_repeat_10() LCDML_DISP_11_function();
#	define LCDML_DISP_func_repeat_10() LCDML_DISP_func_repeat_9()  LCDML_DISP_10_function();
#	define LCDML_DISP_func_repeat_9() LCDML_DISP_func_repeat_8()   LCDML_DISP_9_function();
#	define LCDML_DISP_func_repeat_8() LCDML_DISP_func_repeat_7()   LCDML_DISP_8_function();
#	define LCDML_DISP_func_repeat_7() LCDML_DISP_func_repeat_6()   LCDML_DISP_7_function();
#	define LCDML_DISP_func_repeat_6() LCDML_DISP_func_repeat_5()   LCDML_DISP_6_function();
#	define LCDML_DISP_func_repeat_5() LCDML_DISP_func_repeat_4()   LCDML_DISP_5_function();
#	define LCDML_DISP_func_repeat_4() LCDML_DISP_func_repeat_3()   LCDML_DISP_4_function();
#	define LCDML_DISP_func_repeat_3() LCDML_DISP_func_repeat_2()   LCDML_DISP_3_function();
#	define LCDML_DISP_func_repeat_2() LCDML_DISP_func_repeat_1()   LCDML_DISP_2_function();
#	define LCDML_DISP_func_repeat_1() LCDML_DISP_func_repeat_0()   LCDML_DISP_1_function();
#	define LCDML_DISP_func_repeat_0() LCDML_DISP_0_function();
#	define LCDML_DISP_func_repeat(N) LCDML_DISP_func_repeat_ ## N ()

#endif



