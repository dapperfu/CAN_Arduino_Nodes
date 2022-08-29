#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN0(10); // Set CS to pin 10

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
  xTaskCreate(TaskSend, "Send" // A name just for humans
              ,
              128 // This stack size can be checked & adjusted by reading the
                  // Stack Highwater
              ,
              NULL, 
              2, // Priority, with 3 (configMAX_PRIORITIES - 1) being the
                 // highest, and 0 being the lowest.
              NULL);
}

void loop() {}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void TaskSend(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  TickType_t xLastWakeTime;
  byte sndStat;

  xLastWakeTime = xTaskGetTickCount();

  for (;;) // A Task shall never return or exit.
  {
    sndStat = CAN0.sendMsgBuf(2, 0, 8, data);
    if (sndStat == CAN_OK) {
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
    }
    data[6]--;
    data[7]++;
    vTaskDelayUntil(&xLastWakeTime,
                    1000 / portTICK_PERIOD_MS); // wait for one second
  }
}
