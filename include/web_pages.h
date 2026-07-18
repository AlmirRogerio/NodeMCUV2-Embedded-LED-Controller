#ifndef WEB_PAGES_H
#define WEB_PAGES_H

#include <Arduino.h>

namespace WebPages
{
    String configPage();
    String successPage();
    String controlPage(const String& ipAddress);
}

#endif
