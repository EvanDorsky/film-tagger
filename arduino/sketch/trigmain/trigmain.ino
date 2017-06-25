void setup() {
    pinMode(13, OUTPUT);
    pinMode(9, INPUT);
}

void loop() {
    if (digitalRead(9))
        digitalWrite(13, HIGH);
    else
        digitalWrite(13, LOW);
}