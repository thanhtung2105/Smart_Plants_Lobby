#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
String text="Hello, world! I am Phan Thanh Tung";

void setup()
{
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print(text);
  
}

void loop()
{
  lcd.scrollDisplayRight();
  delay(500);
}
