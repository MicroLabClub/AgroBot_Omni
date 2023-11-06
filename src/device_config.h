#ifndef DEVICE_CONFIG_H_
#define DEVICE_CONFIG_H_

enum traction_wheels_e 
{ 
  WHEEL_FRONT_LEFT,   
  WHEEL_FRONT_RIGHT,   
  WHEEL_BACK_LEFT,    
  WHEEL_BACK_RIGHT,  
  WHEEL_NR_OF, 
}; 
 
#define WHEEL_CONFIG WHEEL_FRONT_LEFT //Setul de date a anumutei roti care este citita
#endif