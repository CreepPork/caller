#pragma once

#include <Arduino.h>

class Log
{
private:
    void static blink(int ms = 500)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(ms);
        digitalWrite(LED_BUILTIN, LOW);
        delay(ms);
    }

    void static rapid_blink(int times = 5)
    {
        for (int i = 0; i < times; i++)
        {
            blink(150);
        }
    }

public:
    void static debug(String message)
    {
#ifdef DEBUG
        blink();
        Serial.println("Debug: " + message);
#endif
    }

    void static info(String message)
    {
        blink(1000);
        Serial.println("Info: " + message);
    }

    void static warn(String message)
    {
        rapid_blink();
        Serial.println("Warning: " + message);
    }

    void static error(String message)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("Error: " + message);

        // Stop execution
        while (true)
            ;
    }
};
