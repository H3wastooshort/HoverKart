//Debug UART      RX, TX
#define SERd_PINS RX, TX
#define SERd_BAUD 115200
//Hoverboard UART RX, TX
#define SER0_PINS 35, 18
#define SER1_PINS 33, 19
#define SER2_PINS 34, 23
#define MAX_SPEED 1000
#define MAX_STEER 1000
//I2C            SDA,SCL
#define I2C_PINS  25, 22
//OLED
#define OLED_RST  27
#define OLED_ADDR 0x3D
//WiFi
String ap_name = "HoverKart";
String ap_pass = "bruh, insecure";
