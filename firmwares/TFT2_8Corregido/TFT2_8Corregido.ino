#include <TouchScreen.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
//#include <Adafruit_MLX90614.h>
#include <Wire.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 195
#define TS_MINY 190
#define TS_MAXX 907
#define TS_MAXY 935

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


int dataGas[6];
int antGas[6];
boolean BE = true;
int posx = 15, posy = 50;
int i = 0;



void setup(void) {
  Serial.begin(9600);
  Wire.begin();
  tft.reset();
  tft.begin(0x9325);
  tft.setRotation(3);
  tft.fillScreen(BLUE);
  //tft.drawRoundRect(5, 20, 310, 35, 15, TFT_BLACK);
  tft.fillRect(30, 7, 260, 57, WHITE);
  tft.fillCircle(30, 35, 28, WHITE);
  tft.fillCircle(288, 35, 28, WHITE);

  tft.fillRect(30, 70, 260, 57, WHITE);
  tft.fillCircle(30, 98, 28, WHITE);
  tft.fillCircle(288, 98, 28, WHITE);

  tft.fillRect(30, 133, 260, 57, WHITE);
  tft.fillCircle(30, 161, 28, WHITE);
  tft.fillCircle(288, 161, 28, WHITE);

  tft.fillRect(30, 195, 260, 42, WHITE);
  tft.fillCircle(30, 216, 20, WHITE);
  tft.fillCircle(288, 216, 20, WHITE);

  //tft.fillCircle(52, 41, 17, WHITE);
  //tft.fillRect(0, 60, 319, 4, BLUE);
  //tft.fillRect(0, 120, 319, 4, BLUE);
  //tft.fillRect(0, 180, 319, 4, BLUE);

  /*tft.fillRect(210, 20, 80, 38, GREEN);
  tft.fillCircle(210, 39, 18, GREEN);
  tft.fillCircle(290, 39, 18, GREEN);*/

  /*tft.setCursor(215, 29);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("MUTE");*/

  /*tft.setCursor(55, 38);
  tft.setTextColor(BLUE);    tft.setTextSize(2);
  tft.println("onalclinics");*/

  tft.setCursor(25, 20);
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.print("OXI");
  tft.setCursor(205, 27);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("MAX 70 psi");
  tft.setCursor(205, 40);
  tft.print("MIN 40 psi");

  tft.setCursor(25, 85);
  tft.setTextColor(BLACK);
  tft.setTextSize(4);
  tft.print("NIT");
  tft.setCursor(205, 90);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("MAX 140 psi");
  tft.setCursor(205, 103);
  tft.print("MIN 110 psi");

  tft.setCursor(25, 147);
  tft.setTextColor(YELLOW);
  tft.setTextSize(4);
  tft.print("MED");
  tft.setCursor(205, 155);
  tft.setTextColor(BLACK);
  tft.setTextSize(1);
  tft.print("MAX 70 psi");
  tft.setCursor(205, 168);
  tft.print("MIN 40 psi");

}

void loop(void) {
 //double timer = millis() + ;
 Serial.println(posx);
 Serial.println(posy);
  TSPoint p = ts.getPoint();
  if (p.z > 700) {
    posx = p.x;
    posy = p.y;
    if (posx > 30 && posx < 340 && posy > 230 && posy < 15) {
      if (BE == true) {
        BE = false;
      } else {
        BE = true;
      }
    }
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    testText();
  } else {
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
/*
    Wire.requestFrom(69, 6);    // request 6 bytes from slave device #8
    i = 0;
    while (Wire.available()) { // slave may send less than requested
      byte idosdato = Wire.read(); // receive a byte as character
      dataGas[i] = idosdato;
      i++;
      Serial.print("El dato numero ");         // print the character
      Serial.print(i);
      Serial.print(" es:   ");
      Serial.println(dataGas[i]);         // print the character
    }*/
    
    delay(500);

    //tft.fillRect(115, 80, 90, 30, WHITE);
    tft.setCursor(115, 20);
    tft.setTextColor(GREEN);
    tft.setTextSize(4);
    tft.print(dataGas[0]);

    //Dato que varía en el segundo renglon

    //tft.fillRect(115, 140, 90, 30, WHITE);
    tft.setCursor(115, 85);
    tft.setTextColor(BLACK);
    tft.setTextSize(4);
    tft.print(dataGas[1]);

    //Dato que varía en el tercer renglon

    //tft.fillRect(115, 190, 90, 30, WHITE);
    tft.setCursor(115, 147);
    tft.setTextColor(YELLOW);
    tft.setTextSize(4);
    tft.print(dataGas[2]);

  }
}



void testText() {
  // dataox  = map(sensorValue, 0, 1023, 0, 100);
  //Dato que varía en el primer renglon
  if (BE == false) {
    tft.fillRect(30, 195, 260, 42, RED);
    tft.fillCircle(30, 216, 20, RED);
    tft.fillCircle(288, 216, 20, RED);
    tft.setCursor(209, 29);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("AUDIO");
  } else {
    tft.fillRect(30, 195, 260, 42, GREEN);
    tft.fillCircle(30, 216, 20, GREEN);
    tft.fillCircle(288, 216, 20, GREEN);
    tft.setCursor(75, 205);
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.print("SILENCIAR");
  }

}
