

#define NBRRELAI                 15

// Define my lights
#define CHAMBRE_JB_GAUCHE         0
#define CHAMBRE_JB_DROITE         1
#define TOILETTE                  2
#define CHAMBRE_AMI_GAUCHE        3
#define CHAMBRE_AMI_DROITE        4
#define SALLE_DE_DOUCHE_MIRROIR   5
#define SALLE_DE_DOUCHE_DOUCHE    6
#define BUREAU                    7
#define DRESSING                  8
#define GRENIER                   9
#define VESTIAIRE                10
#define GARAGE                   11
#define HALL_HAUT                12
#define BUANDERIE                13
#define SALLE_DE_DOUCHE_MUSIQUE  14 

#define NBRSW                        24
// Define my light switch
#define SALLE_DE_DOUCHE_MIRROIR_1     0
#define SALLE_DE_DOUCHE_MIRROIR_2     1
#define SALLE_DE_DOUCHE_DOUCHE_1      2
#define SALLE_DE_DOUCHE_DOUCHE_2      3
#define DRESSING_1                    4
#define DRESSING_2                    5
#define HALL_HAUT_1                   6
#define HALL_HAUT_2                   7
#define CHAMBRE_JB_1                  8   // Entrée
#define CHAMBRE_JB_2                  9   // Entrée
#define CHAMBRE_JB_3                 10
#define CHAMBRE_JB_4                 11
#define CHAMBRE_JB_5                 12
#define CHAMBRE_JB_6                 13
#define CHAMBRE_AMI_1                14
#define CHAMBRE_AMI_2                15
#define CHAMBRE_AMI_3                16
#define CHAMBRE_AMI_4                17
#define BUREAU_1                     18
#define BUREAU_2                     19
#define TOILETTE_1                   20
#define TOILETTE_2                   21
#define BUANDERIE_1                  22
#define BUANDERIE_2                  23
   


// define my t°/humidy sensors
#define SALLE_DE_DOUCHE_DHT 1
#define HALL_DHT 2
#define CHAMBRE_JB_DHT 3

#define DHTTYPE DHT22

#include <DHT.h>

#include <pushbutton.h>
#include <relay.h>

Relay relay[NBRRELAI] = { Relay(4),  // CHAMBRE_JB_GAUCHE
                          Relay(5),  // CHAMBRE_JB_DROITE
                          Relay(6),  // TOILETTE
                          Relay(7),  // CHAMBRE_AMI_GAUCHE
                          Relay(8),  // CHAMBRE_AMI_DROITE
                          Relay(9),  // SALLE_DE_DOUCHE_MIRROIR
                          Relay(10), // SALLE_DE_DOUCHE_DOUCHE
                          Relay(11), // BUREAU
                          Relay(12), // DRESSING
                          Relay(13), // GRENIER
                          Relay(22), // VESTIAIRE
                          Relay(23), // GARAGE
                          Relay(24), // HALL_HAUT
                          Relay(25), // BUANDERIE
                          Relay(26)  // SALLE_DE_DOUCHE_MUSIQUE
                          };

PushButton pushButton[NBRSW] = { PushButton(31, SALLE_DE_DOUCHE_MIRROIR_1),
                                 PushButton(32, SALLE_DE_DOUCHE_MIRROIR_2),
                                 PushButton(33, SALLE_DE_DOUCHE_DOUCHE_1),
                                 PushButton(34, SALLE_DE_DOUCHE_DOUCHE_2),
                                 PushButton(35, DRESSING_1),
                                 PushButton(36, DRESSING_2),
                                 PushButton(37, HALL_HAUT_1),  
                                 PushButton(38, HALL_HAUT_2), 
                                 PushButton(39, CHAMBRE_JB_1),
                                 PushButton(40, CHAMBRE_JB_2),
                                 PushButton(41, CHAMBRE_JB_3), 
                                 PushButton(42, CHAMBRE_JB_4),
                                 PushButton(43, CHAMBRE_JB_5),
                                 PushButton(44, CHAMBRE_JB_6),
                                 PushButton(45, CHAMBRE_AMI_1),
                                 PushButton(46, CHAMBRE_AMI_2),
                                 PushButton(47, CHAMBRE_AMI_3),
                                 PushButton(48, CHAMBRE_AMI_4),
                                 PushButton(49, BUREAU_1),
                                 PushButton(50, BUREAU_2),
                                 PushButton(51, TOILETTE_1),
                                 PushButton(52, TOILETTE_2),
                                 PushButton(29, BUANDERIE_1),
                                 PushButton(30, BUANDERIE_2)
};

char inData[32];
char inChar = -1;
byte arraySize = 0;

char inData2[32];
char inChar2 = -1;
byte arraySize2 = 0;

unsigned long dhtTime = 0;

DHT sdbdht(SALLE_DE_DOUCHE_DHT, DHTTYPE);
DHT halldht(HALL_DHT, DHTTYPE);
DHT brdht(CHAMBRE_JB_DHT, DHTTYPE);

void setup() {
   Serial.begin(115200);
   Serial1.begin(115200); // Raspberry
   Serial2.begin(115200); // Cave       // TX2: 17 (blanc) <-> RX2: 16 (jaune)
   //Serial3.begin(115200); // Grenier 2 

   sdbdht.begin();
   halldht.begin();
   brdht.begin();
  
   for(int i = 0; i < NBRRELAI; ++i) relay[i].begin();
   for(int i = 0; i < NBRSW;    ++i) pushButton[i].setCallbackClicked(on_pushButton_pushed);
}

void loop() {
   // put your main code here, to run repeatedly:
   processMessage();

   for(int i = 0; i < NBRSW; ++i) pushButton[i].read();

  if (dhtTime + 4000 < millis()) { // Max every 4 sec
    float h = sdbdht.readHumidity();
    float t = sdbdht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from SDB DHT sensor!");
      Serial1.println("Failed to read from SDB DHT sensor!");
    } else {
      float hi = sdbdht.computeHeatIndex(t, h, false);
      float dp = dewPoint(t, h);
      Serial.print("SDB Humidity: ");
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("SDB Temperature: ");
      Serial.print(t);
      Serial.print(" °C\t");
      Serial.print("SDB Heat index: ");
      Serial.print(hi);
      Serial.print(" °C\t");
      Serial.print("SDB Dew point: ");
      Serial.print(dp);
      Serial.println(" °C");
      Serial1.print("SDB Humidity: ");
      Serial1.print(h);
      Serial1.print(" %\t");
      Serial1.print("SDB Temperature: ");
      Serial1.print(t);
      Serial1.print(" °C\t");
      Serial1.print("SDB Heat index: ");
      Serial1.print(hi);
      Serial1.print(" °C\t");
      Serial1.print("SDB Dew point: ");
      Serial1.print(dp);
      Serial1.println(" °C");
    }
    h = halldht.readHumidity();
    t = halldht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from Hall DHT sensor!");
      Serial1.println("Failed to read from Hall DHT sensor!");
    } else {
      float hi = halldht.computeHeatIndex(t, h, false);
      float dp = dewPoint(t, h);
      Serial.print("Hall Humidity: ");     Serial.print(h);   Serial.print(" %\t");
      Serial.print("Hall Temperature: ");  Serial.print(t);   Serial.print(" °C\t");
      Serial.print("Hall Heat index: ");   Serial.print(hi);  Serial.print(" °C\t");
      Serial.print("Hall Dew point: ");    Serial.print(dp);  Serial.println(" °C");
      Serial1.print("Hall Humidity: ");    Serial1.print(h);  Serial1.print(" %\t");
      Serial1.print("Hall Temperature: "); Serial1.print(t);  Serial1.print(" °C\t");
      Serial1.print("Hall Heat index: ");  Serial1.print(hi); Serial1.print(" °C\t");
      Serial1.print("Hall Dew point: ");   Serial1.print(dp); Serial1.println(" °C");
    }
    h = brdht.readHumidity();
    t = brdht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from Chambre DHT sensor!");
      Serial1.println("Failed to read from Chambre DHT sensor!");
    } else {
      float hi = brdht.computeHeatIndex(t, h, false);
      float dp = dewPoint(t, h);
      Serial.print("Chambre Humidity: ");     Serial.print(h);   Serial.print(" %\t");
      Serial.print("Chambre Temperature: ");  Serial.print(t);   Serial.print(" °C\t");
      Serial.print("Chambre Heat index: ");   Serial.print(hi);  Serial.print(" °C\t");
      Serial.print("Chambre Dew point: ");    Serial.print(dp);  Serial.println(" °C");
      Serial1.print("Chambre Humidity: ");    Serial1.print(h);  Serial1.print(" %\t");
      Serial1.print("Chambre Temperature: "); Serial1.print(t);  Serial1.print(" °C\t");
      Serial1.print("Chambre Heat index: ");  Serial1.print(hi); Serial1.print(" °C\t");
      Serial1.print("Chambre Dew point: ");   Serial1.print(dp); Serial1.println(" °C");
    }
    dhtTime = millis();
  }
}

void on_pushButton_pushed(int id)
{
   switch(id) {
     case SALLE_DE_DOUCHE_MIRROIR_1:
     case SALLE_DE_DOUCHE_DOUCHE_1:
        relay[SALLE_DE_DOUCHE_MIRROIR].invertState();
        break;
     case SALLE_DE_DOUCHE_MIRROIR_2:
     case SALLE_DE_DOUCHE_DOUCHE_2:
        relay[SALLE_DE_DOUCHE_DOUCHE].invertState();
        relay[SALLE_DE_DOUCHE_MUSIQUE].invertState();
        break;
     case DRESSING_2:
        relay[DRESSING].invertState();
        break;
      case DRESSING_1:
       relay[HALL_HAUT].invertState();
        break;
     case HALL_HAUT_1:
     case BUREAU_2:
        relay[HALL_HAUT].invertState();
        break;
     case HALL_HAUT_2:
        relay[GRENIER].invertState();
        break;
     case CHAMBRE_JB_1:
     case CHAMBRE_JB_3:
     case CHAMBRE_JB_6:
        relay[CHAMBRE_JB_GAUCHE].invertState();
        break;
     case CHAMBRE_JB_2:
     case CHAMBRE_JB_4:
     case CHAMBRE_JB_5:
        relay[CHAMBRE_JB_DROITE].invertState();
        break;
     case CHAMBRE_AMI_1:
     case CHAMBRE_AMI_3:
       relay[CHAMBRE_AMI_GAUCHE].invertState();
        break;
     case CHAMBRE_AMI_2:
     case CHAMBRE_AMI_4:
        relay[CHAMBRE_AMI_DROITE].invertState();
        break;
     case BUREAU_1:
        relay[BUREAU].invertState();
        break;
     case TOILETTE_1:
        relay[VESTIAIRE].invertState();
        break;
     case TOILETTE_2:
        relay[TOILETTE].invertState();
        break;
     case BUANDERIE_1:
        Serial2.println("&relay 06 invertState$");
         break;
     case BUANDERIE_2:
       relay[BUANDERIE].invertState();
     default:
     break;
	}
  sendRelayState(id);
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
  Serial.println(data);
  // cmd: &relay 8 on$
  if (data[0] == 'r' && data[1] == 'e' && data[2] == 'l' && data[3] == 'a' && data[4] == 'y') {
    if (isDigit(data[6]) && isDigit(data[7])) {
      char charId[3] = {data[6], data[7]};
      int id = atoi(charId);
      Serial.write("id "); Serial.print(id);
      if (0 <= id && id <= NBRRELAI && data[9] == 'o' && data[10] == 'n') {
        relay[id].turnOn();
        sendRelayState(id);
        Serial.write(" on");
      }
      if (0 <= id && id <= NBRRELAI && data[9] == 'o' && data[10] == 'f' && data[11] == 'f') {
        relay[id].turnOff();
        sendRelayState(id);
        Serial.write (" off");
      }
      if (0 <= id && id <= NBRRELAI && data[9] == 'i' && data[10] == 'n' && data[11] == 'v' &&
          data[12] == 'e' && data[13] == 'r' && data[14] == 't' && data[15] == 'S' && data[16] == 't' && 
          data[17] == 'a' && data[18] == 't' && data[19] == 'e') {
            relay[id].invertState();
      }
      Serial.println("");
    }
  }
  // cmd &relay state$
  if (data[0] == 'r' && data[1] == 'e' && data[2] == 'l' && data[3] == 'a' && data[4] == 'y' &&
       data[5] == ' ' && data[6] == 's' && data[7] == 't' && data[8] == 'a' && data[9] == 't' && data[10] == 'e') {
        sendAllRelayState();
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
