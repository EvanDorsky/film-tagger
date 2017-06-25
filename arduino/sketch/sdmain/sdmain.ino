#include <SPI.h>
#include <SD.h>

// #define DEBUG_SD

void cardWrite(char *fname, char *contents, bool debug) {
    File file = SD.open(fname, FILE_WRITE);

    if (file) {
        file.println(contents);
        file.close();
    } else {
        return;
    }
}

void setup() {
    pinMode(13, OUTPUT);
    SD.begin(10);
}

int i = 0;
char filename[100];
void loop() {
    if (i < 10) {
        sprintf(filename, "file_%i.txt", i);
        cardWrite(filename, "hiiiiiii", true);
        delay(15);
        i++;
    }
    else {
        digitalWrite(13, HIGH);
    }
}