#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define EEPROM_SIZE       512
#define SSID_ADDR         0
#define SSID_MAX_LEN      32
#define PASS_ADDR         64
#define PASS_MAX_LEN      64
#define MAGIC_ADDR        128
#define MAGIC_VALUE       0xAB

#define AP_SSID           "NodeMCU-Setup"
#define AP_PASS           ""
#define WIFI_TIMEOUT_SEC  15

#define LED_PIN           LED_BUILTIN

#define HTTP_PORT         80
#define DNS_PORT          53

#endif
