#include <Arduino.h>
String readString,odometry;
int dim=0;
int x=01;
void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  //Serial.println(millis());
    
}

/*
//funzionante con la read
void loop(){
  Serial.println("Son viva");
  delay(500);
}
*/

void loop() {
    int time=0;
    while(Serial.available()){
    time=millis();
    delay(3);  //delay to allow buffer to fill
    if (Serial.available()>0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
      dim++;
    }}
    readString[dim-1]=0; //deleting \n on recived string
    if (readString.length()>0) {
       if(readString=="ciao"){
           delay(1000);
           Serial.println("ciao anche a te"); //see what was received
           digitalWrite(13,HIGH);
           delay(1000);
           digitalWrite(13,LOW);
        }
       else {delay(1000);Serial.println("comando sconosciuto");}
       
  }
  dim=0;
  readString="";
  if(time>0){
  int res=millis()-time;}
  //Serial.println("comando sconosciuto");
  //Serial.print("---risposta inviata da arduino in: "); Serial.print(res);Serial.print(" millisecondi\n");}
}
