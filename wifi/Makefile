include ../.env

PROJECT := wifi

BUILD_DIR := ../build/$(PROJECT)

SOURCES := main.cpp

$(BUILD_DIR)/km0_km4_image2.bin: $(PROJECT).ino $(SOURCES)
	arduino-cli compile \
		--fqbn $(FQBN) \
		$(if $(DEBUG),--optimize-for-debug) \
		--build-path $(abspath $(dir $@))

upload: $(BUILD_DIR)/km0_km4_image2.bin
	arduino-cli upload \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--upload-property upload.auto_mode=Enable \
		--input-file $<

.PHONY: upload
