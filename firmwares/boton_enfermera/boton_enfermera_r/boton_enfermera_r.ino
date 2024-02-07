#include <SPI.h>
#include <nRF24L01.h>             
#include <RF24.h>            

const uint64_t pipeIn = 0xE8E8F0F0E1LL; 
const uint64_t pipeOut = 0xF8E8F0F0E1LL;

RF24 radio(9, 10); 
struct MyData {
  int boton_1;
  int boton_2;
  const int apagar = 0;
};
MyData data;
int LED = 3;
int led_boton_1 = 5;

void setup()
{ 
  Serial.begin(9600);
  pinMode(led_boton_1, INPUT_PULLUP); //LED CULERO PANTALLA PUESTO DE ENFERMERIA 
  pinMode(LED,OUTPUT);   
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openWritingPipe(pipeOut);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

/******Reset the received data to 0 if connection is lost******/
unsigned long lastRecvTime = 0;
void recvData()
{
  while ( radio.available() )
  {
    radio.read(&data, sizeof(MyData));
    lastRecvTime = millis(); 
  
  }
}
/**************************************************************/

void loop()
{
recvData();
if(digitalRead(led_boton_1) == LOW){
   radio.write(&data, sizeof(MyData));
  }  

}
