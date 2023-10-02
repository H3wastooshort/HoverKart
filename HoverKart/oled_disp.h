//output
#include <Wire.h>
#define NO_ADAFRUIT_SSD1306_COLOR_COMPATIBILITY
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//why do i have to redefine these??
#define SSD1306_BLACK 0    ///< Draw 'off' pixels
#define SSD1306_WHITE 1    ///< Draw 'on' pixels
#define SSD1306_INVERSE 2  ///< Invert pixels

class oled_disp_c final : public output, public component {
  const uint8_t disp_x = 128;
  const uint8_t disp_y = 64;
  const uint8_t text_height = 8;
  const uint8_t line_height = text_height + 2;  //includes 2px padding at bottom
  const uint8_t char_per_line = disp_y / 6;     //y / char width
  Adafruit_SSD1306 oled{ disp_x, disp_y, &Wire, OLED_RST };
  bool oled_ok;
public:
  void setup() {
    name = "OLED";
    type = "Info Output";
    Wire.begin(I2C_PINS);
    oled_ok = oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    if (oled_ok) logger.log(this, 'I', "OK");
    else {
      logger.log(this, 'W', "Not Found");
      return;
    }
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.cp437(true);
    oled.println(F("HoverKart"));
    oled.display();
  }

  void set(const hover_feedback* fb_array) {
    if (oled_ok) {
      oled.clearDisplay();
      for (uint8_t n = 0; n < 3; n++) {
        uint8_t l1 = (text_height * n * 2);
        uint8_t l2 = (text_height * ((n * 2) + 1));
        //status text
        oled.setCursor(0, l1);
        char buf[char_per_line + 1];
        snprintf(buf, char_per_line, "Board %u: Temp=%dC Vbat=%04.1f", n, fb_array[n].boardTemp, (float)fb_array[n].batVoltage / 100.0);
        //Battery Bar
        oled.drawRect(0, l2, text_height, disp_y, SSD1306_WHITE);
        oled.fillRect(1, l2 + 1, text_height - 2, map(fb_array[n].batVoltage, 3400, 4000, 0, disp_y - 2), SSD1306_WHITE);
      }
    }
  }
} oled_disp;
