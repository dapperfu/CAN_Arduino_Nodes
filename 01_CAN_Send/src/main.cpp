#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <SPI.h>
#include <mcp_can.h>

// Set SPI CS to pin 10
MCP_CAN CAN0(10);

void TaskSend(void *pvParameters);

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the
  // masks and filters disabled.
  if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
    Serial.println("MCP2515 Initialized Successfully!");
  } else {
    Serial.println("Error Initializing MCP2515...");
  }

  CAN0.setMode(MCP_NORMAL);
  while (!Serial) {
  }

  // Now set up two tasks to run independently.
  xTaskCreate(TaskSend, "Send", 128, NULL, 2, NULL);
}

void loop() {
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

void TaskSend(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  TickType_t xLastWakeTime;
  byte sndStat;

  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    sndStat = CAN0.sendMsgBuf(0x100, 0, 8, data);
    if (sndStat == CAN_OK) {
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
    }

    vTaskDelayUntil(&xLastWakeTime,
                    1000 / portTICK_PERIOD_MS); // wait for one second
  }
}
