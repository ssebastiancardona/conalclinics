#include "DHT.h"
#define DHTPIN 26
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

struct servoMoveMessage
{
   float t;
   float h;
   float tt;
   float hh;
};

float tt;
float hh;
int gatillo = 2;
int recepcion = 16;
 
struct servoMoveMessage message;

//////////////////////////////////////////////////////////
void recieveStructure(byte *structurePointer, int structureLength)
{
  if(Serial.available() < sizeof(message)) return;
  Serial.readBytes(structurePointer, structureLength);
  Serial.print("temperatura enviada por el Arduino    ");
  Serial.println(tt);
  Serial.print("Humedad enviada por el Arduino        ");
  Serial.println(hh);
}

////////////////////////////////////////////////////////

void sendStructure(byte *structurePointer, int structureLength)
{
    Serial.write(structurePointer, structureLength);
}

void setup()
{
  Serial.begin(9600);
  pinMode(gatillo, OUTPUT);
  digitalWrite(gatillo, HIGH);
  pinMode(recepcion, INPUT_PULLUP);
  digitalWrite(recepcion, HIGH);
  dht.begin();
  sendStructure((byte*)&message, sizeof(message));
  
}

void loop() 
{
    message.t = dht.readTemperature();
    message.h = dht.readHumidity();
    tt=message.tt;
    hh=message.hh;
    digitalWrite(gatillo, LOW);    
    sendStructure((byte*)&message, sizeof(message));
    digitalWrite(gatillo, HIGH);
    delay(500);
     //recieveStructure((byte*)&message, sizeof(message));
    //delay(100);
    /*if(digitalRead(recepcion)==LOW);{
   
    }    
    delay(500);*/
}