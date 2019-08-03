/* bissencoder.ino
****************************************************************************************************************
****************************************************************************************************************

    This program prints encoder information to the serial console.

    The program has been tested with FAULHABER AESM-4096 Absolute encoder. This encoder has 5V output signal.
    CAUTION: Use signal level converter for input DATA_PIN when you are using Teensy-3.6 or any other non-5V
    tolerant board to avoid damaging. An example of a proper connection can be found at 'images/encoder.png'.
*/

#include <bissencoder.h>
#include <medianfilter.h>

using namespace iclass;

const unsigned  BITS( 12 );
const uint8_t   CLOCK_PIN( 8 );
const uint8_t   DATA_PIN( 7 );
const float     GEAR_RATIO( 1.0f );
const unsigned  PRINT_EACH( 100 );

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
    static unsigned         iteration( 0 );
    static BissEncoder      encoder( BITS, CLOCK_PIN, DATA_PIN );
    static MedianFilter     rpmFilter;

    encoder.update();

    int     rpm( encoder.rpm() / GEAR_RATIO );
    int     filteredRpm( rpmFilter(rpm) );

    if ( iteration % PRINT_EACH == 0 )
    {
        ::Serial.print( iteration );
        ::Serial.print( "\t" );
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

    iteration++;
    delay( 1 );
}
