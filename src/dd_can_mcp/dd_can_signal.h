#ifndef DD_SIGNAL_H_
#define DD_SIGNAL_H_
#include "stdint.h"

void dd_can_signal_loop();
uint8_t dd_can_signal_get_bip();

int8_t dd_can_signal_get_Wheel_pow();
int8_t dd_can_signal_get_Wheel_angle();

void dd_can_signal_report_Wheel_pow();
void dd_can_signal_report_Wheel_angle();

#endif

