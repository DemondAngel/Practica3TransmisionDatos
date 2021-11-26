//Implement de CRC error detection with the P(X) =x^5 + x^2 + x + 1  , at the Rx and Tx
//P = 100111
//P = 



//declaring the libraries for the TX and RX and for the DHT11 Sensor
#include <DHT.h>
#include <SoftwareSerial.h>

SoftwareSerial mySeriall(11,10); // RX, TX (Transmitter)
#define PDHT 15 //define the pin of the sensor
#define TYDH  DHT11 //define type of the sensor
DHT dht(PDHT,TYDH);//initializin the sensor
float TEMP; //declaring variables for the sensor
float HUM;
String TEMP1;
String HUM1;

void setup()
{
  Serial.begin(9600); //Serial monitor
  mySeriall.begin(2400); // transmitter
}
int i;
void loop()
{
  int P = 9; //Sec predeterminada: 00000000 00001001 = x^3 + 1
  int Prec;
  int numberBitsMessage;
  int message; //DEBE SER LEÍDO DESDE EL SENSOR
  int pMSB;
  int messageMSB;
  
  dht.begin();//begining the sensor
  HUM=dht.readHumidity();//reading the humidity
  TEMP=dht.readTemperature();//reading the temperature
  if(isnan(HUM)||isnan(TEMP)){//checking an error in the sensor
    mySeriall.print("Error of the data");
    return;
    }  
  message = TEMP;
  Serial.print("Mensaje: ");
  Serial.println(message);
  //Serial.println(message, HEX);
  Serial.println(message, BIN);
  //Serial.println(message, DEC);
 
  Serial.print("P: ");
  Serial.println(P);
  //Serial.println(message, HEX);
  Serial.println(P, BIN);
   Serial.println("");
  int message2 = message << 3; //recorremos a la izq 3 bits de acuerdo a la sec pred. P=1001 
  
  Serial.println("Mensaje recorrido: ");
  //Serial.println(message2);
  //Serial.println(message2, HEX);
  Serial.println(message2, BIN);
  //Serial.println(message2, DEC);
  Serial.println("");
 for( i=15; i >= 0;i--){ //int tiene 16 bits
    //Serial.print("Bit "); Serial.print(i); Serial.print(" del mensaje es: "); Serial.println(bitRead(message2,i));
    //Serial.println(i);
    if(bitRead(message2,i) == 1)
      {
        Serial.println("Se detectó bit 1");
        Serial.print("El bit ");
        messageMSB = i+1;
        Serial.print(i+1);
        Serial.println(" es el MSB de message");
        Serial.print("El número de bits del mensaje son: ");
        Serial.print(i+1);
        i=0;

      }    
  }
  i=0;
   Serial.println("");
  for( i=15; i>=0;i--){ //int tiene 16 bits
    //Serial.print("Bit "); Serial.print(i); Serial.print(" de P es: "); Serial.println(bitRead(P,i));
    if(bitRead(P,i) == 1)
      {
        Serial.println("Se detectó bit 1");
        Serial.print("El bit ");
        pMSB = i+1;
        Serial.print(i+1);
        Serial.print(" es el MSB de P");
        Serial.print("El número de bits de la P son: ");
        Serial.print(i+1);
        i=0;

      }
 
    
  }
 Serial.println("");
  int CRC = message2; //bin 00000000 0000000; 
  int sumaXOR = 0;//bin 00000000 0000000;

  
  P = P << messageMSB-pMSB; //Recorrer la sec predeterminada a la Izq hasta el bit BSM del mensaje
  
  Serial.print("Secuencia predeterminada recorrida: "); 
  Serial.println(P,BIN); 
 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
     for( i=15; i >= 0;i--){ //int tiene 16 bits
    //Serial.print("Bit "); Serial.print(i); Serial.print(" del mensaje es: "); Serial.println(bitRead(message2,i));
    //Serial.println(i);
      if(bitRead(CRC,i) == 1)
        {
          Serial.println("Se detectó bit 1");
          Serial.print("El bit ");
          //messageMSB = i+1;
          numberBitsMessage = i+1;
          //Serial.print(i+1);
          //Serial.println(" es el MSB de message");
          //Serial.print("El número de bits del mensaje son: ");
          //Serial.print(numberBitsMessage);
          i=0;
  
        }    
    }

    Serial.print("El número de bits del mensaje son: ");
    Serial.println(numberBitsMessage);
    Prec = P >> messageMSB - numberBitsMessage;
    Serial.println(Prec);
    Serial.println(CRC);
    Serial.print("P:");
    
    Serial.println(Prec,BIN);
    CRC = CRC ^ Prec;   //Operacion CHOR
    Serial.println(CRC);
    Serial.println(CRC,BIN);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //numberBitsMessage = 7;// HACER: FUNCIÓN QUE CALCULE EL NÚMERO DE BITS HASTA EL MSB
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //numberBitsMessage = 8;// HACER: FUNCIÓN QUE CALCULE EL NÚMERO DE BITS HASTA EL MSB
     for( i=15; i >= 0;i--){ //int tiene 16 bits
    //Serial.print("Bit "); Serial.print(i); Serial.print(" del mensaje es: "); Serial.println(bitRead(message2,i));
    //Serial.println(i);
      if(bitRead(CRC,i) == 1)
        {
          Serial.println("Se detectó bit 1");
          Serial.print("El bit ");
          //messageMSB = i+1;
          numberBitsMessage = i+1;
          //Serial.print(i+1);
          //Serial.println(" es el MSB de message");
          //Serial.print("El número de bits del mensaje son: ");
          //Serial.print(numberBitsMessage);
          i=0;
  
        }    
    }
    Prec = P >> messageMSB - numberBitsMessage;
    Serial.print("P:");
    Serial.println(Prec,BIN);
    CRC = CRC ^ Prec;
    Serial.println(CRC,BIN);

    numberBitsMessage = 5;// HACER: FUNCIÓN QUE CALCULE EL NÚMERO DE BITS HASTA EL MSB
    Prec = P >> messageMSB - numberBitsMessage;
    Serial.print("P:");
    Serial.println(Prec,BIN);
    CRC = CRC ^ Prec;
    Serial.println(CRC,BIN);

    numberBitsMessage = 4; //termina, si igual o menor al núm de bits de P
    Prec = P >> messageMSB - numberBitsMessage;
    Serial.print("P:");
    Serial.println(Prec,BIN);
    CRC = CRC ^ Prec;
    Serial.println(CRC,BIN);

    
    ///EL MENSAJE A TRANSMITIR T = M + CRC;
    int T = message2  ^ CRC;
    Serial.println("MENSAJE A TRANSMITIR: ");
    Serial.println(T,BIN);
    
    //lo pasamos a String:
    String Tstring = String(T);
    Serial.println("MENSAJE A TRANSMITIR EN STRING: ");
    Serial.println(Tstring);

    
    
    Serial.println("");


  //anterior del codigo  
 
  //HUM1=String(HUM,3); //changing the float to char 
  TEMP1=Tstring;
  //Serial.print("Humedad: ");//printing in serial the data
  //Serial.println(HUM1);
  Serial.print("Temperatura: ");
  Serial.println(TEMP1);
  mySeriall.print("U");//The flag for the data obtained
  //mySeriall.print(HUM1);
  //mySeriall.print("\t");
  mySeriall.print(TEMP1);
  delay(80);//40 chars... 40x8=320bits... 320 bits/2400bps =  133ms-150ms
}
