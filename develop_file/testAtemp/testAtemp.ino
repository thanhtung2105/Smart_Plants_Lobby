#include <math.h>

int sensorPin = A5; // select the input pin for the potentiometer
int warn = 8;

double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0*((1024.0/RawADC-1))); 
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  return Temp;
}

void setup() {
  Serial.begin(9600);
  pinMode(warn,OUTPUT);
}

void loop() {
  int readVal=analogRead(sensorPin);
  int temp =  Thermistor(readVal);
  Serial.print(temp);  // display tempature
  Serial.println("\337C");
  if(temp>30)
  {
    digitalWrite(warn,HIGH);
  }
  else
  digitalWrite(warn,LOW);
  delay(500);
}
