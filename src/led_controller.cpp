#include "led_controller.h"
#include "config.h"
#include <Arduino.h>

namespace LedController
{

static bool ledState = false;

void init()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
}

void toggle()
{
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? LOW : HIGH);
}

bool isOn()
{
    return ledState;
}

}
