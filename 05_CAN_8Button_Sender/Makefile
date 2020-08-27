# Configuration
BUS?=can0
RATE?=500000

SRC:=$(wildcard src/*.cpp)

.PHONY: null
null:
	@echo "Please select from one of the below targets:"
	@echo "--------------------------------------------"
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'




.PHONY: build
build:.pio/build/project.checksum

.pio/build/project.checksum:${SRC}

	platformio run


can_db.dbc: can_db.json
	canconvert ${^} ${@}

.PHONY:
ovaltine: can_db.dbc
	candump ${BUS} | cantools decode ${^}

.PHONY: ovaltine2
ovaltine2: can_db.dbc
	cantools monitor --channel ${BUS} can_db.dbc

.PHONY: ${BUS}up
${BUS}up:
	sudo ip link set ${BUS} type can bitrate ${RATE}
	sleep 1
	sudo ip link set ${BUS} type can restart-ms 100
	sleep 1
	sudo ip link set ${BUS} up

.PHONY: ${BUS}down
${BUS}down:
	sudo ip link set ${BUS} down

.PHONY: vcan0up
vcan0up:
	sudo ip link add dev vcan0 type vcan
	sudo ip link set up vcan0

.PHONY: vcan0down
vcan0down:
	sudo ip link set down vcan0
