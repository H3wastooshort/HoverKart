typedef struct {
  int16_t steer = 0;
  int16_t speed = 0;
  uint32_t crc;
} hover_command;

typedef struct {
  int16_t iSpeedL;  // 100* km/h
  int16_t iSpeedR;  // 100* km/h
  uint16_t iHallSkippedL;
  uint16_t iHallSkippedR;
  uint16_t iTemp;  // °C
  uint16_t iVolt;  // 100* V
  int16_t iAmpL;   // 100* A
  int16_t iAmpR;   // 100* A
  uint32_t crc;
} hover_feedback;


static class hover {
#define HOVER_BAUDRATE 115200
  HardwareSerial ser0(0);
  HardwareSerial ser1(1);
  HardwareSerial ser2(2);

#define SEND_STUFF write((uint8_t*)&cmd, sizeof(hover_command))
  void send(hover_command& cmd) {
    ser0.SEND_STUFF;
    ser1.SEND_STUFF;
    ser2.SEND_STUFF;
  }

  typedef struct {
    std::array<char, sizeof(hover_feedback)> buf;
    uint16_t idx = 0;
  } hover_feedback_buf;
  std::unique_ptr<hover_feedback> receive() {
  }
}

void
setup() {
  ser0.begin(HOVER_BAUDRATE, SERIAL_8N1, SER0_PINS);
  ser1.begin(HOVER_BAUDRATE, SERIAL_8N1, SER1_PINS);
  ser2.begin(HOVER_BAUDRATE, SERIAL_8N1, SER2_PINS);
}
void loop() {
  send(inputs::get_current());
  outputs::set_all(receive());
}
}
