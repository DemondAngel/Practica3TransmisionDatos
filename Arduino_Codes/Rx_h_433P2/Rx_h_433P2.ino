#include <SoftwareSerial.h>//defining the libraries for the RX
SoftwareSerial mySerial1(11, 10); // RX, TX//defining the pins to use 
int POL=25;//Polinomio predeterminado
int MSG;//variable para el mensaje a recibir
int ce=0;//variables para conteo de paquetes
int cc=0;
int ct=0;
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
      for(int i=indexOfU+1; i<indexOfU+12;i++){//because we were using 40 chars
        mensajeStringOk += mensajeString[i];//concatenate the data received
        j++;   
      }
      Serial.print("El mensaje recibido de CRC es: ");
      Serial.println(mensajeStringOk); //we print in the serial monitor the data received
      MSG=mensajeStringOk.toInt();//Transformamos el mensaje crc recibido a Int
      //Serial.print("Mensaje Int antes de crc:");
      //Serial.println(MSG);
  //Parte del CRC
      int lenPol = lengthBit(POL);
      int lenMsg = lengthBit(MSG) - lenPol;
      int frameForXor = MSG >> lenPol;
      while(lenMsg > 0){
        int num = 0;
        int frameXor = frameForXor ^ POL;
        int lenFrameXor = lengthBit(frameXor);
        int bitsMissings = lenPol - lengthBit(frameXor);
        frameXor = frameXor << bitsMissings;
        for(int i = 0, j=lenMsg-1; i < bitsMissings; i++, j--){
          if(bitRead(MSG, j) == 1)
            num += pow(2, bitsMissings-i-1);
            lenMsg--;
            }
        frameForXor = frameXor ^ num;   
  } 

     int error = frameForXor ^ POL;
     if(error == 0){
        //Serial.println("Esta chido");
        //Serial.print("Residuo");
        //Serial.println(error, BIN); 
      }
      else{
        if((MSG>>lenPol-1)==0){
        //Serial.println("No pa ta mal");
        ce++;//Conteo de paquetes incorrectos
          }else{
        Serial.print("Temperatura: ");
        Serial.print(MSG>>lenPol-1);
        Serial.println("°C");
        cc++;//Conteo de paquetes correctos
            }
        }
      ct=cc+ce;//Conteo de paquetes totales enviados
      Serial.print("Paquetes recibidos: ");
      Serial.println(ct);
      Serial.print("Paquetes correctos: ");
      Serial.println(cc);
      Serial.print("Paquetes incorrectos: ");
      Serial.println(ce);
      Serial.println("");
    } 
 delay(80); //40 chars... 40x8=320bits... 320 bits/2400bps =  133ms-150ms for the time of receiving
 mensajeString = "";//space for every message 
 mensajeStringOk = "";
}
//FUNCIONES COMPLEMENTARIAS
bool crc_fec(int message){
  return false;
}

int lengthBit(int value){
  int len = 0;
  while(value>1){
    value = value/2;
    len+=1;
  }
  len += 1;
  return len;
}
