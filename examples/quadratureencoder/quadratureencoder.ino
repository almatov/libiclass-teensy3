/* quadratureencoder.ino
****************************************************************************************************************
****************************************************************************************************************

    This program prints encoder information to the serial console.

    The program has been tested with Pololu Magnetic Encoder Kit for Micro Metal Gearmotors.
*/

#include <quadratureencoder.h>

using namespace iclass;

const unsigned  CPR( 12 );
const uint8_t   PIN1( 14 );
const uint8_t   PIN2( 15 );
const float     GEAR_RATIO( 51.45f );

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

    encoder.update();

    ::Serial.print( ++iteration );
    ::Serial.print( "\t" );
    ::Serial.print( micros() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.delta() );
    ::Serial.print( "\t" );
    ::Serial.print( encoder.rotations() / GEAR_RATIO );
    ::Serial.print( "\t" );
    ::Serial.println( static_cast<int>(encoder.rpm() / GEAR_RATIO) );

    delay( 100 );
}
