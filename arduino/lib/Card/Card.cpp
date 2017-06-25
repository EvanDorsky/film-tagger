#include <SPI.h>

#include "Card.h"

// #define DEBUG_CARD

void Card::write(char *filename, char *contents, bool debug) {
    File file = SD.open(filename, FILE_WRITE);

    if (file) {
        file.println(contents);
        file.close();
    } else {
        return;
    }
}
