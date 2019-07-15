
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

#define NBRRELAI 7

// Define my lights
#define SALON                     0
#define HALL_BAS                  1
#define CUISINE_CENTRAL           2
#define CUISINE_PLAN_DE_TRAVAIL   3
#define EXTERIEUR_JARDIN          4
#define EXTERIEUR_DEVANT          5
#define CAVE                      6

#define NBRSW 12
// Define my light switch
#define SALON_1        0
#define SALON_2        1
#define CUISINE_1      2
#define CUISINE_2      3
#define CUISINE_3      4
#define CUISINE_4      5
#define HALL_1         6
#define HALL_2         7
#define HALL_3         8
#define HALL_4         9
#define TOILETTE_1     10
#define TOILETTE_2     11

#define DHTPIN 31
#define DHTTYPE DHT22


#include <DS3231.h>
//#include <DHT.h>

#include <pushbutton.h>
#include <Relay.h>

Relay relay[NBRRELAI] = { Relay(22), // SALON 
                          Relay(23), // HALL_BAS
                          Relay(24), // CUISINE_CENTRAL
                          Relay(25), // CUISINE_PLAN_DE_TRAVAIL
                          Relay(26), // EXTERIEUR_JARDIN
                          Relay(27), // EXTERIEUR_DEVANT 
                          Relay(28) // CAVE
                          };

PushButton pushButton[NBRSW] = { PushButton(42, SALON_1), 
                                 PushButton(43, SALON_2), 
                                 PushButton(44, CUISINE_1),
                                 PushButton(45, CUISINE_2),
                                 PushButton(46, CUISINE_3),
                                 PushButton(47, CUISINE_4),
                                 PushButton(48, HALL_1),
                                 PushButton(49, HALL_2),
                                 PushButton(50, HALL_3),
                                 PushButton(51, HALL_4),
                                 PushButton(52, TOILETTE_1),
                                 PushButton(53, TOILETTE_2),
                                 };

char inData[32];
char inChar = -1;
byte index = 0;

//unsigned long dhtTime = 0;

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);

//DHT dht(DHTPIN, DHTTYPE);

Time t;
unsigned long sendTime = 0;

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  Serial1.begin(115200);

  // Initialize the rtc object
  //rtc.begin();

  // Initialize the DHT object
  //dht.begin();
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 8, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(20, 11, 2016);   // Set the date to January 1st, 2014
  
  for(int i = 0; i < NBRRELAI; ++i) relay[i].begin();
  for(int i = 0; i < NBRSW; ++i) pushButton[i].setCallback(on_pushButton_pushed);
}

void loop()
{
  processMessage();

  for(int i = 0; i < NBRSW; ++i) pushButton[i].read();

/*  if (dhtTime + 4000 < millis()) { // Max every 2 sec
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
  }*/

  if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
  }

}

void on_pushButton_pushed(int id)
{
  //Serial.print("pushButton ");
  //Serial.print(id);
  //Serial.println(" pressed");
  switch (id) {
    case SALON_1:
      relay[SALON].invertState();
      break;
    case SALON_2:
      Serial.print("SALON_2 pressed ");
      Serial.print("CUISINE_CENTRAL "); Serial.print(relay[CUISINE_CENTRAL].getState());
      if (relay[CUISINE_CENTRAL].getState() || relay[CUISINE_PLAN_DE_TRAVAIL].getState()) {
        Serial.println(" turn off");
         relay[CUISINE_CENTRAL].turnOff();
         relay[CUISINE_PLAN_DE_TRAVAIL].turnOff();
      } else {
        Serial.println(" turn on");
        relay[CUISINE_CENTRAL].turnOn();
         relay[CUISINE_PLAN_DE_TRAVAIL].turnOn();        
      }
      break;
    case CUISINE_1:
      relay[SALON].invertState();
      break;
    case CUISINE_2:
      relay[EXTERIEUR_JARDIN].invertState();
      break;
    case CUISINE_3:
      relay[CUISINE_CENTRAL].invertState();
      break;
    case CUISINE_4:
      relay[CUISINE_PLAN_DE_TRAVAIL].invertState();
      break;
    case HALL_1:
      relay[HALL_BAS].invertState();
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
        relay[id].turnOn();
        //Serial.write(" on");
      }
      if (0 <= id && id <= NBRRELAI && inData[9] == 'o' && inData[10] == 'f' && inData[11] == 'f') {
        relay[id].turnOff();
        //Serial.write (" off");
      }
      //Serial.println("");
    }
  } 
  // cmd: &get time$
/*  else if (inData[0] == 'g' && inData[1] == 'e' && inData[2] == 't' && inData[3] == ' ' && inData[4] == 't'
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
  }*/
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
