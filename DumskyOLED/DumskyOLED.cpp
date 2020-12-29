#include <DumskyOLED.h>


void DumskyOLED::init(const uint8_t font_size) {
    // u8g2.setI2CAddress(0x3C);
    this->font_size = font_size;
    switch(font_size) {
        case 10: this->font = u8g2_font_ncenB08_tr; break;
        case 25: this->font = u8g2_font_crox5tb_tf; break;
        default: this->font = u8g2_font_ncenB08_tr; break;
    }
    
    u8g2.begin();    
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(this->font);	// choose a suitable font
    //u8g2.setFont(u8g2_font_crox5tb_tf);     // For Motion sensor
}


void DumskyOLED::clear() {
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(this->font);	// For GPS Tracker
    // u8g2.setFont(u8g2_font_ncenB08_tr);	// For GPS Tracker
    // u8g2.setFont(u8g2_font_crox5tb_tf);  // For Motion sensor
    currString = 0;
}

void DumskyOLED::renderString(String str) {
    addString(str);
    show(); 
}

void DumskyOLED::addString(String str) {
    currString++;
    if (currString > 3) {
        clear();
        currString = 0;
    } 
    u8g2.drawStr(0, currString * this->font_size, str.c_str()); 
    // u8g2.drawStr(0, currString * 10, str.c_str()); 
    // u8g2.drawStr(0, currString * 25, str.c_str());  // For Motion sensor
}

void DumskyOLED::show() {
    u8g2.sendBuffer();
}



