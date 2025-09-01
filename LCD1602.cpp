#include "LCD1602.h"
#include "pico/binary_info.h"
#include <cstring>

LCD1602::LCD1602(uint8_t i2c_addr, uint baudrate) : _i2c_addr(i2c_addr) {
    // Initialize I2C
    i2c_init(i2c_default, baudrate);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    
    // Initialize the LCD
    initLCD();
}

void LCD1602::clear() {
    sendByte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

void LCD1602::setCursor(int line, int position) {
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    sendByte(val, LCD_COMMAND);
}

void LCD1602::writeChar(char c) {
    sendByte(c, LCD_CHARACTER);
}

void LCD1602::writeString(const char* str) {
    while (*str) {
        writeChar(*str++);
    }
}

void LCD1602::writeString(const std::string& str) {
    for (char c : str) {
        writeChar(c);
    }
}

// Private methods
void LCD1602::i2cWriteByte(uint8_t val) {
#ifdef i2c_default
    i2c_write_blocking(i2c_default, _i2c_addr, &val, 1, false);
#endif
}

void LCD1602::toggleEnable(uint8_t val) {
    sleep_us(DELAY_US);
    i2cWriteByte(val | LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
    i2cWriteByte(val & ~LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
}

void LCD1602::sendByte(uint8_t val, int mode) {
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2cWriteByte(high);
    toggleEnable(high);
    i2cWriteByte(low);
    toggleEnable(low);
}

void LCD1602::initLCD() {
    sendByte(0x03, LCD_COMMAND);
    sendByte(0x03, LCD_COMMAND);
    sendByte(0x03, LCD_COMMAND);
    sendByte(0x02, LCD_COMMAND);

    sendByte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    sendByte(LCD_FUNCTIONSET | LCD_2LINE, LCD_COMMAND);
    sendByte(LCD_DISPLAYCONTROL | LCD_DISPLAYON  | !LCD_CURSORON | !LCD_BLINKON, LCD_COMMAND);
    clear();
}