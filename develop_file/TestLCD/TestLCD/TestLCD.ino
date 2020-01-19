#include <tinyFAT.h>
#include <UTFT.h>
#include <UTFT_tinyFAT.h>


// Declare which fonts we will be using
extern uint8_t SmallFont[];

UTFT myGLCD(QD220A, A2, A1, A5, A4, A3);
UTFT_tinyFAT myFiles(&myGLCD);

char* files220[] = {"1.RAW", "2.RAW", "3.RAW", "4.RAW", "5.RAW", "6.RAW", "7.RAW", "8.RAW", "9.RAW", "4.RAW"};
char* files[10];

int picsize_x, picsize_y;
boolean display_rendertime = false;
boolean display_filename = true;
word res;
long sm, em;

void setup()
{
  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.clrScr();
  file.initFAT();
  myGLCD.setColor(255, 255, 255);
  myGLCD.setFont(SmallFont);
  picsize_x = myGLCD.getDisplayXSize();
  picsize_y = myGLCD.getDisplayYSize();
  for (int z = 0; z < sizeof(files220) / sizeof(*files220); z++)
    files[z] = files220[z];
}

void loop()
{
  int channel;
  channel = random(1, 9);
  for(channel=0;channel<10;channel++)
  {
    sm = micros();
    res = myFiles.loadBitmap(0, 0, picsize_x, picsize_y, files[channel]);
    em = micros();
    if (res != 0)
    {
      if (res == 0x10)
      {
        myGLCD.print("The nho loi roi!!", 0, 0);
        myGLCD.print(files[channel], 0, 14);
      }
      else
      {
        myGLCD.print("ERROR: ", 0, 0);
        myGLCD.printNumI(res, 56, 0);
      }
      delay(1500);
      myGLCD.clrScr();
    }
    else
    {
      if (display_rendertime == true)
      {
        myGLCD.print("Rendertime (secs):", 0, 0);
        myGLCD.printNumF(float((em - sm) / 1000.0), 2, 160, 0);
      }
//              if (display_filename == true)
//              {
//                myGLCD.print(files[i], CENTER, myGLCD.getDisplayYSize() - 12);
//              }
      delay(1500);
    }
  }
    myGLCD.clrScr();
}
