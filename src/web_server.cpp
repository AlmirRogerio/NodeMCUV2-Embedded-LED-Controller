#include "web_server.h"
#include "config.h"
#include "led_controller.h"
#include "web_pages.h"
#include "storage.h"
#include "wifi_manager.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

namespace WebServer
{

static ESP8266WebServer server(HTTP_PORT);

static void handleRoot()
{
    server.send(200, "text/html", WebPages::controlPage(WiFi.localIP().toString()));
}

static void handleStatus()
{
    server.send(200, "text/plain", LedController::isOn() ? "LED LIGADO" : "LED DESLIGADO");
}

static void handleToggle()
{
    LedController::toggle();
    server.send(200, "text/plain", "OK");
}

static void handleResetWifi()
{
    Storage::clearCredentials();
    server.send(200, "text/plain", "OK");
    delay(1000);
    ESP.restart();
}

static void handleConfigRoot()
{
    server.send(200, "text/html", WebPages::configPage());
}

static void handleSave()
{
    String ssid = server.arg("ssid_manual");
    if (ssid.length() == 0)
        ssid = server.arg("ssid");

    String password = server.arg("password");

    if (ssid.length() == 0)
    {
        server.send(400, "text/plain", "SSID não pode ser vazio!");
        return;
    }

    Serial.printf("[WebServer] Salvando SSID: %s\n", ssid.c_str());

    Storage::saveCredentials(ssid, password);
    server.send(200, "text/html", WebPages::successPage());

    delay(2000);
    ESP.restart();
}

static void handleCaptivePortal()
{
    server.sendHeader("Location", "http://192.168.4.1/");
    server.send(302, "text/plain", "");
}

static void handleNotFound()
{
    if (WifiManager::isAPMode())
    {
        server.sendHeader("Location", "http://192.168.4.1/");
        server.send(302, "text/plain", "");
        return;
    }

    server.send(404, "text/plain", "Não encontrado");
}

void initSTAMode()
{
    server.on("/", handleRoot);
    server.on("/toggle", handleToggle);
    server.on("/status", handleStatus);
    server.on("/reset-wifi", handleResetWifi);
    server.onNotFound(handleNotFound);
    server.begin();

    Serial.println("[WebServer] Modo STA iniciado.");
}

void initAPMode()
{
    server.on("/", handleConfigRoot);
    server.on("/save", HTTP_POST, handleSave);

    server.on("/generate_204", handleCaptivePortal);
    server.on("/fwlink", handleCaptivePortal);
    server.on("/hotspot-detect.html", handleCaptivePortal);
    server.on("/library/test/success.html", handleCaptivePortal);
    server.on("/connecttest.txt", handleCaptivePortal);
    server.on("/redirect", handleCaptivePortal);

    server.onNotFound(handleNotFound);
    server.begin();

    Serial.println("[WebServer] Modo AP (captive portal) iniciado.");
}

void loop()
{
    server.handleClient();
}

}
