
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>
#include <Adafruit_GFX.h>          // Core graphics library
#include <Adafruit_ILI9341.h>      // Hardware-specific library
#include <SdFat.h>                 // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>     // SPI / QSPI flash library
#include <Adafruit_ImageReader.h>  // Image-reading functions


#define TFT_CS 10
#define TFT_RST 9 
#define TFT_DC 8
#define SD_CS 7  // SD card select pin

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


SdFat SD;                         // SD card filesystem
Adafruit_ImageReader reader(SD);  // Image-reader object, pass in SD filesys

float p = 3.1415926;
int xAxis = 0;
int yAxis = 0;

int fire = A0;
int waterTower = A1;
int witch = A2;
int ghost = A3;


int light = LOW;
unsigned long previousMillisWater = 0;
const long intervalWaterTower = 1000;  // interval at which to blink (milliseconds)

int magic = LOW;
unsigned long previousMillisMagic = 0;
long intervalMagic = 1000;  // interval at which to blink (milliseconds)

unsigned long previousMillisBurn = 0;
long intervalBurn = 1000;  // interval at which to blink (milliseconds)

int spookLevel = 0;
boolean spookDirection = true;
unsigned long previousMillisSpook=0;
long intervalSpook = 1000;  // interval at which to blink (milliseconds)



void setup(void) {
  randomSeed(analogRead(7));
  Serial.begin(9600);
  tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
  tft.setRotation(2);
  if (!SD.begin(SD_CS, SD_SCK_MHZ(25))) {
    Serial.println(F("SD begin() failed"));
    for (;;)
      ;  // Fatal error, do not continue
  }
  tft.setSPISpeed(4000000);
  tft.fillScreen(ST77XX_BLACK);
  int rand = random(7);
  for (int i = 0; i < 10; i++) {
    rand = random(5);
    Serial.println(rand);
  }
  ImageReturnCode stat;
  if (rand == 0) {
    stat = reader.drawBMP("/miner.bmp", tft, 0, 0);
    reader.printStatus(stat);
  } else if (rand == 1) {
    stat = reader.drawBMP("/ghost.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
  if (rand == 2) {
    stat = reader.drawBMP("/creaper.bmp", tft, 0, 0);
    reader.printStatus(stat);
  } else if (rand == 3) {
    stat = reader.drawBMP("/cheif.bmp", tft, 0, 0);
    reader.printStatus(stat);
  } else if (rand == 4) {
    stat = reader.drawBMP("/bendy.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
  pinMode(fire, OUTPUT);
  pinMode(waterTower, OUTPUT);
  pinMode(witch, OUTPUT);
  pinMode(ghost,OUTPUT);
}

void loop() {
  unsigned long currentMillisWater = millis();
  if (currentMillisWater - previousMillisWater >= intervalWaterTower) {
    // save the last time you blinked the LED
    previousMillisWater = currentMillisWater;

    // if the LED is off turn it on and vice-versa:
    if (light == LOW) {
      light = HIGH;
    } else {
      light = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(waterTower, light);
  }


  unsigned long currentMillisMagic = millis();
  if (currentMillisMagic - previousMillisMagic >= intervalMagic) {
    // save the last time you blinked the LED
    previousMillisMagic = currentMillisMagic;
    intervalMagic = random(100);
    // if the LED is off turn it on and vice-versa:
    if (magic == LOW) {
      magic = HIGH;
    } else {
      if (random(100) < 99) {
        intervalMagic = random(100);
      } else {
        intervalMagic = random(100000);
      }
      magic = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(witch, magic);
  }

  unsigned long currentMillisBurn = millis();
  if (currentMillisBurn - previousMillisBurn >= intervalBurn) {
    // save the last time you blinked the LED
    previousMillisBurn = currentMillisBurn;
    intervalBurn = random(100);
    analogWrite(fire, random(255));
  }

  unsigned long currentMillisSpook = millis();
  if (currentMillisSpook - previousMillisSpook >= intervalSpook) {
    if (spookDirection) {

      intervalSpook = 100;
      spookLevel++;
      analogWrite(ghost, spookLevel);
      if (spookLevel > 254) {
        spookDirection = false;
      }
    } else {
      intervalSpook = 100;
      spookLevel--;
      analogWrite(ghost, spookLevel);
      if (spookLevel < 1) {
        spookDirection = true;
        intervalSpook = random(100000);
        analogWrite(ghost, 0);
      }
    }
    Serial.println(spookLevel);
    Serial.println(spookDirection);
  }
}
