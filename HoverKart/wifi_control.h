//input, output, log_out
#include <WiFi.h>
#include <AsyncTCP.h>           //https://github.com/me-no-dev/AsyncTCP or https://github.com/dvarrel/AsyncTCP
#include <ESPAsyncWebServer.h>  //https://github.com/me-no-dev/ESPAsyncWebServer or https://github.com/dvarrel/ESPAsyncWebSrv
#include <AsyncWebSocket.h>     //https://github.com/me-no-dev/ESPAsyncWebServer
#include <ArduinoJson.h>        //https://arduinojson.org/
#include <LittleFS.h>

#define WIFI_CTRL_TIMEOUT 500

static class wifi_control_c final : public input, public output, public log_out, public component {
  bool all_ok = true;

  AsyncWebServer srv{ 80 };
  AsyncWebSocket ws{ "/ws" };

  tank_command last_cmd;
  uint64_t last_cmd_millis = 0;
  lns_command last_lns_cmd;
  uint64_t last_lns_cmd_millis = 0;

public:
  void setup() override {
    last_cmd_millis = 0;
    name = "WiFi Control";
    type = "In;Out;Log";
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP(ap_name, ap_pass)) logger.log(this, 'I', "OK");
    else {
      all_ok = false;
      logger.log(this, 'W', "AP error");
      return;
    }

    LittleFS.begin(true);
    ws.onEvent([&](AsyncWebSocket* ws_srv, AsyncWebSocketClient* cli, AwsEventType type, void* arg, uint8_t* data, size_t len) {
      switch (type) {
        case WS_EVT_CONNECT:
          {
          }
          break;
        case WS_EVT_DISCONNECT:
        case WS_EVT_ERROR:
          break;
        case WS_EVT_PONG:
          {
          }
          break;
        case WS_EVT_DATA:
          {
            AwsFrameInfo* info = (AwsFrameInfo*)arg;
            if (info->opcode == WS_TEXT) {
              switch ((char)data[0]) {
                case 'T':
                  sscanf((char*)data, "T:L%dR%d#", &(last_cmd.left), &(last_cmd.right));
                  last_cmd_millis = millis();
                  break;
                case 'N':
                  //Format: "N:hl" //h and l control light and horn lowercase means off, upper on
                  last_lns_cmd.horn = data[2] == 'H';
                  last_lns_cmd.lights = data[3] == 'L';
                  last_lns_cmd_millis = millis();
                  break;
                default:
                  logger.log(this, 'D', "Unknown WS text cmd");
                  break;
              }
            } else if (info->opcode == WS_BINARY) {
              memcpy(&last_cmd, data, min(len, sizeof(last_cmd)));
              last_cmd_millis = millis();
            }
          }
          break;
      }
    });
    srv.addHandler(&ws);
    srv.serveStatic("/", LittleFS, "/www/").setDefaultFile("index.htm");
    srv.onNotFound([](AsyncWebServerRequest* request) {
      request->send(LittleFS, "/www/404.htm");
    });
    srv.begin();
  }
  void loop() override {
    static uint64_t last_housekeep = 0;
    if (millis() - last_housekeep > 5000) {
      ws.cleanupClients();
      last_housekeep = millis();
    }
  }
  void log(const char* str, const char level) override {
    DynamicJsonDocument doc(4096);
    doc["type"] = "log";
    doc["uptime"] = millis();
    //doc["level"] = level;
    doc["message"] = str;
    uint16_t len = measureJson(doc);
    AsyncWebSocketMessageBuffer* buf = ws.makeBuffer(len);
    serializeJson(doc, (char*)buf->get(), len);
    ws.textAll(buf);
  }
  void set(const hover_feedback* fb_array) override {
    DynamicJsonDocument doc(512);
    doc["type"] = "info";
    for (uint8_t i = 0; i < 3; i++) {
      doc[i]["speed"]["left"] = fb_array[i].speedL_meas;
      doc[i]["speed"]["right"] = fb_array[i].speedR_meas;
      doc[i]["battery_voltage"] = float(fb_array[i].batVoltage) / 100.0;
      doc[i]["board_temp"] = fb_array[i].boardTemp;
    }
    uint16_t len = measureJson(doc);
    AsyncWebSocketMessageBuffer* buf = ws.makeBuffer(len);
    serializeJson(doc, (char*)buf->get(), len);
    ws.textAll(buf);
  }
  tank_command get() override {
    if (millis() - last_cmd_millis > WIFI_CTRL_TIMEOUT) {
      last_cmd.left = 0;
      last_cmd.right = 0;
    }
    return last_cmd;
  }
  lns_command get_lns() override {
    if (millis() - last_lns_cmd_millis > WIFI_CTRL_TIMEOUT * 4) {
      last_lns_cmd.horn = 0;
      last_lns_cmd.lights = 0;
    }
    return last_lns_cmd;
  }
} wifi_control;
