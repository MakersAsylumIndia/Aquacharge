#define SERIAL Serial
#define sensorPin 13  // use a valid ADC pin on ESP32

int sensorValue = 0;
float tdsValue = 0;
float Voltage = 0;

void setup() {
    SERIAL.begin(9600);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Voltage = sensorValue * (3.3 / 4095.0); // ESP32: 12-bit ADC, 3.3V reference

    // Adjust TDS formula based on new voltage scale
    tdsValue = (133.42 * Voltage * Voltage * Voltage 
              - 255.86 * Voltage * Voltage 
              + 857.39 * Voltage) * 0.5;

    SERIAL.print("TDS Value = "); 
    SERIAL.print(tdsValue);
    SERIAL.println(" ppm");
    delay(1000);
}
