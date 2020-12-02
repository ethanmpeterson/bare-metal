#define BAUD_RATE 115200

void setup() { Serial.begin(BAUD_RATE); }

void loop() {
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
}
