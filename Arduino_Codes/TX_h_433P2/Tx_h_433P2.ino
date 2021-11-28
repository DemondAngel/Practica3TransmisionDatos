#include <SoftwareSerial.h>
#include <DHT.h>
SoftwareSerial mySerial1(11, 10); // RX, TX (Transmitter)
#define PDHT 15
#define TYDH DHT11
int TEMP;
int HUM;
String TEMP1;
String HUM1;
DHT dht (PDHT, TYDH);

void setup()
{
  dht.begin();
  Serial.begin(9600); //Serial monitor
  mySerial1.begin(2400); // transmitter
}

void loop()
{
  TEMP = dht.readTemperature();
  HUM = dht.readHumidity();
  if(isnan(TEMP) || isnan(HUM)){
    Serial.println("Error of data");
    return;
  }

  Serial.print("Mensaje: ");
  Serial.println(TEMP);
  Serial.println(" ");

  TEMP = ProcedimientoCRC(TEMP);
  TEMP1 += TEMP;
  int n = 1;
  for(n; n<=3; n++){
    mySerial1.print("U");
    mySerial1.print(TEMP1);
  }
  Serial.print("Mensaje a transmitir: ");
  Serial.println(TEMP1);
  Serial.println(" ");
  TEMP1 = "";
  delay(80);//40 chars... 40x8=320bits... 320 bits/2400bps =  133ms-150ms
}

int ProcedimientoCRC(int message){
  int i;
  //int message = 22; //Mensaje que será leido del arduino
  int messagedesp = message << 4; //Mensaje desplazado el número de bits corresponientes a FCS
  int P=25;
  int pMSB; //Posición del Bit más significativo de P
  int mdMSB; //Posición del Bit más significativo del mensaje desplazado
  int mesTransmit; //Valor utilizado para condensar el mensaje a transmitir
  Serial.print("Mensaje: ");
  Serial.println(message,BIN);
  Serial.println("");
  Serial.print("Mensaje recorrido: ");
  Serial.println(messagedesp,BIN);
  Serial.println("");
  Serial.print("P: ");
  Serial.println(P);
  Serial.print("P: ");
  Serial.println(P, BIN);
  Serial.println("");
  mdMSB=MSB(messagedesp);
  pMSB=MSB(P);
  P = P << mdMSB-pMSB;//Corrimiento de P para empatar los MSB entre él y mensaje desplazado  
  mesTransmit = messagedesp ^ algoCRC(messagedesp,P);
  return mesTransmit;
}

int MSB(int message){
  int i;
  int MSBbuscado;
  if(message==0){
    printf("El mensaje no tiene MSB \n");
    return NULL;
  }else{
    for( i=16; i>0; i--){ //int tiene 16 bits
        if(bitRead(message,i-1) == 1){
            MSBbuscado = i-1;  
            i=0;
        }
      }
      return MSBbuscado;
  }
}

int algoCRC(int CRC, int P){
  int value=CRC;
  int Prec=P;
  if(MSB(CRC)<4||CRC==0){ 
  }else{
    value = CRC ^ Prec;
    Prec = P >> MSB(P)-MSB(value);
    value = algoCRC(value,Prec);
  }
  return value;
}
