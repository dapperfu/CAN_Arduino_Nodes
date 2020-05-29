#!/usr/bin/env bash

# Simple script to bring up SocketCAN can0 for this project.

ip link set can0 type can bitrate 500000
sleep 0.5
ip link set can0 type can restart-ms 250
sleep 0.5
ip link set up can0
