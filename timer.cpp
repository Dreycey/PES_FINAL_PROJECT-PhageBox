#include "timer.h"

#define ONE_SECOND (15625)


/*
 * Global timers.
 */
volatile int g_TIMER_OVERFLOW = 0;
volatile int g_TIMER_OVERFLOW_1 = 0;
volatile int g_TIMER_OVERFLOW_2 = 0;

/*
 * This function initializes the 
 * timer using compare register B and
 * the max prescaler.
 */
void init_timer() {

    TCCR1A = 0;

    // set timer to reset on compare
//    TCCR1A &= ~(1 << 1);
//    TCCR1A |= (1 << 1);
//    TCCR1B |= (1 << 3);
//    TCCR1B |= (1 << 4);
    
    // set prescaler - 1024 divider
    TCCR1B |= (1 << 0);
    TCCR1B &= ~(1 << 1);
    TCCR1B |= (1 << 2);
    
    // set compare value - register B
    OCR1B = ONE_SECOND;
    
    // start timer
    TCNT1 = 0;

    // set up interupts
    TIMSK1 &= ~(1 << 1); // NOT channel A
    TIMSK1 |= (1 << 2); // channel B    
    
    sei(); // start interupts using status register
}


void reset_timer(volatile int* timer) {
    *timer = 0;
}

void reset_timer_2() {
    g_TIMER_OVERFLOW_2 = 0;
}

volatile int* get_timer_1() {
    return &g_TIMER_OVERFLOW_1;
}

volatile int*  get_timer_2() {
    return &g_TIMER_OVERFLOW_2;
}


/*
 * input number of seconds for delay
 */
void adv_delay(int seconds2delay) {
    g_TIMER_OVERFLOW = 0;
    while (g_TIMER_OVERFLOW < seconds2delay)
       ;;
}

//void TIM1_COMPB(void) 
ISR(TIMER1_COMPB_vect) {
    char cSREG;
    cSREG = SREG; /* store SREG value */
    /* disable interrupts during timed sequence */
    cli();

    // Serial.print(g_TIMER_OVERFLOW);
    // Serial.print("\n");
    // increment timer
    g_TIMER_OVERFLOW++;
    g_TIMER_OVERFLOW_1++;
    g_TIMER_OVERFLOW_2++;
    TCNT1 = 0;
    
    SREG = cSREG; /* restore SREG value (I-bit) */
}

