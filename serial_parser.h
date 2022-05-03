#ifndef  serial_parser_h                                                            
#define serial_parser_h                                            
                                                                                
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include "TemperatureModule.h"
#include "GPIO_Control.h"


/*
 * Function: 
 *     getDataFromPC()
 * Description:
 *     this metthod parses incoming serial data and saves it into a buffer
 *     for downstream processing. This allows for picking up on start and end
 *     delimiters.
 * 
 * adopted from - https://forum.arduino.cc/t/data-input-demo-sketch/229829
 * Input:
 *     void/NA
 * Output: 
 *     void/NA
 * Error Handling:
 *     void/NA
 */
void getDataFromPC(TemperatureModule *temp_modules[]);

/*
 * Function: 
 *     parseData()
 * Description:
 *     This method parses an input string once the characters from serial
 *     have fully filled the buffer.
 * adopted from - https://forum.arduino.cc/t/data-input-demo-sketch/229829
 * Input:
 *     void/NA
 * Output: 
 *     void/NA
 * Error Handling:
 *     void/NA
 */
void parseData(TemperatureModule *temp_modules[]);

#endif