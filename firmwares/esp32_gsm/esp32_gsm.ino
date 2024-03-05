#include <SoftwareSerial.h>

// Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(16, 17); // SIM800L RX & TX is connected to Arduino #2 & #3

void setup()
{
    // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
    Serial.begin(9600);

    // Begin serial communication with Arduino and SIM800L
    mySerial.begin(115200);

    Serial.println("Initializing...");
    delay(1000);

    mySerial.println("AT"); // Once the handshake test is successful, it will back to OK
    updateSerial();
}

void loop()
{
    updateSerial();
}

void updateSerial()
{
    delay(100);
    while (Serial.available())
    {
        mySerial.write(Serial.read()); // Forward what Serial received to Software Serial Port
    }
    while (mySerial.available())
    {
        Serial.write(mySerial.read()); // Forward what Software Serial received to Serial Port
    }
}