#include "stdint.h"
#include "stdio.h"
#include "Arduino.h"
#include "dd_can_matrix.h"

#define CAN_MESSAGE_LEN 8

typedef struct can_message_t
{
    uint32_t id;
    uint8_t message[CAN_MESSAGE_LEN];
} can_message_t;

// {ID_L, ID_H, byte0, byte1, ... byte 7}
can_message_t CanMatrix_new[CAN_MATRIX_SIZE];

int8_t CanMatrix[2 + 8][CAN_MATRIX_SIZE];

char msg_string[128]; // Array to store serial string

uint8_t * dd_can_matrix_get_msg_buff_ref(uint16_t matrix_id){
    return CanMatrix_new[matrix_id].message;
}

uint16_t dd_can_matrix_get_msg_ref(uint16_t rxId)
{
    size_t msg_ref = 0;

    switch (rxId & 0x1FFFFFFF) // ignore flags
    {
    case CAN_ID_ALEX_C:
        msg_ref = CAN_MSG_1;
        break;
    case CAN_ID_CRISTI_S:
        msg_ref = CAN_MSG_2;
        break;
    case CAN_ID_CRISTI_P:
        msg_ref = CAN_MSG_3;
        break;
    case CAN_ID_ADRIAN_B:
        msg_ref = CAN_MSG_4;
        break;
    case CAN_ID_DORIN_A:
        msg_ref = CAN_MSG_5;
        break;
    case CAN_ID_MIHAIL_P:
        msg_ref = CAN_MSG_6;
        break;
    case CAN_ID_ANDREI_B:
        msg_ref = CAN_MSG_7;
        break;
    case CAN_ID_ROMAN_A:
        msg_ref = CAN_MSG_8;
        break;
    case CAN_ID_DAVID_C:
        msg_ref = CAN_MSG_9;
        break;
    case CAN_ID_VICTOR_C:
        msg_ref = CAN_MSG_10;
        break;
    default:
        msg_ref = CAN_MSG_DUMMY;
        break;
    }

    return msg_ref;
}

void dd_can_matrix_setup(){

}

void dd_can_matrix_set(uint16_t rxId, uint8_t *rxBuf, size_t len)
{

    size_t matrixID = dd_can_matrix_get_msg_ref(rxId);
    CanMatrix_new[matrixID].id = rxId;

    for (size_t i = 0; i < len; i++)
    {
        CanMatrix_new[matrixID].message[i] = rxBuf[i];
    }
}

void dd_can_matrix_print()
{
    Serial.println("CAN Matrix report:");
    for (size_t msg_id = 0; msg_id < CAN_MATRIX_SIZE; msg_id++)
    {
        uint16_t rxId;
        rxId = CanMatrix_new[msg_id].id;

        if (rxId)
        {
            sprintf(msg_string, "Mtrx ID:[%d] ", msg_id);
            Serial.print(msg_string);

            sprintf(msg_string, "CAN ID: 0x%.4X Data:", rxId);
            Serial.print(msg_string);

            for (int i = 0; i < 8; i++)
            {
                sprintf(msg_string, " 0x%.2X", CanMatrix_new[msg_id].message[i]);
                Serial.print(msg_string);
            }
            Serial.println();
        }
    }
}
