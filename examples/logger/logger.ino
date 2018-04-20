/* logger.ino
****************************************************************************************************************
****************************************************************************************************************
*/

#include <avr/sleep.h>
#include <ChRt.h>
#include <SdFat.h>

#include <logger.h>

using namespace iclass;

const unsigned  LEDBLINKER_STACK_SIZE   ( 64 );             // bytes
const unsigned  LOGFEEDER_STACK_SIZE    ( 256 );            // bytes
const uint8_t   SPI_CS_PIN              ( 10 );             // external SD card SPI pin
const uint8_t   SPI_SCK_PIN             ( 14 );             // external SD card SPI pin
const char*     LOG_FILE_NAME           ( "test.log" );     // writing file

class LedBlinker : public ChTask<LEDBLINKER_STACK_SIZE>
{
    virtual void    routine();
};

class LogFeeder : public ChTask<LOGFEEDER_STACK_SIZE>
{
    virtual void    routine();
};

static LedBlinker   ledBlinker;
static LogFeeder    logFeeder;
static Logger       logger( LOG_FILE_NAME, 16384 );

/**************************************************************************************************************/
void
LedBlinker::routine()
{
    while ( true )
    {
        digitalWrite( LED_BUILTIN, HIGH );
        chThdSleepMilliseconds( 50 );
        digitalWrite( LED_BUILTIN, LOW );

        if ( isStopped() )
        {
            break;
        }

        chThdSleepMilliseconds( 950 );
    }
}

/**************************************************************************************************************/
void
LogFeeder::routine()
{
    unsigned        iteration( 0 );
    unsigned long   oldTm( 0 );

    while ( true )
    {
        unsigned long   tm( micros() );
        unsigned        loggerQueueSize( logger.queueSize() );
        unsigned        loggerOverflows( logger.overflows() );
        unsigned        loggerWrites( logger.writes() );
        unsigned        loggerWriteBytes( logger.writeBytes() );
        unsigned        loggerFileSize( logger.fileSize() );

        logger.print( ++iteration );
        logger.print( '\t' );
        logger.print( tm - oldTm );
        logger.print( '\t' );
        logger.print( loggerQueueSize );
        logger.print( '\t' );
        logger.print( loggerOverflows );
        logger.print( '\t' );
        logger.print( loggerWrites );
        logger.print( '\t' );
        logger.print( loggerWriteBytes );
        logger.print( '\t' );
        logger.print( loggerFileSize );
        logger.print( '\t' );

        for ( int i = 0; i < 10; ++i )
        {
            logger.print( "logfiller" );
        }

        logger.print( '\t' );
        logger.println( micros() - tm );
        oldTm = tm;

        if ( isStopped() )
        {
            break;
        }

        if ( iteration % 1000 >= 990 )
        {
            chThdSleepMilliseconds( 50 );
        }
        else
        {
            chThdSleepMilliseconds( 1 );

#if defined( __MK20DX256__ ) && !ENABLE_EXTENDED_TRANSFER_CLASS

            chThdSleepMilliseconds( 2 );

#endif

        }
    }
}

/**************************************************************************************************************/
void
chSetup()
{
    logger.start();
    ledBlinker.start( NORMALPRIO + 2 );
    chThdSleepMilliseconds( 50 );
    logger.println( "" );
    logger.println( "" );
    logFeeder.start( NORMALPRIO + 2 );
}

/**************************************************************************************************************/
void
setup()
{
    ::Serial.begin( 115200 );
    ::Serial.println( "Press any key to stop\n" );
    pinMode( LED_BUILTIN, OUTPUT );

#if defined( __MK20DX128__ )

    #error Teensy 3.0 has too small RAM size

#elif defined( __MK20DX256__ ) && !ENABLE_EXTENDED_TRANSFER_CLASS

    static SdFat        sd;

    pinMode( SPI_CS_PIN, OUTPUT );
    ::SPI.setSCK( SPI_SCK_PIN );
    sd.begin( SPI_CS_PIN );
    ::Serial.println( "SdFat" );

#elif defined( __MK20DX256__ ) && ENABLE_EXTENDED_TRANSFER_CLASS

    static SdFatEX      sd;

    pinMode( SPI_CS_PIN, OUTPUT );
    ::SPI.setSCK( SPI_SCK_PIN );
    sd.begin( SPI_CS_PIN );
    ::Serial.println( "SdFatEX" );

#else

    static SdFatSdioEX  sd;

    sd.begin();
    ::Serial.println( "SdFatSdioEX" );

#endif

    chBegin( chSetup );
    // no return from chBegin()
}

/**************************************************************************************************************/
void
loop()
{
    static int  iteration( 0 );

    ::Serial.print( ++iteration );
    ::Serial.print( '\t' );
    ::Serial.print( logger.overflows() );
    ::Serial.print( '\t' );
    ::Serial.println( logger.fileSize() );

    if ( ::Serial.available() > 0 )
    {
        logFeeder.stop();
        ledBlinker.stop();
        logger.stop();
        chThdSleepMilliseconds( 200 );
        digitalWrite( LED_BUILTIN, HIGH );
        ::Serial.print( LOG_FILE_NAME );
        ::Serial.print( '\t' );
        ::Serial.println( logger.fileSize() );

        noInterrupts();
        sleep_enable();
        sleep_cpu();
        // halt
    }

    chThdSleepMilliseconds( 1000 );
}
