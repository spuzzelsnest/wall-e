#define LFSensor_1 A0 //line follow sensor1
#define LFSensor_2 A1 //line follow sensor2

void setup() {
  /*line follow sensors */
    sensor[0]=digitalRead(LFSensor_1);
    sensor[1]=digitalRead(LFSensor_2);
    Serial.begin(9600);
}

void loop() {
    Serial.println("");
}