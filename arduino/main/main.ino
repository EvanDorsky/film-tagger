#include <Rtc.h>
#include <Card.h>

Rtc *rtc;
Card *card;
void setup() {
    card = new Card(10);
    rtc = new Rtc(0xd0 >> 1);
    pinMode(13, OUTPUT);
}

int i = 0;
char filename[100];
void loop() {
    if (i < 10) {
        sprintf(filename, "file_%i.txt", i);
        card->write(filename, "some more", true);
        delay(15);
        i++;
    }
    else {
        digitalWrite(13, HIGH);
    }
    rtc->printDateTime();
    delay(100);
}
