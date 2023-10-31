//Debug UART      RX, TX
#define SERd_PINS RX, TX
#define SERd_BAUD 9600
//Hoverboard UART RX, TX
#define SER0_PINS 27, 25
#define SER1_PINS 18, 19
#define SER2_PINS 23, 5
#define MAX_SPEED 60
#define INVERT_AXIS_1 false
#define INVERT_AXIS_2 false
#define INVERT_AXIS_3 true 
//I2C            SDA,SCL
#define I2C_PINS  21, 22
//OLED
#define OLED_RST  2
#define OLED_ADDR 0x3D
//Lights 'n Sounds
#define LIGHTS_PIN 0
#define HORN_PIN 2
//WiFi
const String ap_name = "HoverKart";
const String ap_pass = "bruh, insecure";
