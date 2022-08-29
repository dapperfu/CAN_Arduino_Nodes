# **02** CAN Counters

An decrementing and incrementing counter on the 6th and 7th bytes of the CAN message, respectively.

A minimal sketch to check that your toolchain

Compile:

    pio run

Upload to Arduino:

    pio run -t upload


Monitor the serial output:

    pio run -t monitor



Monitor ```can0``` and decode it with the provided ```.json``` (needs converted to dbc first). 


     canconvert can_db.json can_db.dbc
     cantools monitor --channel can0 can_db.dbc
