#ifndef MY_NHD2x20
#define MY_NHD2x20
#include <Wire.h>           //I2C library
#include <Arduino.h>

/*
 ***************************************************** 
 ** NHD2x20 Usage                                   **  
 **                                                 **  
 ** This class implements the 2x20 Monochrome LCD   **  
 ** display from Newhaven Devices.It does so in I2C **  
 ** mode using the wire library. The default I2C    **  
 ** addrss for this device is 0x28 but this can be  **  
 ** changed with one of the methods provided.       **  
 ** Other than minimal delays to ensure I2C comms   **  
 ** no long delays are used.                        **  
 *****************************************************
*/
class LCD_NHD2x20 { 
  
private:
      byte LCDa = 0x28;                          // LCD address on I2C bus
 String _toSend = "";                            // Text we will send
    char _buffer[0x20];                          // The send buffer  

public:
    void NHD2x20();                           // constructor
    void On();                                // 0x41 Turn Display On
    void Off();                               // 0x42 Turn Display Off
    void SetCursor(byte _posn);               // 0x45  Set Cursor to _posn  (Line 1 = 0x00 to 0x13  Line 2 = 0x40 to 0x53)
    void Home();                              // 0x46 Cursor to home position
    void UnderlineOn();                       // 0x47 Turn on underline cursor
    void UnderlineOff();                      // 0x48 Turn off underline cursor
    void CursorLeft();                        // 0x49 Move Cursor Left one place
    void CursorRight();                       // 0x4A Move Cursor Right one place
    void BlinkOn();                           // 0x4B Turn on Blink cursor
    void BlinkOff();                          // 0x4C Turn off Blink cursor
    void Backspace();                         // 0x4E Backspace
    void Clear();                             // 0x51 Clear LCD Screen
    void SetContrast(byte _contrast);         // 0x52 Set Contrast
    void SetBacklight(byte _backlight);       // 0x53  Set Backlight
    void Print(char _buffer[]);               // Display buffered Text on LCD
	void Print(char _buffer[], byte _row, byte _col);   // Display buffered Text on LCD at row (1 or 2), col (1-20)
    void LoadCustomChar( byte _a, char _c[8]);// 0x54 Load a Custom Character. _a is address of character (0-7), _c is the binary depiction of it.
                                                  //      To display a custom character, user would first need to call ‘Set Cursor Position’
                                                  //      followed by the address of the custom character (0 to 8). The following command does this.
    void PrintCustom(byte _posn, byte _addr); // 0x45  Set Cursor to _posn  (Line 1 = 0x00 to 0x13  Line 2 = 0x40 to 0x53) and displays custom character _addr
    void MoveLeft();                          // 0x55 Move Display Left
    void MoveRight();                         // 0x56 Move Display Right
    void Firmware();                          // 0x70  Display Firmware Version
    void SetI2CAddress(byte _newI2Ca);        // 0x62  Change the I2C Address
    void I2CAddress();                        // 0x72  Display I2C Address
    void L1C1();                              // 0x45 0x40 Set Cursor to Line #1, Col #1
    void L2C1();                              // 0x45 0x40 Set Cursor to Line #2, Col #1
};
#endif