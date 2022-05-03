#include "TemperatureModule.h"
#include "GPIO_Control.h"



// Defined in header
TemperatureModule::TemperatureModule(uint8_t relay_pin, uint8_t tempsense_pin, volatile int* timer) {
    // start in off state
    current_state = STOPPED;
    // update temperature sensor
    register OneWire *oneWire = new OneWire(tempsense_pin);
    temp_sensor.setOneWire(oneWire);
    temp_sensor.setResolution(12);
    temp_sensor.setWaitForConversion(false);
    // temp_sensor = sensors;
    temp_sensor.begin();
    // update temperature sensor
    relayPin = relay_pin;
    // assign timer
    internal_timer = timer;
}

// Defined in header
void TemperatureModule::update_states() {
    // Serial.println("*internal_timer");
    // Serial.println(*internal_timer);

    if (*internal_timer >= get_currentTimeLen()) {
        go2nextstate();
        reset_timer(internal_timer);
        if (current_state == ELONGATE)
            number_cycles_used++;
    }
    // Serial.println("cycle_count \n");
    // Serial.println(cycle_count);
    if (number_cycles_used >= cycle_count) {
        stop_pcr();
    }
}

// Defined in header
float TemperatureModule::getTemp() { 
    temp_sensor.requestTemperatures();
    current_temperature = temp_sensor.getTempCByIndex(0);
    return current_temperature;
}

// Defined in header
void TemperatureModule::toggle_relay() { 
    toggle_pin(relayPin); // from GPIO
}

// Defined in header
void TemperatureModule::heater_on() { 
    void toggle_pin_on(int PIN_NUMBER); // from GPIO module
}

// Defined in header
void TemperatureModule::heater_off() { 
    void toggle_pin_off(int PIN_NUMBER); // from GPIO module
}

// Defined in header
void TemperatureModule::update_state_table(pcr_state state, int time, int temp) {
    state_table[state].time = time;
    state_table[state].temp = temp;
}

// Defined in header
int TemperatureModule::get_currentTimeLen() {
    return state_table[current_state].time;
}

// Defined in header
float TemperatureModule::get_desiredTemp() {
    return state_table[current_state].temp;
}

// Defined in header
void TemperatureModule::set_cycle_count(int cycle_count_in) {
    cycle_count = cycle_count_in;
    Serial.println("cycle_count is set \n");
    Serial.println(cycle_count);
}

// Defined in header
void TemperatureModule::start_pcr() {
    reset_timer(internal_timer);
    number_cycles_used = 0;
    current_state = DENATURE;
}

// Defined in header
void TemperatureModule::stop_pcr() {
    Serial.print("stop called");
    current_state = STOPPED;
}