#include <Arduino.h>
#include <TM1637Display.h>


#define CLK D2
#define DIO D3
#define OKU D1
#define UP D4
#define DOWN D6
#define SIL D5

TM1637Display display(CLK, DIO);

int SAYIM = 0;
int OKUDURUM = HIGH;
int DEGER = 0;
int SAY = 0;
bool ISLEM = false;
unsigned long eskiZaman = 0;
unsigned long yeniZaman;

void setup() {
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);
  display.setSegments(data);
  delay(1000);
  display.clear();
  pinMode(OKU, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(SIL, INPUT_PULLUP);
}

void loop() {
  yeniZaman = millis();
  display.showNumberDec(SAYIM, false); 
  DEGER=digitalRead(SIL);
  OKUDURUM = digitalRead(OKU);
      if (OKUDURUM == LOW){
      delay(10);
      SAYIM ++ ;
      display.showNumberDec(SAYIM, false);
      eskiZaman = yeniZaman;
      display.setBrightness(0x0f);
        while(OKUDURUM == LOW){
             OKUDURUM = digitalRead(OKU);
             delay(10);
             if(digitalRead(UP) == LOW){
             eskiZaman = yeniZaman;
             display.setBrightness(0x0f);
             SAYIM ++ ;
             display.showNumberDec(SAYIM, false);
                while(digitalRead(UP) == LOW){
               delay(10); 
                  }
              }
                      
              if(digitalRead(DOWN) == LOW){
              eskiZaman = yeniZaman;
              display.setBrightness(0x0f);
              SAYIM -- ;
                if(SAYIM < 0){
                  SAYIM = 0;
                }
                display.showNumberDec(SAYIM, false);
                while(digitalRead(DOWN) == LOW){
                delay(10); 
              }
            
                }
          delay(100);
          }
        }

  
  if((yeniZaman - eskiZaman) >600000){
    display.setBrightness(7, false);

  }
 else if ((yeniZaman - eskiZaman) >300000){
    display.setBrightness(1);
  }

  if(digitalRead(UP) == LOW){
    eskiZaman = yeniZaman;
    display.setBrightness(0x0f);
    SAYIM ++ ;
    display.showNumberDec(SAYIM, false);
    while(digitalRead(UP) == LOW){
    delay(10); 
  }

}

  if(digitalRead(DOWN) == LOW){
    eskiZaman = yeniZaman;
    display.setBrightness(0x0f);
    SAYIM -- ;
    if(SAYIM < 0){
      SAYIM = 0;
    }
    display.showNumberDec(SAYIM, false);
    while(digitalRead(DOWN) == LOW){
    delay(10); 
  }

}
while(DEGER == LOW){
  delay(1000);
  SAY++;
  DEGER=digitalRead(SIL);
  ISLEM = true;
  eskiZaman = yeniZaman;
  display.clear();
  display.setBrightness(0x0f);
  display.showNumberDec(SAY, true, 2, 2);
}
  if(ISLEM == true){
    if(SAY >0 && SAY>3){
      SAYIM = 0;
    }
    SAY=0;
    ISLEM=false;
    
  }

  if(SAYIM > 9999)
  SAYIM=0;
}
