#include "Arduino.h"
#include "stdio.h"

char dd_can_signal_report[100];


#include "dd_can_signal.h"
#include "dd_can_mcp.h"
#include "dd_can_matrix.h"
#include "dd_joystick/dd_joystick.h"
#include "stdint.h"

#include "device_config.h"

void dd_can_signal_loop(){

    uint16_t x = dd_joystick_get_x();
    uint16_t y = dd_joystick_get_y();
    uint8_t b = dd_joystick_get_b();

    uint8_t * tx_buff = dd_can_get_tx_buff_ref();

    tx_buff[0] = (x >>8) & 0xFF; // HIGH Byte X
    tx_buff[1] = x & 0xFF;       // Low Byte X

    tx_buff[2] = (y >>8) & 0xFF; // High Byte Y
    tx_buff[3] = y & 0xFF;       // Low Byte Y

    tx_buff[4] = b; // Button state

}

uint8_t dd_can_signal_get_bip(){
    uint32_t matrix_id = dd_can_matrix_get_msg_ref(CAN_ID_ROMAN_A);
    uint8_t * msg_buff = dd_can_matrix_get_msg_buff_ref( matrix_id);

    uint8_t bip_sig = msg_buff[4];

    return bip_sig;
}


int8_t dd_can_signal_get_Wheel_pow(){
    uint32_t matrix_id = dd_can_matrix_get_msg_ref(CAN_ID_WHEEL_POW);
    uint8_t * msg_buff = dd_can_matrix_get_msg_buff_ref( matrix_id);

    int motorSpeed =     msg_buff[WHEEL_CONFIG * 2 + 0];  // Get motor speed from data 
    int motorDirection = msg_buff[WHEEL_CONFIG * 2 + 1];  // Get motor direction from data

    if (motorDirection == 0)motorSpeed*=(-1);
    return motorSpeed;
}



void dd_can_signal_report_Wheel_pow(){

    int pow = dd_can_signal_get_Wheel_pow();

    sprintf(dd_can_signal_report, "WHEEL Power:  Pow = %d, ", pow);
    Serial.println(dd_can_signal_report);
}

int8_t dd_can_signal_get_Wheel_angle(){
    uint32_t matrix_id = dd_can_matrix_get_msg_ref(CAN_ID_WHEEL_POW);
    uint8_t * msg_buff = dd_can_matrix_get_msg_buff_ref( matrix_id);

    int wheelAngle =     msg_buff[WHEEL_CONFIG * 2 + 2];  // Get motor speed from data 
    int WheelAngleSign = msg_buff[WHEEL_CONFIG * 2 + 3];  // Get motor direction from data

    if (WheelAngleSign == 0)wheelAngle*=(-1);
    return wheelAngle;
}



void dd_can_signal_report_Wheel_angle(){

    int angle = dd_can_signal_get_Wheel_angle();

    sprintf(dd_can_signal_report, "WHEEL Angle:  Angle = %d, ", angle);
    Serial.println(dd_can_signal_report);
}
