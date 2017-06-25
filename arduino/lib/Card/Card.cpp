#include "Card.h"

// #define DEBUG_CARD

void Card::write(char *fname, char *contents, bool debug) {
    File file = SD.open(fname, FILE_WRITE);

    if (file) {
        file.println(contents);
        file.close();
    } else {
        return;
    }
}
