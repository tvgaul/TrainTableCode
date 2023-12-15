/**************************************************************************
  This is a library for several Adafruit displays based on ST77* drivers.

  Works with the Adafruit 1.8" TFT Breakout w/SD card
    ----> http://www.adafruit.com/products/358
  The 1.8" TFT shield
    ----> https://www.adafruit.com/product/802
  The 1.44" TFT breakout
    ----> https://www.adafruit.com/product/2088
  The 1.14" TFT breakout
  ----> https://www.adafruit.com/product/4383
  The 1.3" TFT breakout
  ----> https://www.adafruit.com/product/4313
  The 1.54" TFT breakout
    ----> https://www.adafruit.com/product/3787
  The 2.0" TFT breakout
    ----> https://www.adafruit.com/product/4311
  as well as Adafruit raw 1.8" TFT display
    ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams.
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional).

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 **************************************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include "imageData.h"
#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_ILI9341.h>     // Hardware-specific library
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
#include <Adafruit_ImageReader.h> // Image-reading functions

  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
  #define SD_CS   4 // SD card select pin
// OPTION 1 (recommended) is to use the HARDWARE SPI pins, which are unique
// to each board and not reassignable. For Arduino Uno: MOSI = pin 11 and
// SCLK = pin 13. This is the fastest mode of operation and is required if
// using the breakout board's microSD card.

// For 1.44" and 1.8" TFT with ST7735 use:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


  SdFat                SD;         // SD card filesystem
  Adafruit_ImageReader reader(SD); // Image-reader object, pass in SD filesys

float p = 3.1415926;
int xAxis = 0;
int yAxis = 0;
void setup(void) {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  // OR use this initializer (uncomment) if using a 0.96" 160x80 TFT:
  tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
  tft.setRotation(2);
  if(!SD.begin(SD_CS, SD_SCK_MHZ(25))) { // ESP32 requires 25 MHz limit
    Serial.println(F("SD begin() failed"));
    for(;;); // Fatal error, do not continue
  }
  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.
  tft.setSPISpeed(4000000);
  tft.fillScreen(ST77XX_BLACK);
  int rand = random(7);
  ImageReturnCode stat;
  if(rand==0){
    stat = reader.drawBMP("/miner.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
  else if(rand==1){
    stat = reader.drawBMP("/ghost.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
  else if(rand==2){
    ghostRun();
  }
    if(rand==3){
    stat = reader.drawBMP("/creaper.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
  else if(rand==4){
    stat = reader.drawBMP("/cheif.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
    else if(rand==5){
    stat = reader.drawBMP("/bendy.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
    else if(rand==6){
    stat = reader.drawBMP("/dino.bmp", tft, 0, 0);
    reader.printStatus(stat);
  }
  
}

void loop() {


}

void ghostRun(){
  while(1){
    drawGhost(xAxis,yAxis);
  xAxis++;
  if(xAxis > 80){
    xAxis = -60;
    tft.fillScreen(ST77XX_BLACK);
  }
  yAxis++;
  if(yAxis > 180){
    yAxis = -80;
    tft.fillScreen(ST77XX_BLACK);
  }
  }
}


void drawGhost(int x,int y){

  //tft.drawCircle(40+x, 80+y, 16, ST77XX_BLACK);
  //main ghost body
  tft.fillTriangle(20+x, 20+y, 25+x, 80+y, 25+x, 20+y, ST77XX_WHITE);
  tft.fillTriangle(55+x, 20+y, 55+x, 80+y, 60+x, 20+y, ST77XX_WHITE);
  tft.fillCircle(40+x, 80+y, 15, ST77XX_WHITE);  
  tft.fillRect(25+x, 20+y, 30, 60, ST77XX_WHITE);

  //bottom fringe of ghost
  tft.fillCircle(22+x,20+y, 3, ST77XX_BLACK);  
  tft.fillCircle(28+x,20+y, 3, ST77XX_BLACK);  
  tft.fillCircle(34+x,20+y, 3, ST77XX_BLACK);  
  tft.fillCircle(40+x,20+y, 3, ST77XX_BLACK);
  tft.fillCircle(46+x,20+y, 3, ST77XX_BLACK);
  tft.fillCircle(52+x,20+y, 3, ST77XX_BLACK);
  tft.fillCircle(58+x,20+y, 3, ST77XX_BLACK);

  //eyes
  tft.fillCircle(35+x,85+y, 1, ST77XX_BLACK);  
  tft.fillCircle(45+x,85+y, 1, ST77XX_BLACK);  

    //for animation purposes
  tft.drawLine(19+x, 20+y, 27+x, 116+y, ST77XX_BLACK);
  tft.drawLine(61+x, 20+y, 53+x, 116+y, ST77XX_BLACK);
}



void Miner49er(){
  //testdrawtext("Four Score and seven years ago ", ST77XX_WHITE);
  //tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, ST77XX_BROWN);
}
