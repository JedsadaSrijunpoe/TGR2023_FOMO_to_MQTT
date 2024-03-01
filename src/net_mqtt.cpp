#include "net_mqtt.h"
#include "main.h"

// constants
#define TAG "net_mqtt"

#define MQTT_BROKER "192.168.1.2"
#define MQTT_PORT 1883

#define USER "TGR_GROUP23"
#define PASS "RT388P"

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 76);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 255, 0);

// static variables
static WiFiClient wifi_client;
static PubSubClient mqtt_client(wifi_client);

// connect WiFi and MQTT broker
void net_mqtt_init(char *ssid, char *passwd)
{
    // initialize WiFi
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    if (!WiFi.config(local_IP, gateway, subnet))
    {
        Serial.println("STA Failed to configure");
    }
    WiFi.begin(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(10);
    }
    ESP_LOGI(TAG, "Connected to %s", ssid);

    // initialize MQTT
    mqtt_client.setServer(MQTT_BROKER, MQTT_PORT);
}

// connect and subscribe to topic
void net_mqtt_connect(unsigned int dev_id, char *topic, mqtt_callback_t msg_callback)
{
    String client_id = "tgr2023_" + String(dev_id);
    mqtt_client.setCallback(msg_callback);
    mqtt_client.connect(client_id.c_str(), USER, PASS);
    mqtt_client.subscribe(topic);
}

// publish message to topic
void net_mqtt_publish(char *topic, char *payload)
{
    if (mqtt_client.publish(topic, payload))
    {
        ESP_LOGI(TAG, "Message published on topic %s", topic);
        ESP_LOGI(TAG, "Payload: %s", payload);
        ESP_LOGI(TAG, "Send success");
    }
}

// maintain MQTT connection
void net_mqtt_loop(void)
{
    mqtt_client.loop();
}