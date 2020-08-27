# 00_Blink

A minimal sketch to check that your toolchain

Compile:

    pio run

Upload to Arduino:

    pio run -t upload


Monitor the serial output:

    pio run -t monitor

The serial terminal should print the value of Analog 0.

The simplest way to validate the setup is to jumper A0 to 5V & Ground.


The LED should blink at 0.5 Hz with 50% duty cycle.

     pio check; pio run;pio run -t upload; pio run -t monitor

     canconvert can_db.json can_db.dbc; candump can0 | cantools decode can_db.dbc                    1 ↵
