#include <Arduino.h>
#include "storage.h"
#include "wifi_manager.h"
#include "led_controller.h"
#include "web_server.h"

void setup()
{
    Serial.begin(115200);
    Serial.println("\n\n=============================");
    Serial.println("  NodeMCU WiFi Manager");
    Serial.println("=============================");

    Storage::init();
    LedController::init();

    if (WifiManager::tryConnect())
    {
        WebServer::initSTAMode();
        return;
    }

    WifiManager::startAP();
    WebServer::initAPMode();
}

void loop()
{
    WifiManager::loopAP();
    WebServer::loop();
}
