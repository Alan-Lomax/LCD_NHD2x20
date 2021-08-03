#include "LCD_NHD2x20.h"
/* ####################################
   ## NHD Extended LCD Screen        ##
   ## 2X20 LCD Display               ##
   ####################################
*/

LCD_NHD2x20::LCD_NHD2x20() {                               // Constructor
/* Note re I2C Frequency

   TWBR is part of a frequency prescaler formula and is defined by the formula
        I2C freq = CPU Clock / ( 16+(2*TWBR*Prescaler)
   The default Prescaler = 1 and the CPU Clock is typically 16Mhz therefore: 
      For a TWBR = 12, Prescaler =1, I2C freq = 400 kHz
      For a TWBR = 32, Prescaler =1, I2C freq = 200 kHz
      For a TWBR = 72, Prescaler =1, I2C freq = 100 kHz
      For a TWBR = 152, Prescaler =1, I2C freq = 50 kHz

   For my display the speed = 100Khz max (any faster clock results in garbage).
   According to Spec Sheet max speed is 50khz so leave well enough alone.
   Because I2C and the LCD is relatively slow vs the Arduino a very small delay is needed after
   an I2C command is sent to allow the serial buffer to be emptied and processed by the display.
   Not having this delay results in corrupted messages. Different commands do have different
   delay requirements per spec sheet. (most often only 1ms)
  */
   TWBR = 72;                                            // Clock prescaler
}

void LCD_NHD2x20::On() {                                  // 0x41 Turn Display On
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x41);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::Off() {                                 // 0x42 Turn Display Off
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x42);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::SetCursor(byte _posn) {                 // 0x45  Set Cursor to _posn  (Line 1 = 0x00 to 0x13  Line 2 = 0x40 to 0x53)
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x45);
  Wire.write(_posn);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::Home() {                                // 0x46 Cursor to home position
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x46);
  Wire.endTransmission();
  delay(2);
}

void LCD_NHD2x20::UnderlineOn() {                         // 0x47 Turn on underline cursor
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x47);
  Wire.endTransmission();
  delay(2);
}

void LCD_NHD2x20::UnderlineOff() {                 // 0x48 Turn off underline cursor
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x48);
  Wire.endTransmission();
  delay(2);
}

void LCD_NHD2x20::CursorLeft() {                   // 0x49 Move Cursor Left one place
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x49);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::CursorRight() {                  // 0x4A Move Cursor Right one place
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x4A);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::BlinkOn() {                      // 0x4B Turn on Blink cursor
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x4B);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::BlinkOff() {                     // 0x4C Turn off Blink cursor
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x4C);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::Backspace() {                    // 0x4E Backspace
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x4E);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::Clear() {                        // 0x51 Clear LCD Screen
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x51);
  Wire.endTransmission();
  delay(2);
}

void LCD_NHD2x20::SetContrast(byte _contrast) {    // 0x52  Set Contrast to _contrast
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x52);
  Wire.write(_contrast);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::SetBacklight(byte _backlight) {   // 0x53  Set Backlight to _backlight
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x53);
  Wire.write(_backlight);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::Print(char _buffer[]) {  // Display Text on LCD
  Wire.beginTransmission(LCDa);
  Wire.write(_buffer);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::Print(char _buffer[], byte _row, byte _col) { 
  
  // Display buffered Text on LCD at row (1 or 2), col (1-20) 
  int _posn = 0;                              // A new variable each time through
  _row -= 1;                                  // Deduct 1 from row - now zero based
  _col -= 1;                                  // Deduct 1 from col - now zero based
  
  if (_row == 0) {
      _posn = 0x00;                           // row 1 so _posn does not need an offset
  }
  else if (_row == 1) {
      _posn = 0x40;                           // row 2 so _posn begins at offset 0x40
  }
  _posn += _col;                              // add the number of columns to determine actual position.

  Wire.beginTransmission(LCDa);               // First put cursor in position
  Wire.write (0xFE);
  Wire.write(0x45);
  Wire.write(_posn);
  delay(1);                                   // Let display process it
  
  Wire.write(_buffer);                        // Write out the string.
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::LoadCustomChar( byte _a, char _c[8]) {  // 0x54 Load a Custom Character
  Wire.beginTransmission(LCDa);
  Wire.write(0xFE);
  Wire.write(0x54);
  Wire.write(_a);                       // Address of custom character ( 0 -7)
  Wire.write(_c[0]);                    // data byte 1
  Wire.write(_c[1]);
  Wire.write(_c[2]);
  Wire.write(_c[3]);
  Wire.write(_c[4]);
  Wire.write(_c[5]);
  Wire.write(_c[6]);
  Wire.write(_c[7]);                    // data byte 8
  Wire.endTransmission();
  delay(1);
}
//  In order to display the custom character, user would first need to call ‘Set Cursor Position’ command, then followed by the address of the custom character (0 to 8).

void LCD_NHD2x20::PrintCustom(byte _p, byte _a) {   // 0x45  Set Cursor to _posn  (Line 1 = 0x00 to 0x13  Line 2 = 0x40 to 0x53) and displays custom character _addr
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x45);
  Wire.write(_p);                                       // position to write
  Wire.write(_a);                                       // address of custom character (0 to 8)
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::MoveLeft() {                      // 0x55 Move Display Left
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x55);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::MoveRight() {                     // 0x56 Move Display Right
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x56);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::SetI2CAddress(byte _newI2Ca) {    // 0x62  Change the I2C Address
  Wire.beginTransmission(LCDa);            //       range is 0x00 to 0xFE and it must be an even number
  Wire.write (0xFE);
  Wire.write(0x62);
  Wire.write(_newI2Ca);
  LCDa = _newI2Ca;                         // save the new LCD address for future calls.
  Wire.endTransmission();
  delay(3);
}

void LCD_NHD2x20::Firmware() {                      // 0x70  Display Firmware Version
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x70);
  Wire.endTransmission();
  delay(5);
}

void LCD_NHD2x20::I2CAddress() {                     // 0x72  Display I2C Address
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x72);
  Wire.endTransmission();
  delay(5);
}

void LCD_NHD2x20::L1C1() {                           // 0x45 0x40 Set Cursor to Line #1, Col #1
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x45);
  Wire.write(0x00);
  Wire.endTransmission();
  delay(1);
}

void LCD_NHD2x20::L2C1() {                            // 0x45 0x40 Set Cursor to Line #2, Col #1
  Wire.beginTransmission(LCDa);
  Wire.write (0xFE);
  Wire.write(0x45);
  Wire.write(0x40);
  Wire.endTransmission();
  delay(1);
}