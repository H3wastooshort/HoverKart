//largely taken from https://github.com/EFeru/hoverboard-firmware-hack-FOC/blob/main/Arduino/hoverserial/hoverserial.ino

struct vector_command {
  float speed = 0;  // y axis
  float steer = 0;  // x axis
};
struct tank_command {
  float left = 0;
  float right = 0;
};

#define START_FRAME 0xABCD
struct hover_command {
  uint16_t start = START_FRAME;
  int16_t left = 0;
  int16_t right = 0;
  uint16_t checksum;
};

struct hover_feedback {
  int16_t cmd1;
  int16_t cmd2;
  int16_t speedR_meas;
  int16_t speedL_meas;
  int16_t batVoltage;
  int16_t boardTemp;
  uint16_t cmdLed;
  uint16_t checksum;
};

struct lns_command {
  bool horn = 0;
  bool lights = 0;
};
