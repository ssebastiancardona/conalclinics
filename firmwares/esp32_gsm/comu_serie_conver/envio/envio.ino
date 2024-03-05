#include "DHT.h"
#define DHTPIN 26
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


struct servoMoveMessage
{
   float t;
   float h;
   int numero;
};

int numero;
 
struct servoMoveMessage message;

//////////////////////////////////////////////////////////
void recieveStructure(byte *structurePointer, int structureLength)
{
  if(Serial.available() < sizeof(message)) return;
  Serial.readBytes(structurePointer, structureLength);
}

////////////////////////////////////////////////////////

void sendStructure(byte *structurePointer, int structureLength)
{
    Serial.write(structurePointer, structureLength);
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  sendStructure((byte*)&message, sizeof(message));
}

void loop() 
{
    message.t = dht.readTemperature();
    message.h = dht.readHumidity();
    numero = message.numero;
    sendStructure((byte*)&message, sizeof(message));
    delay(1000);
}