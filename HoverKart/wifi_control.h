//input, output, log_out
#include <WiFi.h>
#include <AsyncTCP.h>           //https://github.com/me-no-dev/AsyncTCP
#include <ESPAsyncWebServer.h>  //https://github.com/me-no-dev/ESPAsyncWebServer
#include <AsyncWebSocket.h>     //https://github.com/me-no-dev/ESPAsyncWebServer
#include <ArduinoJson.h>        //https://arduinojson.org/
#include <LittleFS.h>

#define WIFI_CTRL_TIMEOUT 500

class wifi_control_c : public input, public output, public log_out {
  bool all_ok = true;

  AsyncWebServer srv{ 80 };
  AsyncWebSocket ws{ "/ws" };

  hover_command last_cmd;
  uint64_t last_cmd_millis = 0;

  void ws_event(AsyncWebSocket* ws_srv, AsyncWebSocketClient* cli, AwsEventType type, void* arg, uint8_t* data, size_t len) {
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
            sscanf(data, "G%dS%d#", &last_cmd.speed, &last_cmd.steer);
          } else if (info->opcode == WS_BINARY) {
            memcpy(&last_cmd, data, min(len, sizeof(hover_command)))
          }
        }
        break;
    }
  }

public:
  void setup() {
    name = "WiFi Control";
    type = "In;Out;Log";
    WiFi.mode(WIFI_AP);
    if (WiFi.softAP(ap_name, ap_pass)) logger.log(this, 'I', "OK");
    else {
      all_ok = false;
      logger.log(this, 'W', "AP error");
      return;
    }

    LittleFS.begin();
    ws.onEvent(ws_event);
    srv.addHandler(&ws);
    srv.serveStatic("/", LittleFS, "/www/").setDefaultFile("index.htm");
    srv.onNotFound([](AsyncWebServerRequest* request) {
      request->send(LittleFS, "/www/404.htm");
    });
    srv.begin();
  }
  void loop() {
    static uint64_t last_housekeep = 0;
    if (millis() - last_housekeep > 5000) {
      ws_srv->cleanupClients();
      last_housekeep = millis();
    }
  }
  void log(const char* str, const char level) {
    ws.textAll("");
  }
  void set(const hover_feedback* fb_array) {
    ws.textAll("");
  }
  hover_command get() {
    if (millis() - last_cmd_millis > WIFI_CTRL_TIMEOUT) {
      last_cmd.speed = 0;
      last_cmd.steer = 0;
    }
    return last_cmd;
  }
} wifi_control;
