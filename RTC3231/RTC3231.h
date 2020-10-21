#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

class RTC3231 {

public:

    RTC3231();
    void init(const char *compileDate, const char *compileTime, uint32_t timeStamp);
    uint32_t getTimeStamp();
    String getDateTime();
    String getDate();
    String getTime();

private:

    // RtcDS3231<TwoWire> Rtc{Wire};
    DateTime readDateTime();

    RTC_DS3231 rtc;

};