/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "AD9833.h"

LiquidCrystal_I2C lcd(0x27,16,2);                          // set the LCD address to 0x27 for a 16 chars and 2 line display

const int xpin = A3;                                       // variables for the joystick  
const int ypin = A2;
const int switch_pin = 9;

int menuPos = 0;                                           // variables for the display menu
long dispFrequency = 1;                                    // 
long maxFrequency = 100;
long startFreq = 1;
long endFreq = 2;  
String menuTitle[5] = {"Freq Sweep", "PWM", "Sine Wave", "Triangle Wave", "Square Wave"};

                                                          // the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 and 9 as an output.
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);

  
  

  lcd.init();                                             // initialize the lcd 
  // Print a intro message to the LCD.
  lcd.backlight();
  lcd.print("DDS FUNCTION GEN");
  lcd.setCursor(1,1);
  lcd.print("BY DBOT");
  delay(2000);

  ////////////////////////////////////////////Serial for debugging//////////////////////////////////
  Serial.begin(38400);
  Serial.println("Debug info");

}

// the loop function runs over and over again forever
void loop() {

  //////////////////////////////////////read joystick to change menu postion//////////////////////////
  //if stick in down position
  if (analogRead(ypin) < 100){
    if(menuPos == 0){
      //do nothing
    }
    else{
      menuPos -= 1;
    }
  }

  //if stick in up position
  if (analogRead(ypin) > 900){
    if(menuPos == 4){
      //do nothing
    }
    else{
      menuPos += 1;
    }
  }

  //if stick in left position
  if (analogRead(xpin) < 100){
    if(dispFrequency == 1){
      //do nothing
    }
    else{
      dispFrequency -= 1;
    }
  }

  //if stick in right position
  if (analogRead(xpin) > 900){
    if(dispFrequency == maxFrequency){
      //do nothing
    }
    else{
      dispFrequency += 1;
    }
  }

  Serial.print("Xpin = ");
  Serial.println(analogRead(xpin));
  Serial.print("Ypin = ");
  Serial.println(analogRead(ypin));

  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(menuTitle[menuPos]);
  lcd.setCursor(1,1);
  lcd.print(dispFrequency);
  delay(500);

}
