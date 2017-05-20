#include <SPI.h>
#include <SD.h>

File myFile;

void cardWrite(char *filename, char *contents) {
    if (!SD.begin(3)) {
        return;
    }

    myFile = SD.open(filename, FILE_WRITE);

    if (myFile) {
        myFile.println(contents);
        myFile.close();
    } else { //error
        return;
    }
}

void setup() {
    cardWrite("heyyy.txt", "what goes here boi");
}

void loop() {
    // nothing happens after setup
}