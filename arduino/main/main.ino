#include <Rtc.h>
#include <Card.h>

Rtc *rtc;
Card *card;
int shutterPin = 9;
int shutterState = LOW;
void setup() {
    card = new Card(10);
    rtc = new Rtc(0xd0 >> 1);
    pinMode(13, OUTPUT);
}

char *dtStr;
void loop() {
    if (digitalRead(shutterPin) && !shutterState) {
        shutterState = HIGH;
        digitalWrite(13, HIGH);
        // rtc->dateTimeString(dtStr);
        card->write("time.txt", "test2", true);
    }
    else {
        shutterState = LOW;
    }
}
