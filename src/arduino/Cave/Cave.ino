
// DS3231_Serial_Easy
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/

// Arduino Mega:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the DS3231 to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

#define NBRRELAI 26

// Define my lights
#define SALON_DEVANT              0
#define SALON_MILIEU              1
#define SALON_ARRIERE             2
#define HALL_BAS                  3
#define HALL_ENTREE               4
#define HALL_VESTIAIRE            5
#define CUISINE_CENTRAL           6
#define CUISINE_PLAN_DE_TRAVAIL   7
#define CUISINE_PLAQUE_CUISSON    8
#define BUANDERIE                 9
#define TOILETTE                  10
#define EXTERIEUR_CHEMIN_AVANT    11
#define EXTERIEUR_CHEMIN_ARRIERE  12
#define EXTERIEUR_ARRIERE         13
#define EXTERIEUR_GARAGE_ARRIERE  14
#define EXTERIEUR_GARAGE_AVANT    15
#define CHAMBRE_JB                16
#define SALLE_DE_DOUCHE_MIRROIR   17
#define SALLE_DE_DOUCHE_DOUCHE    18
#define SALLE_DE_DOUCHE_CENTRAL   19
#define SALLE_DE_DOUCHE_VENTILLATION 20
#define CHAMBRE_AMI               21
#define BUREAU                    22
#define DRESSING                  23
#define GRENIER                   24
#define CAVE                      25

#define NBRSW 4
// Define my light switch
#define SALON_HALL     1
#define SALON_CUISINE  2
#define HALL           3
#define CUISINE        4

#define DHTPIN 48
#define DHTTYPE DHT22


#include <DS3231.h>
#include <DHT.h>

#include <pushbutton.h>
#include <relay.h>

Relay relay[NBRRELAI] = { Relay(22, SALON_DEVANT), Relay(23, SALON_MILIEU), Relay(24, SALON_ARRIERE), 
                          Relay(25, HALL_BAS), Relay(26, HALL_ENTREE), Relay(27, HALL_VESTIAIRE), 
                          Relay(28, CUISINE_CENTRAL), Relay(29, CUISINE_PLAN_DE_TRAVAIL), Relay(30, CUISINE_PLAQUE_CUISSON), 
                          Relay(31, BUANDERIE), Relay(32, TOILETTE), 
                          Relay(33, EXTERIEUR_CHEMIN_AVANT), Relay(34, EXTERIEUR_CHEMIN_ARRIERE), Relay(35, EXTERIEUR_ARRIERE), 
                          Relay(36, EXTERIEUR_GARAGE_ARRIERE), Relay(37, EXTERIEUR_GARAGE_AVANT), 
                          Relay(38, CHAMBRE_JB),
                          Relay(39, SALLE_DE_DOUCHE_MIRROIR), Relay(40, SALLE_DE_DOUCHE_DOUCHE), Relay(41, SALLE_DE_DOUCHE_CENTRAL), 
                          Relay(42, SALLE_DE_DOUCHE_VENTILLATION),
                          Relay(43, CHAMBRE_AMI), Relay(44, BUREAU), Relay(45, DRESSING),
                          Relay(46, GRENIER), Relay(47, CAVE) };

PushButton pushButton[NBRSW] = { PushButton(50, SALON_HALL), 
                                 PushButton(51, SALON_CUISINE), 
                                 PushButton(52, HALL),
                                 PushButton(53, CUISINE)
                                 };

char inData[32];
char inChar = -1;
byte index = 0;

unsigned long dhtTime = 0;

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

DHT dht(DHTPIN, DHTTYPE);

Time t;
unsigned long sendTime = 0;

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  Serial1.begin(115200);

  // Initialize the rtc object
  rtc.begin();

  // Initialize the DHT object
  dht.begin();
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 8, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(20, 11, 2016);   // Set the date to January 1st, 2014

  for(int i = 0; i < NBRSW; ++i) pushButton[i].setCallback(on_pushButton_pushed);
}

void loop()
{
  processMessage();

  for(int i = 0; i < NBRSW; ++i) pushButton[i].read();

  if (dhtTime + 4000 < millis()) { // Max every 2 sec
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
    } else {
      float hi = dht.computeHeatIndex(t, h, false);
      float dp = dewPoint(t, h);
      Serial.print("Salon Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Salon Temperature: ");
      Serial.print(t);
      Serial.print(" °C\t");
      Serial.print("Salon Heat index: ");
      Serial.print(hi);
      Serial.print(" °C\t");
      Serial.print("Salon Dew point: ");
      Serial.print(dp);
      Serial.println(" °C");
    }
    dhtTime = millis();
  }

  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

}

void on_pushButton_pushed(int id)
{
  Serial.print("pushButton ");
  Serial.print(id);
  Serial.println(" pressed");
  switch (id) {
    case SALON_HALL:
    case SALON_CUISINE:
      relay[SALON_DEVANT].invertState();
      relay[SALON_MILIEU].invertState();
      relay[SALON_ARRIERE].invertState();
      break;
    case HALL:
      relay[HALL_BAS].invertState();
      relay[HALL_VESTIAIRE].invertState();
      break;
    case CUISINE:
      relay[CUISINE].invertState();
      break;        
    default:
      // if nothing else matches, do the default
      // default is optional
    break;
  }
}

void processMessage() {
  while (Serial.available() > 0) {
    if (index < 31) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      if (inChar == '&') {
        index = 0;
        return;
      }
      if (inChar == '$') {
        inData[index] = '\0';
        processCmd();
      }
      inData[index] = inChar; // Store it
      index++; // Increment where to write next
      inData[index] = '\0'; // Null terminate the string
    } else {
      index = 0;
    }
  }
}

void processCmd() {
  //Serial.println(inData);
  // cmd: &relay 8 on$
  if (inData[0] == 'r' && inData[1] == 'e' && inData[2] == 'l' && inData[3] == 'a' && inData[4] == 'y') {
    if (isDigit(inData[6]) && isDigit(inData[7])) {
      char charId[3] = {inData[6], inData[7]};
      int id = atoi(charId);
      //Serial.write("id "); Serial.print(id);
      if (0 <= id && id <= NBRRELAI && inData[9] == 'o' && inData[10] == 'n') {
        relay[id].setState(true);
        //Serial.write(" on");
      }
      if (0 <= id && id <= NBRRELAI && inData[9] == 'o' && inData[10] == 'f' && inData[11] == 'f') {
        relay[id].setState(false);
        //Serial.write (" off");
      }
      //Serial.println("");
    }
  } 
  // cmd: &get time$
  else if (inData[0] == 'g' && inData[1] == 'e' && inData[2] == 't' && inData[3] == ' ' && inData[4] == 't'
             && inData[5] == 'i' && inData[6] == 'm' && inData[7] == 'e'){
    t = rtc.getTime();
  
    // Send Day-of-Week
    Serial.print(rtc.getDOWStr());
    Serial.print(" ");
  
    // Send date
    Serial.print(rtc.getDateStr());
    Serial.print(" -- ");

    // Send time
    Serial.println(rtc.getTimeStr());
  }
  // cmd: &set time 16:47:30$
  else if (inData[0] == 's' && inData[1] == 'e' && inData[2] == 't' && inData[3] == ' ' && inData[4] == 't'
             && inData[5] == 'i' && inData[6] == 'm' && inData[7] == 'e'){
                if (isDigit(inData[9]) && isDigit(inData[10]) && isDigit(inData[12]) && isDigit(inData[13]) && isDigit(inData[15]) && isDigit(inData[16])) {
                  char charHour[3] = {inData[9], inData[10]};
                  int newHour = atoi(charHour);
                  char charMinute[3] = {inData[12], inData[13]};
                  int newMinute = atoi(charMinute);
                  char charSec[3] = {inData[15], inData[16]};
                  int newSec = atoi(charSec);
                  rtc.setTime(newHour, newMinute, newSec);
                  Serial.write("new time "); Serial.print(newHour); Serial.write(":");Serial.print(newMinute); Serial.write(":");Serial.print(newSec); Serial.println("");
              }
  }
}

double dewPoint(double celsius, double humidity)
{
  // (1) Saturation Vapor Pressure = ESGG(T)
  double RATIO = 373.15 / (273.15 + celsius);
  double RHS = -7.90298 * (RATIO - 1);
  RHS += 5.02808 * log10(RATIO);
  RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO ))) - 1) ;
  RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
  RHS += log10(1013.246);

  // factor -3 is to adjust units - Vapor Pressure SVP * humidity
  double VP = pow(10, RHS - 3) * humidity;

  // (2) DEWPOINT = F(Vapor Pressure)
  double T = log(VP / 0.61078); // temp var
  return (241.88 * T) / (17.558 - T);
}
