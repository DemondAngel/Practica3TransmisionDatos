#include <SoftwareSerial.h>//defining the libraries for the RX
SoftwareSerial mySerial1(9, 10); // RX, TX//defining the pins to use 

void setup() {
  // Begin the Serial at 9600 Baud
  Serial.begin(9600);
  mySerial1.begin(2400);//Receiver
}
String mensajeString;//defining the messages for the receiver
String mensajeStringOk;
char caracter;//the flag character used for the data

void loop() {
  while(mySerial1.available()) {//Reading what is sent by the transmitter and adding the characters   
    if (mySerial1.available() > 0){    
        caracter = mySerial1.read();          
        mensajeString += caracter;
    }   
  }
    int indexOfU = mensajeString.indexOf('U'); //defining the flag character for every pack of data
    if(indexOfU > 0){//if we receive data with the correct flag, it is going to be read
      int j = 0;
      for(int i=indexOfU+1; i<indexOfU+15;i++){//because we were using 40 chars
        mensajeStringOk += mensajeString[i];//concatenate the data received
        j++;   
      }
      Serial.println("El mensaje recibido es: ");
      Serial.println(mensajeStringOk); //we print in the serial monitor the data received
    }   
 delay(80); //40 chars... 40x8=320bits... 320 bits/2400bps =  133ms-150ms for the time of receiving
 mensajeString = "";//space for every message 
 mensajeStringOk = "";
}
