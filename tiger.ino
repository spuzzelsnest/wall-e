#include <Servo.h>
#define SERVO       11  //servo connect to D11
#define buzzer      7   //buzzer connect to D7
#define IN1         8   //K1、K2 motor direction
#define IN2         9   //K1、K2 motor direction
#define IN3         10  //K3、K4 motor direction
#define IN4         12  //K3、K4 motor direction
#define ENA         5   // Needs to be a PWM pin to be able to control motor speed ENA
#define ENB         6
#define LFSensor_1  A0  //line follow sensor1
#define LFSensor_2  A1  //line follow sensor2
#define trig        A2
#define echo        A3
#define RSPEED      255
#define LSPEED      255

Servo head;
int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
const int distancelimit = 30; //distance limit for obstacles in front           
const int sidedistancelimit = 18; //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)

void go_ahead(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //delay(t);
}
void go_back(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  //delay(t);
}
void go_stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); 
}
void turn_left(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //delay(t);
}
void turn_right(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //delay(t);
}

void set_motorspeed(int lspeed,int rspeed){
  analogWrite(ENA,lspeed); 
  analogWrite(ENB,rspeed);   
}

void buzz_on(){
  digitalWrite(buzzer, LOW);
}
void buzz_off(){
    digitalWrite(buzzer, HIGH);
}
void alarm() {
  buzz_on();
  delay(100);
  buzz_off();
}

int watch() {
  long howfar;
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);
  howfar = pulseIn(echo, HIGH);
  howfar = howfar * 0.01657; //how far away is the object in cm
  Serial.println((int)howfar);
  return round(howfar);
}

void auto_avoidance() {
  head.write(90); 
  delay(100);
  centerscanval = watch();
  if (centerscanval >= distancelimit) {
    set_motorspeed(LSPEED, RSPEED);
    go_ahead();
  }
  else {
    go_stop();
    alarm();
    head.write(120);
    delay(150);
    ldiagonalscanval = watch();

    head.write(180);
    delay(150);
    leftscanval = watch();

    head.write(90);
    delay(150);

    head.write(60);
    delay(150);
    rdiagonalscanval = watch();

    head.write(0);
    delay(150);
    rightscanval = watch();

    head.write(90);
    if (ldiagonalscanval >= sidedistancelimit && leftscanval >= sidedistancelimit) {
      set_motorspeed(LSPEED, RSPEED);
      go_back();
      delay(200);
      turn_left();
      delay(500);
    }
    else if (rdiagonalscanval >= sidedistancelimit && rightscanval >= sidedistancelimit) {
      set_motorspeed(LSPEED, RSPEED);
      go_back();
      delay(200);
      turn_right();
      delay(500);
    }
  }
}

void setup() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    digitalWrite(trig, LOW);
    
    pinMode(buzzer, OUTPUT);
    digitalWrite(buzzer, HIGH);
    buzz_off();
    
    head.attach(SERVO);
    head.write(90);
    
    Serial.begin(9600);
    go_stop();
    Serial.println("<Arduino is ready>");
}

void loop(){
    //avoidance
    auto_avoidance();
    
    int senL = analogRead(A0);
    int senR = analogRead(A1);
    int data = Serial.read();
    
    Serial.println(data);
    Serial.println(senL);
    Serial.println(senR);
    delay (1000);
}