#include "dd_buzzer.h"
#include "Arduino.h"
uint8_t dd_buzzer_state = 0;

void dd_buzzer_setup(){
    pinMode(DD_BUZZER_PIN, OUTPUT);
    dd_buzzer_state = 0;
}

uint8_t dd_buzzer_get_state(){
    return dd_buzzer_state;
}

void dd_buzzer_set_state(uint8_t state){
    dd_buzzer_state = state;
}

void dd_buzzer_loop(){
    uint8_t state = dd_buzzer_get_state();
    digitalWrite(DD_BUZZER_PIN, state);
}



