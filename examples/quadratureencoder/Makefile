ARDUINO_QUIET	= 1
BOARD_TAG    	= teensy36
F_CPU        	= 180000000
ARDUINO_LIBS 	= libiclass-teensy3 ChRt SdFat SPI

include ~/opt/Arduino-Makefile/Teensy.mk

flash:
	teensy_loader_cli --mcu=$(BOARD_TAG) -w -s -v build-$(BOARD_TAG)/$(TARGET).hex
