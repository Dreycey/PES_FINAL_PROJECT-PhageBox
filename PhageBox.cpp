#include "PhageBox.h" 
#define TEMPMODULE_COUNT  (2)



/*
 * Globals
 *    The globall temp_modules below are used for each
 *    of the temperature modules on the device. 
 */
TemperatureModule *temp_modules[TEMPMODULE_COUNT] = {&temp_Ctrl_1, &temp_Ctrl_2};

// Defined in header
void init_phagebox() {
    init_timer();
    initialize_gpio_pins(); 
    Serial.println("<Arduino is ready>");

    // toggle LED to show it is on.
    for (int i=0; i < 8; i++) {
        toggle_pin(LED_PIN);
        adv_delay(1);
    }
}

// Defined in header
void start_phagebox() {
    getDataFromPC(temp_modules);

    // if PCR is on, evaluate
    for (int i=0; i<TEMPMODULE_COUNT; i++) {
        TemperatureModule *curr_temp_module = temp_modules[i];
        if (curr_temp_module->current_state != STOPPED) { // if ON...
            int curr_temp = curr_temp_module->getTemp();
            int desired_temp = curr_temp_module->get_desiredTemp();
            // bang bang controller
            if (curr_temp <= desired_temp) {
                curr_temp_module->heater_on();
            } else if (curr_temp >= desired_temp) {
                curr_temp_module->heater_off();
            }
            // go to next state or cancel
            curr_temp_module->update_states();
        }
    }

}