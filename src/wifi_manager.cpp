#include "wifi_manager.h"
#include "config.h"
#include "storage.h"
#include <ESP8266WiFi.h>
#include <DNSServer.h>

namespace WifiManager
{

static DNSServer dnsServer;
static bool apModeActive = false;

bool tryConnect()
{
    if (!Storage::hasCredentials())
    {
        Serial.println("[WiFi] Nenhuma credencial salva.");
        return false;
    }

    String ssid = Storage::readSSID();
    String pass = Storage::readPassword();

    Serial.printf("[WiFi] Tentando conectar em: %s\n", ssid.c_str());

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < WIFI_TIMEOUT_SEC * 2)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    Serial.println();

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.printf("[WiFi] Conectado! IP: %s\n", WiFi.localIP().toString().c_str());
        return true;
    }

    Serial.println("[WiFi] Falha ao conectar.");
    return false;
}

void startAP()
{
    apModeActive = true;

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

    Serial.printf("[AP] Rede criada: %s\n", AP_SSID);
    Serial.printf("[AP] IP: %s\n", WiFi.softAPIP().toString().c_str());
}

void loopAP()
{
    if (apModeActive)
        dnsServer.processNextRequest();
}

bool isAPMode()
{
    return apModeActive;
}

}
