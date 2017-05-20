#include <SPI.h>
#include <SD.h>

void cardWrite(char *filename, char *contents, bool debug) {
    if (debug) {
        Serial.print("Writing to file: ");
        Serial.println(filename);
    }

    File file;
    file = SD.open(filename, FILE_WRITE);

    if (file) {
        file.println(contents);
        file.close();

        if (debug) {
            Serial.print("File written successfully: ");
            Serial.println(filename);
        }
    } else { //error
        if (debug) {
            Serial.print("Error writing to file: ");
            Serial.println(filename);
        }
        return;
    }
}

void setup() {
    Serial.begin(9600);
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
    // nothing happens after setup
}