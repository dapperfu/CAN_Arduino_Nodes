#!/usr/bin/env bash

while [ 1 ];
do
pre-commit run -a;
platformio run --target upload;
make ovaltine2;
done
