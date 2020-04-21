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

#define SALON_DHT_PIN 2
#define DHTTYPE DHT22

#include <Wire.h>
#include <DS3231.h>
#include <DHT.h>

#include <pushbutton.h>
#include <relay.h>

Relay relay[NBRRELAI] = { Relay(22), // SALON 
                          Relay(23), // HALL_BAS
                          Relay(24), // CUISINE_CENTRAL
                          Relay(25), // CUISINE_PLAN_DE_TRAVAIL
                          Relay(26), // EXTERIEUR_JARDIN
                          Relay(27), // EXTERIEUR_DEVANT 
                          Relay(28)  // CAVE
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
byte arraySize = 0;

char inData2[32];
char inChar2 = -1;
byte arraySize2 = 0;

unsigned long dhtTime = 0;
unsigned long clockTime = 0;

// Init the DS3231 using the hardware interface
DS3231 Clock;
bool Century, H12 = false, PM;


DHT salondht(SALON_DHT_PIN, DHTTYPE);


void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200); // Grenier     // TX2: 17 (jaune) <-> RX2:16 (blanc)

  salondht.begin();
 
  // The following lines can be uncommented to set the date and time
  Wire.begin();
  //clock.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //clock.setTime(12, 8, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(20, 11, 2016);   // Set the date to January 1st, 2014
  
  for(int i = 0; i < NBRRELAI; ++i) relay[i].begin();
  for(int i = 0; i < NBRSW; ++i) pushButton[i].setCallbackClicked(on_pushButton_pushed);
}

void loop()
{
  processMessage();

  for(int i = 0; i < NBRSW; ++i) pushButton[i].read();

  if (dhtTime + 4000 < millis()) { // Max every 4 sec
    float h = salondht.readHumidity();
    float t = salondht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from salon DHT sensor!");
    } else {
      float hi = salondht.computeHeatIndex(t, h, false);
      float dp = dewPoint(t, h);
      Serial.print("Salon Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(t);
      Serial.print(" °C\t");
      Serial.print("Heat index: ");
      Serial.print(hi);
      Serial.print(" °C\t");
      Serial.print("Dew point: ");
      Serial.print(dp);
      Serial.println(" °C");
    }
    dhtTime = millis();
  }

  if (clockTime + 1000 < millis()) { // Every sec
    Serial.print(dayOfTheWeektoChar(Clock.getDoW()));
    Serial.print(' ');
    Serial.print(Clock.getDate(), DEC);
    Serial.print('/');
    Serial.print(Clock.getMonth(Century), DEC);
    Serial.print('/');
    Serial.print(Clock.getYear() + 2000, DEC);
    Serial.print(' ');
    Serial.print(Clock.getHour(H12, PM), DEC);
    Serial.print(':');
    Serial.print(Clock.getMinute(), DEC);
    Serial.print(':');
    Serial.print(Clock.getSecond(), DEC);
    Serial.print(" Temperature: ");
    Serial.print(Clock.getTemperature());
    Serial.print(" °C");
    Serial.println();
    clockTime = millis();
  /*
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");
  */
  }

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
    case HALL_2:
      Serial2.println("&relay 12 invertState$");
      break;        
    case HALL_3:
      Serial2.println("&relay 10 invertState$");
      break;
    case HALL_4:
      
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
    break;
  }
}

void processMessage() {
  while (Serial.available() > 0) {
    if (arraySize < 31) // One less than the size of the array
    {
      inChar = Serial.read(); // Read a character
      if (inChar == '&') {
        arraySize = 0;
        return;
      }
      if (inChar == '$') {
        inData[arraySize] = '\0';
        processCmd(inData, arraySize);
      }
      inData[arraySize] = inChar; // Store it
      arraySize++; // Increment where to write next
      inData[arraySize] = '\0'; // Null terminate the string
    } else {
      arraySize = 0;
    }
  }
    while (Serial2.available() > 0) {
    if (arraySize2 < 31) // One less than the size of the array
    {
      inChar2 = Serial2.read(); // Read a character
      if (inChar2 == '&') {
        arraySize2 = 0;
        return;
      }
      if (inChar2 == '$') {
        inData2[arraySize2] = '\0';
        processCmd(inData2, arraySize2);
      }
      inData2[arraySize2] = inChar2; // Store it
      arraySize2++; // Increment where to write next
      inData2[arraySize2] = '\0'; // Null terminate the string
    } else {
      arraySize2 = 0;
    }
  }
}

void processCmd(char data[], byte size) {
  //Serial.println(inData);
  // cmd: &relay 8 on$
  if (data[0] == 'r' && data[1] == 'e' && data[2] == 'l' && data[3] == 'a' && data[4] == 'y') {
    if (isDigit(data[6]) && isDigit(data[7])) {
      char charId[3] = {data[6], data[7]};
      int id = atoi(charId);
      //Serial.write("id "); Serial.print(id);
      if (0 <= id && id <= NBRRELAI && data[9] == 'o' && data[10] == 'n') {
        relay[id].turnOn();
        //Serial.write(" on");
      }
      if (0 <= id && id <= NBRRELAI && data[9] == 'o' && data[10] == 'f' && data[11] == 'f') {
        relay[id].turnOff();
        //Serial.write (" off");
      }
      if (0 <= id && id <= NBRRELAI && data[9] == 'i' && data[10] == 'n' && data[11] == 'v' &&
          data[12] == 'e' && data[13] == 'r' && data[14] == 't' && data[15] == 'S' && data[16] == 't' && 
          data[17] == 'a' && data[18] == 't' && data[19] == 'e') {
            relay[id].invertState();
      }
      //Serial.println("");
    }
  }
  // cmd &relay state$
  if (data[0] == 'r' && data[1] == 'e' && data[2] == 'l' && data[3] == 'a' && data[4] == 'y' &&
       data[5] == ' ' && data[6] == 's' && data[7] == 't' && data[8] == 'a' && data[9] == 't' && data[10] == 'e') {
        sendAllRelayState();
       } 
  // cmd: &get time$
  else if (data[0] == 'g' && data[1] == 'e' && data[2] == 't' && data[3] == ' ' && data[4] == 't'
             && data[5] == 'i' && data[6] == 'm' && data[7] == 'e'){

    Serial.print(Clock.getDate(), DEC);
    Serial.print('/');
    Serial.print(Clock.getMonth(Century), DEC);
    Serial.print('/');
    Serial.print(Clock.getYear() + 2000, DEC);
    Serial.print(' ');
    Serial.print(Clock.getHour(H12, PM), DEC);
    Serial.print(':');
    Serial.print(Clock.getMinute(), DEC);
    Serial.print(':');
    Serial.print(Clock.getSecond(), DEC);
    Serial.println();
  }
  // cmd: &set time 16:47:30$
  else if (data[0] == 's' && data[1] == 'e' && data[2] == 't' && data[3] == ' ' && data[4] == 't'
             && data[5] == 'i' && data[6] == 'm' && data[7] == 'e'){
                if (isDigit(data[9]) && isDigit(data[10]) && isDigit(data[12]) && isDigit(data[13]) && isDigit(data[15]) && isDigit(data[16])) {
                  char charHour[3] = {data[9], data[10]};
                  int newHour = atoi(charHour);
                  char charMinute[3] = {data[12], data[13]};
                  int newMinute = atoi(charMinute);
                  char charSec[3] = {data[15], data[16]};
                  int newSec = atoi(charSec);
                  Clock.setHour(newHour);
                  Clock.setMinute(newMinute);
                  Clock.setSecond(newSec);
                  Serial.write("new time "); Serial.print(newHour); Serial.write(":");Serial.print(newMinute); Serial.write(":");Serial.print(newSec); Serial.println("");
              }
  }
  // cmd: &set date 30/04/20$ // DD/MM/YY
  else if (data[0] == 's' && data[1] == 'e' && data[2] == 't' && data[3] == ' ' 
             && data[4] == 'd' && data[5] == 'a' && data[6] == 't' && data[7] == 'e'){
                if (isDigit(data[9]) && isDigit(data[10]) && isDigit(data[12]) && isDigit(data[13]) && isDigit(data[15]) && isDigit(data[16])) {
                  char charDay[3] = {data[9], data[10]};
                  int newDay = atoi(charDay);
                  char charMonth[3] = {data[12], data[13]};
                  int newMonth = atoi(charMonth);
                  char charYear[3] = {data[15], data[16]};
                  int newYear = atoi(charYear);
                  Clock.setDate(newDay);
                  Clock.setMonth(newMonth);
                  Clock.setYear(newYear);
                  newYear += 2000;
                  Serial.write("new date "); Serial.print(newDay); Serial.write("/");Serial.print(newMonth); Serial.write("/");Serial.print(newYear); Serial.println("");
              }
  }
  // cmd: &set DoW 1$ // Day of the Week (1-7)
  else if (data[0] == 's' && data[1] == 'e' && data[2] == 't' && data[3] == ' ' 
             && data[4] == 'D' && data[5] == 'o' && data[6] == 'W'){
                if (isDigit(data[8])) {
                  char charDoW[1] = {data[8]};
                  int doW = atoi(charDoW);
                  Clock.setDoW(doW);
                  Serial.write("new day of the week "); Serial.println(Clock.getDoW(), DEC);
              }
  }
}

void sendAllRelayState()
{
  for(int i = 0; i < NBRRELAI; ++i) {
    sendRelayState(i);
  }
}

void sendRelayState(int id)
{
   if (relay[id].getState()) {
      Serial.print("relay ");   Serial.print(id); Serial.println(" on");
   } else {
      Serial.print("relay ");   Serial.print(id); Serial.println(" off");
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

const char* dayOfTheWeektoChar(int DoW)
{
  switch (DoW) {
    case 1:
    return "Monday";
    break;
    case 2:
    return "Tuesday";
    break;
    case 3:
    return "Wednesday";
    break;
    case 4:
    return "Thursday";
    break;
    case 5:
    return "Friday";
    break;
    case 6:
    return "Saturday";
    break;
    case 7:
    return "Sunday";
    break;
    default:
    return "";
    break;
  }
}


