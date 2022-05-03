
/*
*/
#ifndef  GPIO_Control_h                                                            
#define GPIO_Control_h                                                    
                                                                                
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#define LED_PIN (3)
#define RELAY_MAG (5)
#define RELAY_TEMP1 (6)
#define RELAY_TEMP2 (7)

#define FRONT_TEMPSENSE_PIN (10)
#define METAL_TEMPSENSE_PIN (11)
#define BACK_TEMPSENSE_PIN  (12)

// int num_portd_gpio_pins = 4;
const int portd_gpio_pins[4] = {LED_PIN, RELAY_MAG, RELAY_TEMP1, RELAY_TEMP1};

/*
 * Function: 
 *     init_led()
 * Description:
 *     Activates the phagebox LED
 * Input:
 *     1. PIN Number for port D
 * Output: 
 *     void/NA
 * Error Handling:
 *     void/NA
 */
void init_pin(int PIN_NUMBER);

/*
 * Function: 
 *     toggle_pin();
 * Description:
 *     toggles the LED on or off
 * Input:
 *     1. PIN Number for port D
 * Output: 
 *     void/NA
 * Error Handling:
 *     void/NA
 */
void toggle_pin(int PIN_NUMBER);

/*
 * Function: 
 *     initialize_gpio_pins()
 * Description:
 *     initializes all of the pins on port D
 * Input:
 *     void/NA
 * Output: 
 *     void/NA
 * Error Handling:
 *     void/NA
 */
void initialize_gpio_pins();

void toggle_pin_on(int PIN_NUMBER);

void toggle_pin_off(int PIN_NUMBER);

#endif