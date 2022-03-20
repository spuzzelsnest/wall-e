//WALL*E
// Libraries
#include <Servo.h>

// Controlls
int incomingByte = 0;

// Motor parts
#define SERVO 11    // Motor on pin D11
#define IN1 8       // Motor direction on pin D8
#define IN2 9       // Motor direction on pin D9
#define IN3 10      // Motor direction on pin D10
#define IN4 12      // Motor direction on pin D12
#define ENA 5       // PWM pin ENA speed
#define ENB 6       // PWM pin ENB speed

// Tools
#define LSNS A0     // Light sensor left pin A0
#define RSNS A1     // Light sensor right pin A1
#define BUZZER 13   // Buzzer on pin D13
#define LED1 0      // left led connect to D0
#define LED2 2      // right led connect to D2

#define trig A2     // 
#define echo A3     // Head Motor
Servo head;

void goForward(){
  Serial.println("Forward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void goBack(){
  Serial.println("Reverse");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void goStop(){
  Serial.println("Stop the Vehicle");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); 
}

void goLeft(){
  Serial.println("Left");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void goRight(){
  Serial.println("Right");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void setSpeed(int lspeed,int rspeed){
  analogWrite(ENA,lspeed);
  analogWrite(ENB,rspeed);
}

void buzzOn(){
  digitalWrite(BUZZER, LOW);
}
void buzzOff(){
  digitalWrite(BUZZER, HIGH);
}

void lightsOn(){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
}

void lightsOff(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void alarm(){
  buzzOn();
  delay(100);
  buzzOff();
}

int watch(){
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

void setup(){

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  setSpeed(255,255);

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, HIGH);
  buzzOff();

  head.attach(SERVO);
  head.write(90);

  Serial.begin(9600);
  Serial.println("Wall*E ready");
}

void loop() {

  if (Serial.available() > 0) {
   
    int inByte = Serial.read();        // read the incoming byte:
    Serial.print("I received: ");
    Serial.println(inByte, DEC);   // say what you got
  
    switch (inByte){

	case 'w':
	  goForward(),delay(500);
	  break;
	case 's':
	  goBack(),delay(500);
	  break;
	case 'a':
	  goLeft(),delay(500);
	  break;
	case 'd':
	  goRight(),delay(500);
	  break;
	case 'q':
	  goStop();
	  break;
	default:
	  goStop();
    }
  }
}
