#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <SPI.h>
#include <mcp_can.h>

#include <semphr.h>

#include "Button_Sender.h"

MCP_CAN CAN0(10); // Set CS to pin 10

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at
// any time.
SemaphoreHandle_t xSerialSemaphore;
SemaphoreHandle_t xCANSemaphore;

void TaskSendCounter(void *pvParameters);
void TaskSendSine(void *pvParameters);
void TaskSendButtons2(void *pvParameters);
void TaskSendButtons(void *pvParameters);

void makeNgive(SemaphoreHandle_t semaphore) {}

// the setup function runs once when you press reset or power the board
void setup() {

  // Sinks for buttons
  pinMode(BTN_GND1, OUTPUT);
  digitalWrite(BTN_GND1, LOW);

  pinMode(BTN_GND2, OUTPUT);
  digitalWrite(BTN_GND2, LOW);

  // Button Set 1
  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  // Button Set 2
  pinMode(9, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);

  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the
  // masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
  } else {
    Serial.println("Error Initializing MCP2515...");
  }

  CAN0.setMode(MCP_NORMAL);
  while (!Serial) {
    // pass
  }

  // Semaphores are useful to stop a Task proceeding,
  /// where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can
  // set it up here.
  if (xSerialSemaphore == NULL) // Check to confirm that the Serial Semaphore
                                // has not already been created.
  {
    xSerialSemaphore =
        xSemaphoreCreateMutex(); // Create a mutex semaphore we will use
                                 // to manage the Serial Port
    if ((xSerialSemaphore) != NULL)
      xSemaphoreGive((xSerialSemaphore)); // Make the Serial Port available for
                                          // use, by "Giving" the Semaphore.
  }
  if (xCANSemaphore == NULL) // Check to confirm that the Serial Semaphore
                             // has not already been created.
  {
    xCANSemaphore = xSemaphoreCreateMutex(); // Create a mutex semaphore we will
                                             // use to manage the Serial Port
    if ((xCANSemaphore) != NULL)
      xSemaphoreGive((xCANSemaphore)); // Make the Serial Port available for
                                       // use, by "Giving" the Semaphore.
  }

  // makeNgive(xSerialSemaphore);
  // makeNgive(xCANSemaphore);
  // Now set up two tasks to run independently.
  // xTaskCreate(TaskSendCounter, "TaskSendCounter", 128, NULL, 2, NULL);

  xTaskCreate(TaskSendSine, "TaskSendSine", 128, NULL, 2, NULL);

  xTaskCreate(TaskSendButtons, "TaskSendButtons", 128, NULL, 2, NULL);
  xTaskCreate(TaskSendButtons2, "TaskSendButtons2", 128, NULL, 2, NULL);
}

void loop() {}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskSendSine(void *pvParameters) {
  (void)pvParameters;

  byte sndStat;
  byte data[3] = {0x00, 0x00, 0x00};

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    data[0]] += (byte)1;
    data[1] =
        (unsigned char)(128 * sin(2 * PI * (float)(data[4]) / (float)(255)) +
                        128);
    data[2] =
        (signed char)(128 * sin(2 * PI * (float)(data[4]) / (float)(255)));

    if (xSemaphoreTake(xCANSemaphore, (TickType_t)5) == pdTRUE) {
      sndStat = CAN0.sendMsgBuf(0x250, 0, 3, data);
      xSemaphoreGive(xCANSemaphore);
    }

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // If the message was sent
      if (sndStat == CAN_OK) {
        Serial.println(" Pass: TaskSendSine");
      } else {
        Serial.println(" Error: TaskSendSine");
      }

      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelayUntil(&xLastWakeTime, 250 / portTICK_PERIOD_MS);
  }
}

void TaskSendSine2(void *pvParameters) {
  (void)pvParameters;

  byte sndStat;
  byte data[3] = {0x00, 0x00, 0x00};

  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    data[0]] += (byte)1;
    data[1] =
        (unsigned char)(128 * sin(2 * PI * (float)(data[4]) / (float)(255)) +
                        128);
    data[2] =
        (signed char)(128 * sin(2 * PI * (float)(data[4]) / (float)(255)));

    if (xSemaphoreTake(xCANSemaphore, (TickType_t)5) == pdTRUE) {
      sndStat = CAN0.sendMsgBuf(0x275, 0, 3, data);
      xSemaphoreGive(xCANSemaphore);
    }

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // If the message was sent
      if (sndStat == CAN_OK) {
        Serial.println(" Pass: TaskSendSine");
      } else {
        Serial.println(" Error: TaskSendSine");
      }

      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelayUntil(&xLastWakeTime, 250 / portTICK_PERIOD_MS);
  }
}

void TaskSendCounter(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  byte sndStat;
  byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    data[0] += (byte)1;
    data[1] += (byte)2;
    data[2] += (byte)4;
    data[3] += (byte)8;
    data[4] -= (byte)1;
    data[5] -= (byte)2;
    data[6] -= (byte)4;
    data[7] -= (byte)8;

    if (xSemaphoreTake(xCANSemaphore, (TickType_t)5) == pdTRUE) {
      sndStat = CAN0.sendMsgBuf(1, 0, 8, data);
      xSemaphoreGive(xCANSemaphore);
    }

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // If the message was sent
      if (sndStat == CAN_OK) {
        Serial.println("Pass: TaskSendCounter");
      } else {
        Serial.println("Error: TaskSendCounter");
      }

      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_PERIOD_MS);
  }
}

void TaskSendButtons2(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  byte sndStat;
  byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    // Read each of the
    data[0] = !(byte)digitalRead(12);
    data[3] = !(byte)digitalRead(9);
    // Heartbeat Counter
    data[7]++;

    if (xSemaphoreTake(xCANSemaphore, (TickType_t)5) == pdTRUE) {
      sndStat = CAN0.sendMsgBuf(2, 0, 8, data);
      xSemaphoreGive(xCANSemaphore);
    }

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // If the message was sent
      if (sndStat == CAN_OK) {
        Serial.println("Pass: TaskSendButtons");
      } else {
        Serial.println("Error: TaskSendButtons");
      }

      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelayUntil(&xLastWakeTime, 250 / portTICK_PERIOD_MS);
  }
}

void TaskSendButtons(void *pvParameters) {
  (void)pvParameters;

  TickType_t xLastWakeTime;
  byte sndStat;
  byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    // Read each of the
    data[0] = (byte)digitalRead(7);
    data[1] = (byte)digitalRead(6);
    data[2] = (byte)digitalRead(5);
    data[3] = (byte)digitalRead(4);
    // Heartbeat Counter
    data[7]++;

    if (xSemaphoreTake(xCANSemaphore, (TickType_t)5) == pdTRUE) {
      sndStat = CAN0.sendMsgBuf(3, 0, 8, data);
      xSemaphoreGive(xCANSemaphore);
    }

    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // If the message was sent
      if (sndStat == CAN_OK) {
        Serial.println("Pass: TaskSendButtons");
      } else {
        Serial.println("Error: TaskSendButtons");
      }

      xSemaphoreGive(xSerialSemaphore);
    }

    vTaskDelayUntil(&xLastWakeTime, 250 / portTICK_PERIOD_MS);
  }
}
