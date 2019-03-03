#define LFSensor_1 A0 //line follow sensor1
#define LFSensor_2 A1 //line follow sensor2

void read_sensor_values() {

  sensor[0]=digitalRead(LFSensor_1);
  sensor[1]=digitalRead(LFSensor_2);
}

void setup() {
  /*line follow sensors */
  pinMode(LFSensor_1,INPUT);
  pinMode(LFSensor_2,INPUT); 
  Serial.begin(9600);
}

void loop() {
    Serial.print(sensor[0]);
}