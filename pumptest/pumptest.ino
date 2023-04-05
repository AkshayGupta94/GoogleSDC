#define PIN_PUMP_ON 7

void setup() {
  pinMode(PIN_PUMP_ON, OUTPUT);
}

void loop() {
  digitalWrite(PIN_PUMP_ON, HIGH);
  delay(3000);
    digitalWrite(PIN_PUMP_ON, LOW);
  delay(8000);
}
