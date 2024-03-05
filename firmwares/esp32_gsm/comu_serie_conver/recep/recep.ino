struct servoMoveMessage
{
   float t;
   float h;
   int numero;
};

float t;
float h;
int numero;
 
struct servoMoveMessage message;

void recieveStructure(byte *structurePointer, int structureLength)
{
  if(Serial.available() < sizeof(message)) return;
  Serial.readBytes(structurePointer, structureLength);
  Serial.println("temperatura ");
  Serial.print(t);
  Serial.println("Humedad ");
  Serial.print(h);
  sendStructure((byte*)&message, sizeof(message));
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
  recieveStructure((byte*)&message, sizeof(message));
  sendStructure((byte*)&message, sizeof(message));
}

void loop() 
{
    t=message.t;
    h=message.h;
    //void recieveStructure(byte *structurePointer, int structureLength);
    recieveStructure((byte*)&message, sizeof(message));
    message.numero = numero++;
    
}