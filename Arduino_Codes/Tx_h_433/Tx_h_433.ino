//declaring the libraries for the TX and RX and for the DHT11 Sensor
#include <DHT.h>
#include <SoftwareSerial.h>

SoftwareSerial mySeriall(9,10); // RX, TX (Transmitter)
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

void loop()
{
  dht.begin();//begining the sensor
  HUM=dht.readHumidity();//reading the humidity
  TEMP=dht.readTemperature();//reading the temperature
  if(isnan(HUM)||isnan(TEMP)){//checking an error in the sensor
    mySeriall.print("Error of the data");
    return;
    }  
  HUM1=String(HUM,3); //changing the float to char 
  TEMP1=String(TEMP,2);
  Serial.print("Humedad: ");//printing in serial the data
  Serial.println(HUM1);
  Serial.print("Temperatura: ");
  Serial.println(TEMP1);
  mySeriall.print("U");//The flag for the data obtained
  mySeriall.print("Humedad: ");//data transmitted
  mySeriall.print(HUM1);
  mySeriall.print(" %\t");
  mySeriall.print("Temperatura: ");
  mySeriall.print(TEMP1);
  mySeriall.print("*C");
  delay(150);//40 chars... 40x8=320bits... 320 bits/2400bps =  133ms-150ms
}
