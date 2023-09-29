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


#define START_FRAME 0xABCD
static class hover {
#define HOVER_BAUDRATE 115200
  HardwareSerial ser0(0);
  HardwareSerial ser1(1);
  HardwareSerial ser2(2);

#define SEND_STUFF write((uint8_t*)&cmd, sizeof(hover_command))


  typedef struct {
    std::array<char, sizeof(hover_feedback)> buf;
    int32_t idx = 0;
  } hover_feedback_buf;

  hover_feedback_buf bufs[3];
  hover_feedback feedbacks[3];
  void read_hoverser(Serial& ser, uint8_t n) {
    while (ser.available()) {
      static uint8_t ser_read_prev = 0;
      uint8_t ser_read_now = Serial.read();
      switch (bufs[n].idx) {
        case -1:
          if (((uint16_t)(ser_read_now) << 8) | ser_read_prev == START_FRAME)  //if start detected
            bufs[n].idx = 0;
          break;

        case sizeof(hover_feedback):  //finished reading
          bufs[n].idx = -1;
          break;

        default:
          bufs[n].buf[bufs[n].idx] = ser_read_now;
          break;
      }
      ser_read_prev = ser_read_now;
    }
  }

public:

  void send(hover_command& cmd) {
    ser0.SEND_STUFF;
    ser1.SEND_STUFF;
    ser2.SEND_STUFF;
  }

  const hover_feedback* receive() {
    read_hoverser(ser0, 0);
    read_hoverser(ser1, 1);
    read_hoverser(ser2, 2);
    return &hover_feedback;
  }

  void setup() {
    ser0.begin(HOVER_BAUDRATE, SERIAL_8N1, SER0_PINS);
    ser1.begin(HOVER_BAUDRATE, SERIAL_8N1, SER1_PINS);
    ser2.begin(HOVER_BAUDRATE, SERIAL_8N1, SER2_PINS);
  }
  void loop() {
    send(inputs::get_current());
    outputs::set_all(receive());
  }
};
