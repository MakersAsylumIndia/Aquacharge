#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SERIAL Serial
#define sensorPin 32      // TDS signal pin (ADC1_CH4)
#define buttonPin 25      // Button input pin

int sensorValue = 0;
float tdsValue = 0;
float Voltage = 0;

void setup() {
  SERIAL.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);  // Button with internal pull-up

  // OLED setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    SERIAL.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("TDS Sensor Ready");
  display.display();
  delay(1000);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {  // Button pressed (active low)
    // Take sensor reading
    sensorValue = analogRead(sensorPin);
    Voltage = sensorValue * (3.3 / 4095.0); // Convert ADC to voltage

    // Apply TDS formula
    tdsValue = (133.42 * Voltage * Voltage * Voltage
               - 255.86 * Voltage * Voltage
               + 857.39 * Voltage) * 0.5;

    // Print to Serial
    SERIAL.print("ADC Value = ");
    SERIAL.print(sensorValue);
    SERIAL.print(" | TDS = ");
    SERIAL.print(tdsValue, 2);
    SERIAL.print(" ppm | Status: ");
    if (tdsValue < 50) {
      SERIAL.println("PURE");
    } else {
      SERIAL.println("IMPURE");
    }

    // Show on OLED
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("TDS: ");
    display.print(tdsValue, 2);
    display.println(" ppm");

    if (tdsValue < 50) {
      display.setCursor(0,20);
      display.setTextSize(2);
      display.println("PURE");
      display.setTextSize(1);
    } else {
      display.setCursor(0,20);
      display.setTextSize(2);
      display.println("IMPURE");
      display.setTextSize(1);
    }
    display.display();

    delay(1000); // Small delay to avoid bouncing
  }
}
