/*************************************************** 
A little demo for the adafruit BiColor LED Matrix backpack.
Drives a little "worm" around the matrix.

This is for the BiColor version of the matrix:
    http://www.adafruit.com/products/902

Uses the Adafruit libraries available at their github:


*/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

#define TAILENGTH 4
#define STARTX 5
#define STARTY 5
 
int ball[TAILENGTH][2]; // hard-coding the length of point array
int ballVX = 1;
int ballVY = 1;
int newDX=ballVX;
int newDY=ballVY;
int tailColor[TAILENGTH];

void setup() {
  randomSeed(analogRead(0)); // seed stream with noise from unconnected pin
  matrix.begin(0x70);  // I2C address of display module
   for(int j=0;j<TAILENGTH; j++){
     ball[j][0] = STARTX;
     ball[j][1] = STARTY;
     tailColor[j]=LED_YELLOW; // color of the "body"
   }
  tailColor[0]=LED_RED; // color of the "head"
    matrix.clear();
}


 
void loop() {
  //erase the last pixel of the tail:
     matrix.drawPixel(ball[TAILENGTH-1][0], ball[TAILENGTH-1][1], LED_OFF);

    // shif thte data down the tail:
    // not using a a loop beacuse simple assignments will be smaller for this array
   
    ball[3][0]=ball[2][0];
    ball[3][1]=ball[2][1];
    ball[2][0]=ball[1][0];
    ball[2][1]=ball[1][1];
    ball[1][0]=ball[0][0];
    ball[1][1]=ball[0][1];
    // bounce a ball:
    ball[0][0] = ball[1][0] + ballVX;
    ball[0][1] = ball[1][1] + ballVY;
    newDX=ballVX;
    newDY=ballVY;
    // check for bounds
    if ((ball[0][0] > 7) || (ball[0][0] < 0)){
     newDX = 0 - ballVX;
     ball[0][0]=ball[0][0]+newDX; // we went out of bounds, so back up
     if (newDX != 0){
       newDY = (random(3)-1);
     }
    }
 
    if ((ball[0][1] > 7) || (ball[0][1] < 0)){
     newDY = 0 - ballVY;
     ball[0][1]=ball[0][1]+newDY; // we went out of bounds, so back up
  
     if (newDY != 0){
       newDX = (random(3)-1);
     }
    } 
    
 ballVX=newDX; // copy the new vectors to the global values
 ballVY=newDY;
    for(int j=3;j>=0; j--){
      matrix.drawPixel(ball[j][0], ball[j][1], tailColor[j]);
    }

    matrix.writeDisplay();

    delay(40);


}
