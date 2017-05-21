
void setup() {
    pinMode(13, OUTPUT);
    pinMode(4, INPUT);
}

bool hasExposed = false;
void loop() {
    if (digitalRead(4)) {
        hasExposed = true;
    }
    if (hasExposed) {
        digitalWrite(13, HIGH);
    }
}