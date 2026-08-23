#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/web_server_base/web_server_base.h"

namespace esphome {
namespace custom_endpoint {

class CustomApiHandler : public AsyncWebHandler {
 protected:
  sensor::Sensor *act_power{nullptr};

 public:
  void set_act_power(sensor::Sensor *sensor) {
    this->act_power = sensor;
  }

  bool canHandle(AsyncWebServerRequest *request) const override {
    if (request->method() != HTTP_GET) {
      return false;
    }

    char url_buf[AsyncWebServerRequest::URL_BUF_SIZE];

    return request->url_to(url_buf) == "/rpc/EM1.GetStatus";
  }

  void handleRequest(AsyncWebServerRequest *request) override {
    if (this->act_power == nullptr) {
      request->send(
          500,
          "application/json",
          "{\"error\":\"Act power sensor not configured\"}");
      return;
    }

    // Read the current value from:
    // id: sofar_current_power
    const float act_power_value = this->act_power->state;

    char response[768];

    snprintf(
        response,
        sizeof(response),
        "{"
        "\"id\":0,"
        "\"voltage\":%.1f,"
        "\"current\":%.3f,"
        "\"act_power\":%.1f,"
        "\"aprt_power\":%.1f,"
        "\"pf\":%.2f,"
        "\"freq\":%.0f,"
        "\"calibration\":\"factory\","
        "\"errors\":[\"out_of_range:current\"],"
        "\"flags\":[\"count_disabled\"]"
        "}",
        NAN,
        NAN,
        act_power_value,
        NAN,
        NAN,
        NAN);

    request->send(200, "application/json", response);
  }
};


class CustomEndpointComponent : public Component {
 protected:
  CustomApiHandler handler_;

 public:
  void set_act_power(sensor::Sensor *sensor) {
    this->handler_.set_act_power(sensor);
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