#include "LCD_NHD2x20.h"    //LCD library
/*
 * A test sketch demonstrating many features of the 2 row by 20 character LCD display.
 * This display has two long rows of character memory, with only the first 20 displayed.
 *    positions 0x00-0x13 (decimal 00 -19) are visible on line 1
 *    positions 0x40-0x53 (decimal 64 -83) are visible on line 2
 * One of the benefits of this library is doing the math so that a 'row, collumn' approach
 * can be used to define the cursor position.
 */
 
LCD_NHD2x20 myLCD;                  // define our LCD object
       char SBuffer[0x20];          // A character array acting as a string buffer

void setup() {
  Serial.begin(9600);               // for serial / debug console
  Serial.println(__FILE__);         // by default I like to output the file name as a minimum.
  LoadCustomChar();
  myLCD.Clear();
  delay(1000);
  
  myLCD.PrintCustom(0x00, 0);      // Display our custom character in a specific location
  myLCD.PrintCustom(0x0A, 0);      // Display our custom character in a specific location
  myLCD.PrintCustom(0x40, 0);      // Display our custom character in a specific location
  myLCD.PrintCustom(0x4A, 0);      // Display our custom character in a specific location
  delay(1000);
  
  myLCD.Clear();
  myLCD.Print("Quad.....1", 1, 1);  // display using row and collumn
  delay(1000);
  myLCD.Print("Quad.....2", 1, 11); // display using row and collumn
  delay(1000);
  myLCD.Print("Quad.....3", 2, 1);  // display using row and collumn
  delay(1000);
  myLCD.Print("Quad.....4", 2, 11); // display using row and collumn
  delay(2000);

  myLCD.Clear();                    // clear display
  myLCD.L1C1();                     // position cursor Line #1, col#1
  myLCD.Print("Firmware");          // simple text
  myLCD.SetCursor(0x40);            // move cursor
  myLCD.Firmware();                 // tell display to show its firmware version
  delay(2000);

  myLCD.Clear();
  myLCD.L1C1();
  myLCD.Print("I2C Address");
  myLCD.SetCursor(0x40);
  myLCD.I2CAddress();               // tell display to show its I2C address
  delay(2000);
}

void loop() {
  for (int i = 0; i < 60; i++) {
    myLCD.SetCursor(0x40);
    sprintf(SBuffer, "Loop Running. i=%03d  ", i);   // The best approach to combining text and variables.
    myLCD.Print(SBuffer);
    delay(1000);
  }
}

void LoadCustomChar() {
  byte Heart[] = {         // an array of bytes to define the pattern of our custom character
    B00000,
    B01010,
    B11111,
    B11111,
    B01110,
    B00100,
    B00000,
    B00000
  };
  myLCD.LoadCustomChar( 0, Heart);  // Load the heart previously defined into custom character zero withing the display unit
}