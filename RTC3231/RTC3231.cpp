#include <RTC3231.h>

RTC3231::RTC3231() {

}

void RTC3231::init(const char *compileDate, const char *compileTime, uint32_t timeStamp) {

    Serial.println('Initializing RTC...');

    if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");
        // Serial.flush();
        // abort();
    }

    // Serial.println('Adjusting time');
    // rtc.adjust(DateTime(F(compileDate), F(compileTime)));
    // rtc.adjust(DateTime(timeStamp));

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(compileDate), F(compileTime)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
}

uint32_t RTC3231::getTimeStamp() {
    return rtc.now().unixtime();
}

String RTC3231::getDateTime() {
    DateTime now = rtc.now();

    
    // char buf1[] = "hh:mm";
    // Serial.println(now.toString(buf1));

    char buf2[] = "YYYYMMDD-hh:mm:ss";
    // Serial.println(now.toString(buf2));

    /*
    char buf3[] = "Today is DDD, MMM DD YYYY";
    Serial.println(now.toString(buf3));

    char buf4[] = "MM-DD-YYYY";
    Serial.println(now.toString(buf4));

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");
    */

    return now.toString(buf2); 
}

String RTC3231::getDate() {
    return "";
}

String RTC3231::getTime() {
    return "";
}