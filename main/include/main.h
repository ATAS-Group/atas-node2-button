#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include <esp_log.h>
#include "sdkconfig.h"
#include "sound.h"

#define BUTTON_GPIO GPIO_NUM_4
int buttonIsPressedCounter = 0;
bool buttonIsPressed = false;
Sound* soundhandler = new Sound();