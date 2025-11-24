include .env

ifeq ($(OS),Windows_NT)
	PYTHON := python
	RM := del /s/q
else
	PYTHON := python3
	RM := rm -rf
endif

PROJECTS := sample wifi

all: $(PROJECTS)
	$(PYTHON) scripts/join.py $(PROJECTS) > compile_commands.json

sample:
	$(MAKE) -C $@

wifi:
	$(MAKE) -C $@

monitor:
	arduino-cli monitor \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--config baudrate=$(BAUDRATE) \
		--quiet

clean:
	$(RM) build

.PHONY: clean monitor $(PROJECTS)
