#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel led1 = Adafruit_NeoPixel(30, 7, NEO_GRB + NEO_KHZ800);
int sensor = A0;
int relay = 13;
int SWITCH = 0;

void setup() {
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  led1.begin();
  led1.show();
}

void loop() {
  // Man

  int percent = 100 - ((analogRead(sensor) - 260) / 3.4);
  Serial.print(analogRead(sensor));
  Serial.print("   ");
  Serial.println(percent);

  if (percent >= 80) {    //Tat tuoi
    digitalWrite(relay, LOW);
    if (SWITCH == 1) {
      for (int i = led1.numPixels() - 1; i >= 0; i--) {
        led1.setPixelColor(i, led1.Color(0, 0, 0));
        led1.show();
        delay(100);
      }
      SWITCH = 0;
    }
  }

  if (percent <= 35) {
    digitalWrite(relay, HIGH);
    if (SWITCH == 0) {
      for (int i = 0; i < led1.numPixels(); i++) {
        led1.setPixelColor(i, led1.Color(0, 255, 0));
        led1.show();
        delay(100);
      }
      SWITCH = 1;
    }


    //    rainbow(20);
  }

  delay(1000);
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

void rainbow(uint8_t wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < led1.numPixels(); i++) {
      led1.setPixelColor(i, Wheel((i + j) & 255));
    }
    led1.show();
    delay(wait);
  }
}
