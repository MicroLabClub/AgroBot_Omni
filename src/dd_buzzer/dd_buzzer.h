#ifndef DD_BUZZER_H_
#define DD_BUZZER_H_
#include "stdint.h"


#define DD_BUZZER_PIN 9

void dd_buzzer_setup();
void dd_buzzer_loop();
uint8_t dd_buzzer_get_state( );
void dd_buzzer_set_state(uint8_t state);


#endif
