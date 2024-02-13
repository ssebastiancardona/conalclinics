#include <SPI.h>
#include <nRF24L01.h>             
#include <RF24.h>            

const uint64_t pipeOut = 0xE8E8F0F0E2LL;
const uint64_t pipeIn = 0xE8E8F0F0E1LL;
const byte addresses[][6] = {"00001", "00002"};
RF24 radio(7, 5); // select  CSN and CE  pins // 9 y 10 en nano
struct MyData {
  int apagarLamparas;  
  int alertaEnfermera ; 
};
int boton = 2;
int LED = 3;
int alertaEnfermera = 1;
MyData data;

void setup()
{  
  pinMode(LED,OUTPUT);
  pinMode(boton,INPUT_PULLUP);
  digitalWrite(LED, LOW);

  Serial.begin(9600); 
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  radio.openWritingPipe(pipeOut);
  radio.startListening();
}

/******Reset the received data to 0 if connection is lost******/
unsigned long lastRecvTime = 0;
void recvData()
{
  while ( radio.available() ) 
  {
    radio.read(&data, sizeof(MyData));
    lastRecvTime = millis(); //here we receive the data
    if(data.apagarLamparas == 0 && digitalRead(LED) == HIGH){
    Serial.print("Estado de lampara: "); Serial.println(data.apagarLamparas);  
    digitalWrite(LED,data.apagarLamparas);
    }    
  }
}
/**************************************************************/

void loop()
{
recvData();

if(digitalRead(boton) == LOW){
    radio.stopListening();
    //delay(100);
    data.alertaEnfermera = alertaEnfermera;
    digitalWrite(LED, HIGH);
    radio.write(&data, sizeof(MyData));
    Serial.print("Boton presionado:  "); Serial.println(data.alertaEnfermera);
    delay(100);
    radio.startListening();
}


}