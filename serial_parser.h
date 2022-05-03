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


void getDataFromPC(TemperatureModule *temp_modules[]);
void parseData(TemperatureModule *temp_modules[]);

#endif