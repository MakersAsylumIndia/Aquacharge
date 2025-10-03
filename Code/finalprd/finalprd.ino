#include <U8g2lib.h>
#include <Wire.h>

// ---------- Pin Definitions ----------
#define sensorPin 13     // TDS sensor signal
#define buttonPin 4      // Button
#define redPin 27        // RGB LED Red
#define greenPin 25      // RGB LED Green
#define bluePin 33       // RGB LED Blue

// ---------- OLED (U8g2) ----------
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 22, /* data=*/ 21);

// ---------- Variables ----------
int sensorValue = 0;
float Voltage = 0;
float tdsValue = 0;

void setup() {
  Serial.begin(9600);

  // Button input
  pinMode(buttonPin, INPUT_PULLUP); // button connected to GND

  // RGB LED output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Turn LED off initially
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  // Initialize OLED
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "Water Purity Tester");
  u8g2.sendBuffer();
  delay(2000);
}

void loop() {
  // Wait for button press
  if (digitalRead(buttonPin) == LOW) {
    delay(50); // debounce

    // Read TDS
    sensorValue = analogRead(sensorPin);
    Voltage = sensorValue * (3.3 / 4095.0); // ESP32 ADC 12-bit

    // TDS formula
    tdsValue = (133.42 * Voltage * Voltage * Voltage 
              - 255.86 * Voltage * Voltage 
              + 857.39 * Voltage) * 0.5;

    // Print to Serial
    Serial.print("TDS Value = ");
    Serial.print(tdsValue);
    Serial.println(" ppm");

    // Show on OLED
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 10, "Water Purity Tester");

    u8g2.setFont(u8g2_font_ncenB14_tr);
    char buf[20];
    sprintf(buf, "%.1f ppm", tdsValue);
    u8g2.drawStr(0, 40, buf);

    u8g2.sendBuffer();

    // Control RGB LED
    if (tdsValue < 50) {
      setColor(0, 0, 255); // Blue
    } else if (tdsValue >= 50 && tdsValue <= 150) {
      setColor(0, 255, 0); // Green
    } else {
      setColor(255, 0, 0); // Red
    }

    delay(1000); // short delay before next read
  }
}

// ---------- Helper Function ----------
void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
