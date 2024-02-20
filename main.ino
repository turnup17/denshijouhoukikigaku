#include <Servo.h>


const int IR_SOCKET_F = 2;
const int IR_SOCKET_B = 3;
const int IR_SOCKET_FR = 4;
const int IR_SOCKET_FL = 5;
const int IR_SOCKET_BR = 6;
const int IR_SOCKET_BL = 7;

Servo motor_servo_left;
Servo motor_servo_right;

void motor_speed_left(int pct) {
  int angle = 90-0.9*(pct+2);
  if(angle > 180) angle = 180;
  motor_servo_left.write(angle);
}
void motor_speed_right(int pct) {
  int angle = 90-0.9*(pct + 3);
    if(angle > 180) angle = 180;
  motor_servo_right.write(angle);
}

void setup() {
    Serial.begin(9600);
    motor_servo_left.attach(8,700,2300);
    motor_servo_right.attach(9,700,2300);
    pinMode(IR_SOCKET_F, INPUT);
    pinMode(IR_SOCKET_B, INPUT);
    pinMode(IR_SOCKET_FR, INPUT);
    pinMode(IR_SOCKET_FL, INPUT);
    pinMode(IR_SOCKET_BR, INPUT);
    pinMode(IR_SOCKET_BL, INPUT);
}
void loop() { 
    String message = "";
    int F =digitalRead(IR_SOCKET_F);
    int B =digitalRead(IR_SOCKET_B);
    int FR =digitalRead(IR_SOCKET_FR);
    int FL =digitalRead(IR_SOCKET_FL);
    int BR =digitalRead(IR_SOCKET_BR);
    int BL =digitalRead(IR_SOCKET_BL);
    if (F == 0 && B == 1){
       message = "Some One Is Here!";
       Serial.println("FRONT");
       motor_speed_left(100);
       motor_speed_right(-100);
       for(int i = 0; i < 50; i++){
        delay(10);
        if(digitalRead(IR_SOCKET_B) == 0){
          motor_speed_left(0);
          motor_speed_right(0);
          delay(500);
        }
       } 

    }
    else if (B == 0 && F == 1){
       Serial.println("BACK");
       motor_speed_left(-100);
       motor_speed_right(100); 
       for(int i = 0; i < 50; i++){
        delay(10);
        if(digitalRead(IR_SOCKET_F) == 0){
          motor_speed_left(0);
          motor_speed_right(0);
          delay(500);
        }
       } 
    }
    else if(BR == 0){
      Serial.println("BACK RIGHT");
       motor_speed_left(-10);
       motor_speed_right(100);
       delay(500);
       motor_speed_left(-100);
       motor_speed_right(100);
       for(int i = 0; i < 50; i++){
        delay(10);
        if(digitalRead(IR_SOCKET_F) == 0){
          motor_speed_left(0);
          motor_speed_right(0);
        }
       } 

    }
    else if(BL == 0){
      Serial.println("BACK LEFT");
       motor_speed_left(-100);
       motor_speed_right(10);
       delay(500);
       motor_speed_left(-100);
       motor_speed_right(100);
       for(int i = 0; i < 50; i++){
        delay(10);
        if(digitalRead(IR_SOCKET_F) == 0){
          motor_speed_left(0);
          motor_speed_right(0);
        }
       } 
    }
    else if(FR == 0){
      Serial.println("FRONT RIGHT");
       motor_speed_left(10);
       motor_speed_right(-100);
       delay(500);
       motor_speed_left(100);
       motor_speed_right(-100);
       for(int i = 0; i < 50; i++){
        delay(10);
        if(digitalRead(IR_SOCKET_B) == 0){
          motor_speed_left(0);
          motor_speed_right(0);
        }
       } 

    }
    else if(FL == 0){
      Serial.println("FRONT LEFT");
       motor_speed_left(100);
       motor_speed_right(-10);
       delay(500);
       motor_speed_left(100);
       motor_speed_right(-100);
       for(int i = 0; i < 50; i++){
        delay(10);
        if(digitalRead(IR_SOCKET_B) == 0){
          motor_speed_left(0);
          motor_speed_right(0);
        }
       }  
    }
    else if(F + B == 0){
       motor_speed_left(0);
       motor_speed_right(0); 
    }
    else if (B*F*FR*FL*BR*BL == 1){
      Serial.println("STOP");
      motor_speed_left(0);
      motor_speed_right(0);
    }
     
    Serial.println(message);
    //delay(1000);

}
