#include "Mouse.h"
#define vecLong 6
#define buzzer 2

int portAnal[4] = {A0 , A1, A2, A3};
int portDigi[2] = {14, 15};
int portVal[vecLong];
int enviado[vecLong];
double temp1 = millis();
int sensorValue = 0;
byte cadena[10];
String entrada;
bool alarma = false;
bool cambio = false;


void setup() {
  Serial.begin(9600);
 // Mouse.begin();
  for (int i = 0 ; i < 2; i++) {
    pinMode(portDigi[i], INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);
}

void loop() {
  leersensor();
  puerto();
  sound(alarma);
}

void sound(bool estado) {
  if (estado) {
    if (temp1 < millis()) {
      trocar();
      temp1 = millis() + 500;
    }

    if (cambio) {
      digitalWrite(buzzer, 1);
    }
    else {
      digitalWrite(buzzer, 0);
    }

  }else{
    digitalWrite(buzzer, 0);
  }

}

void trocar() {
  if (cambio) {
    cambio = false;
  } else {
    cambio = true;
  }
}

void puerto() {
  memset(cadena, 0, 9);

  if (Serial.available()) {
    Serial.readBytes(cadena, 10);
    for (int i = 0; i < 10 ; i++) {
      entrada = (entrada + (char)cadena[i]);
    }

    if (entrada == "mutegoooff") {
      alarma = true;
    }

    if (entrada == "mutegoooon") {
      alarma = false;
    }

    if (entrada == "sendmeData") {
      int sumai = 0;
      for (int i = 0; i < vecLong; i++) {
        if (portVal[i] != enviado[i]) {
          sumai++;
        }
      }
      if (sumai > 0) {
        Serial.println("todoquever");
        for (int i = 0; i < vecLong; i++) {
          Serial.println(portVal[i]);
          delay(20);
        }
        for (int i = 0; i < vecLong; i++) {
          enviado[i] = portVal[i];
        }
      } else {
        Serial.println("nadaquever");
      }
    }
  }
  entrada = "";
}


void leersensor() {
  for (byte i = 0; i < 4; i++) {
    portVal[i] = analogRead(portAnal[i]);
  }

  for (byte i = 0; i < 2; i++) {
    portVal[i + 4] = digitalRead(portDigi[i]);
  }
}
