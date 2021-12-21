//<platformConfigChecks>
#define PLATFORM_NAME QTCreatorC

#ifndef USING_STDINT
#error Must compile with -DUSING_STDINT on QTCreatorC
#endif // !USING_STDINT
#ifndef USING_CSTDINT
#error Must compile with -DUSING_CSTDINT on QTCreatorC
#endif // !USING_CSTDINT
#ifdef USING_NONSTDINT_SHORTER
#error Must not compile with -DUSING_NONSTDINT_SHORTER on QTCreatorC
#error Must not compile with -DUSING_NONSTDINT_SHORTER on QTCreatorC
#endif // !USING_NONSTDINT_SHORTER
#ifdef USING_NONSTDINT_LONGER
#error Must not compile with -DUSING_NONSTDINT_LONGER on QTCreatorC
#endif // !USING_NONSTDINT_LONGER
#ifdef REDEFINE_NULLPTR
#error Must not compile with -DREDEFINE_NULLPTR on QTCreatorC
#endif // !REDEFINE_NULLPTR
#ifdef __NOEXCEPTIONS
#error Must not compile with -D__NOEXCEPTIONS on QTCreatorC
#endif // !__NOEXCEPTIONS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#define uSEC_PER_CLOCK (1000000/CLOCKS_PER_SEC)
#define MAXLINELENGTH (80)

/* Function Prototype for systick isr callback function */
//void SysTickISRCallback(void); // not using on QTCreatorC
//</platformConfigChecks>
#include "../ccNOos/tests/ccNOos_tests.h"

//<moduleAPIFunctions>
////////////////////////////////////////////////////////////
// An Execution System Requires Platform Implementations of:
// 1) Platform Configure Function

void platformSetup()
{
    //<platformSetup>
    //
    // open config device


    // read config string??
    //
    // open log device
    // wrtie log string??
    //
    //</platformSetup>
}
// 2) Platform Start Function
void platformStart()
{
    //<platformStart>
    //</platformStart>
}
// 3) Platform Loop Delay Function
void platformLoopDelay()
{
    //<platformLoopDelay>
    usleep(100000);
    //</platformLoopDelay>
}
void GetMenuChars(char* inStringPtr)
{

}
void WriteMenuLine(char* outStringPtr)
{

}

void WriteLogLine(char* outStringPtr)
{

}
void ReadConfigLine(char* inStringPtr)
{


}
int SN_PrintF(char* str, unsigned int size, const char* format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    int chars = vsnprintf(str, size, format, argptr);
    va_end(argptr);
    return chars;
}
bool ATO_F(const char* str, float* val)
{
    if (isNumberString((char*)str))
    {
        *val = (float)atof(str);
        return true;
    }
    else
        return false;
}
bool ATO_D(const char* str, double* val)
{
    if (isNumberString((char*)str))
    {
        *val = atof(str);
        return true;
    }
    else
        return false;
}
bool ATO_I8(const char* str, int8_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int8_t)atoi(str);
        return true;
    }
    else
        return false;
}
bool ATO_I16(const char* str, int16_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int16_t)atoi(str);
        return true;
    }
    else
        return false;
}
bool ATO_I32(const char* str, int32_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int32_t)atoll(str);
        return true;
    }
    else
        return false;
}
bool ATO_I64(const char* str, int64_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int64_t)atoll(str);
        return true;
    }
    else
        return false;
}
bool ATO_U8(const char* str, uint8_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint8_t)atoll(str);
        return true;
    }
    else
        return false;
}
bool ATO_U16(const char* str, uint16_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint16_t)atoll(str);
        return true;
    }
    else
        return false;
}
bool ATO_U32(const char* str, uint32_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint32_t)atoll(str);
        return true;
    }
    else
        return false;
}
bool ATO_U64(const char* str, uint64_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint64_t)atoll(str);
        return true;
    }
    else
        return false;
}

PLATFORM_EXESYS_DECLARE(PLATFORM_NAME);

// and 4) Module API Functions
uint32_t getuSecTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).uSecTicks;
}
uint32_t getHourTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).hourTicks;
}
//</moduleAPIFunctions>

#ifdef COMPILE_TESTS

#else

///////////////////////////////////////////////////////////////////////
// SysTick Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_SYSTICK

//<applicationIncludes>
#include <math.h>
//</applicationIncludes>

//<applicationDefines>
#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others
//</applicationDefines>

//<applicationClass>
MODdeclareDATA(Mn);
//MODSTRUCT(Mn) SysTickClockData;
//PLATFORM_APP_CLASS_SYSTICK(PLATFORM_NAME, Mn);
//</applicationClass>

//<moduleIOFunctions>
//////////////////////////////////////////////////
// IO Devices Require Platform Implementations of
// of open,close,read,write
// This SysTick Example Application only uses write
// for each of its three application devices
// 1) Minute LED Device Write
void WriteMinLED(MODdeclarePTRIN(Mn))
{
    //<writeMinLEDdevice>
    //LED_Min_Write(MODdataPTR(Mn)->MinLEDvalue);
    //</writeMinLEDdevice>
}
// 2) Second LED Device Write
void WriteSecLED(MODdeclarePTRIN(Mn))
{
    //<writeSecLEDdevice>
    //LED_Sec_Write(MODdataPTR(Mn)->SecLEDvalue);
    //</writeSecLEDdevice>
}
// 3) Serial Device Write
void WriteTimeSerial(MODdeclarePTRIN(Mn))
{
    //<writeSerialdevice>
    printf("%s",MODdataPTR(Mn)->time);// << std::fflush;
    fflush(stdout);
    //UART_PutString(sysTickDataPtr->time);
    //</writeSerialdevice>
}
//</moduleIOFunctions>


//<moduleSerializationFunctions>
// 4) Serialization of Time String
void SerializeTimeString(MODdeclarePTRIN(Mn))
{
    int retval = sprintf(MODdataPTR(Mn)->time, "\r%02u:%02u:%02u",
        (int)(MODdataPTR(Mn)->hrCount % 100),
        (int)(MODdataPTR(Mn)->minCount % TIME_MIN_PER_HR),
        (int)(MODdataPTR(Mn)->secCount % TIME_SEC_PER_MIN)
    );
    //sysTickDataPtr->time[retval] = 0x00;
}
//</moduleSerializationFunctions>

PLATFORM_APP_CTEMPLATE(PLATFORM_NAME,Mn)

#endif //!EXAMPLE_SYSTICK

#endif // !COMPILE_TESTS

////////////////////////////////////////////////////////////////////////////////
// Finally, an applications entry points call the execution system entry points
C_OS_MAIN_TEMPLATE(PLATFORM_NAME)

