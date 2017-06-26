#include "Card.h"

void Card::write(char *fname, char *contents, bool debug) {
    if (debug) {
        Serial.println("================");
        Serial.print("Writing to file: ");
        Serial.println(fname);
    }

    File file = SD.open(fname, FILE_WRITE);

    Serial.println("File open attempt complete");

    if (file) {
        if (debug) {
            Serial.print("File opened successfully -- file exists: ");
            Serial.println(fname);
        }
        file.println(contents);
        file.close();

        if (debug) {
            Serial.print("File written and closed successfully: ");
            Serial.println(fname);
        }
    } else {
        if (debug) {
            Serial.print("Error writing to file. File could not be opened: ");
            Serial.println(fname);
        }
        return;
    }
}
