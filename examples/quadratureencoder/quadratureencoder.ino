/* quadratureencoder.ino
****************************************************************************************************************
****************************************************************************************************************

    This program prints encoder information to the serial console.

    The program has been tested with Pololu Magnetic Encoder Kit for Micro Metal Gearmotors.
*/

#include <quadratureencoder.h>
#include <medianfilter.h>

using namespace iclass;

const unsigned  CPR( 12 );
const uint8_t   PIN1( 14 );
const uint8_t   PIN2( 15 );
const float     GEAR_RATIO( 51.45f );
const unsigned  PRINT_EACH( 20 );

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
    static unsigned             iteration( 0 );
    static QuadratureEncoder    encoder( CPR, PIN1, PIN2 );
    static MedianFilter         rpmFilter( 4 );

    encoder.update();

    int     delta( encoder.delta() );
    float   rotations( encoder.rotations() / GEAR_RATIO );
    int     rpm( encoder.rpm() / GEAR_RATIO );
    int     filteredRpm( rpmFilter(rpm) );

    if ( iteration % PRINT_EACH == 0 )
    {
        ::Serial.print( iteration );
        ::Serial.print( "\t" );
        ::Serial.print( micros() );
        ::Serial.print( "\t" );
        ::Serial.print( delta );
        ::Serial.print( "\t" );
        ::Serial.print( rotations );
        ::Serial.print( "\t" );
        ::Serial.print( rpm );
        ::Serial.print( "\t" );
        ::Serial.println( filteredRpm );
    }

    iteration++;
    delay( 5 );
}
