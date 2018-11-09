String readString;
void setup() {
  Serial.begin(9600);  
}


//funzionante con la read
void loop(){
  Serial.println("Son viva");
  delay(5000);
  
}
/*
void loop() {
   while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill
    if (Serial.available() >0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    }
   }
    if (readString.length() >0) {
       
       Serial.print("Ho letto: ");
       Serial.print(readString); //see what was received
  }
  readString="";
}*/
