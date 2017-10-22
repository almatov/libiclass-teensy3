## libiclass-teensy3 Arduino library

This is the set of C++ classes.

It had been tested with Teensy-3.x boards. But it should work with other boards
except QuadratureEncoder class.

Multitasking is based on ChRt project https://github.com/greiman/ChRt.git. You need
patch the ChRt library with command

	patch -p0 < ChRt.patch

**AbsoluteEncoder** class is tested with Maxon ENX absolute encoder.

**Common** class is a base class for all classes that assume concurrent access.

**Logger** class is SD card logger with simple Serial like interface. It was written
as a parallel task to avoid of jitter increasing of main thread.

**MeanFilter** class is a filter of incoming data based on computing of mean value of
last set.

**MedianFilter** class is a filter of incoming data based on computing of median value
of last set.

**MotorRegulator** class computes PWM value for target rotary per minute speed.

**Qtr8a** class is tested with Pololu QTR-8A reflectance sensor array. It can compute
deviation of position relative the center of the line.

**QuadratureEncoder** class is tested with Pololu magnetic encoder kit.

**Task** class is a base for all classes that assume parallel execution.

**Tb6612** class is tested with Toshiba TB6612FNG dual motor driver.

**Vnh** class is tested with Pololu VNH2SP30 dual motor driver.
