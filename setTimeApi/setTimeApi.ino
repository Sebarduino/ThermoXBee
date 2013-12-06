#include <DS1302.h>
#include "PowerCommand.h"

DS1302 rtc(2, 3, 4);

Time t;
PowerCommand pc;

int led = 13;

void allumeLed(char *args) {
 digitalWrite(led, HIGH); 
}

void eteintLed(char *args) {
 digitalWrite(led, LOW); 
}

void setTime(char *args) {
	int jour,mois,annee,heure,minute,seconde,jourSemaine;
	sscanf(args,"%d %d/%d/%d %d:%d:%d",&jourSemaine,&jour,&mois,&annee,&heure,&minute,&seconde);
	rtc.setDOW(jourSemaine);
	rtc.setTime(heure, minute, seconde);
	rtc.setDate(jour, mois, annee);
}

void getTime(char *args) {
	char str[20];
	t = rtc.getTime();
	sprintf(str, "%02d/%02d/%02d %02d:%02d:%02d\n", t.date, t.mon, t.year, t.hour, t.min, t.sec);
	Serial.print(str);
}


void setup() {                
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setTCR(TCR_D1R2K);
  pinMode(led, OUTPUT);     
  Serial.begin(9600);
  pc.add("ALLUMER",allumeLed);
  pc.add("ETEINDRE",eteintLed);
  pc.add("setTime",setTime);
  pc.add("getTime",getTime);
}

void loop() {
	pc.listen();

}


