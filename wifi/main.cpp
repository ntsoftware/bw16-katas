#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define BLINK_STACK_SIZE 256 // words

static void task_blink(void *);

WiFiUDP udp;

IPAddress local_ip;
uint16_t local_port;

void setup()
{
    Serial.begin(115200);
    while (!Serial) {}

    xTaskCreate(task_blink, "blink", BLINK_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    char ssid[] = "TDS-Team";
    char pass[] = "password";

    while (1) {
        Serial.print("connecting to SSID ");
        Serial.println(ssid);
        int status = WiFi.begin(ssid, pass);
        delay(10000);
        if (status == WL_CONNECTED) {
            Serial.println();
            Serial.println("connected");
            break;
        }
    }

    local_ip = WiFi.localIP();
    local_port = 5000;

    Serial.print("ssid: ");
    Serial.println(WiFi.SSID());
    Serial.print("ip: ");
    Serial.println(local_ip);
    Serial.print("port: ");
    Serial.println(local_port);
    Serial.print("rssi: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    udp.begin(local_port);
}

void loop() {
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

static void task_blink(void *)
{
    pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);

    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);

    while (1) {
        digitalWrite(LED_G, HIGH);
        delay(1000);
        digitalWrite(LED_G, LOW);
        delay(1000);
    }
}
