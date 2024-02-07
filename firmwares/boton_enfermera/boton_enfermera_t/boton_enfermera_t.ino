#include <SPI.h>
#include <nRF24L01.h>             
#include <RF24.h>            

const uint64_t pipeOut = 0xE8E8F0F0E1LL; 
const uint64_t pipeIn = 0xF8E8F0F0E1LL;

RF24 radio(9, 10); // select  CSN and CE  pins
struct MyData {
  int boton_1;
  int boton_2;
  const int apagar = 0;
};
MyData data;
int led_boton_1 = 2;
int led_boton_2 = 3;
int apagar_lamparas = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(led_boton_1, OUTPUT); //LED CULERO PANTALLA PUESTO DE ENFERMERIA
  pinMode(led_boton_2, OUTPUT); //LED CULERO PANTALLA PUESTO DE ENFERMERIA
  pinMode(apagar_lamparas, INPUT_PULLUP); //BOTON APAGADO LAMPARAS 

  digitalWrite(led_boton_1, LOW);
  digitalWrite(led_boton_2, LOW);

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

}

void recvData()
{
  while ( radio.available() )
  {
    radio.read(&data, sizeof(MyData));
    
    if (data.boton_1 == 1){
      digitalWrite(led_boton_1, HIGH);//enciende led llamado habitacion 1 en puesto de enfermeria
    }
    if (data.boton_2 == 1){
      digitalWrite(led_boton_2, HIGH);//enciende led llamado habitacion 2 en puesto de enfermeria
    }
  }
}


void loop(){

  recvData();

  if(digitalRead(apagar_lamparas) == LOW){
   radio.write(&data, sizeof(MyData));
  }  
  
}

  

