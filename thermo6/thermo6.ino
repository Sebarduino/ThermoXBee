#include <stdio.h>
#include <avr/pgmspace.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <DS1302.h>
/*  
*   Adresses sur EEPROM :
*   6 et 7 : durée de chauffage en cours
*   8 et 9 : durée de chauffage de Lundi
*   10 et 11 : durée de chauffage de Mardi
*   12 et 13 : durée de chauffage de Mercredi
*   14 et 15 : durée de chauffage de Jeudi
*   16 et 17 : durée de chauffage de Vendredi
*   18 et 19 : durée de chauffage de Samedi
*   20 et 21 : durée de chauffage de Dimanche
*/

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Initialisation du DS1302
DS1302 rtc(10, 11, 12);

// Initialisation de l'heure
byte heures;
byte minutes;
byte secondes;
byte jours;
const unsigned int uneSeconde = 999; // 999
/* 
*  0 : "Lundi";
*  1 : "Mardi";
*  2 : "Mercredi";
*  3 : "Jeudi";
*  4 : "Vendredi";
*  5 : "Samedi";
*  6 : "Dimanche";
*/

// Horaires de chauffage
const int nbHoraires = 12;

const prog_uint16_t horaireDebutJour[] PROGMEM = {     0,	0,	1,	1,	2,	2,	3,	3,	4,	4,	5,	6   };
const prog_uint16_t horaireFinJour[] PROGMEM = {       0,	0,	1,	1,	2,	2,	3,	3,	4,	4,	5,	6   };
const prog_uint16_t horaireDebutHeure[] PROGMEM = {    6,	17,	6,	17,	6,	17,	6,	17,	6,	17,	8,	8   };
const prog_uint16_t horaireDebutMinute[] PROGMEM = {   0,	30,	0,	30,	0,	30,	0,	30,	0,	30,	0,	0   };
const prog_uint16_t horaireFinHeure[] PROGMEM = {      7,	21,	7,	21,	7,	21,	7,	21,	7,	21,	21,	21  };
const prog_uint16_t horaireFinMinute[] PROGMEM = {    45,	30,	45,	30,	45,	30,	45,	30,	45,	30,	30,	30   };
const int horaireTemperature[] = {	             220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220 };

const prog_uint16_t horairePlusDebutJour[] PROGMEM = {     0,	1,	2,	3,	4,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6    };
const prog_uint16_t horairePlusFinJour[] PROGMEM = {       0,	1,	2,	3,	4,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6    };
const prog_uint16_t horairePlusDebutHeure[] PROGMEM = {    8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8,	8    };
const prog_uint16_t horairePlusDebutMinute[] PROGMEM = {   0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0    };
const prog_uint16_t horairePlusFinHeure[] PROGMEM = {      21,	21,	21,	21,	21,	21,	21,	23,	23,	23,	23,	23,	23,	23,	23,	23,	23   };
const prog_uint16_t horairePlusFinMinute[] PROGMEM = {     30,	30,	30,	30,	30,	30,	30,	59,	59,	59,	59,	59,	59,	59,	59,	59,	59   };
const int horairePlusTemperature[] = {	                 220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220,	220  };

const prog_uint16_t horaireMoinsDebutJour[] PROGMEM = {     0,	1,	2,	3,	4,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6    };
const prog_uint16_t horaireMoinsFinJour[] PROGMEM = {       0,	1,	2,	3,	4,	5,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6,	6    };
const prog_uint16_t horaireMoinsDebutHeure[] PROGMEM = {    7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7    };
const prog_uint16_t horaireMoinsDebutMinute[] PROGMEM = {   0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0    };
const prog_uint16_t horaireMoinsFinHeure[] PROGMEM = {      22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22,	22   };
const prog_uint16_t horaireMoinsFinMinute[] PROGMEM = {     0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0    };
const int horaireMoinsTemperature[] = {	                  180,	180,	180,	180,	180,	180,	180,	180,	180,	180,	180,	180,	180,	180,	180,	180,	180  };

//Optimisation des horaires
unsigned int horaireDebut[nbHoraires];
unsigned int horaireFin[nbHoraires];
unsigned int horairePlusDebut[nbHoraires];
unsigned int horairePlusFin[nbHoraires];
unsigned int horaireMoinsDebut[nbHoraires];
unsigned int horaireMoinsFin[nbHoraires];
unsigned int horaireEnCours;

const int temperatureParDefaut = 180;

// Temps de chauffage du jour
int dureeChauffage = 0;
int tabDureeChauffage[7];

// Horloge
unsigned long previousMillis = 0;
boolean debug = false;

// Moyenne de chauffage
const int maxMesures = 10;
int mesuresTemperature[maxMesures];
int nbMesures = 0;

const char* NOMS_JOURS[] = { "Lun","Mar","Mer","Jeu","Ven","Sam","Dim" };
const char SEPARATEUR[] = " - ";

// 0 : normal
// 1 : plus de chauffage +
// 2 : moins de chauffage -
// 3 : absence *
// 4 : vacances #
// 5 : consommation
int modeAffichage = 0;
int positionLcd = 0;

void setup() {
  lcd.begin(16, 2);
  if(debug) {
    Serial.begin(9600);
  }
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  
  // Lecture de l'heure sur le DS1302
  rtc.halt(false);
  rtc.writeProtect(false);
  Time t = rtc.getTime();
  rtc.setTCR(TCR_D1R2K);
  
  secondes = t.sec;
  minutes = t.min;
  heures = t.hour;
  jours = t.dow - 1;
  
  calculerOptimisationHoraires();
  
  dureeChauffage = EEPROMReadInt(6);
}

void loop() {
  unsigned long currentMillis = millis();
  //digitalWrite(13, LOW);
  
  if(currentMillis - previousMillis > uneSeconde) {
    previousMillis = millis();
    //digitalWrite(13, HIGH);
    
     if (digitalRead(A1) == HIGH) {
      modeAffichage++;
      if(modeAffichage >= 6) modeAffichage = 0;
    }
    
    uneSecondeDePlus();
    
    int therm = getTemperature();
    
    int cible = getTemperatureCible();
    
    // on peut changer d'état toutes les minutes
    if (secondes % 60 == 0) {
      if (therm < cible) {
        digitalWrite(8, HIGH);
        dureeChauffage ++;
        EEPROMWriteInt(6,dureeChauffage);
      } else {
        digitalWrite(8, LOW);
      }
    }
    
    affichage(cible, therm);
  }

}

void affichage(int cible, int therm) {
  if(debug) {
    Serial.print(availableMemory(), DEC);
    Serial.print(SEPARATEUR);
    Serial.print(getTime(heures,minutes,secondes,jours));
    Serial.print(SEPARATEUR);
    Serial.print(cible, DEC);
    Serial.print(SEPARATEUR);
    Serial.print(therm, DEC);
    Serial.print(SEPARATEUR);
    Serial.println(modeAffichage, DEC);
  }
  
  char myTemp[28];
  
  if(modeAffichage == 0 || modeAffichage == 1 || modeAffichage == 2 || modeAffichage == 3 || modeAffichage == 4) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(getTime(heures,minutes,secondes,jours));
    
    if(modeAffichage == 0) myTemp[0] = ' ';
    else if(modeAffichage == 1) myTemp[0] = '+';
    else if(modeAffichage == 2) myTemp[0] = '-';
    else if(modeAffichage == 3) myTemp[0] = '*';
    else if(modeAffichage == 4) myTemp[0] = '#';
    myTemp[1] = '\0';
    lcd.setCursor(15, 0);
    lcd.print(myTemp);
    
    lcd.setCursor(0, 1);
    sprintf(myTemp,"%d.%d",therm/10,therm%10);
    lcd.print(myTemp);
    
    lcd.setCursor(6, 1);
    sprintf(myTemp,"%d.%d",cible/10,cible%10);
    lcd.print(myTemp);
    
    lcd.setCursor(13, 1);
    sprintf(myTemp,"%03d",dureeChauffage);
    lcd.print(myTemp);
    
  } else if(modeAffichage == 5) {
    lcd.scrollDisplayLeft();
    
    lcd.setCursor(0, 0);
    sprintf(myTemp," %s %s %s %s %s %s %s",NOMS_JOURS[0],NOMS_JOURS[1],NOMS_JOURS[2],NOMS_JOURS[3],NOMS_JOURS[4],NOMS_JOURS[5],NOMS_JOURS[6]);
    lcd.print(myTemp);
    
    lcd.setCursor(0, 1);
    sprintf(myTemp," %03d %03d %03d %03d %03d %03d %03d",tabDureeChauffage[0],tabDureeChauffage[1],tabDureeChauffage[2],tabDureeChauffage[3],tabDureeChauffage[4],tabDureeChauffage[5],tabDureeChauffage[6]);
    lcd.print(myTemp);
  }
}

void calculerOptimisationHoraires() {
  for(int i=0;i<nbHoraires;i++) {
    horaireDebut[i] = pgm_read_word_near(horaireDebutJour + i) * 1440 + pgm_read_word_near(horaireDebutHeure + i) * 60 + pgm_read_word_near(horaireDebutMinute + i);
    horaireFin[i] = pgm_read_word_near(horaireFinJour + i) * 1440 + pgm_read_word_near(horaireFinHeure + i) * 60 + pgm_read_word_near(horaireFinMinute + i);
    horairePlusDebut[i] = pgm_read_word_near(horairePlusDebutJour + i) * 1440 + pgm_read_word_near(horairePlusDebutHeure + i) * 60 + pgm_read_word_near(horairePlusDebutMinute + i);
    horairePlusFin[i] = pgm_read_word_near(horairePlusFinJour + i) * 1440 + pgm_read_word_near(horairePlusFinHeure + i) * 60 + pgm_read_word_near(horairePlusFinMinute + i);
    horaireMoinsDebut[i] = pgm_read_word_near(horaireMoinsDebutJour + i) * 1440 + pgm_read_word_near(horaireMoinsDebutHeure + i) * 60 + pgm_read_word_near(horaireMoinsDebutMinute + i);
    horaireMoinsFin[i] = pgm_read_word_near(horaireMoinsFinJour + i) * 1440 + pgm_read_word_near(horaireMoinsFinHeure + i) * 60 + pgm_read_word_near(horaireMoinsFinMinute + i);
  }
  horaireEnCours = jours * 1440 + heures * 60 + minutes;
}

const int getTemperature() {
  int sensorValue = analogRead(A0);
  int maTemperature = 1000.0 * sensorValue * 5.0 / 1024;
  
  // cas ou on a pas beaucoup de mesures
  if(nbMesures < maxMesures) {
    mesuresTemperature[nbMesures] = maTemperature;
    nbMesures++;
  }
  
  // cas ou on a trop de mesures : on prend les n dernières
  else {
    for(int i=0; i<maxMesures-1; i++) {
      mesuresTemperature[i] = mesuresTemperature[i+1];
    }
    mesuresTemperature[maxMesures-1] = maTemperature;
  }
  
  // moyenne
  maTemperature = 0;
  for(int i=0; i<nbMesures; i++) {
    maTemperature += mesuresTemperature[i];
  }
  maTemperature = maTemperature / nbMesures;
  
  return maTemperature;
}

void uneSecondeDePlus() {
  secondes++;
  if(secondes >= 60) {
    secondes = 0;
    minutes++;
    horaireEnCours = jours * 1440 + heures * 60 + minutes;
  }
  if(minutes >= 60) {
    minutes = 0;
    heures++;
  }
  if(heures >= 24) {
    heures = 0;
    EEPROMWriteInt(8+(jours*2),dureeChauffage);
    tabDureeChauffage[jours] = dureeChauffage;
    dureeChauffage = 0;
    if(modeAffichage != 3 && modeAffichage != 4) {
      modeAffichage = 0;
    }
    jours++;
  }
  if(jours >= 7) {
    jours = 0;
  }

}

char* getTime(byte hh,byte mm,byte ss,byte jj) {
  char myTime[16];
  sprintf(myTime,"%s %02d:%02d:%02d",NOMS_JOURS[jj],hh,mm,ss);
  return myTime;
}

const int getTemperatureCible() {
  for(int i=0;i<nbHoraires;i++) {
    if(modeAffichage == 0 || modeAffichage == 5) {
      if ((horaireDebut[i] <= horaireEnCours) && (horaireFin[i] >= horaireEnCours)) {
        return horaireTemperature[i];
      }
    } else if(modeAffichage == 1 || modeAffichage == 4) {
      if ((horairePlusDebut[i] <= horaireEnCours) && (horairePlusFin[i] >= horaireEnCours)) {
        return horairePlusTemperature[i];
      }
    } else if(modeAffichage == 2 || modeAffichage == 3) {
      if ((horaireMoinsDebut[i] <= horaireEnCours) && (horaireMoinsFin[i] >= horaireEnCours)) {
        return horaireMoinsTemperature[i];
      }
    }
  }
  return temperatureParDefaut;
}

int availableMemory() {
  int size = 2048; // Use 2048 with ATmega328
  byte *buf;
  while ((buf = (byte *) malloc(--size)) == NULL)
    ;
  free(buf);
  return size;
}

//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void EEPROMWriteInt(int p_address, int p_value)
{
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);
  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int EEPROMReadInt(int p_address)
{
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);
  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}
