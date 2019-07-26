/* bissencoder.ino
****************************************************************************************************************
****************************************************************************************************************

    This program prints encoder information to the serial console.

    The program has been tested with FAULHABER AESM-4096 Absolute encoder. If you are using Teensy-3.6 or any
    other non-5V tolerant board make sure to change the input signal level on the DATA_PIN from 5V to 3.3V to
    avoid damaging.
*/

#include <bissencoder.h>
#include <medianfilter.h>

using namespace iclass;

const unsigned  BITS( 12 );
const uint8_t   CLOCK_PIN( 8 );
const uint8_t   DATA_PIN( 7 );
const float     GEAR_RATIO( 1.0f );

/**************************************************************************************************************/
void
setup()
{
    ::Serial.begin( 115200 );
    delay( 5000 );
}
 
/**************************************************************************************************************/
void
loop()
{
    static BissEncoder      encoder( BITS, CLOCK_PIN, DATA_PIN );
    static MedianFilter     rpmFilter;
    int                     rpm;
    int                     filteredRpm;

    for ( unsigned i = 100; i > 0; --i )
    {
        encoder.update();
        rpm = static_cast<int>( encoder.rpm() / GEAR_RATIO );
        filteredRpm = rpmFilter( rpm );
        delay( 1 );
    }

    ::Serial.print( micros() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.transmitErrors() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.deviceErrors() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.deviceWarnings() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.position() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.delta() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.rotations() / GEAR_RATIO );
    ::Serial.print( "\t" );
    ::Serial.print( rpm );
    ::Serial.print( "\t" );
    ::Serial.println( filteredRpm );
}
