//output, log_out
#include <SoftwareSerial.h>  //https://github.com/plerup/espsoftwareserial

class debug_serial_c final : public log_out, public output, public component {
  bool ran_setup = false;
public:
  EspSoftwareSerial::UART ser;
  void setup() override {
    if (ran_setup) return;
    ser.begin(SERd_BAUD, EspSoftwareSerial::SWSERIAL_8N1, SERd_PINS, false);
    ser.println(F("HoverKart"));
    //ser.setDebugOutput(true);
    ran_setup = true;
  }
  void log(const char* str, const char level) override {
    ser.println(str);
  }
  void set(const hover_feedback* fb_array) override {
    ser.println();
    for (uint8_t n = 0; n < 3; n++) ser.printf("N%u\t\tL%d\tR%d\t%d°C\t%dV\n", n, fb_array[n].speedL_meas, fb_array[n].speedR_meas, fb_array[n].boardTemp, fb_array[n].batVoltage);
  }
} debug_serial;