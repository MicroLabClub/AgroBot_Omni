#include "Arduino.h"

#include "dd_can_mcp/dd_can_mcp.h"
#include "dd_can_mcp/dd_can_matrix.h"
#include "dd_can_mcp/dd_can_signal.h"

#include "dd_joystick/dd_joystick.h"
#include "dd_buzzer/dd_buzzer.h"

#include "srv_control/srv_control.h"

void setup()
{
  Serial.begin(9600);

  dd_can_setup();
  dd_joystick_setup();
  dd_buzzer_setup();

  srv_control_setup();
}

#define SYS_TICK 1

#define CAN_SEND_REC (10 / SYS_TICK)
int send_rec_cnt = CAN_SEND_REC+1;

#define CAN_RECV_REC (1 / SYS_TICK)
int recv_rec_cnt = CAN_RECV_REC+2;

#define CAN_PRINT_REC (2000 / SYS_TICK)
int print_rec_cnt = CAN_PRINT_REC+3;

#define DD_JOYSTICK_REC (10 / SYS_TICK)
int dd_joystick_rec_cnt = DD_JOYSTICK_REC+3;

#define DD_BUZZER_REC (10 / SYS_TICK)
int dd_buzzer_rec_cnt = DD_BUZZER_REC+4;

#define SRV_CONTROL_REC (10 / SYS_TICK)
int srv_control_rec_cnt = SRV_CONTROL_REC+5;


void loop()
{
  if (--dd_joystick_rec_cnt <= 0)
  {// send data per 10ms
    dd_joystick_loop();
    dd_joystick_rec_cnt = DD_JOYSTICK_REC;
  }  
  
  if (--dd_buzzer_rec_cnt <= 0)
  {// send data per 10ms
    dd_buzzer_loop();
    dd_buzzer_rec_cnt = DD_BUZZER_REC;
  }  

  if (--srv_control_rec_cnt <= 0)
  {
    srv_control_loop();
    srv_control_rec_cnt = SRV_CONTROL_REC;
  }  
  
  if (--send_rec_cnt <= 0)
  {// send data per 100ms
    dd_can_send_loop();
    send_rec_cnt = CAN_SEND_REC;
  }

  if (--recv_rec_cnt <= 0)
  {
    dd_can_recv_loop();
    dd_can_signal_loop();
    recv_rec_cnt = CAN_RECV_REC;
  }

  if (--print_rec_cnt <= 0)
  {// print data per 100ms
    dd_can_matrix_print();
    dd_joystick_report();
    dd_can_tx_buff_print();

    print_rec_cnt = CAN_PRINT_REC;
  }

  delay(SYS_TICK); 
}
