#include "secrets.hpp"

#include "log.cpp"
#include "network.cpp"

#include "Arduino.h"

class Slack
{
private:
    char url[16] = "hooks.slack.com";

public:
    Network *network;

    Slack(Network *network)
    {
        this->network = network;
    }

    void send_message(const char *message)
    {
        Log::debug("Connecting to server");

        if (network->client.connect(url, 443))
        {
            Log::info("Sending message...");

            String post = (String) "{\"text\": \"" + message + "\"}";

            network->client.print("POST ");
            network->client.print(SLACK_WEBHOOK);
            network->client.println(" HTTP/1.1");

            network->client.println("Host: hooks.slack.com");
            network->client.println("User-Agent: Arduino/Mkr1010");
            network->client.println("Content-Type: application/json");
            network->client.println("Connection: close");
            network->client.print("Content-Length: ");
            network->client.println(post.length());
            network->client.println();
            network->client.println(post);
            network->client.println();

            while (network->client.available())
            {
                char c = network->client.read();
#ifdef DEBUG
                Serial.write(c);
#endif
            }

            if (!network->client.connected())
            {
                Serial.println();
                Log::debug("Disconnecting from server");
                network->client.stop();
            }

            Log::info("Message sent");
        }
        else
        {
            Log::warn("Failed to connect to the server");
        }
    }
};
