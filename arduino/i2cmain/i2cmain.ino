#include <Wire.h>

#define SECONDS 0x00
#define MINUTES 0x01
#define HOUR    0x02
#define DAY     0x03
#define DATE    0x04
#define MONTH   0x05
#define YEAR    0x06

const uint8_t LED = 13;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    pinMode(13, OUTPUT);

    delay(200);
    Serial.println("Ready to go");
}

uint8_t getByte(uint8_t addr, uint8_t reg) {
    Wire.beginTransmission(addr);
    Wire.write(reg);

    Wire.endTransmission(false);

    uint8_t boge = Wire.requestFrom(addr, (uint8_t)1);
    return Wire.read();
}

uint8_t tenByte(uint8_t b, uint8_t mask = 0xf0) {
    return ((b & mask)>>4)*10 + (b & 0x0f);
}

uint8_t rtcRead = 0xd0 >> 1;

int get(uint8_t PART, uint8_t mask = 0xf0) {
    return tenByte(getByte(rtcRead, PART), mask);
}

int seconds() {
    return get(SECONDS);
}

int minutes() {
    return get(MINUTES);
}

int hour() {
    return get(HOUR, 0x10);
}

int date() {
    return get(DATE);
}

int month() {
    return get(MONTH, 0x10);
}

int century() {
    return ((getByte(rtcRead, MONTH) & 0x80) >> 7)*100;
}

int year() {
    return century() + get(YEAR);
}

void printDateTime() {
    Serial.print("m");
    Serial.print(month());
    Serial.print(" ");
    Serial.print(date());
    Serial.print("th, ");
    Serial.print(year());
    Serial.print(" at ");
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minutes());
    Serial.print(":");
    Serial.println(seconds());
}

void loop() {
    printDateTime();

    delay(1000);
}