#include <Adafruit_GFX.h>
#include <logger.h>
#include <Wire.h>
#include "custom_characters.h"
#include "configuration.h"
#include "pins_config.h"
#include "display.h"

#define ssd1306 //uncomment this line when using SH1106 screen instead of SSD1306

#ifdef ssd1306
#include <Adafruit_SSD1306.h>
#else
#include <Adafruit_SH110X.h>
#endif

#define SYM_HEIGHT 14
#define SYM_WIDTH  16

extern Configuration    Config;
extern Beacon           *currentBeacon;
extern int              menuDisplay;
extern bool             symbolAvailable;

String symbolArray[10]         = {"[", ">", "j", "b", "<", "s", "u", "R", "v"};
int   symbolArraySize         = sizeof(symbolArray)/sizeof(symbolArray[0]);
const uint8_t *symbolsAPRS[]  = {runnerSymbol, carSymbol, jeepSymbol, bikeSymbol, motorcycleSymbol, shipSymbol, truckSymbol, recreationalVehicleSymbol, vanSymbol};

// T-Beams bought with soldered OLED Screen comes with only 4 pins (VCC, GND, SDA, SCL)
// If your board didn't come with 4 pins OLED Screen and comes with 5 and one of them is RST...
// Uncomment Next Line (Remember ONLY if your OLED Screen has a RST pin). This is to avoid memory issues.
//#define OLED_DISPLAY_HAS_RST_PIN

extern logging::Logger logger;

#ifdef ssd1306
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RST);
#else
Adafruit_SH1106G display(128, 64, &Wire, OLED_RST);
#endif

// cppcheck-suppress unusedFunction
void setup_display() {
  delay(500);
  #ifdef OLED_DISPLAY_HAS_RST_PIN // 
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW);
    delay(20);
    digitalWrite(OLED_RST, HIGH);
  #endif

  Wire.begin(OLED_SDA, OLED_SCL);
  #ifdef ssd1306
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, "SSD1306", "allocation failed!");
    while (true) {
    }
  }
  #else
  if (!display.begin(0x3c, true)) {
    logger.log(logging::LoggerLevel::LOGGER_LEVEL_ERROR, "SH1106", "allocation failed!");
    while (true) {
    }
  }
  #endif
  display.clearDisplay();
  #ifdef ssd1306
  display.setTextColor(WHITE);
  #else
  display.setTextColor(SH110X_WHITE);
  #endif
  display.setTextSize(1);
  display.setCursor(0, 0);
  #ifdef ssd1306
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(1);
  #endif
  display.display();
}

// cppcheck-suppress unusedFunction
void display_toggle(bool toggle) {
  if (toggle) {
    #ifdef ssd1306
    display.ssd1306_command(SSD1306_DISPLAYON);
    #endif
  } else {
    #ifdef ssd1306
    display.ssd1306_command(SSD1306_DISPLAYOFF);
    #endif
  }
}

// cppcheck-suppress unusedFunction
void show_display(String header, int wait) {
  display.clearDisplay();
  #ifdef ssd1306
  display.setTextColor(WHITE);
  #else
  display.setTextColor(SH110X_WHITE);
  #endif  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(header);
  #ifdef ssd1306
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(1);
  #endif
  display.display();
  delay(wait);
}

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, int wait) {
  display.clearDisplay();
  #ifdef ssd1306
  display.setTextColor(WHITE);
  #else
  display.setTextColor(SH110X_WHITE);
  #endif  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(header);
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println(line1);
  #ifdef ssd1306
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(1);
  #endif
  display.display();
  delay(wait);
}

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, String line2, int wait) {
  display.clearDisplay();
  #ifdef ssd1306
  display.setTextColor(WHITE);
  #else
  display.setTextColor(SH110X_WHITE);
  #endif  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(header);
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println(line1);
  display.setCursor(0, 26);
  display.println(line2);
  #ifdef ssd1306
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(1);
  #endif
  display.display();
  delay(wait);
}

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, String line2, String line3, int wait) {
  display.clearDisplay();
  #ifdef ssd1306
  display.setTextColor(WHITE);
  #else
  display.setTextColor(SH110X_WHITE);
  #endif  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(header);
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println(line1);
  display.setCursor(0, 26);
  display.println(line2);
  display.setCursor(0, 36);
  display.println(line3);
  #ifdef ssd1306
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(1);
  #endif
  display.display();
  delay(wait);
}

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, String line2, String line3, String line4, int wait) {
  display.clearDisplay();
  #ifdef ssd1306
  display.setTextColor(WHITE);
  #else
  display.setTextColor(SH110X_WHITE);
  #endif  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(header);
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println(line1);
  display.setCursor(0, 26);
  display.println(line2);
  display.setCursor(0, 36);
  display.println(line3);
  display.setCursor(0, 46);
  display.println(line4);
  #ifdef ssd1306
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(1);
  #endif
  display.display();
  delay(wait);
}

// cppcheck-suppress unusedFunction
void show_display(String header, String line1, String line2, String line3, String line4, String line5, int wait) {
  display.clearDisplay();
  #ifdef ssd1306
  display.setTextColor(WHITE);
  #else
  display.setTextColor(SH110X_WHITE);
  #endif  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(header);
  display.setTextSize(1);
  display.setCursor(0, 16);
  display.println(line1);
  display.setCursor(0, 26);
  display.println(line2);
  display.setCursor(0, 36);
  display.println(line3);
  display.setCursor(0, 46);
  display.println(line4);
  display.setCursor(0, 56);
  display.println(line5);
  #ifdef ssd1306
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(1);
  #endif

  if (menuDisplay==0 && Config.showSymbolOnScreen) {
    int symbol = 100;
    for (int i=0; i<symbolArraySize; i++) {
      if (currentBeacon->symbol == symbolArray[i]) {
        symbol = i;
        break;
      }
    }
    if (symbol != 100) {
      symbolAvailable = true;
      display.drawBitmap((display.width() - SYM_WIDTH), 0, symbolsAPRS[symbol], SYM_WIDTH, SYM_HEIGHT, 1);
    } else {
      symbolAvailable = false;
    }
  }
  
  display.display();
  delay(wait);
}