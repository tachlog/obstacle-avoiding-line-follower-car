#define enA 6//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 3 //Motor1  L298 Pin in1 
#define in3 5 //Motor2  L298 Pin in1 
#define in4 10 //Motor2  L298 Pin in1 
#define enB 11 //Enable2 L298 Pin enB 

#define L_S A0 //ir sensor Left
#define R_S A1 //ir sensor Right

#define echo 13    //Echo pin
#define trigger 12 //Trigger pin

#define servo A5 //pwm pin of servomotor

int Set=15;
int distance_L, distance_F, distance_R; 

void setup(){ // put your setup code here, to run once

Serial.begin(9600); // start serial communication at 9600bps

pinMode(R_S, INPUT); // declare if sensor as input  
pinMode(L_S, INPUT); // declare ir sensor as input

pinMode(echo, INPUT );// declare ultrasonic sensor Echo pin as input
pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output  

pinMode(enA, OUTPUT); // declare as output for L298 Pin enA 
pinMode(in1, OUTPUT); // declare as output for L298 Pin in1 
pinMode(in2, OUTPUT); // declare as output for L298 Pin in2 
pinMode(in3, OUTPUT); // declare as output for L298 Pin in3   
pinMode(in4, OUTPUT); // declare as output for L298 Pin in4 
pinMode(enB, OUTPUT); // declare as output for L298 Pin enB 

analogWrite(enA, 200); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 
analogWrite(enB, 200); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed 

pinMode(servo, OUTPUT);

 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
 for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }

 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }

distance_F = Ultrasonic_read();

delay(500);
}


void loop(){  
//==============================================
//     Line Follower and Obstacle Avoiding
//==============================================  

distance_F = Ultrasonic_read();
Serial.print("D F=");Serial.println(distance_F);


//if Right Sensor and Left Sensor are at White color then it will call forword function
 if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){
  if(distance_F > Set){forward();}
                  else{Check_side();}  
 }  
 
//if Right Sensor is Black and Left Sensor is White then it will call turn Right function
else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){turnRight();}  

//if Right Sensor is White and Left Sensor is Black then it will call turn Left function
else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){turnLeft();} 

//if Right Sensor and Left Sensor are at black color then it will call forword function
else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){Stop();} 
    
delay(10);
}

void servoPulse (int pin, int angle){
int pwm = (angle*11) + 500;      // Convert angle to microseconds
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50); // Refresh cycle of servo
}


//**********************Ultrasonic_read****************************
long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}

void compareDistance(){
    if(distance_L > distance_R){
  turnLeft();
  delay(500);
  forward();
  delay(600);
  turnRight();
  delay(500);
  forward();
  delay(600);
  turnRight();
  delay(400);
  }
  else{
  turnRight();
  delay(500);
  forward();
  delay(600);
  turnLeft();
  delay(500);
  forward();
  delay(600);  
  turnLeft();
  delay(400);
  }
}

void Check_side(){
    Stop();
    delay(100);
 for (int angle = 0; angle <= 100; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    distance_R = Ultrasonic_read();
    Serial.print("D R=");Serial.println(distance_R);
    delay(100);
  for (int angle = 100; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
    Serial.print("D L=");Serial.println(distance_L);
    delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    compareDistance();
}

void forward(){  //forward
digitalWrite(in1, LOW); //Left Motor forward Pin 
digitalWrite(in2, HIGH); //Left Motor backward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, HIGH); //Right Motor backward Pin 
}

void backward(){ //backward
digitalWrite(in1, HIGH); //Left Motor forward Pin 
digitalWrite(in2, LOW); //Left Motor backward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, HIGH); //Right Motor backward Pin 
}

void turnRight(){ //turnRight
digitalWrite(in1, HIGH); //Left Motor forward Pin 
digitalWrite(in2, HIGH); //Left Motor backward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, HIGH); //Right Motor backward Pin 
}

void turnLeft(){ //turnLeft
digitalWrite(in1, LOW); //Left Motor forward Pin 
digitalWrite(in2, HIGH); //Left Motor backward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, LOW); //Right Motor backward Pin 
}

void Stop(){ //stop
digitalWrite(in1, LOW); //Left Motor forward Pin 
digitalWrite(in2, LOW); //Left Motor backward Pin 
digitalWrite(in3, LOW); //Right Motor forward Pin 
digitalWrite(in4, LOW); //Right Motor backward Pin 
}
