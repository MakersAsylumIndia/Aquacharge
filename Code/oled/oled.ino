#include <U8g2lib.h>
#include <Wire.h>

// Using hardware I2C for SH1106 128x64
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr); // Choose a font
  u8g2.drawStr(0, 10, "Hello, ESP32!");
  u8g2.sendBuffer(); // Send to display
}
void loop() {
  // Leave empty if you don't need updates
}