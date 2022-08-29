#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <SPI.h>
#include <mcp_can.h>

void TaskBlink13(void *pvParameters);
void TaskBlink12(void *pvParameters);
void TaskBlink11(void *pvParameters);
void TaskBlink10(void *pvParameters);
void TaskBlink9(void *pvParameters);

void setup() {
  Serial.begin(115200);

  while (!Serial) {
  }

  xTaskCreate(TaskBlink13, "Blink13", 128, NULL, 0, NULL);
  xTaskCreate(TaskBlink12, "Blink12", 128, NULL, 0, NULL);
  xTaskCreate(TaskBlink11, "Blink11", 128, NULL, 0, NULL);
  xTaskCreate(TaskBlink10, "Blink10", 128, NULL, 0, NULL);
  xTaskCreate(TaskBlink9, "Blink9", 128, NULL, 0, NULL);
}

void loop() {}

void TaskBlink13(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  bool led_status = true;
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(13, OUTPUT);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN, led_status);
    led_status = !led_status;
    vTaskDelayUntil(&xLastWakeTime,
                    1000 / portTICK_PERIOD_MS); // wait for one second
  }
}

void TaskBlink12(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  bool led_status = true;
  pinMode(12, OUTPUT);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(12, led_status);
    led_status = !led_status;
    vTaskDelayUntil(&xLastWakeTime,
                    1000 / portTICK_PERIOD_MS); // wait for one second
  }
}

void TaskBlink11(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  bool led_status = true;
  pinMode(11, OUTPUT);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(11, led_status);
    led_status = !led_status;
    vTaskDelayUntil(&xLastWakeTime,
                    1000 / portTICK_PERIOD_MS); // wait for one second
  }
}

void TaskBlink10(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  bool led_status = true;
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(10, OUTPUT);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(10, led_status);
    led_status = !led_status;
    vTaskDelayUntil(&xLastWakeTime,
                    500 / portTICK_PERIOD_MS); // wait for one second
  }
}

void TaskBlink9(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  bool led_status = true;
  uint8_t pin = 9
  pinMode(pin, OUTPUT);
  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(pin, led_status);
    led_status = !led_status;
    vTaskDelayUntil(&xLastWakeTime,
                    250 / portTICK_PERIOD_MS); // wait for one second
  }
}
