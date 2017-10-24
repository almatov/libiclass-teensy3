/* logger.ino
****************************************************************************************************************
****************************************************************************************************************
*/

#include <ChRt.h>
#include <logger.h>

using namespace iclass;

const unsigned  LEDTASK_STACK_SIZE( 64 );
const unsigned  SOURCETASK_STACK_SIZE( 256 );
const uint8_t   SPI_CS_PIN( 10 );               // used for external SD card only
const uint8_t   SPI_SCK_PIN( 14 );              // used for external SD card only

class LedTask : public ChTask<LEDTASK_STACK_SIZE>
{
    virtual void    routine();
};

class SourceTask : public ChTask<SOURCETASK_STACK_SIZE>
{
    virtual void    routine();
};

LedTask     ledTask;
Logger      logger( "test.log" );
SourceTask  source;

/**************************************************************************************************************/
void
LedTask::routine()
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
SourceTask::routine()
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
        ::logger.println( tm );
        oldTm = tm;

        chThdSleepMilliseconds( 1 );
    }
}

/**************************************************************************************************************/
void
chSetup()
{
    ::logger.start();
    ::ledTask.start();
    chThdSleepMilliseconds( 50 );
    ::source.start( NORMALPRIO + 2 );
}

/**************************************************************************************************************/
void
setup()
{
    Serial.begin( 115200 );
    pinMode( LED_BUILTIN, OUTPUT );

#if defined( __MK20DX256__ ) || defined( __MK20DX128__ )

    ::logger.setSpiPins( SPI_CS_PIN, SPI_SCK_PIN );     // need for external SD card only

#endif

    chBegin( chSetup );
    // no return from chBegin()
}

/**************************************************************************************************************/
void
loop()
{
    static int  i( 0 );

    Serial.print( ++i );
    Serial.print( '\t' );
    Serial.println( logger.overflows() );

    chThdSleepMilliseconds( 1000 );
}
