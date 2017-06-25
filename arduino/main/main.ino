#include <Rtc.h>

Rtc rtc = Rtc(0xd0 >> 1);
void setup() {
    Serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop() {
    rtc.printDateTime();
    delay(1000);
}