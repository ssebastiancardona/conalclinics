#include <SPI.h>
#include <nRF24L01.h>             
#include <RF24.h>            

const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
const uint64_t pipeIn = 0xE8E8F0F0E2LL;
const byte addresses[][6] = {"00001", "00002"};
RF24 radio(9, 10); // select  CSN and CE  pins

int boton = 5;
int ledBoton_1 = 3;
int apagarLamparas = 0;

struct MyData {
  int apagarLamparas;
  int alertaEnfermera;  
};
MyData data;


void setup()
{
  //Start everything up
  Serial.begin(9600);
  pinMode(boton, INPUT);
  pinMode(ledBoton_1, OUTPUT);
  digitalWrite(boton, HIGH);
  digitalWrite(ledBoton_1, HIGH);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  radio.openReadingPipe(1,pipeIn);
  //radio.openWritingPipe(addresses[1]);
  //radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
}

unsigned long lastRecvTime = 0;
void recvData()
{
  radio.startListening();
  while ( radio.available() )
  {
    Serial.print("While Estado de lampara: "); Serial.println(data.alertaEnfermera);
    radio.read(&data, sizeof(MyData));
    lastRecvTime = millis(); //here we receive the data
    if(data.alertaEnfermera == 1){
    Serial.print("Estado de lampara: "); Serial.println(data.alertaEnfermera);  
    digitalWrite(ledBoton_1, HIGH);
    }    
  }
}


void loop()
{
 recvData();
  
  if(digitalRead(boton)== LOW){
    radio.stopListening();
    //delay(100);
    apagarLamparas = apagarLamparas;
    digitalWrite(ledBoton_1, LOW);
    radio.write(&data, sizeof(MyData));
    Serial.print("Boton presionado: "); Serial.println(data.apagarLamparas);
    //delay(100);
    radio.startListening();
  }  
}