#include <Servo.h>
#include <IRremote.h>
#define IN1  8   //K1、K2 motor direction
#define IN2  9     //K1、K2 motor direction
#define IN3  10    //K3、K4 motor direction
#define IN4  12   //K3、K4 motor direction
#define ENA  5    // Needs to be a PWM pin to be able to control motor speed ENA
#define ENB  6    // Needs to be a PWM pin to be able to control motor speed ENB
#define LED1 2  //lefe led connect to D2
#define LED2 3  //right led connect to D3
#define IRPIN  13 //IR receiver Signal pin connect to Arduino pin 13
#define LFSensor_1 A0 //line follow sensor1
#define LFSensor_2 A1 //line follow sensor2
#define SERVO     11  //servo connect to D11
#define echo    A3 // Ultrasonic Echo pin connect to A2
#define trig    A2  // Ultrasonic Trig pin connect to A3
#define buzzer     7 //buzzer connect to D7
Servo head;    // create servo object to control a servo
IRrecv IR(IRPIN);  //   IRrecv object  IR get code from IR remoter
decode_results IRresults;   
String inputString = "";//Store serial data
boolean stringComplete = false;  // whether the string is complete

int pos = 0;
void setup() {
  /******LED******/
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  /*line follow sensors */
  pinMode(LFSensor_1,INPUT);
  pinMode(LFSensor_2,INPUT); 
  /*servo*/
  head.attach(SERVO);
  head.write(90);
  /*init HC-SR04*/
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);
  /*buzzer*/
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, HIGH);//close buzzer
  /*IR sensor*/
  pinMode(IRPIN, INPUT); 
  digitalWrite(IRPIN, HIGH);  
  IR.enableIRIn();
  /******L298N******/
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("welcome to use osoyoo tank robot car...");
  Serial.println("send <line follow/>:test line follow sensor");
  Serial.println("send <led on/>:turn on LED ");
  Serial.println("send <led off/>:turn off LED ");
  Serial.println("send <servo/>: test servo");
  Serial.println("send <distance/>: test HC-SR04");
  Serial.println("send <buzzer/>: test buzzer");
  Serial.println("send <go/>: test robot go ahead");
  Serial.println("send <back/>: test robot go back");
  Serial.println("send <stop/>: test robot stop");
  Serial.println("--------------------------------------------------->>");
}

/*receive serial data*/
void read_serial()
{
  if (Serial.available()>0) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '/') {
      stringComplete = true;
    }
  }
}

void loop() {
  read_serial();
  if(stringComplete){
    if(inputString =="line follow/") read_sensor_values();
    else if(inputString =="led on/") led_on();
    else if(inputString =="led off/") led_off();
    else if(inputString =="servo/") test_servo();
    else if(inputString == "distance/") test_hc_sr04();
    else if(inputString == "buzzer/") test_buzzer();
    else if(inputString == "go/") go_ahead();
    else if(inputString == "back/") go_back();
    else if(inputString == "stop/") go_stop();
    inputString = "";
    stringComplete = false;
  }
  test_ir();//test IR receiver
}

/*read line folloe sensors*/
void read_sensor_values()
{
  char sensor[2];
  sensor[0]=digitalRead(LFSensor_1);
  sensor[1]=digitalRead(LFSensor_2);
  if(sensor[0]==1 && sensor[1]== 0)
    Serial.println("left sensor is on the black line,right sensor is not on the black line");
  if(sensor[0]==0 && sensor[1]== 1)
    Serial.println("left sensor is not on the black line,right sensor is on the black line");
  if(sensor[0]==1 && sensor[1]== 1)
    Serial.println("all sensons are on the black line");
  if(sensor[0]==0 && sensor[1]== 0)
    Serial.println("all sensons are not on the black line");
}
/*test led*/
void led_on()
{
  //turn on led
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  Serial.println("turn on led");
}
void led_off()
{
  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  Serial.println("turn off led");
}
/*tets servo*/
void test_servo()
{
  Serial.println("servo is ok!");
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    head.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    head.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  head.write(90);//go to centre position
}
/*tets HC-SR04*/
void test_hc_sr04()
{
  long howfar;
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);
  howfar = pulseIn(echo, HIGH);
  howfar = howfar * 0.01657; //how far away is the object in cm
  Serial.print("distance:");
  Serial.print(howfar);
  Serial.println(" cm");
}
/*tets buzzer*/
void test_buzzer()
{
  digitalWrite(buzzer, LOW);//turn on buzzer
  delay(300);
  digitalWrite(buzzer, HIGH);//turn off buzzer
  Serial.println("buzzer is ok!");
}
/*robot go ahead*/
void go_ahead()
{
  //set motor spped
  analogWrite(ENA,255); 
  analogWrite(ENB,255);
  //motor go ahead
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
}
/*robot go back*/
void go_back()
{ 
  //set motor spped
  analogWrite(ENA,255); 
  analogWrite(ENB,255);
  //motor go back
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW); 
}
/*robot stop*/
void go_stop()
{
  //change the speed to 0 to stop the motor
  analogWrite(ENA,0); 
  analogWrite(ENB,0);
}
/*test IR receiver*/
void test_ir()
{
  if(IR.decode(&IRresults))
  {
    Serial.println(IRresults.value, HEX);
    IR.resume();
  } 
}
