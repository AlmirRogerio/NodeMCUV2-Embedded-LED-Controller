#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>

namespace Storage
{
    void init();
    void saveCredentials(const String& ssid, const String& password);
    String readSSID();
    String readPassword();
    bool hasCredentials();
    void clearCredentials();
}

#endif
