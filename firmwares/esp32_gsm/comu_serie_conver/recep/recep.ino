struct servoMoveMessage
{
   float t;
   float h;
   float tt =200;
   float hh =300;
};

float t;
float h;
int gatillo = 3;
int recepcion = 2;

struct servoMoveMessage message;

void recieveStructure(byte *structurePointer, int structureLength)
{
  if(Serial.available() < sizeof(message)) return;
  Serial.readBytes(structurePointer, structureLength);
  Serial.print("temperatura enviada por el esp_32    ");
  Serial.println(t);
  Serial.print("Humedad enviada por el esp_32        ");
  Serial.println(h);
}
//////////////////////////////////
void sendStructure(byte *structurePointer, int structureLength)
{
    Serial.write(structurePointer, structureLength);
}

///////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  pinMode(recepcion, INPUT_PULLUP);
  digitalWrite(recepcion, HIGH);
  recieveStructure((byte*)&message, sizeof(message));
  sendStructure((byte*)&message, sizeof(message));
}

void loop() 
{
    t=message.t;
    h=message.h;
    if(digitalRead(recepcion)==LOW){
      recieveStructure((byte*)&message, sizeof(message));  
    } 
   /* while(digitalRead(recepcion)==HIGH){            
      sendStructure((byte*)&message, sizeof(message));
      }   */ 
    
}