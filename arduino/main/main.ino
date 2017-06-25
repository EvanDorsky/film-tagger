// #include <Rtc.h>
#include <Card.h>

// Rtc rtc = Rtc(0xd0 >> 1);
Card card = Card(10);
void setup() {
    // Serial.begin(9600);
    pinMode(13, OUTPUT);
}

int i = 0;
char filename[100];
void loop() {
    if (i < 5) {
        sprintf(filename, "file_%i.txt", i);
        card.write(filename, "hiiiiiii", true);
        delay(15);
        i++;
    }
    else {
        digitalWrite(13, HIGH);
    }
    // rtc.printDateTime();
    // delay(100);
}
