#ifndef __TASK_FOMO_H__
#define __TASK_FOMO_H__

// include files
#include <Arduino.h>
#include <ArduinoJson.h>
#include <FreeRTOS.h>
#include <Esp.h>
#include <esp_log.h>
#include "hw_camera.h"

// shared variables

// public function prototypes
void task_fomo_init();

#endif // __TASK_FOMO_H__