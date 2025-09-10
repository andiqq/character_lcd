#ifndef LCD1602_H
#define LCD1602_H

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <string>

class LCD1602 {
public:
  // Constructor - handles initialization
  LCD1602(uint8_t i2c_addr = 0x27, uint baudrate = 100000);

  // Public methods
  void clear();
  void setCursor(int line, int position);
  void writeChar(char c);
  void writeString(const char *str);
  void writeString(const std::string &str);

  // Constants
  static const int max_lines = 2;
  static const int max_chars = 16;

private:
  // LCD Commands
  enum Commands {
    clear_display = 0x01,
    return_home = 0x02,
    set_entrymode = 0x04,
    display_control = 0x08,
    cursor_shift = 0x10,
    set_function = 0x20,
    set_cgramaddr = 0x40,
    set_ddramaddr = 0x80
  };

  // LCD Flags
  enum Flags {
    entry_shift_increment = 0x01,
    entry_left = 0x02,
    blink_on = 0x01,
    cursor_on = 0x02,
    display_on = 0x04,
    move_right = 0x04,
    move_left = 0x08,
    lcd_5x10dots = 0x04,
    lcd_2line = 0x08,
    lcd_8bitmode = 0x10,
    backlight = 0x08,
    enable_bit = 0x04
  };

  // Modes
  static const int character = 1;
  static const int command = 0;

  // Private methods
  void i2cWriteByte(uint8_t val);
  void toggleEnable(uint8_t val);
  void sendByte(uint8_t val, int mode);
  void initLCD();

  // Member variables
  uint8_t _i2c_addr;
  static const uint delay_us = 600;
};

#endif // LCD1602_H