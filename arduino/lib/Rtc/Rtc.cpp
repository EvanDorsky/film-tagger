#include <Wire.h>
#include <Arduino.h>
#include "Rtc.h"

uint8_t rtcAddr = 0xd0 >> 1;

// i2c transactions
uint8_t __i2c_getByte(uint8_t _addr, uint8_t reg) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);

    Wire.endTransmission(false);

    uint8_t boge = Wire.requestFrom(_addr, (uint8_t)1);
    return Wire.read();
}

uint8_t __i2c_setByte(uint8_t _addr, uint8_t reg, uint8_t val) {
    Wire.beginTransmission(_addr);
    Wire.write(reg);
    Wire.write(val);

    Wire.endTransmission(false);
}

// byte conversions
uint8_t __tenByteToNum(uint8_t b, uint8_t mask = 0xf0) {
    return ((b & mask)>>4)*10 + (b & 0x0f);
}

uint8_t __numToTenByte(uint8_t num, uint8_t mask = 0xf0) {
    uint8_t tens = num/10;
    return ((tens << 4) & mask) + num - (tens*10);
}

// instance methods

int Rtc::read(uint8_t PART) {
    uint8_t mask = 0xf0;
    if (PART == MONTH)
        mask = 0x10;
    else if (PART == HOUR)
        mask = 0x30;

    int part = __tenByteToNum(__i2c_getByte(rtcAddr, PART), mask);

    if (PART == YEAR)
        part += ((__i2c_getByte(rtcAddr, MONTH) & 0x80) >> 7)*100;
    return part;
}

void Rtc::write(uint8_t PART, uint8_t val) {
    uint8_t mask = 0xf0;
    if (PART == MONTH)
        mask = 0x10;
    else if (PART == HOUR)
        mask = 0x30;

    __i2c_setByte(rtcAddr, PART, __numToTenByte(val, mask));
}

bool Rtc::in12hourMode() {
    return (__i2c_getByte(rtcAddr, HOUR) & 0x40) != 0;
}

void Rtc::printDateTime() {
    Serial.print("m");
    Serial.print(read(MONTH));
    Serial.print(" ");
    Serial.print(read(DATE));
    Serial.print("th, ");
    Serial.print(read(YEAR));
    Serial.print(" at ");
    Serial.print(read(HOUR));
    Serial.print(":");
    Serial.print(read(MINUTES));
    Serial.print(":");
    Serial.println(read(SECONDS));
}