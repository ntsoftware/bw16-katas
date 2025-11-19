FQBN = realtek:AmebaD:Ai-Thinker_BW16
PORT = /dev/ttyUSB0
BAUDRATE = 9600

SAMPLE_EXE = build/sample/application.axf
SAMPLE_SOURCES = \
	sample/sample.ino \
	sample/main.cpp

all: sample

sample: $(SAMPLE_EXE)

$(SAMPLE_EXE): $(SAMPLE_SOURCES)
	cd sample && arduino-cli compile \
		--fqbn $(FQBN) \
		--optimize-for-debug \
		--build-path $(abspath $(dir $@))

monitor:
	arduino-cli monitor \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--config baudrate=$(BAUDRATE) \
		--quiet

clean:
	rm -rf build

.PHONY: clean monitor sample
