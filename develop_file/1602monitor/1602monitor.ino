#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int TemperSensor = A0;
int HumidSensor = A3;
int LED = 7;
int Relay = 6;
int i = 0;

String temp = "Temperature: ";
//String oC="\337C";
String humid = "Humidity: ";
String modeauto = "Mode: Auto ";
String modemanual = "Mode: Manual ";
String statusOK = "Status: OK ";
String statusChar = "Watering";

uint8_t oC[8]  = {0x08, 0x14, 0x08, 0x06, 0x09, 0x08, 0x09, 0x06};
uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t check[8] = {0x0, 0x1 , 0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};
uint8_t tree[8] = {0x04, 0x0E, 0x1F, 0x0E, 0x1F, 0x04, 0x04, 0x0E};

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  pinMode(LED, OUTPUT);
  pinMode(Relay, OUTPUT);

  lcd.createChar(0, bell);
  lcd.createChar(1, oC);
  lcd.createChar(2, clock);
  lcd.createChar(3, heart);
  lcd.createChar(4, retarrow);
  lcd.createChar(5, check);
  lcd.createChar(6, note);
}


void loop() {

  int HumidValue;
  int TemperValue;

  for (int i = 0; i < 17; i++)
  {
    lcd.scrollDisplayLeft();
    lcd.setCursor(3, 0);
    lcd.print("Physics and Computer Science");
    lcd.setCursor(5, 1);
    lcd.write(6);
    lcd.print(" YUMI Corporation ");
    lcd.write(6);
    delay(350);
  }

  while (i < 10)
  {
    HumidValue = (100 - ((analogRead(HumidSensor) - 260) / 3.4) );
    TemperValue = ((analogRead(TemperSensor)) * 5.0 / 1024) * 100;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(temp);
    lcd.print(TemperValue);
    lcd.write(1);
    lcd.setCursor(1, 1);
    lcd.print(humid);

    if (HumidValue > 0)
    {
      lcd.print(HumidValue);
      lcd.print("%");
      delay(500);
      lcd.clear();
    }
    else
    {
      lcd.print("0%");
      delay(500);
      lcd.clear();
    }
    i++;
  }
  lcd.clear();
  i = 0;

  lcd.setCursor(2, 0);
  lcd.print(modeauto);
  lcd.write(5);
  lcd.setCursor(1, 1);
  lcd.print(statusOK);
  while (i < 4)
  {
    lcd.setCursor(12, 1);
    lcd.print("^_^");
    delay(400);
    lcd.setCursor(12, 1);
    lcd.print(">_<");
    delay(400);
    lcd.setCursor(12, 1);
    lcd.print("^O^");
    delay(400);
    lcd.setCursor(12, 1);
    lcd.print("   ");
    delay(400);
    i++;
  }
  i = 0;
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print(modemanual);
  lcd.write(2);
  lcd.setCursor(1, 1);
  lcd.print(statusChar);
  while (i < 6)
  {
    lcd.setCursor(9, 1);
    lcd.print(".");
    delay(200);
    lcd.setCursor(9, 1);
    lcd.print("..");
    delay(200);
    lcd.setCursor(9, 1);
    lcd.print("...");
    delay(200);
    lcd.setCursor(9, 1);
    lcd.print("   ");
    delay(200);
    i++;
  }
  lcd.clear();
  i = 0;
}
