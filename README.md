# LCD_NHD2x20
 LCD Display Class

  This class implements the 2x20 Monochrome LCD display from Newhaven Devices.
  It does so in I2C mode using the wire library. The default I2C address for this device is 0x28 but this can be    
  changed with one of the methods provided. Other than absolute minimal delays to ensure I2C comms no long delays are used.

### Files: LCD_NHD2x20.h, LCD_NHD2x20.CPP

### Usage:
Include the header file near the top of your code. (After this is done the compiler will know how to handle you using it.)

    #include "LCD_NHD2x20.h";

Notice there are a large number of methods available for this display. 
These are effectively wrappers for all of the commands the display can process (according to the datasheet).
I have only added L1C1() and L2C1() to move the cursor to line 1 column 1, and line 2 column 1 respectively.

Create a new member of this class is simple as no parameters or additional setup is needed.
(Assuming the default Arduino I2C pins are used and the display is still on its default I2C address)

         LCD_NHD2x20();

### Instantiation:
     LCD_NHD2x20 myLCD();	           // create new member called myLCD

### Methods
    void LCD_On();                                // 0x41 Turn Display On
    void LCD_Off();                               // 0x42 Turn Display Off
    void LCD_SetCursor(byte _posn);               // 0x45  Set Cursor to _posn  (Line 1 = 0x00 to 0x13  Line 2 = 0x40 to 0x53)
    void LCD_Home();                              // 0x46 Cursor to home position
    void LCD_UnderlineOn();                       // 0x47 Turn on underline cursor
    void LCD_UnderlineOff();                      // 0x48 Turn off underline cursor
    void LCD_CursorLeft();                        // 0x49 Move Cursor Left one place
    void LCD_CursorRight();                       // 0x4A Move Cursor Right one place
    void LCD_BlinkOn();                           // 0x4B Turn on Blink cursor
    void LCD_BlinkOff();                          // 0x4C Turn off Blink cursor
    void LCD_Backspace();                         // 0x4E Backspace
    void LCD_Clear();                             // 0x51 Clear LCD Screen
    void LCD_SetContrast(byte _contrast);         // 0x52 Set Contrast
    void LCD_SetBacklight(byte _backlight);       // 0x53  Set Backlight
    void LCD_Print(char _buffer[]);               // Display buffered Text on LCD
	void LCD_Print(char _buffer[], byte _row, byte _col);   // Display buffered Text on LCD at row (1 or 2), col (1-20)
    void LCD_LoadCustomChar( byte _a, char _c[8]);// 0x54 Load a Custom Character. _a is address of character (0-7), _c is the binary depiction of it.
                                                  //      To display a custom character, user would first need to call ‘Set Cursor Position’
                                                  //      followed by the address of the custom character (0 to 8). The following command does this.
    void LCD_PrintCustom(byte _posn, byte _addr); // 0x45  Set Cursor to _posn  (Line 1 = 0x00 to 0x13  Line 2 = 0x40 to 0x53) and displays custom character _addr
    void LCD_MoveLeft();                          // 0x55 Move Display Left
    void LCD_MoveRight();                         // 0x56 Move Display Right
    void LCD_Firmware();                          // 0x70  Display Firmware Version
    void LCD_SetI2CAddress(byte _newI2Ca);        // 0x62  Change the I2C Address
    void LCD_I2CAddress();                        // 0x72  Display I2C Address
    void LCD_L1C1();                              // 0x45 0x40 Set Cursor to Line #1, Col #1
    void LCD_L2C1();                              // 0x45 0x40 Set Cursor to Line #2, Col #1

### Properties:
(none - the display itself can show some information such as firmware version if the appropriate method is called.)