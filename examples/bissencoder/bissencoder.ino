/* bissencoder.ino
****************************************************************************************************************
****************************************************************************************************************

    This program prints encoder information to the serial console.

    The program has been tested with FAULHABER AESM-4096 Absolute encoder. This encoder has 5V output signal.
    CAUTION: Use signal level converter for input DATA_PIN when you are using Teensy-3.6 or any other non-5V
    tolerant board to avoid damaging. An example of a proper connection can be found at 'images/encoder.png'.
*/

#include <AVR/sleep.h>
#include <ChRt.h>

#include <bissencoder.h>

using namespace iclass;

const unsigned  BITS( 12 );
const uint8_t   CLOCK_PIN( 8 );
const uint8_t   DATA_PIN( 7 );
const float     GEAR_RATIO( 1.0f );

static BissEncoder  encoder( BITS, CLOCK_PIN, DATA_PIN );

/**************************************************************************************************************/
void
chSetup()
{
    encoder.start( NORMALPRIO + 2 );
}

/**************************************************************************************************************/
void
setup()
{
    ::Serial.begin( 115200 );
    delay( 5000 );
    ::Serial.println( "Press any key to stop" );

    chBegin( chSetup );
    // no return from chBegin()
}
 
/**************************************************************************************************************/
void
loop()
{
    static unsigned         iteration( 0 );

    encoder.update();

    ::Serial.print( iteration++ );
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
    ::Serial.println( static_cast<int>(encoder.rpm() / GEAR_RATIO) );

    if ( ::Serial.available() > 0 )
    {
        encoder.stop();
        chThdSleepMilliseconds( 5 );
        ::Serial.println( "Example stopped" );

        noInterrupts();
        sleep_enable();
        sleep_cpu();
        // halt
    }

    chThdSleepMilliseconds( 100 );
}
