#include <SPI.h>
#include <WiFiNINA.h>

#include "secrets.hpp"
#include "constants.hpp"

#include "network.cpp"
#include "slack.cpp"

Network *network;
Slack *slack;

int buttonPressed;

void setup()
{
    pinMode(BUTTON_PIN, INPUT);

    Serial.begin(9600);

#ifdef DEBUG
    while (!Serial)
    {
        ;
    }
#endif

    buttonPressed = LOW;

    network = new Network();
    network->attempt_connection();

    slack = new Slack(network);
}

void loop()
{
    network->monitor_connection();

    buttonPressed = digitalRead(BUTTON_PIN);

    if (buttonPressed == HIGH)
    {
        Log::debug("Button was pressed");

        slack->send_message("Someone wants your attention at the office! Stand up and see!");

        delay(2000);
    }
}
