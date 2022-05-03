#ifndef  TemperatureModule_h                                                            
#define TemperatureModule_h                                            
                                                                                
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include "OneWire.h"
#include "DallasTemperature.h"
#include "GPIO_Control.h"
#include "timer.h"
#define NUM_STATES (4)



/*
 * pcr_state
 *
 * This enum describes the different PCR states
 * available.
 * 
 * NOTE: if you add to this update NUM_STATES
 */
typedef enum pcr_state {
	STOPPED = 0,
	DENATURE = 1,
	ANNEAL = 2,
	ELONGATE = 3,
} pcr_state;

/*
 * States
 *
 *    This table describes the states
 *    the finite state machine may have.
 *    Note these state are based on PCR. 
 */
struct States {
	pcr_state current_state;
	int time;
	int temp;
	pcr_state next_state;
};


class TemperatureModule 
{
public:

	TemperatureModule(uint8_t relay_pin, uint8_t tempsense_pin, volatile int* timer);

	// update the state table with new values. 
    void update_state_table(pcr_state state, int time, int temp);

	// go to next state
	void go2nextstate() {current_state = state_table[current_state].next_state;};
	void update_states();

	//start and stop PCR from running.
	void start_pcr();
	void stop_pcr();

    // get the current temperature
    float getTemp();
	void toggle_relay();
    void heater_on();
	void heater_off();
    pcr_state current_state;

	// setters and getters
	int get_currentTimeLen();
	float get_desiredTemp();
	void set_cycle_count(int cycle_count);

private:
	typedef uint8_t ScratchPad[9];
	uint8_t relayPin;
	DallasTemperature temp_sensor;
	float current_temperature;
	int cycle_count = 0;
	int number_cycles_used = 0;
	volatile int* internal_timer;
    /*
	* state_table
	* ------------------
	* For this particular FSM, we define the following
	* table for each state, containing information on
	* delay times, next state, and the state's color.
	*/
	struct States state_table[NUM_STATES] = 
    {
	  {STOPPED, 0, 0, STOPPED},
	  {DENATURE, 0, 0, ANNEAL},
	  {ANNEAL, 0, 0, ELONGATE},
	  {ELONGATE, 0, 0, DENATURE}
	};
};

/*
 * Global temperature sensors
 */
// volatile int* p_g_TIMER_OVERFLOW_1 = get_timer_1();
// volatile int* p_g_TIMER_OVERFLOW_2 = get_timer_2();
static TemperatureModule temp_Ctrl_2(RELAY_TEMP1, FRONT_TEMPSENSE_PIN, get_timer_1());
static TemperatureModule temp_Ctrl_1(RELAY_MAG, BACK_TEMPSENSE_PIN, get_timer_2());

#endif

