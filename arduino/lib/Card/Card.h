#include <SPI.h>
#include <SD.h>

#ifndef CARD_H
#define CARD_H

class Card {
    int pin;

public:
    void write(char *filename, char *contents, bool debug);

    Card (int pin):
        pin(pin)
    {
        SD.begin(pin);
    }
};

#endif