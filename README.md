## libiclass-teensy3 Arduino library

This is a set of C++ classes.

They have been tested with Teensy-3.x boards, but most of them should work with
other boards except for the QuadratureEncoder class.

SD card interaction uses the SdFat library which, accordingly, depends on an SPI
library. This library can be found at https://github.com/greiman/SdFat.git.

Multitasking is based on ChRt project https://github.com/greiman/ChRt.git. You need
to patch the ChRt library with this command:

	patch -p0 < libiclass-teensy3/ChRt.patch

**AbsoluteEncoder** class is an absolute encoder with SSI Gray code protocol. It was
tested with Maxon ENX 16 EASY Absolute encoder.

**BissEncoder** class is an absolute encoder with BiSS-C protocol. It was tested with
FAULHABER AESM-4096 Absolute encoder.

**Common** class is a base class for all classes that assume concurrent access.

**Logger** class is an SD card logger with simple Serial like interface. It was written
as a parallel task to avoid jitter increasing of the main thread.

**MeanFilter** class is a filter of incoming data based on the computing of the mean
value of the last set.

**MedianFilter** class is a filter of incoming data based on the computing of the
median value of the last set.

**Qtr8a** class was tested with Pololu QTR-8A reflectance sensor array. It can compute
the position deviation relative to the center of the line. The deviation accuracy is about
0.1 millimeters. The class uses an adaptive threshold to discriminate black and white.

**QuadratureEncoder** class is a digital Hall sensor based encoder. It was tested with
Pololu Magnetic Encoder Kit for Micro Metal Gearmotors.

**Task** class is a base for all classes that assume parallel execution.

**Tb6612** class was tested with Toshiba TB6612FNG dual motor driver.

**Vnh** class was tested with Pololu VNH2SP30 dual motor driver.
