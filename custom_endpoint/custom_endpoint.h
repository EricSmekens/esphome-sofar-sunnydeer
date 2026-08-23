#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/web_server_base/web_server_base.h"
#include <cstring>

namespace esphome {
namespace custom_endpoint {

class CustomApiHandler : public AsyncWebHandler {
 protected:
  sensor::Sensor *uptime{nullptr};
  sensor::Sensor *act_power{nullptr};
  sensor::Sensor *voltage{nullptr};
  sensor::Sensor *current{nullptr};
  sensor::Sensor *total_power{nullptr};


 public:
  void set_act_power(sensor::Sensor *sensorUptime, sensor::Sensor *sensorPower, sensor::Sensor *sensorVoltage = nullptr, sensor::Sensor *sensorCurrent = nullptr, sensor::Sensor *sensorTotalPower = nullptr) {
    this->uptime = sensorUptime;
    
    this->act_power = sensorPower;
    this->voltage = sensorVoltage;
    this->current = sensorCurrent;
    this->total_power = sensorTotalPower;
  }

  bool canHandle(AsyncWebServerRequest *request) const override {
    if (request->method() != HTTP_GET) {
      return false;
    }

    char url_buf[AsyncWebServerRequest::URL_BUF_SIZE];
    request->url_to(url_buf);
    ESP_LOGI("custom_endpoint", "Endpoint aangeroepen: %s", url_buf);

    return strcmp(url_buf, "/rpc/Shelly.GetStatus") == 0 ||
      strcmp(url_buf, "/rpc/Shelly.GetDeviceInfo") == 0;
  }

  void handleRequest(AsyncWebServerRequest *request) override {
    char url_buf[AsyncWebServerRequest::URL_BUF_SIZE];
    request->url_to(url_buf);

    if (strcmp(url_buf, "/rpc/Shelly.GetStatus") == 0) {
      if (this->uptime == nullptr || this->act_power == nullptr || this->voltage == nullptr || this->current == nullptr || this->total_power == nullptr) {
        request->send(
            500,
            "application/json",
            "{\"error\":\"One or more sensors not configured\"}");
        return;
      }

      char response[512];
      snprintf(response, sizeof(response),
               "{"
               "\"sys\":{ \"uptime\":%.0f },"
               "\"switch:0\":{"
               "\"id\":0,"
               "\"output\":true,"
               "\"apower\":%.1f,"
               "\"voltage\":%.1f,"
               "\"current\":%.2f,"
               "\"aenergy\":{\"total\":%.1f,\"by_minute\":[0.0,0.0,0.0]}"
               "},"
               "\"wifi\":{ \"rssi\":80 }"
               "}",
               this->uptime->state,
               -this->act_power->state,
               this->voltage->state,
               this->current->state,
               -this->total_power->state);

      request->send(200, "application/json", response);
      return;
    }

    if (strcmp(url_buf, "/rpc/Shelly.GetDeviceInfo") == 0) {
      const char shelly_resp[] =
          "{\"id\":\"shellyplugsg3-1234567890bc\","
          "\"name\":\"Sofar Solar Plug\","
          "\"model\":\"S3PL-00112EU\","
          "\"mac\":\"1234567890BC\","
          "\"app\":\"PlugSG3\","
          "\"ver\":\"1.4.0\","
          "\"generation\":3}";
      request->send(200, "application/json", shelly_resp);
      return;
    }

    request->send(404, "application/json", "{\"error\":\"Not found\"}");
  }
};


class CustomEndpointComponent : public Component {
 protected:
  CustomApiHandler handler_;

 public:
  void set_act_power(sensor::Sensor *sensorUptime, sensor::Sensor *sensorPower, sensor::Sensor *sensorVoltage = nullptr, sensor::Sensor *sensorCurrent = nullptr, sensor::Sensor *sensorTotalPower = nullptr) {
    this->handler_.set_act_power(sensorUptime, sensorPower, sensorVoltage, sensorCurrent, sensorTotalPower);
  }

  void setup() override {
    if (esphome::web_server_base::global_web_server_base != nullptr) {
      esphome::web_server_base::global_web_server_base->add_handler(
          &this->handler_);

      ESP_LOGI(
          "custom_endpoint",
          "Registreren van endpoint geslaagd onder ESP-IDF!");
    } else {
      ESP_LOGE(
          "custom_endpoint",
          "Webserver component niet gevonden in YAML!");
    }
  }
};

}  // namespace custom_endpoint
}  // namespace esphome