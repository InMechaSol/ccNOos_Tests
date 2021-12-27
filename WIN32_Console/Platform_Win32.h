#if PLATFORM_NAME!=Win32
    error PLATFORM_NAME must be Win32
#endif


#ifdef REDEFINE_NULLPTR
#error Must not compile with -DREDEFINE_NULLPTR on WIN32
#endif // !REDEFINE_NULLPTR
#ifdef __NOEXCEPTIONS
#error Must not compile with -D__NOEXCEPTIONS on WIN32
#endif // !__NOEXCEPTIONS


#include <ctime>
#include <thread>
#include <cstdarg>
#include <cstdio>
#include <iostream>
#include <fstream>
#include "../ccNOos/tests/ccNOos_tests.h"
#define uSEC_PER_CLOCK (1000000/CLOCKS_PER_SEC)
#define MAXLINELENGTH (80)

// 0) (Optional) Platform Config and Log Files/Devices
std::ifstream configFile;
std::ofstream LogFile;
// 1) Platform Setup Function
void platformSetup()
{
    //<platformSetup>
    // 
    // open config device
    configFile.open("conFile.json");
    LogFile.open("logFile.json");
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
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //</platformLoopDelay>
}
// 4) Basic ability for user console input
void GetMenuChars(char* inStringPtr)
{
    std::cin >> inStringPtr;
}
// 5) Basic ability for user console output
void WriteMenuLine(char* outStringPtr)
{
    std::cout << outStringPtr;
}
// 6) (Optional) Logging Output
void WriteLogLine(char* outStringPtr)
{
    int logLineLen = -1;
    while (logLineLen < MAXLINELENGTH)
        if (outStringPtr[++logLineLen] == 0x00)
            break;
    if (logLineLen > 0)
        LogFile.write(outStringPtr, logLineLen);
}
// 7) (Optional) Config Input
void ReadConfigLine(char* inStringPtr)
{
    int confLineLen = 0;
    while (confLineLen < MAXLINELENGTH)
    {
        if (0 < configFile.peek())
            configFile.read(&inStringPtr[confLineLen++], 1);
        else
            break;
    }

}
// 8) Platform API Functions (From Template?)
int SN_PrintF(char* str, unsigned int size, const char* format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    int chars = vsnprintf(str, size, format, argptr);
    va_end(argptr);
    return chars;
}
UI_8 ATO_F(const char* str, float* val)
{
    if (isNumberString((char*)str))
    {
        *val = (float)atof(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_D(const char* str, double* val)
{
    if (isNumberString((char*)str))
    {
        *val = atof(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_I8(const char* str, int8_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int8_t)atoi(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_I16(const char* str, int16_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int16_t)atoi(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_I32(const char* str, int32_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int32_t)atoll(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_I64(const char* str, int64_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int64_t)atoll(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_U8(const char* str, uint8_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint8_t)atoll(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_U16(const char* str, uint16_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint16_t)atoll(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_U32(const char* str, uint32_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint32_t)atoll(str);
        return true;
    }
    else
        return false;
}
UI_8 ATO_U64(const char* str, uint64_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint64_t)atoll(str);
        return true;
    }
    else
        return false;
}
// 9) Global Execution System Instance
executionSystemClass PLATFORM_EXESYS_NAME(PLATFORM_NAME)(uSEC_PER_CLOCK);
// 10) ExeSys API Functions (From Template?)
UI_32 getuSecTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecTicks;
}
UI_32 getHourTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->hourTicks;
}
UI_32 getuSecPerSysTick()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecPerSysTick;
}

