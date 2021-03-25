//FM Radio OLED Copyright by GhostLion v1.6 GOLD

#include <EEPROM.h>
#include <radio.h>
#include <RDA5807M.h>

#include "U8glib.h"
#include "rus6x10.h"
#include "MyDigitsHelveticaBold24.h"

#define Pin_DOWN 4   // левая кнопка 
#define Pin_UP 2     // правая кнопка 
#define Pin_SET 3    // центральная кнопка
#define FIX_BAND 1

const uint8_t Radio [] U8G_PROGMEM = {0x3F, 0xFF, 0xFF, 0xFF, 0xFC, 0x40, 0x00, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0xC0, 0x01, 0x80,0x00, 0x00, 0xC0, 0x01, 0x8E, 0x88, 0x00, 0xC0, 0x01, 0x88, 0xD8, 0x00, 
0xC0, 0x01, 0x88, 0xA8,0x00, 0xC0, 0x01, 0x8C, 0xA8, 0x00, 0xC0, 0x01, 0x88, 0xA8, 0x00, 0xC0, 0x01, 0x80, 0x00, 0x00,0xC0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x81, 0x04, 0x10, 0x41, 0x05, 0x81, 0x04, 0x10, 
0x41,0x05, 0x95, 0x55, 0x55, 0x55, 0x55, 0x95, 0x55, 0x55, 0x55, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80,0x00, 0x00, 
0xF8, 0x01, 0x80, 0x00, 0x03, 0xFE, 0x01, 0x80, 0x00, 0x07, 0x03, 0x01, 0x80, 0x00,0x0C, 0x01, 0x81, 0x80, 0x60, 0x18, 0x00, 0xC1, 0x81, 0xF8, 0x18, 0x00, 0x41, 0x83, 0x9C, 0x10,0x00, 0x61, 0x83, 0x0C, 0x30, 
0x00, 0x61, 0x83, 0x0C, 0x30, 0x00, 0x61, 0x83, 0x0C, 0x30, 0x00,0x61, 0x83, 0x9C, 0x10, 0x00, 0x61, 0x81, 0xF8, 0x18, 0x00, 0x41, 0x80, 0x60, 0x18, 0x00, 0xC1,0x80, 0x00, 0x0C, 0x01, 0x81, 0x80, 0x00, 0x07, 
0x03, 0x01, 0x80, 0x00, 0x03, 0xFE, 0x01, 0x80,0x00, 0x00, 0xF8, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00,0x00, 0x00, 0x02, 0x3F, 0xFF, 0xFF, 0xFF, 0xFC};

const uint8_t Volume[] U8G_PROGMEM = {0x7E, 0x42, 0x81, 0x81, 0x81, 0x81, 0xE7, 0xE7, 0x66, 0x66};
const uint8_t Bass[] U8G_PROGMEM = {0x7F, 0xFE, 0x80, 0x01, 0x9B, 0x8D, 0xA2, 0x51, 0xA3, 0x91, 0x9A, 0x4D, 0x8A, 0x45, 0xB3, 0x99,0x80, 0x01, 0x7F, 0xFE};
const uint8_t FM[] U8G_PROGMEM = {0x7F, 0xFE, 0x80, 0x01, 0x8C, 0x51, 0x90, 0xA9, 0x90, 0xA9, 0x98, 0xA9, 0x90, 0xA9, 0x90, 0x89,0x80, 0x01, 0x7F, 0xFE};
const uint8_t Stereo[] U8G_PROGMEM = {0x7F, 0xFE, 0x80, 0x01, 0x9B, 0xB9, 0xA1, 0x25, 0xA1, 0x39, 0x99, 0x31, 0x89, 0x29, 0xB1, 0x25,0x80, 0x01, 0x7F, 0xFE};
const uint8_t SM[] U8G_PROGMEM = {0x7F, 0xFE, 0x80, 0x01, 0x8C, 0x51, 0x90, 0xA9, 0x90, 0xA9, 0x8C, 0xA9, 0x84, 0xA9, 0x98, 0x89,0x80, 0x01, 0x7F, 0xFE};

const uint8_t Bat1[] U8G_PROGMEM = {0x7F, 0xFC, 0x80, 0x02, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01,0x80, 0x02, 0x7F, 0xFC};
const uint8_t Bat2[] U8G_PROGMEM = {0x7F, 0xFC, 0x80, 0x02, 0xA0, 0x01, 0xA0, 0x01, 0xA0, 0x01, 0xA0, 0x01, 0xA0, 0x01, 0xA0, 0x01,0x80, 0x02, 0x7F, 0xFC};
const uint8_t Bat3[] U8G_PROGMEM = {0x7F, 0xFC, 0x80, 0x02, 0xA8, 0x01, 0xA8, 0x01, 0xA8, 0x01, 0xA8, 0x01, 0xA8, 0x01, 0xA8, 0x01,0x80, 0x02, 0x7F, 0xFC};
const uint8_t Bat4[] U8G_PROGMEM = {0x7F, 0xFC, 0x80, 0x02, 0xAA, 0x01, 0xAA, 0x01, 0xAA, 0x01, 0xAA, 0x01, 0xAA, 0x01, 0xAA, 0x01,0x80, 0x02, 0x7F, 0xFC};
const uint8_t Bat5[] U8G_PROGMEM = {0x7F, 0xFC, 0x80, 0x02, 0xAA, 0x81, 0xAA, 0x81, 0xAA, 0x81, 0xAA, 0x81, 0xAA, 0x81, 0xAA, 0x81,0x80, 0x02, 0x7F, 0xFC};
const uint8_t Bat6[] U8G_PROGMEM = {0x7F, 0xFC, 0x80, 0x02, 0xAA, 0xA1, 0xAA, 0xA1, 0xAA, 0xA1, 0xAA, 0xA1, 0xAA, 0xA1, 0xAA, 0xA1,0x80, 0x02, 0x7F, 0xFC};
const uint8_t Bat7[] U8G_PROGMEM = {0x7F, 0xFC, 0x80, 0x02, 0xAA, 0xA9, 0xAA, 0xAD, 0xAA, 0xAD, 0xAA, 0xAD, 0xAA, 0xAD, 0xAA, 0xA9,0x80, 0x02, 0x7F, 0xFC};

const uint8_t Vol1[] U8G_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x60, 0x00, 0x60, 0x00};
const uint8_t Vol2[] U8G_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x0C, 0x00,0x6C, 0x00, 0x6C, 0x00};
const uint8_t Vol3[] U8G_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x01, 0x80, 0x0D, 0x80, 0x0D, 0x80,0x6D, 0x80, 0x6D, 0x80};
const uint8_t Vol4[] U8G_PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x30, 0x01, 0xB0, 0x01, 0xB0, 0x0D, 0xB0, 0x0D, 0xB0,0x6D, 0xB0, 0x6D, 0xB0};
const uint8_t Vol5[] U8G_PROGMEM = {0x00, 0x06, 0x00, 0x06, 0x00, 0x36, 0x00, 0x36, 0x01, 0xB6, 0x01, 0xB6, 0x0D, 0xB6, 0x0D, 0xB6,0x6D, 0xB6, 0x6D, 0xB6};

byte v,k,m,rs, flag1=1,flag2=0,flag3=0;
int Voltage;
unsigned int s,s2;
boolean b,ms,sm,flag=1,MODE=1;
long TimeOut;

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);
RDA5807M radio; 

void setup()
{
pinMode(Pin_DOWN,INPUT_PULLUP);
pinMode(Pin_UP,INPUT_PULLUP);
pinMode(Pin_SET,INPUT_PULLUP); 

Inicial();
}

void loop()
{
Parsing();
Menu();
Energy();  
}
//==============================================
void Inicial()
{
 u8g.firstPage();  
do {
  u8g.drawBitmapP (5, 16, 5, 40, Radio);
  u8g.setFont(rus6x10);
  u8g.setPrintPos(40,11);u8g.print(F("FM Radio"));
  u8g.setPrintPos(55,45);u8g.print(F("v 1.6 GOLD"));
  u8g.setPrintPos(55,55);u8g.print(F("By GhostLion"));  
   }
while( u8g.nextPage() );

delay(1500);
if (EEPROM[0]!=1)
    {
     EEPROM[0]=1;
     EEPROM[1]=5;
     EEPROM[2]=9; // здесь установить номер текущего канала (моя частота 98.90 "Русское радио") (или 0)
     EEPROM[3]=1;
     EEPROM[4]=1;
     EEPROM[5]=0;
     EEPROM[6]=98;  // частота текущей радиостанции
     EEPROM[7]=90;  // "Русское радио"
     EEPROM[8]=1;
    }
v  = EEPROM[1];               // громкость
k  = EEPROM[2];               // текущий канал
m  = EEPROM[3];               // текущее меню
b  = EEPROM[4];               // супербасс
ms = EEPROM[5];               // моно/стерео
s  = EEPROM[6]*100+EEPROM[7]; // текущая частота
sm = EEPROM[8];               // softmute
s2=s;
radio.init();
radio.setVolume(v);
radio.setMono(ms);
radio.setMute(false);
radio.setBassBoost(b);
radio.setSoftMute(sm);  
radio.setBandFrequency(FIX_BAND, s);
readVcc();
}
//================================================
void Parsing()
{
boolean SET=digitalRead(Pin_SET);
boolean UP=digitalRead(Pin_UP);
boolean DOWN=digitalRead(Pin_DOWN);

if(SET==HIGH && flag1==0)
  {
    flag1=1;
  }
if(SET==LOW && flag1==1)
  {
    flag1=0;
    TimeOut=millis();
    if(MODE==1) {m++; flag=1; if(m>7) m=1;}
  }
  
 if(UP==LOW && flag2==1)
  {
    flag2=0;
  }
   if(UP==HIGH && flag2==0)
   {
    if(MODE==1)
    {
    switch(m)
      {
        case 1:{ (v==15?0:v++); radio.setVolume(v); break; }
        case 2:{ b = 1; radio.setBassBoost(b); radio.setBandFrequency(FIX_BAND,s); break; }
        case 3:{ ms = 0; radio.setMono(ms); radio.setBandFrequency(FIX_BAND,s); break; }
        case 4:{sm = 1; radio.setSoftMute(true);radio.setBandFrequency(FIX_BAND,s); break;}
        case 5:{ radio.seekUp(true); delay(3000); s = radio.getFrequency(); Kanal(); break; }
        case 6:{ s=s+10; if (s > 10800) s = 8700; delay(100); radio.setBandFrequency(FIX_BAND,s);Kanal(); break; }
        case 7:{ k++; if (k>23) k=1; Frequency(); radio.setBandFrequency(FIX_BAND,s); break;}
      }
   flag=1;
   TimeOut=millis();
    }
   else {(v==15?0:v++);radio.setVolume(v);}
   flag2=1;
   }
   if(DOWN==LOW && flag3==1)
  {
    flag3=0;
  }
   if(DOWN==HIGH && flag3==0)
   {
    if(MODE==1)
    {
    switch(m)
      {
        case 1:{ (v==0?15:v--); radio.setVolume(v); break; }
        case 2:{ b = 0; radio.setBassBoost(b); radio.setBandFrequency(FIX_BAND,s); break; }
        case 3:{ ms = 1; radio.setMono(ms); radio.setBandFrequency(FIX_BAND,s); break; }
        case 4:{sm = 0; radio.setSoftMute(false);radio.setBandFrequency(FIX_BAND,s); break;}
        case 5:{ radio.seekDown(true); delay(3000); s=radio.getFrequency(); Kanal(); break; }
        case 6:{ s=s-10; if (s<8700) s=10800; delay(100); radio.setBandFrequency(FIX_BAND,s); Kanal(); break; }
        case 7:{ k--; if (k<1) k=23; Frequency(); radio.setBandFrequency(FIX_BAND,s); break;}
      }
   flag=1;
   TimeOut=millis();
   }
   else {(v==0?15:v--);radio.setVolume(v);}
   flag3=1;
  }
}
//================================================
void Menu()
{
float ch;
if(flag==1 && MODE==1)
{
rs = radio.getRSSI();   
ch=float(s)/100; 
u8g.firstPage();  
do {
u8g.setDefaultForegroundColor();
if(Voltage>85) u8g.drawBitmapP (110, 0, 2, 10, Bat7);
  else if(Voltage>70) u8g.drawBitmapP (110, 0, 2, 10, Bat6);
  else if(Voltage>55) u8g.drawBitmapP (110, 0, 2, 10, Bat5);
  else if(Voltage>40) u8g.drawBitmapP (110, 0, 2, 10, Bat4);
  else if(Voltage>25) u8g.drawBitmapP (110, 0, 2, 10, Bat3);
  else if(Voltage>10) u8g.drawBitmapP (110, 0, 2, 10, Bat2);
  else u8g.drawBitmapP (110, 0, 2, 10, Bat1);
u8g.drawBitmapP (0, 0, 1, 10, Volume);
if(v<3) u8g.drawBitmapP (13, 0, 2, 10, Vol1);
  else if(v<7) u8g.drawBitmapP (13, 0, 2, 10, Vol2);
  else if(v<10) u8g.drawBitmapP (13, 0, 2, 10, Vol3);
  else if(v<13) u8g.drawBitmapP (13, 0, 2, 10, Vol4);
  else u8g.drawBitmapP (13, 0, 2, 10, Vol5);
if(ms==0) u8g.drawBitmapP (55, 0, 2, 10, Stereo);
if(b==1) u8g.drawBitmapP (75, 0, 2, 10, Bass);
if(sm==1) u8g.drawBitmapP (35, 0, 2, 10, SM);

u8g.setFont(MyDigitsHelveticaBold24);
if(ch<100) u8g.setPrintPos(30,43); else u8g.setPrintPos(23,43);
u8g.print(ch,1);
u8g.setFont(rus6x10);
u8g.print(" MHz");
if (rs>43) u8g.drawBitmapP (0, 16, 2, 10, FM); 
if(k!=0){
    u8g.drawRFrame (0,32,18,13,2);
    u8g.setPrintPos(3,42);
    if(k<10) u8g.print("0");
    u8g.print(k);
        }
u8g.drawRFrame (0,51,127,12,3);
u8g.setPrintPos(13,61);
 switch(m)
 {
  case 1: {u8g.print(F("- <   VOLUM   > +"));break;}
  case 2: {u8g.print(F(" NU  < BASS > DA"));break;}
  case 3: {u8g.print(F("NU  < STEREO > DA"));break;}
  case 4: {u8g.print(F("NU  < S.MUTE > DA"));break;}
  case 5: {u8g.print(F(" <  AUTO TUNE  >"));break;}
  case 6: {u8g.print(F("< MANUAL TUNE >"));break;}
  case 7: {u8g.print(F("  <  CANALE  >"));break;}
 
 }


}
while( u8g.nextPage() );     
  flag=0;    
}
}
//================================================
void Energy()
{
 if(MODE==1 && millis()-TimeOut>2000) flag=1;
 if(MODE==1 && millis()-TimeOut>8000)
  {
   // u8g.sleepOn(); 
   u8g.sleepOn(); 
    MODE=0;
    if(v!= EEPROM[1]) EEPROM[1] = v;
    if(k!= EEPROM[2]) EEPROM[2] = k;
    if(m!= EEPROM[3]) EEPROM[3] = m;
    if(b!= EEPROM[4]) EEPROM[4] = b;
    if(ms!=EEPROM[5]) EEPROM[5] = ms;
    if(s2!=s){s2=s;   EEPROM[6] = int(s/100); 
                      EEPROM[7] = s%100;
             }
    if(sm!=EEPROM[8]) EEPROM[8] = sm;         
  }
  if(MODE==0 && millis()-TimeOut<500)
  {
    u8g.sleepOff(); 
    readVcc();
    MODE = 1; 
    flag = 1; 
    m = 7;
  }
}
//===================================================
void readVcc() 
{
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring
  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both
  long result = (high << 8) | low;

  result = 1.080 * 1023 * 1000 / result; // расчёт реального VCC
  Voltage = int(result);
  Voltage = map(Voltage, 3200, 4200, 0, 100);
  Voltage = constrain(Voltage, 0, 100);
}
//=======================================================
void Kanal()
{
  switch (s)
  {
    case 8750 : k=1;break;
    case 9240 : k=2;break;
    case 9370 : k=3;break;
    case 9410 : k=4;break;
    case 9620 : k=5;break;
    case 9740 : k=6;break;
    case 9800 : k=7;break;
    case 9840 : k=8;break;
    case 9890 : k=9;break;
    case 9950 : k=10;break;
    case 10040: k=11;break;
    case 10110: k=12;break;
    case 10170: k=13;break;
    case 10210: k=14;break;
    case 10250: k=15;break;
    case 10290: k=16;break;
    case 10370: k=17;break;
    case 10460: k=18;break;
    case 10510: k=19;break;
    case 10570: k=20;break;
    case 10620: k=21;break;
    case 10710: k=22;break;
    case 10790: k=23;break;
    default: k=0;
    
  }
}
//==========================================================
void Frequency()
{
 switch(k)
  {
    case 1 :{s=8750;break;}
    case 2 :{s=9370;break;}
    case 3 :{s=8750;break;}
    case 4 :{s=9410;break;}
    case 5 :{s=9620;break;}
    case 6 :{s=9740;break;}
    case 7 :{s=9800;break;}
    case 8 :{s=9840;break;}
    case 9 :{s=9890;break;}
    case 10 :{s=9950;break;}
    case 11 :{s=10010;break;}
    case 12 :{s=10120;break;}
    case 13 :{s=10170;break;}
    case 14 :{s=10210;break;}
    case 15 :{s=10250;break;}
    case 16 :{s=10290;break;}
    case 17 :{s=10370;break;}
    case 18 :{s=10460;break;}
    case 19 :{s=10510;break;}
    case 20 :{s=10570;break;}
    case 21 :{s=10620;break;}
    case 22 :{s=10710;break;}
    case 23 :{s=10790;break;}
  } 
}
