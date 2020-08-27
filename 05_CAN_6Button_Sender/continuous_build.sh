#!/usr/bin/env bash

while [ 1 ];
do
pre-commit run -a;
platformio run;
sleep 5;
done
