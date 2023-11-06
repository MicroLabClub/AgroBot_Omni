#ifndef DD_MCP_CAN_H_
#define DD_MCP_CAN_H_
#include "dd_can_matrix.h"

#define MY_CAN_ID CAN_ID_ANDREI_B

#define CAN0_INT 8 // Set INT to pin 2
#define CAN0_CS 10 // Set CS to pin 2

void dd_can_setup();
void dd_can_recv_loop();
void dd_can_send_loop();
uint8_t * dd_can_get_tx_buff_ref();
void dd_can_tx_buff_print();


#endif