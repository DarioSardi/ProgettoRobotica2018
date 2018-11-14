String readString,odometry;
int dim=0;
int x=0;
void setup() {
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  
    
}

/*
//funzionante con la read
void loop(){
  Serial.println("Son viva");
  delay(5000);
  
}
*/
void loop() {
    while(Serial.available()){
    delay(3);  //delay to allow buffer to fill
    if (Serial.available()>0) {
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
      dim++;
    }}
    readString[dim-1]=0; //deleting \n on recived string
    if (readString.length()>0) {
       if(readString=="ciao"){
           Serial.println("ciao anche a te"); //see what was received
        }
       else {Serial.print("il comando :-"); Serial.print(readString); Serial.print("- non è riconosciuto\n");}
       digitalWrite(12,HIGH);
       delay(1000);
       digitalWrite(12,LOW);
  }
  dim=0;
  readString="";
}
