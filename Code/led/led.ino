const int RED_PIN = 27;
const int GREEN_PIN = 25;
const int BLUE_PIN = 33;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // Nothing here – LED stays ON
  digitalWrite(RED_PIN, LOW);
  delay(500);
  digitalWrite(RED_PIN, HIGH);
  delay(500);
    digitalWrite(GREEN_PIN, LOW);
  delay(500);
  digitalWrite(GREEN_PIN, HIGH);
  delay(500);
    digitalWrite(BLUE_PIN, LOW);
  delay(500);
  digitalWrite(BLUE_PIN, HIGH);
  delay(500);
}