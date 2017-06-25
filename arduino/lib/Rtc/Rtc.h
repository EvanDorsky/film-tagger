#ifndef RTC_H
#define RTC_H

#define SECONDS 0x00
#define MINUTES 0x01
#define HOUR    0x02
#define DAY     0x03
#define DATE    0x04
#define MONTH   0x05
#define YEAR    0x06
#define CONTROL 0x0E
#define STATUS  0x0F

class Rtc {
    uint8_t addr;

public:
    int  read(uint8_t PART);
    void write(uint8_t PART, uint8_t val);
    bool in12hourMode();

    void printDateTime();

    Rtc (uint8_t addr):
        addr(addr)
    {}
};

#endif