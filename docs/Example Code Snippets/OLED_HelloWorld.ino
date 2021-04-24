#include "SSD1306Wire.h"
SSD1306Wire display(0x3c, 4, 5, GEOMETRY_128_32);

void setup() {
//Manual reset of the OLED display
pinMode(16, OUTPUT);
digitalWrite(16, LOW);
delay(50);
digitalWrite(16, HIGH);
display.init();
display.flipScreenVertically();
display.setFont(ArialMT_Plain_16);
}

void loop() {
display.setTextAlignment(TEXT_ALIGN_CENTER);
display.drawString(64, 8, "Hello World");
display.display();
}