#define LFSensor_1 A0 //line follow sensor1
#define LFSensor_2 A1 //line follow sensor2

void setup() {
    /*line follow sensors */
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop(){
    //print info
    int senL = analogRead(A0);
    int senR = analogRead(A1);
    
    Serial.print(senL);
    Serial.print(senR);
    Serial.print('\n');
    delay (1000);
}