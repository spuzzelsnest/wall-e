#include <Servo.h>
#define SERVO      11  //servo connect to D11
#define buzzer     7 //buzzer connect to D7
#define LFSensor_1 A0 //line follow sensor1
#define LFSensor_2 A1 //line follow sensor2
#define RSPEED   255  //right motor speed
#define LSPEED   255 

void go_ahead()//go ahead
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,HIGH);
  //delay(t);
}
void go_back() //go back
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW); 
  //delay(t);
}
void go_stop() //stop
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
}
void turn_left()//turn left
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //delay(t);
}
void turn_right()//turn right
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //delay(t);
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
    /*line follow sensors */
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop(){
    //avoidance
    auto_avoidance();
    //print info
    
    int senL = analogRead(A0);
    int senR = analogRead(A1);
    
    Serial.println(senL);
    Serial.println(senR);
    delay (1000);
}