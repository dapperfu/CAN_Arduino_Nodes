# **01** Static CAN Message

A minimal sketch to send a static message on CAN:

     byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};


Compile:

    pio run

Upload to Arduino:

    pio run -t upload

Monitor the serial output:

    pio run -t monitor

Monitor the CAN bus

    candump can0

```
candump can0
  can0  100   [8]  00 01 02 03 04 05 06 07
  can0  100   [8]  00 01 02 03 04 05 06 07
  can0  100   [8]  00 01 02 03 04 05 06 07
  can0  100   [8]  00 01 02 03 04 05 06 07
  can0  100   [8]  00 01 02 03 04 05 06 07
```
