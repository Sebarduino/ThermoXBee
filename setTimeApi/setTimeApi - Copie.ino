#include <DS1302.h>

DS1302 rtc(2, 3, 4);

Time t;


int led = 13;
boolean modeBalise = false;
char balise[51];
int iBalise = 0;

void setup() {                
  rtc.halt(false);
  rtc.writeProtect(false);
  pinMode(led, OUTPUT);     
  Serial.begin(9600);
}

void allumeLed() {
 digitalWrite(led, HIGH); 
}






void loop() {
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    if(inByte != -1) {
      //Serial.println(inByte);
      if(modeBalise) {
        if(iBalise >= 50) {
          modeBalise = false;
        } else {
          switch (inByte) {
            case '>':
              balise[iBalise]='\0';
              modeBalise = false;
              break;
            default:
              balise[iBalise] = inByte;
              iBalise++;
              break;
          }
        }
        // traitement de la balise
        if(!modeBalise) {
          switch (balise[0]) {
            case 's':
              //int d = balise[1];
              break;
            case 'g':
              break;
            default:
              Serial.println(balise);
              break;
          }
        }
      } else {
        switch (inByte) {
          case 'a':
            allumeLed();
            break;
          case 'e':
            digitalWrite(led, LOW);
            break;
          case 'h':
            Serial.println("Hello World!");
            break;
          case '<':
            modeBalise = true;
            iBalise = 0;
            break;
          default:
            Serial.println(inByte);
            break;
        }
      }
    }
  }
}
/*
void setup()
{
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(9600);

  rtc.setDOW(SATURDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(9, 40, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(17, 11, 2012);   // Set the date to August 6th, 2010
}

void loop()
{
  // Get data from the DS1302
  t = rtc.getTime();
  
  // Send date over serial connection
  Serial.print(t.date, DEC);
  Serial.print("/");
  Serial.print(t.mon, DEC);
  Serial.print("/");
  Serial.print(t.year, DEC);
  
  // Send Day-of-Week and time
  Serial.print(" ");
  Serial.print(t.hour, DEC);
  Serial.print(":");
  Serial.print(t.min, DEC);
  Serial.print(":");
  Serial.print(t.sec, DEC);
  Serial.println();

  // Wait one second before repeating :)
  delay (1000);
}*/
