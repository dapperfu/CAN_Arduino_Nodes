#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

void TaskBlink(void *pvParameters);

void setup() {
  Serial.begin(115200);

  while (!Serial) {
  }

  xTaskCreate(TaskBlink, "Blink", 128, NULL, 0, NULL);
}

void loop() {}

void TaskBlink(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  bool led_status = true;
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, led_status);
    led_status = !led_status;
    vTaskDelayUntil(&xLastWakeTime,
                    1000 / portTICK_PERIOD_MS); // wait for one second
  }
}
