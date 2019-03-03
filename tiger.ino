#define LFSensor_1 A0 //line follow sensor1
#define LFSensor_2 A1 //line follow sensor2

void setup() {
    /*line follow sensors */
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop(){
    //print info
    int sensorValue = analogRead(A0);
    int data = Serial.read();
    Serial.println(data);
    Serial.print(sensorValue);
    delay (1000);
}