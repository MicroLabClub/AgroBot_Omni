#ifndef DD_ENCODER_H_
#define DD_ENCODER_H_


void dd_encoder_setup();
void dd_encoder_loop();

int  dd_encoder_get_counter();
int  dd_encoder_set_counter(int cnt);
int  dd_encoder_reset_counter();


#endif

