//AGNES
//Lumen

String aVersion = "1.0.2";

//Include Statements

#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Time.h>
#include <TimeLib.h>

int WaterLevel = 2; //Water level sensor
int SoilMoisture = 3; //Soil moisture sensor
int TempHumidity = 2; //Environment Sensor
int PumpRelay = 7; //Relay to control pump
int LightRelay = 6; //Relay to control lights

//LCD Pins
int LCDclk = 13; //LCD CLK pin
int LCDmosi = 11; //LCD MOSI pin
int LCDrst = 9; //LCD RST pin
int LCDcs = 10; //LCD CS pin
int LCDdc = 8; // LCD DIC pin

//Set up DHT sensor
//Analog 2
DHT dht(2, DHT22);

//Set up LCD
Adafruit_ST7735 tft = Adafruit_ST7735(LCDcs, LCDdc, LCDrst);

// 'AgnesSpashScreen', 148x36px
const unsigned char epd_bitmap_AgnesSpashScreen [] PROGMEM = {
  0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x78, 0x78, 
  0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0x80, 0x78, 0x78, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0x80, 0x78, 0x78, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x78, 0x78, 0x07, 0x80, 0x00, 0x30, 0x00, 0x07, 0xc0, 
  0x0c, 0x00, 0xc0, 0xff, 0xfc, 0x00, 0x7c, 0x00, 0x07, 0x87, 0xf8, 0x7f, 0x87, 0x80, 0x00, 0x38, 
  0x00, 0x1f, 0xf0, 0x1e, 0x00, 0xe0, 0xff, 0xfc, 0x01, 0xff, 0x00, 0x07, 0x87, 0xf8, 0x7f, 0x87, 
  0x80, 0x00, 0x78, 0x00, 0x7e, 0xf8, 0x1e, 0x00, 0xe0, 0xff, 0xfc, 0x07, 0xef, 0x80, 0x07, 0x87, 
  0xf8, 0x7f, 0x87, 0x80, 0x00, 0x78, 0x00, 0x70, 0x3c, 0x1f, 0x00, 0xe0, 0xe0, 0x00, 0x07, 0x03, 
  0xc0, 0x07, 0x87, 0xf8, 0x7f, 0x87, 0x80, 0x00, 0x7c, 0x00, 0xe0, 0x1c, 0x1f, 0x00, 0xe0, 0xe0, 
  0x00, 0x0e, 0x01, 0xe0, 0x7f, 0x80, 0x00, 0x00, 0x07, 0xf8, 0x00, 0xfc, 0x00, 0xe0, 0x0e, 0x1f, 
  0x80, 0xe0, 0xe0, 0x00, 0x0e, 0x00, 0xe0, 0x7f, 0x80, 0x00, 0x00, 0x07, 0xf8, 0x00, 0xec, 0x01, 
  0xc0, 0x0e, 0x1f, 0x80, 0xe0, 0xe0, 0x00, 0x0e, 0x00, 0xe0, 0x7f, 0x80, 0x00, 0x00, 0x07, 0xf8, 
  0x00, 0xce, 0x01, 0xc0, 0x00, 0x1d, 0xc0, 0xe0, 0xe0, 0x00, 0x0e, 0x00, 0x00, 0x7f, 0x80, 0x00, 
  0x00, 0x07, 0xf8, 0x01, 0xce, 0x01, 0xc0, 0x00, 0x1c, 0xe0, 0xe0, 0xe0, 0x00, 0x0f, 0x00, 0x00, 
  0x00, 0x78, 0x78, 0x78, 0x78, 0x00, 0x01, 0xc6, 0x01, 0xc0, 0x00, 0x1c, 0xe0, 0xe0, 0xe0, 0x00, 
  0x07, 0x80, 0x00, 0x00, 0x78, 0x78, 0x78, 0x78, 0x00, 0x01, 0x87, 0x01, 0xc0, 0x00, 0x1c, 0x70, 
  0xe0, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x78, 0x78, 0x78, 0x78, 0x00, 0x03, 0x87, 0x01, 0xc0, 
  0x00, 0x1c, 0x70, 0xe0, 0xff, 0xf8, 0x01, 0xfc, 0x00, 0x00, 0x78, 0x78, 0x78, 0x78, 0x00, 0x03, 
  0x83, 0x01, 0xc0, 0xfe, 0x1c, 0x38, 0xe0, 0xff, 0xf8, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00, 
  0x07, 0xf8, 0x03, 0x03, 0x81, 0xc0, 0xfe, 0x1c, 0x38, 0xe0, 0xe0, 0x00, 0x00, 0x1f, 0x80, 0x7f, 
  0x80, 0x00, 0x00, 0x07, 0xf8, 0x07, 0x03, 0x81, 0xc0, 0xfe, 0x1c, 0x1c, 0xe0, 0xe0, 0x00, 0x00, 
  0x03, 0xc0, 0x7f, 0x80, 0x00, 0x00, 0x07, 0xf8, 0x07, 0xff, 0x81, 0xc0, 0x0e, 0x1c, 0x1c, 0xe0, 
  0xe0, 0x00, 0x00, 0x01, 0xe0, 0x7f, 0x80, 0x00, 0x00, 0x07, 0xf8, 0x07, 0xff, 0x81, 0xc0, 0x0e, 
  0x1c, 0x0e, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x87, 0xf8, 0x7f, 0x87, 0x80, 0x0f, 0xff, 
  0xc1, 0xc0, 0x0e, 0x1c, 0x0f, 0xe0, 0xe0, 0x00, 0x1c, 0x00, 0xe0, 0x07, 0x87, 0xf8, 0x7f, 0x87, 
  0x80, 0x0e, 0x01, 0xc0, 0xe0, 0x0e, 0x1c, 0x07, 0xe0, 0xe0, 0x00, 0x1c, 0x00, 0xe0, 0x07, 0x87, 
  0xf8, 0x7f, 0x87, 0x80, 0x0e, 0x00, 0xc0, 0xe0, 0x0e, 0x1c, 0x07, 0xe0, 0xe0, 0x00, 0x1e, 0x00, 
  0xe0, 0x07, 0x87, 0xf8, 0x7f, 0x87, 0x80, 0x0c, 0x00, 0xe0, 0x70, 0x0e, 0x1c, 0x03, 0xe0, 0xe0, 
  0x00, 0x0f, 0x01, 0xe0, 0x07, 0x80, 0x78, 0x78, 0x07, 0x80, 0x1c, 0x00, 0xe0, 0x7c, 0x3e, 0x1c, 
  0x03, 0xe0, 0xe0, 0x00, 0x07, 0x83, 0xc0, 0x07, 0x80, 0x78, 0x78, 0x07, 0x80, 0x1c, 0x00, 0x60, 
  0x3f, 0xf8, 0x1c, 0x01, 0xe0, 0xff, 0xfc, 0x03, 0xff, 0x80, 0x07, 0x80, 0x78, 0x78, 0x07, 0x80, 
  0x18, 0x00, 0x70, 0x0f, 0xf0, 0x1c, 0x01, 0xe0, 0xff, 0xfc, 0x00, 0xfe, 0x00, 0x07, 0x80, 0x78, 
  0x78, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x07, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void splash(){
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);
    tft.drawBitmap(1, 46, epd_bitmap_AgnesSpashScreen, 148, 36, ST77XX_WHITE);
    tft.setCursor(110, 85);
    tft.print("V. ");
    tft.println(aVersion);
}

void setup() {
  
  Serial.begin(9600);

  //Start LCD and show splashscreen
  tft.initR(INITR_BLACKTAB); 
  tft.setRotation(3);
  splash();

  pinMode(LightRelay, OUTPUT);
  pinMode(PumpRelay, OUTPUT);
  pinMode(LCDclk, OUTPUT);
  pinMode(LCDmosi, OUTPUT);
  pinMode(LCDrst, OUTPUT);
  pinMode(LCDcs, OUTPUT);
  pinMode(LCDdc, OUTPUT);

  Serial.println("Pin Modes Set");

  dht.begin();

  Serial.println("DHT loaded");

  Serial.print("Welcome to A.G.N.E.S. Version ");
  Serial.println(aVersion);

  delay(1000);
  tft.fillScreen(ST77XX_BLACK);
}

//CONTROL VARIABLES
//TIME (In microseconds, seconds x 1000)
long wait = 60000L;
int water = 3000;
//TIME (In hours)
int lightHours = 15; //Desired hours - 1 (i.e. enter 15 for 16 hours of light)
//SOIL MOISTURE
int moisturePercent = 15; //Level of moisture tha triggers watering
//MOISTURE CALIBRATION
//Soil should be pretty accurate, water just needs to be good enough
int soilDry = 833;
int soilWet = 823;
int waterDry = 282;
int waterWet = 203;


void loop() {

  //DO EVERYTHING BELOW ON EVERY LOOP
  //Read from sensors
  float soilMoisture = analogRead(SoilMoisture);
  float waterLevel = analogRead(WaterLevel);
  float temperature = dht.readTemperature(true);
  float humidity = dht.readHumidity();

  //Convert moisture readings to % and water status
  float percentSoil = map(soilMoisture, soilWet, soilDry, 100, 0);
  float percentWater = map(waterLevel, waterWet, waterDry, 100, 0);
  bool waterFull = percentWater > 50;

  //Check the current hour (since boot)
  int isHour = hour();
  int isMinute = minute();
  

  //PRINT EVERYTHING TO SERIAL
  Serial.println("-----------------------------");
  Serial.print("System time is " );
  Serial.print(isHour);
  Serial.print(":");
  Serial.println(isMinute);
  Serial.print("Soil moisture level:  ");
  Serial.print(percentSoil);
  Serial.println("%");
  Serial.print("Environmental temperature: ");
  Serial.print(temperature);
  Serial.println(" F");
  Serial.print("Environmental humidity is ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Water reservoir is ");
  if (waterFull){
    Serial.println("full");
   } else {
    Serial.println("low");
   }
  Serial.print("Current soil reading: ");
  Serial.println(soilMoisture);

   //SET SCREEN PROPERTIES
   tft.fillScreen(ST77XX_BLACK);
   tft.setTextColor(ST77XX_WHITE);
   tft.setCursor(0, 0);
   tft.setTextSize(0);

   //PRINT IMPORTANT PARTS TO SCREEN
   tft.print("Soil moisture: ");
   tft.print(percentSoil);
   tft.println("%");
   tft.print("Env. temperature: ");
   tft.print(temperature);
   tft.println(" F");
   tft.print("Env. humidity: ");
   tft.print(humidity);
   tft.println("%");

   if (!waterFull){
      tft.setTextColor(ST77XX_RED);
      tft.setTextSize(2);
      tft.setCursor(0, 90);
      tft.println("Check Water");
      tft.println("Level!!");
    }

  
  //FUNCTIONS THAT RUN AT CERTAIN TIMES/CONDITIONS
  //Turn on light from 0-lightHours hours
  if (isHour < lightHours){
    digitalWrite(LightRelay, LOW);
    tft.drawChar(155, 0, 0x2A, ST7735_WHITE, ST7735_BLACK, 1);
   } else {
    digitalWrite(LightRelay, HIGH);
   }

  //If soil is less than moisturePercent% moisture, turn on pump for water microseconds
  //Remove the pumping time from the total wait
  //Only check/water during the 12th hour
  if (isHour == 12){
   if (percentSoil < moisturePercent){
      Serial.println("Watering...");
      digitalWrite(PumpRelay, HIGH);
      delay(water);
      digitalWrite(PumpRelay, LOW);
      wait = wait - water;
    }
  }

  
  //Loop every minute
  delay(wait);


}