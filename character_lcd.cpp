#include <stdio.h>
#include "pico/stdlib.h"
#include "LCD1602.h"
#include <array>

int main() {

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    
    // Create LCD instance
    LCD1602 lcd;
    
    // Messages to display
    const std::array<std::string, 10> messages = {
        "RP2040 by", "Raspberry Pi",
        "A brand new", "microcontroller", 
        "Twin core M0", "Full C SDK",
        "More power in", "your product",
        "More beans", "than Heinz!"
    };

    while (true) {

        for (size_t m = 0; m < messages.size(); m += LCD1602::max_lines) {
            for (int line = 0; line < LCD1602::max_lines; line++) {
                if (m + line < messages.size()) {
                    // Center the text
                    int padding = (LCD1602::max_chars - messages[m + line].length()) / 2;
                    lcd.setCursor(line, padding);
                    lcd.writeString(messages[m + line]);
                }
            }
            sleep_ms(2000);
            lcd.clear();
        }
    }
#endif
    return 0;
}