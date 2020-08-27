#!/usr/bin/env bash

while [ 1 ];
do
pre-commit run -a;
platformio run --target upload;
candump can0;
done
