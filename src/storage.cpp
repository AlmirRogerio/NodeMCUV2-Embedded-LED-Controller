#include "storage.h"
#include "config.h"
#include <EEPROM.h>

namespace Storage
{

static void writeString(int addr, const String& data, int maxLen)
{
    for (int i = 0; i < maxLen; i++)
    {
        if (i < (int)data.length())
            EEPROM.write(addr + i, data[i]);
        else
            EEPROM.write(addr + i, 0);
    }
    EEPROM.commit();
}

static String readString(int addr, int maxLen)
{
    String data = "";
    for (int i = 0; i < maxLen; i++)
    {
        char c = (char)EEPROM.read(addr + i);
        if (c == 0) break;
        data += c;
    }
    return data;
}

void init()
{
    EEPROM.begin(EEPROM_SIZE);
}

void saveCredentials(const String& ssid, const String& password)
{
    writeString(SSID_ADDR, ssid, SSID_MAX_LEN);
    writeString(PASS_ADDR, password, PASS_MAX_LEN);
    EEPROM.write(MAGIC_ADDR, MAGIC_VALUE);
    EEPROM.commit();
    Serial.println("[Storage] Credenciais salvas.");
}

String readSSID()
{
    return readString(SSID_ADDR, SSID_MAX_LEN);
}

String readPassword()
{
    return readString(PASS_ADDR, PASS_MAX_LEN);
}

bool hasCredentials()
{
    return EEPROM.read(MAGIC_ADDR) == MAGIC_VALUE;
}

void clearCredentials()
{
    EEPROM.write(MAGIC_ADDR, 0);
    EEPROM.commit();
    Serial.println("[Storage] Credenciais apagadas.");
}

}
