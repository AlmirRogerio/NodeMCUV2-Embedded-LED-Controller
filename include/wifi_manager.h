#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

namespace WifiManager
{
    bool tryConnect();
    void startAP();
    void loopAP();
    bool isAPMode();
}

#endif
