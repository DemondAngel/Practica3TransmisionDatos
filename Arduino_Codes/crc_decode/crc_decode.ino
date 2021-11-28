int MSG = 400; // 195
int POL = 25;

void setup() {
  Serial.begin(9600);
  Serial.print("MSG: ");
  Serial.println(MSG, BIN);
}

void loop() { 
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

  if(error == 0)
    Serial.println("Esta chido");
  else
    Serial.println("No pa ta mal");

  Serial.print("Residuo");
  Serial.println(error, BIN);
 
  Serial.println("FCS: ");
  Serial.println(MSG>>lenPol-1);


  delay(1000);
  
}

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
