#include <Wire.h>

const uint8_t LED = 13;
uint8_t rtcAddr = 0xd0 >> 1;

// i2c transactions
uint8_t i2c_getByte(uint8_t addr, uint8_t reg) {
    Wire.beginTransmission(addr);
    Wire.write(reg);

    Wire.endTransmission(false);

    uint8_t boge = Wire.requestFrom(addr, (uint8_t)1);
    return Wire.read();
}

uint8_t i2c_setByte(uint8_t addr, uint8_t reg, uint8_t val) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(val);

    Wire.endTransmission(false);
}

// byte conversions
uint8_t tenByteToNum(uint8_t b, uint8_t mask = 0xf0) {
    return ((b & mask)>>4)*10 + (b & 0x0f);
}

uint8_t numToTenByte(uint8_t num, uint8_t mask = 0xf0) {
    uint8_t tens = num/10;
    return ((tens << 4) & mask) + num - (tens*10);
}

// read a register from the RTC
#define SECONDS 0x00
#define MINUTES 0x01
#define HOUR    0x02
#define DAY     0x03
#define DATE    0x04
#define MONTH   0x05
#define YEAR    0x06
int rtcRead(uint8_t PART) {
    uint8_t mask = 0xf0;
    if (PART == HOUR || PART == MONTH)
        mask = 0x10;

    int part = tenByteToNum(i2c_getByte(rtcAddr, PART), mask);

    if (PART == YEAR)
        part += ((i2c_getByte(rtcAddr, MONTH) & 0x80) >> 7)*100;
    return part;
}

void rtcWrite(uint8_t PART, uint8_t val) {
    uint8_t mask = 0xf0;
    if (PART == HOUR || PART == MONTH)
        mask = 0x10;

    i2c_setByte(rtcAddr, PART, numToTenByte(val, mask));
}

void rtcPrintDateTime() {
    Serial.print("m");
    Serial.print(rtcRead(MONTH));
    Serial.print(" ");
    Serial.print(rtcRead(DATE));
    Serial.print("th, ");
    Serial.print(rtcRead(YEAR));
    Serial.print(" at ");
    Serial.print(rtcRead(HOUR));
    Serial.print(":");
    Serial.print(rtcRead(MINUTES));
    Serial.print(":");
    Serial.println(rtcRead(SECONDS));
}

void setup() {
    Wire.begin();
    Serial.begin(9600);
    pinMode(13, OUTPUT);

    delay(200);
    Serial.println("Ready to go");
}

void loop() {
    rtcWrite(SECONDS, 4);
    rtcWrite(MINUTES, 11);
    rtcWrite(HOUR, 10);
    rtcWrite(DATE, 22);
    rtcWrite(MONTH, 6);
    rtcWrite(YEAR, 17);
    rtcPrintDateTime();

    delay(1000);
}