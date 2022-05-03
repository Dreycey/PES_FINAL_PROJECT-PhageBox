

#ifndef  timer_h                                                            
#define timer_h                                                    
                                                                                
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

// volatile int* p_g_TIMER_OVERFLOW_1;
// volatile int* p_g_TIMER_OVERFLOW_2;


void init_timer();

void adv_delay(int seconds2delay);

void reset_timer(volatile int* timer);



void reset_timer_1();

void reset_timer_2();

volatile int*  get_timer_1();

volatile int*  get_timer_2();


#endif