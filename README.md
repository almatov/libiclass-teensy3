## libiclass-teensy3 Arduino library

This is the set of C++ classes.

It had been tested with Teensy-3.x boards. But it should work with other boards
except QuadratureEncoder class.

SD card interaction uses SdFat library https://github.com/greiman/SdFat.git. That
library accordingly depends on SPI library.

Multitasking is based on ChRt project https://github.com/greiman/ChRt.git. You need
patch the ChRt library with command

	patch -p0 < libiclass-teensy3/ChRt.patch

**AbsoluteEncoder** class is tested with Maxon ENX 16 EASY Absolute encoder with SSI
Gray code protocol.

**Common** class is a base class for all classes that assume concurrent access.

**Logger** class is SD card logger with simple Serial like interface. It was written
as a parallel task to avoid jitter increasing of main thread.

**MeanFilter** class is a filter of incoming data based on computing of mean value of
last set.

**MedianFilter** class is a filter of incoming data based on computing of median value
of last set.

**Qtr8a** class is tested with Pololu QTR-8A reflectance sensor array. It can compute
deviation of position relative the center of the line. The deviation accuracy is about
0.1 millimeters. The class uses adaptive threshold to discriminate black and white.

**QuadratureEncoder** class is tested with Pololu magnetic encoder kit.

**Task** class is a base for all classes that assume parallel execution.

**Tb6612** class is tested with Toshiba TB6612FNG dual motor driver.

**Vnh** class is tested with Pololu VNH2SP30 dual motor driver.
