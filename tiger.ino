#define LFSensor_1 A0 //line follow sensor1
#define LFSensor_2 A1 //line follow sensor2

void setup() {
    /*line follow sensors */
    Serial.begin(9600);
}

void loop(){
    //print info
    int data = Serial.read(LFSensor_1);
    Serial.println(data);
    delay (1000);
}