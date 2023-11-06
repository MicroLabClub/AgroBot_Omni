#include "srv_control.h"
#include "stdint.h"
#include "dd_can_mcp/dd_can_signal.h"
#include "dd_buzzer/dd_buzzer.h"

void srv_control_setup()
{
}

void srv_control_loop()
{

    uint8_t bip_sig = dd_can_signal_get_bip();
    if (bip_sig == 0x00)
    {
        dd_buzzer_set_state(1);
    }
    else
    {
        dd_buzzer_set_state(0);
    }
}