#ifndef LCD1602_H
#define LCD1602_H

#include <string>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

class LCD1602 {
public:
    // Constructor - handles initialization
    LCD1602(uint8_t i2c_addr = 0x27, uint baudrate = 100000);
    
    // Public methods
    void clear();
    void setCursor(int line, int position);
    void writeChar(char c);
    void writeString(const char* str);
    void writeString(const std::string& str);
    
    // Constants
    static const int MAX_LINES = 2;
    static const int MAX_CHARS = 16;

private:
    // LCD Commands
    enum Commands {
        LCD_CLEARDISPLAY = 0x01,
        LCD_RETURNHOME = 0x02,
        LCD_ENTRYMODESET = 0x04,
        LCD_DISPLAYCONTROL = 0x08,
        LCD_CURSORSHIFT = 0x10,
        LCD_FUNCTIONSET = 0x20,
        LCD_SETCGRAMADDR = 0x40,
        LCD_SETDDRAMADDR = 0x80
    };
    
    // LCD Flags
    enum Flags {
        LCD_ENTRYSHIFTINCREMENT = 0x01,
        LCD_ENTRYLEFT = 0x02,
        LCD_BLINKON = 0x01,
        LCD_CURSORON = 0x02,
        LCD_DISPLAYON = 0x04,
        LCD_MOVERIGHT = 0x04,
        LCD_DISPLAYMOVE = 0x08,
        LCD_5x10DOTS = 0x04,
        LCD_2LINE = 0x08,
        LCD_8BITMODE = 0x10,
        LCD_BACKLIGHT = 0x08,
        LCD_ENABLE_BIT = 0x04
    };
    
    // Modes
    static const int LCD_CHARACTER = 1;
    static const int LCD_COMMAND = 0;
    
    // Private methods
    void i2cWriteByte(uint8_t val);
    void toggleEnable(uint8_t val);
    void sendByte(uint8_t val, int mode);
    void initLCD();
    
    // Member variables
    uint8_t _i2c_addr;
    static const uint DELAY_US = 600;
};

#endif // LCD1602_H