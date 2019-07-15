
// Define my lights
#define NBRRELAI      9
#define CHAMBRE_JB                0
#define SALLE_DE_DOUCHE_MIRROIR   1
#define SALLE_DE_DOUCHE_DOUCHE    2
#define SALLE_DE_DOUCHE_CENTRAL   3
#define SALLE_DE_DOUCHE_VENTILLATION 4
#define CHAMBRE_AMI               5
#define BUREAU                    6
#define DRESSING                  7
#define GRENIER                   8


// Define my light switch
#define NBRSW          4
#define SALLE_DE_DOUCHE_MIRROIR     1
#define SALLE_DE_DOUCHE_DOUCHE  2
#define DRESSING           3
#define HALL_HAUT        4


// define my t°/humidy sensors
#define SALLE_DE_DOUCHE_DHT 48
#define HALL_DHT 49
#define CHAMBRE_JB_DHT 50
#define DHTTYPE DHT22

#include <DHT.h>

#include <pushbutton.h>
#include <relay.h>

unsigned long dhtTime = 0;

DHT sdbdht(SALLE_DE_DOUCHE_DHT, DHTTYPE);
DHT halldht(HALL_DHT, DHTTYPE);
DHT brdht(CHAMBRE_JB_DHT, DHTTYPE);

void setup() {
   Serial.begin(115200);
   Serial1.begin(115200);

   sdbdht.begin();
   halldht.begin();
   brdht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

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
