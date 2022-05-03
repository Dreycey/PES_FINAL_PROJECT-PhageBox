#include "PhageBox.h" 



#define TEMPMODULE_COUNT  (2)
TemperatureModule *temp_modules[TEMPMODULE_COUNT] = {&temp_Ctrl_1, &temp_Ctrl_2};


void init_phagebox() {
    init_timer();
    initialize_gpio_pins();
    Serial.println("<Arduino is ready>");
}

void start_phagebox() {
    // testing PCR
    // int time_now = temp_Ctrl_1.current_state;
    // Serial.print(time_now);
    // temp_Ctrl_1.go2nextstate();
    // temp_Ctrl_1.toggle_relay();
    // Serial.println(temp_Ctrl_2.getTemp());
    
    // toggle_pin(LED_PIN);

    // Read data from serial, update GPIO & TempModules.
    getDataFromPC(temp_modules);

    // Update states for finite state machine.
    // adv_delay(1);

    // if PCR is on, evaluate
    for (int i=0; i<TEMPMODULE_COUNT; i++) {
        TemperatureModule *curr_temp_module = temp_modules[i];
        //Serial.println(curr_temp_module);
        if (curr_temp_module->current_state != STOPPED) { // if ON...
            // Serial.println("ITS ONNNNNNNNNNNNNNnn");
            int curr_temp = curr_temp_module->getTemp();
            int desired_temp = curr_temp_module->get_desiredTemp();
            Serial.println("curr_temp:");
            Serial.println(curr_temp);
            Serial.println("desired_temp:");
            Serial.println(desired_temp);
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