#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel led1 = Adafruit_NeoPixel(30, 7, NEO_GRB + NEO_KHZ800);

LiquidCrystal_I2C lcd(0x27, 16, 2);
int i = 0;

String temp = "Temperature: ";
//String oC="\337C";
String humid = "Humidity: ";
String modeauto = "Mode: Auto ";
String modemanual = "Mode: Manual ";
String statusOK = "Status: OK ";
String statusChar = "Watering . . .";

uint8_t oC[8]  = {0x08, 0x14, 0x08, 0x06, 0x09, 0x08, 0x09, 0x06};
uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t check[8] = {0x0, 0x1 , 0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  led1.begin();
  led1.show();

  lcd.createChar(0, bell);
  lcd.createChar(1, oC);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, retarrow);
  lcd.createChar(5, check);
  lcd.createChar(6, note);
}


void loop() {
  i = 0;
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(modemanual);
  lcd.write(2);
  lcd.setCursor(1, 1);
  lcd.print(statusChar);
  rainbow();
  lcd.clear();
  i = 0;
}

uint32_t Wheel(byte WheelPos) {
  if (WheelPos < 85) {
    return led1.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return led1.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return led1.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void rainbow() {
  int r, g, b;
  r = random(0, 255);
  g = random(0, 255);
  b = random(0, 255);
  for (int i = 0; i < led1.numPixels(); i++) {

    led1.setPixelColor(i, led1.Color(r, g, b));
    led1.show();
    delay(50);
  }
  for (int i = led1.numPixels(); i >= 0; i--) {
    led1.setPixelColor(i, led1.Color(0, 0, 0));
    led1.show();
    delay(10);
  }
}
