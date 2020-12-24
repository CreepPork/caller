#pragma once

#include <SPI.h>
#include <WiFiNINA.h>

#include "secrets.hpp"
#include "log.cpp"

class Network
{
private:
    void print_connection()
    {
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        Serial.print("Signal strength (dBm): ");
        Serial.println(WiFi.RSSI());
    }

public:
    int status;
    WiFiSSLClient client;

    Network()
    {
        if (WiFi.status() == WL_NO_SHIELD)
        {
            Log::error("WiFi shield not present");
        }

        if (WiFi.firmwareVersion() != WIFI_FIRMWARE_LATEST_VERSION)
        {
            Log::warn("WiFi module firmware out-of-date");
        }
    }

    void attempt_connection()
    {
        while (status != WL_CONNECTED)
        {
            Log::info("Attempting to connect to WiFi");

            // Set static IP
            WiFi.config(IPAddress(NETWORK_IP), IPAddress(NETWORK_DNS), IPAddress(NETWORK_GATEWAY), IPAddress(NETWORK_GATEWAY));

            status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

            delay(10000);
        }

        print_connection();
    }

    void monitor_connection()
    {
        status = WiFi.status();

        if (status != WL_CONNECTED)
        {
            Log::warn("Lost connection to WiFi, retrying...");
            attempt_connection();

            // Re-check if successful
            monitor_connection();
        }
    }
};
