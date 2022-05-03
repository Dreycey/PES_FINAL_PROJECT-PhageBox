

#ifndef  PhageBox_h
#define PhageBox_h 


// IN-HOUSE PACKAGES
#include "timer.h"
#include "GPIO_Control.h"
#include "serial_parser.h"
#include "TemperatureModule.h"

/*
 * Function: 
 *     init_phagebox()
 * Description:
 *     initilization sequence for the phagebox.
 *     allows for getting the device set up for Serial 
 *     commmunication as well as gving the aility for an
 *     "on" lighting sequence.
 * Input:
 *     void/NA
 * Output: 
 *     void/NA
 * Error Handling:
 *     void/NA
 */
void init_phagebox();

/*
 * Function: 
 *     start_phagebox()
 * Description:
 *     this is the main function for the package. It 
 *     uses the TemperatureModule to control temperature
 *     using a bang-bang controller and finite state machine.
 *     additionally, it parses input Serial commands.
 * Input:
 *     void/NA
 * Output: 
 *     void/NA
 * Error Handling:
 *     void/NA
 */
void start_phagebox();



#endif