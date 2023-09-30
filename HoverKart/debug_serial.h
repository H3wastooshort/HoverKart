//output, log_out
#include <SoftwareSerial.h>  //https://github.com/plerup/espsoftwareserial

EspSoftwareSerial::UART debug_ser;
void debug_serial_setup() {
  debug_ser.begin(SERd_BAUD, EspSoftwareSerial::SWSERIAL_8N1, SERd_PINS, false);
  //ser.setDebugOutput(true);
}

class dserial_log_c final : public log_out {
public:
  void log(const char* str, const char level) {
    debug_ser.print(str);
  }
} dserial_log;

class dserial_out_c final : public output {
public:
  void set(const hover_feedback* fb_array) {
    debug_ser.println();
    for (uint8_t n = 0; n < 3; n++) debug_ser.printf("N%u\t\tL%d\tR%d\t%d°C\t%dV\n", n, fb_array[n].speedL_meas, fb_array[n].speedR_meas, fb_array[n].boardTemp, fb_array[n].batVoltage);
  }
} dserial_out;