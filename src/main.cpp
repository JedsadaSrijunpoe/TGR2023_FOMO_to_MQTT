#include "main.h"
#include "task_mqtt.h"
#include "task_period.h"
#include "task_fomo.h"
#include "net_mqtt.h"

// constants
#define TAG "main"

// static function prototypes
void print_memory(void);
static void mqtt_callback(char *topic, byte *payload, unsigned int length);

// static variables
bool enable_flag = true;

StaticJsonDocument<128> cmd_doc;

static char cmd_buf[128];

QueueHandle_t evt_queue;
QueueHandle_t fomo_queue;

// Setup hardware
void setup()
{
  Serial.begin(115200);
  print_memory();
  evt_queue = xQueueCreate(3, sizeof(evt_msg_t));
  fomo_queue = xQueueCreate(3, sizeof(evt_msg_t));
  // task_period_init(2000);
  task_fomo_init();
  task_mqtt_init(mqtt_callback);
}

// Main loop
void loop()
{
  net_mqtt_loop();
  delay(100);

  static bool press_state = false;
  static uint32_t prev_millis = 0;

  if (digitalRead(0) == 0)
  {
    if ((millis() - prev_millis > 500) && (press_state == false))
    {
      prev_millis = millis();
      // capture
      static evt_msg_t evt_msg;
      ESP_LOGI(TAG, "Got capture command");
      xQueueSend(fomo_queue, &evt_msg, portMAX_DELAY);
    }
    press_state = true;
  }
  else
  {
    if (press_state)
    {
      press_state = false;
    }
  }
}

// Print memory information
void print_memory()
{
  ESP_LOGI(TAG, "Total heap: %u", ESP.getHeapSize());
  ESP_LOGI(TAG, "Free heap: %u", ESP.getFreeHeap());
  ESP_LOGI(TAG, "Total PSRAM: %u", ESP.getPsramSize());
  ESP_LOGI(TAG, "Free PSRAM: %d", ESP.getFreePsram());
}

// callback function to handle MQTT message
void mqtt_callback(char *topic, byte *payload, unsigned int length)
{
  ESP_LOGI(TAG, "Message arrived on topic %s", topic);
  ESP_LOGI(TAG, "Payload: %.*s", length, payload);
  memcpy(cmd_buf, payload, length);
  cmd_buf[length] = '\0';
  deserializeJson(cmd_doc, cmd_buf);
  if (cmd_doc["capture"] == true)
  {
    // capture
    static evt_msg_t evt_msg;
    ESP_LOGI(TAG, "Got capture command");
    xQueueSend(fomo_queue, &evt_msg, portMAX_DELAY);
  }
}