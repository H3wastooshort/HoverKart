//some stuff taken from https://github.com/EFeru/hoverboard-firmware-hack-FOC/blob/main/Arduino/hoverserial/hoverserial.ino
#include <HardwareSerial.h>

#define HOVER_BAUDRATE 115200
#define HOVER_CTRL_INTERVAL 100
#define HOVER_INFO_INTERVAL 1000

HardwareSerial ser0(0);
HardwareSerial ser1(1);
HardwareSerial ser2(2);

class hover_c final : public component {

  typedef struct {
    std::array<char, sizeof(hover_feedback)> buf;
    int32_t idx = 0;
  } hover_feedback_buf;

  hover_feedback_buf bufs[3];
  hover_feedback feedbacks[3];
  void read_hoverser(Stream& ser, uint8_t n) {
    while (ser.available()) {
      static uint8_t ser_read_prev = 0;
      uint8_t ser_read_now = Serial.read();
      switch (bufs[n].idx) {
        case -1:                                                               //currently not reading
          if (((uint16_t)(ser_read_now) << 8) | ser_read_prev == START_FRAME)  //if start detected
            bufs[n].idx = 0;
          break;

        case sizeof(hover_feedback):  //finished reading
          memcpy(&feedbacks[n], bufs[n].buf.data(), sizeof(hover_feedback));
          bufs[n].idx = -1;
          break;

        default:  //reading struct
          bufs[n].buf.at(bufs[n].idx) = ser_read_now;
          break;
      }
      ser_read_prev = ser_read_now;
    }
  }

public:
#define SEND_STUFF write((uint8_t*)&cmd, sizeof(hover_command))
  void send(hover_command cmd) {
    ser0.SEND_STUFF;
    ser1.SEND_STUFF;
    ser2.SEND_STUFF;
  }

  void receive() {
    read_hoverser(ser0, 0);
    read_hoverser(ser1, 1);
    read_hoverser(ser2, 2);
  }

public:
  void setup() {
    name = "HoverCtrl";
    type = "Hoverboard";
    ser0.begin(HOVER_BAUDRATE, SERIAL_8N1, SER0_PINS);
    ser0.setDebugOutput(false);
    ser1.begin(HOVER_BAUDRATE, SERIAL_8N1, SER1_PINS);
    ser1.setDebugOutput(false);
    ser2.begin(HOVER_BAUDRATE, SERIAL_8N1, SER2_PINS);
    ser2.setDebugOutput(false);
  }

  uint64_t last_ctrl_millis = 0;
  void loop() {
    if (millis() - last_ctrl_millis > HOVER_CTRL_INTERVAL) {
      last_ctrl_millis = millis();
      send(inputs.get_current());
    }

    receive();
    static uint64_t last_info_millis = 0;
    if (millis() - last_info_millis > HOVER_INFO_INTERVAL) {
      outputs.set_all(feedbacks);
    }
  }
} hover;
