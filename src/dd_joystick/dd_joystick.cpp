
#include "dd_joystick.h"
#include "Arduino.h"
#include "stdint.h"
#include "stdio.h"

uint16_t dd_joystick_x = 0;
uint16_t dd_joystick_y = 0;
uint8_t dd_joystick_b = 0;


char joy_msg_string[100];

void dd_joystick_setup()
{
    pinMode(DD_JOYSTICK_X, INPUT);
    pinMode(DD_JOYSTICK_Y, INPUT);
    pinMode(DD_JOYSTICK_B, INPUT_PULLUP);
}


uint16_t dd_joystick_get_x()
{
    return dd_joystick_x;
}
uint16_t dd_joystick_get_y()
{
    return dd_joystick_y;
}
uint8_t dd_joystick_get_b()
{
    return dd_joystick_b;
}

void dd_joystick_loop()
{
    dd_joystick_x = analogRead(DD_JOYSTICK_X);
    dd_joystick_y = analogRead(DD_JOYSTICK_Y);
    dd_joystick_b = digitalRead(DD_JOYSTICK_B);
}

void dd_joystick_report(){

    uint16_t x = dd_joystick_get_x();
    uint16_t y = dd_joystick_get_y();
    uint8_t b = dd_joystick_get_b();

    sprintf(joy_msg_string, "JOYSTICK:  X = %d, Y = %d, B = %d, ", 
    x,y,b);
    Serial.println(joy_msg_string);
}
