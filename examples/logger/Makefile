ARDUINO_QUIET   = 1
BOARD_TAG       = teensy36
F_CPU           = 180000000
ARDUINO_LIBS    = SPI SdFat ChRt libiclass-teensy3

include ~/opt/Arduino-Makefile/Teensy.mk

flash:
	        teensy_loader_cli --mcu=$(BOARD_TAG) -w -s -v build-$(BOARD_TAG)/$(TARGET).hex
