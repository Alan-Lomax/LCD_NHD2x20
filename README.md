# LCD_NHD2x20
 LCD Display Class

This class implements the 2x20 Monochrome LCD display from Newhaven Devices. It does so in I2C mode using the wire library. The default I2C address for this device is 0x28 but this can be changed with one of the methods provided. Other than absolute minimal delays to ensure I2C comms (typ 1ms) no other delays are used.

### Files: LCD_NHD2x20.h, LCD_NHD2x20.CPP

### Example Sketch:

    #include "LCD_NHD2x20.h"    //LCD library
    /*
     * A test sketch demonstrating many features of the 2 row by 20 character LCD display.
     * This display has two long rows of character memory, with only the first 20 of each row displayed.
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

### Instantiation:
     LCD_NHD2x20 myLCD();	              // create new member called myLCD

### Methods
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

### Properties:
(none - the display itself can show some information such as firmware version if the appropriate method is called.)
