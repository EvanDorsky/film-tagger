#include <SPI.h>
#include <SD.h>

// #define DEBUG_SD

void cardWrite(char *filename, char *contents, bool debug) {
    #ifdef DEBUG_SD
        Serial.print("Writing to file: ");
        Serial.println(filename);
    #endif

    File file = SD.open(filename, FILE_WRITE);

    if (file) {
        file.println(contents);
        file.close();

        #ifdef DEBUG_SD
            Serial.print("File written and closed successfully: ");
            Serial.println(filename);
        #endif
    } else {
        #ifdef DEBUG_SD
            Serial.print("Error writing to file. File could not be opened: ");
            Serial.println(filename);
        #endif
        return;
    }
}

void setup() {
    #ifdef DEBUG_SD
        Serial.begin(9600);
    #endif
    pinMode(13, OUTPUT);
    SD.begin(3);
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