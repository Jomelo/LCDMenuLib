Arduino LCDMenuLib with layers for any LCD Type (Row Displays, Graphic Displays, Console output)
=================================================================
Display System:
*  max 254 menu elements												
*  max 254 menu elements per layer								    
*  max 6 layers from root (configurable in LCDMenuLib.h)				
*  max support for 6 buttons up, down, left, right, back/quit, enter  
*  min 3 buttons needed up, down, enter                               
*  separation of structural and functional level                     
*  support for initscreen which is shown after x secounds or at begin (configurable) 
*  scrollbar when more menu elments in a layer then rows              
*  possibility to jump from one menu elment directly to another       
*  support for many different lcd librarys 
*  the menu function are only updated when a button is hit or a trigger is set														
*  different triggers for display function
*  many small function for other things								

Backend System
* max 255 backend function 
* backend function work with different ms times, not with interrupts
* backend function can be stopped and started
* backend function use three functions setup,loop,stable
* backend function can be grouped, groups can start / stop together
* backend signals use one bit to transfer a status bit between backend functions

Examples in english

Description & Support (german):
http://forum.arduino.cc/index.php?topic=73816.0
