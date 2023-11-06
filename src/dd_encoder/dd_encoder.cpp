#include "dd_encoder.h"
#include "Arduino.h"


/*     Arduino Rotary Encoder Tutorial
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 */
 
 #define outputA 3
 #define outputB 2

 int counter = 0; 
 int aState;
 int aLastState;  

 int  dd_encoder_get_counter(){
    return counter;
 }

int  dd_encoder_set_counter(int cnt){
    counter = cnt;
    return counter;
}
int  dd_encoder_reset_counter(){
    counter = dd_encoder_set_counter(0);
    return counter;
}

 void dd_encoder_setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   
//    Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 

 void dd_encoder_loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }
    //  Serial.print("Position: ");
    //  Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }