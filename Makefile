include .env

PROJECTS = sample wifi

all: $(PROJECTS)
	scripts/join.py $(PROJECTS) > compile_commands.json

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
	rm -rf build

.PHONY: clean monitor $(PROJECTS)
