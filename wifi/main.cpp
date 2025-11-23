#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "TDS-Team";
char pass[] = "password";

IPAddress local_ip;
uint16_t local_port = 5000;

WiFiUDP udp;

void setup() {
    Serial.begin(115200);
    while (!Serial) {}

    while (1) {
        Serial.print("connecting to SSID ");
        Serial.println(ssid);
        int status = WiFi.begin(ssid, pass);
        delay(10000);
        if (status == WL_CONNECTED) {
            Serial.println("connected");
            break;
        }
    }

    Serial.print("ssid: ");
    Serial.println(WiFi.SSID());
    Serial.print("ip: ");
    Serial.println(WiFi.localIP());
    Serial.print("rssi: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    local_ip = WiFi.localIP();

    udp.begin(local_port);
}

void loop()
{
    int packet_size = udp.parsePacket();
    if (packet_size) {
        char request[256];
        int request_size = udp.read(request, sizeof(request) - 1);
        request[request_size] = 0;

        // Note: make sure to read packet data before getting remote address otherwise it will be corrupt
        IPAddress remote_ip = udp.remoteIP();
        uint16_t remote_port = udp.remotePort();

        Serial.print("[");
        Serial.print(remote_ip);
        Serial.print(":");
        Serial.print(remote_port);
        Serial.print(" -> ");
        Serial.print(local_ip);
        Serial.print(":");
        Serial.print(local_port);
        Serial.print("] ");
        Serial.println(request);

        const char response[] = "hello";

        udp.beginPacket(udp.remoteIP(), udp.remotePort());
        udp.write(response);
        udp.endPacket();

        Serial.print("[");
        Serial.print(local_ip);
        Serial.print(":");
        Serial.print(local_port);
        Serial.print(" -> ");
        Serial.print(remote_ip);
        Serial.print(":");
        Serial.print(remote_port);
        Serial.print("] ");
        Serial.println(response);
    }
}
