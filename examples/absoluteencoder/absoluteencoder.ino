/* absoluteencoder.ino
****************************************************************************************************************
****************************************************************************************************************

    This program prints encoder information to the serial console.

    The program has been tested with Maxon ENX 16 EASY Absolute encoder. This encoder has 5V output signal.
    CAUTION: Use signal level converter for input DATA_PIN when you are using Teensy-3.6 or any other non-5V
    tolerant board to avoid damaging. An example of a proper connection can be found at 'images/encoder.png'.
*/

#include <absoluteencoder.h>
#include <medianfilter.h>

using namespace iclass;

const unsigned  BITS( 12 );
const uint8_t   CLOCK_PIN( 8 );
const uint8_t   DATA_PIN( 7 );
const float     GEAR_RATIO( 3.9f );

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
    static AbsoluteEncoder  encoder( BITS, CLOCK_PIN, DATA_PIN );
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
