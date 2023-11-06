#include "srv_control_dir.h"
#include "stdint.h"
#include "dd_can_mcp/dd_can_signal.h"
#include "dd_buzzer/dd_buzzer.h"
#include "dd_encoder/dd_encoder.h"


#include <Arduino.h> 
 
 



 
int target_angle = 0; 
int current_angle = 0; 

int turn_active = 0; 
 
 
#define MIN_ANGLE (-100) 
#define MAX_ANGLE 100 
#define DELTA_ANGLE 5 
#define TURN_POW 50 
 
void srv_control_dir_setup()
{
 
  pinMode(outputA, INPUT); 
  pinMode(outputB, INPUT); 
 
  pinMode(ENA_PIN, OUTPUT); 
  pinMode(IN1_PIN, OUTPUT); 
  pinMode(IN2_PIN, OUTPUT); 
 

 
} 
 
 
void MotorStop(int ENA,int IN1,int IN2) { 
  digitalWrite(ENA, 0);  // Turn off the motor by setting the speed to 0 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW); 
  digitalWrite(ENA, 0); 
} 
 
void MotorGoLeft(int ENA,int IN1,int IN2,int pow) { 
  digitalWrite(ENA, 0);  // Turn off the motor by setting the speed to 0 
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH); 
  digitalWrite(ENA, pow); 
} 
 
void MotorGoRight(int ENA,int IN1,int IN2,int pow) { 
  digitalWrite(ENA, 0);  // Turn off the motor by setting the speed to 0 
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW); 
  digitalWrite(ENA, pow); 
} 
 
 
int GetTargerAngle() { 
  return target_angle; 
} 
 
int SetTargerAngle(int angle) { 
  angle = constrain(angle, MIN_ANGLE, MAX_ANGLE); 
  target_angle = angle; 
  return target_angle; 
} 
 
int TurnLeft(int angle) { 
  int target_ang_lcl = GetTargerAngle(); 
  target_ang_lcl -= angle; 
  target_ang_lcl = SetTargerAngle(target_ang_lcl); 
  return target_ang_lcl; 
} 
 
int TurnRight(int angle) { 
  int target_ang_lcl = GetTargerAngle(); 
  target_ang_lcl += angle;                                       // < -  
  target_ang_lcl = SetTargerAngle(target_ang_lcl); 
  return target_ang_lcl; 
} 
 
int IsTurnEnable() { 
  return turn_active; 
} 

int TurnEnable() { 
  turn_active = 1; 
  return turn_active; 
} 
void TurnDisable() { 
  turn_active = 0; 
} 
 
int GetAngleError() { 
  int error = target_angle - current_angle; 
 
  return error; 
} 
 
void srv_control_dir_PrintReoprt() { 
 
  Serial.print(" Current angle: "); 
  Serial.println(current_angle); 
 
  Serial.print(" Target angle: "); 
  Serial.println(target_angle); 
 
 
  Serial.print(" Angle ERROR : "); 
  Serial.println(GetAngleError()); 
 
  Serial.print(" Turn active : "); 
  Serial.println(turn_active); 
} 
 
#define ANGLE_GEAR_RATIO (5*4*3)
 
void srv_control_dir_loop()
{

    uint8_t angle = dd_can_signal_get_Wheel_angle();
    SetTargerAngle(angle);



    current_angle = dd_encoder_get_counter();

 
  if (IsTurnEnable())  
  { 
    int error = GetAngleError(); 
    if (error > 0) { 
      MotorGoRight(ENA_PIN,IN1_PIN,IN2_PIN,TURN_POW); 
    } else if (error < 0 ) { 
      MotorGoLeft(ENA_PIN,IN1_PIN,IN2_PIN,TURN_POW); 
    } else { 
      MotorStop(ENA_PIN,IN1_PIN,IN2_PIN); 
    } 
  } 
  else 
  { 
    MotorStop(ENA_PIN,IN1_PIN,IN2_PIN); 
  } 
} 
 