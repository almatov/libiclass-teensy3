/* logger.ino
****************************************************************************************************************
****************************************************************************************************************
*/

#include <ChRt.h>
#include <SdFat.h>
#include <logger.h>

using namespace iclass;

const unsigned  LEDBLINKER_STACK_SIZE   ( 64 );     // bytes
const unsigned  LOGFEEDER_STACK_SIZE    ( 256 );    // bytes
const uint8_t   SPI_CS_PIN              ( 10 );     // external SD card SPI pin
const uint8_t   SPI_SCK_PIN             ( 14 );     // external SD card SPI pin

class LedBlinker : public ChTask<LEDBLINKER_STACK_SIZE>
{
    virtual void    routine();
};

class LogFeeder : public ChTask<LOGFEEDER_STACK_SIZE>
{
    virtual void    routine();
};

LedBlinker  ledBlinker;
LogFeeder   logFeeder;
Logger      logger( "test.log", 16384 );

/**************************************************************************************************************/
void
LedBlinker::routine()
{
    while ( true )
    {
        digitalWrite( LED_BUILTIN, HIGH );
        chThdSleepMilliseconds( 50 );
        digitalWrite( LED_BUILTIN, LOW );
        chThdSleepMilliseconds( 950 );
    }
}

/**************************************************************************************************************/
void
LogFeeder::routine()
{
   while ( true )
    {
        static int            i( 0 );
        static unsigned long  oldTm( 0 );
        unsigned long         tm( micros() );

        ::logger.print( ++i );
        ::logger.print( '\t' );
        ::logger.print( tm - oldTm );
        ::logger.print( '\t' );
        ::logger.print( tm );
        ::logger.print( '\t' );
        ::logger.print( ::logger.overflows() );
        ::logger.print( '\t' );

        for ( int i = 0; i < 13; ++i )
        {
            ::logger.print( "logfiller" );
        }

        ::logger.print( '\t' );
        ::logger.println( micros() - tm );
        oldTm = tm;

        chThdSleepMilliseconds( 1 );
    }
}

/**************************************************************************************************************/
void
chSetup()
{
    ::logger.start();
    ::ledBlinker.start( NORMALPRIO + 2 );
    chThdSleepMilliseconds( 50 );
    ::logFeeder.start( NORMALPRIO + 2 );
}

/**************************************************************************************************************/
void
setup()
{
    Serial.begin( 115200 );
    pinMode( LED_BUILTIN, OUTPUT );

#if defined( __MK20DX128__ )

    #error Teensy 3.0 has too small RAM size

#elif defined( __MK20DX256__ )

    static SdFat        sd;

    pinMode( SPI_CS_PIN, OUTPUT );
    SPI.setSCK( SPI_SCK_PIN );
    sd.begin( SPI_CS_PIN );

#else

    static SdFatSdioEX  sd;

    sd.begin();

#endif

    chBegin( chSetup );
    // no return from chBegin()
}

/**************************************************************************************************************/
void
loop()
{
    static int  iteration( 0 );

    Serial.print( ++iteration );
    Serial.print( '\t' );
    Serial.println( logger.overflows() );

    chThdSleepMilliseconds( 1000 );
}
