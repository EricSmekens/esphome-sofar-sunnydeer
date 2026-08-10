# Sofar Solar 1-40kw-tlm-g1 ESPHome Modbus Integration

A complete, tested ESPHome configuration for monitoring **Sofar Solar** solar inverters via RS485 Modbus RTU protocol, integrated with Home Assistant and/or MQTT for real-time solar energy monitoring.

This README was heavily inspired by the great work of `JasperE84`: [Growatt_ESPHome_ESP32_Modbus_RS485_Example](https://github.com/JasperE84/Growatt_ESPHome_ESP32_Modbus_RS485_Example/blob/main/README.md)

## Tested with models:
* SOFAR SOLAR 3000 TLM G1

## Table of Contents

1. [Architecture Overview](#1-architecture-overview)

---

## 1. Architecture Overview

### System Architecture

This project creates a complete solar monitoring and control solution using a modern, local-first approach:

```
Solar Panels → SOFAR SOLAR 3000 TLM G1 → RS485/Modbus RTU → Waveshare ESP32-S3-RS485-CAN → WiFi → Home Assistant / MQTT
```

### Component Roles

**Home Assistant**
- Central monitoring and automation platform
- Real-time dashboards and energy analytics
- Historical data storage and visualization
- Automation triggers based on solar production

**ESPHome**
- ESP32 Firmware platform providing seamless Home Assistant integration
- Automatic device discovery and configuration
- Over-the-air (OTA) updates
- Native Home Assistant API integration

**Waveshare ESP32-S3-RS485-CAN**
- ESP32 microcontroller with built-in RS485 transceiver, no soldering or wiring required
- Eliminates need for external RS485 converter circuits
- WiFi connectivity for Home Assistant communication
- GPIO pins pre-configured for RS485 communication
- Easily installed in the PV circuit-breaker box because of DIN rail compatability

**Modbus RTU Protocol**
- Industrial-standard communication protocol
- Reliable data transmission over RS485
- Supports multiple data types (16-bit, 32-bit integers)
- Error detection and correction

**SOFAR Solar 3000 TLM G1**
- Solar inverter with PCB Phoenix connecter plug-in terminal for RS485
- Modbus RTU slave device (default address: 1, configurable with on-device-screen)
- Provides real-time solar production data
- System status and diagnostic information

### Benefits

- **Local Control**: No cloud dependency, works offline 👏
- **Real-time Monitoring**: 'x'-second update intervals, or less
- **Professional Integration**: Native Home Assistant device discovery
- **Expandable**: Easy to add multiple inverters or additional sensors
- **Reliable**: Industrial Modbus protocol ensures data integrity

---

## 🚨 Safety and Installation Notes

**⚠️ WARNING: High Voltage Present**
- Always disconnect AC and DC power before wiring
- Use insulated tools and follow electrical safety procedures

**Installation Requirements**
- Must be installed by qualified electrical personnel
- Comply with local electrical codes and regulations
- Obtain necessary permits and utility approvals

**System Compatibility**
- ✅ Tested with Sofar Solar 3000 TLM G1

---

## 📚 Documentation References

- [ESPHome Modbus Controller Documentation](https://esphome.io/components/modbus_controller.html)
- [Growatt Modbus Protocol Specification](SOFAR 1-40KTL G1 Modbus Protocol 2020-07-27.pdf)
- [Waveshare ESP32-S3-RS485-CAN Hardware Documentation](https://www.waveshare.com/wiki/ESP32-S3-RS485-CAN)

---

**Status:** 🪠 Fully in development 👷👷‍♀️  