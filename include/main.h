#ifndef __MAIN_H__
#define __MAIN_H__

// include files
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FreeRTOS.h>
#include <Esp.h>
#include <esp_log.h>

// constants
#define TASK_BUTTON_PRIO 1
#define TASK_PERIOD_PRIO 3
#define TASK_MQTT_PRIO 2
#define TASK_FOMO_PRIO 4

#define TASK_BUTTON_TYPE 0
#define TASK_PERIOD_TYPE 1
#define TASK_FOMO_TYPE 2

// #define WIFI_SSID "Atom"
// #define WIFI_PASSWORD "12356789"
// #define WIFI_SSID "SmileTae"
// #define WIFI_PASSWORD "e8668b3ff94d"
#define WIFI_SSID "TGR17_2.4G"
#define WIFI_PASSWORD ""
#define MQTT_DEV_ID 23
#define MQTT_EVT_TOPIC "/TGR_23/data"
#define MQTT_CMD_TOPIC "/TGR_23/cmd"

// type definitions
typedef struct evt_msg_t
{
    int type;
    uint32_t timestamp;
    bool pressed;
    uint32_t value;
    const char *label;
    int Day;
    const char *Height;
    String Name;
} evt_msg_t;

// shared variables
extern xQueueHandle evt_queue;
extern xQueueHandle fomo_queue;
extern bool enable_flag;

// public function prototypes

#endif // __MAIN_H__