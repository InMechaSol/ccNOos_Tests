/** \file WIN32_Console.cpp
*   \brief WIN32 Console Implementation of ccNOos_Tests in c++

   Copyright 2021 InMechaSol, Inc

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

Notes:
 the systick example demonstrates the basic operation of the "systick" execution
 area and timing maintained by the execution system.  when properly implemented
 and configured, this example blinks LED(s) every second and minute.  when
 properly implemented and configured, this example formats and writes a
 character array of current execution system time - once per second to a serial
 device.

 proper implementation and configuration is as follows:
 1) Create Project using Platform IDE (PSoC Creator, MPLAB X, etc)
 2) Replace the "main.c" of the project with this file, and rename appropriately
 3) Complete all sections of platform specific code enclosed in <tags> </tags>.
   <platformIncludes> - The platform specific header includes
   <platformAppDefines> - Constants of the application, unique to the platform
   <writeMinLEDdevice> - IO Write Function for Minute LED
   <writeSecLEDdevice> - IO Write Function for Second LED
   <writeSerialdevice> - IO Write Function for Time String Output
   <platformSetup> - Base Execution System Setup
   <platformStart> - Executed after platformSetup and all Modules Setup,
                                                     but before any modules Loop
   <platformLoopDelay> - Define "rest" between main loop cycles

*/
//<platformConfigChecks>
#define PLATFORM_NAME Win32

#ifndef USING_STDINT
#error Must compile with -DUSING_STDINT on WIN32
#endif // !USING_STDINT
#ifndef USING_CSTDINT
#error Must compile with -DUSING_CSTDINT on WIN32
#endif // !USING_CSTDINT
#ifdef USING_NONSTDINT_SHORTER
#error Must not compile with -DUSING_NONSTDINT_SHORTER on WIN32
#error Must not compile with -DUSING_NONSTDINT_SHORTER on WIN32
#endif // !USING_NONSTDINT_SHORTER
#ifdef USING_NONSTDINT_LONGER
#error Must not compile with -DUSING_NONSTDINT_LONGER on WIN32
#endif // !USING_NONSTDINT_LONGER
#ifdef REDEFINE_NULLPTR
#error Must not compile with -DREDEFINE_NULLPTR on WIN32
#endif // !REDEFINE_NULLPTR
#ifdef __NOEXCEPTIONS
#error Must not compile with -D__NOEXCEPTIONS on WIN32
#endif // !__NOEXCEPTIONS

//#include <cstring>
#include <ctime>
#include <thread>
#include <cstdarg>
#define uSEC_PER_CLOCK (1000000/CLOCKS_PER_SEC)

/* Function Prototype for systick isr callback function */
//void SysTickISRCallback(void); // not using on WIN32
//</platformConfigChecks>
#include "../ccNOos/tests/ccNOos_tests.h"

//<moduleAPIFunctions>
////////////////////////////////////////////////////////////
// An Execution System Requires Platform Implementations of:
// 1) Platform Configure Function
void platformSetup()
{
    //<platformSetup>
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

// Global Execution System Instance
executionSystemClass PLATFORM_EXESYS_NAME(PLATFORM_NAME)(uSEC_PER_CLOCK);
// and 4) Module API Functions
uint32_t getuSecTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecTicks;
}
uint32_t getHourTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->hourTicks;
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
//</moduleAPIFunctions>


#ifdef COMPILE_TESTS

PLATFORM_APP_CLASS_ccNOosTests(PLATFORM_NAME, MODULENAME);

#else

///////////////////////////////////////////////////////////////////////
// SysTick Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_SYSTICK

//<applicationIncludes>
#include <iostream>
#include <cstdio>
#include <cmath>
//</applicationIncludes>

//<applicationDefines>
#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others
//</applicationDefines>

//<applicationClass>
PLATFORM_APP_CLASS_SYSTICK(PLATFORM_NAME, MODULENAME);
//</applicationClass>

//<moduleIOFunctions>
//////////////////////////////////////////////////
// IO Devices Require Platform Implementations of
// of open,close,read,write
// This SysTick Example Application only uses write
// for each of its three application devices
// 1) Minute LED Device Write
void WriteMinLED(MODSTRUCTPTR_IN(MODULENAME))
{
    //<writeMinLEDdevice>
    //LED_Min_Write(sysTickDataPtr->MinLEDvalue); 
    //</writeMinLEDdevice>
}
// 2) Second LED Device Write
void WriteSecLED(MODSTRUCTPTR_IN(MODULENAME))
{
    //<writeSecLEDdevice>
    //LED_Sec_Write(sysTickDataPtr->SecLEDvalue);
    //</writeSecLEDdevice>
}
// 3) Serial Device Write
void WriteTimeSerial(MODSTRUCTPTR_IN(MODULENAME))
{
    //<writeSerialdevice>

    std::cout << SysTickClockDataPtrIn->time;// << std::fflush;
    //UART_PutString(sysTickDataPtr->time); 
    //</writeSerialdevice>
}
//</moduleIOFunctions>


//<moduleSerializationFunctions>
// 4) Serialization of Time String
void SerializeTimeString(MODSTRUCTPTR_IN(MODULENAME))
{
    int retval = sprintf_s(SysTickClockDataPtrIn->time, "\r%02u:%02u:%02u",
        (int)(SysTickClockDataPtrIn->hrCount % 100),
        (int)(SysTickClockDataPtrIn->minCount % TIME_MIN_PER_HR),
        (int)(SysTickClockDataPtrIn->secCount % TIME_SEC_PER_MIN)
    );
    //sysTickDataPtr->time[retval] = 0x00;
}
//</moduleSerializationFunctions>

#endif //!EXAMPLE_SYSTICK



///////////////////////////////////////////////////////////////////////
// Attenuators UI Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_ATTEN_UI


//<applicationIncludes>
#include <iostream>
#include <cstdio>
#include <cmath>
//</applicationIncludes>

//<applicationDefines>
//</applicationDefines>

//<applicationClass>
PLATFORM_APP_CLASS_ATTEN_UI(PLATFORM_NAME, MODULENAME);
//</applicationClass>

float ModuloFloat(float floatValue, float* intPartPtr)
{
    return modf(floatValue, intPartPtr);
}

//<moduleIOFunctions>
// platform and application specific io device functions
void WriteAttenuators(MODSTRUCTPTR_IN(MODULENAME))
{
#define bit16   ( (0b10000000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 7 )
#define bit8    ( (0b01000000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 6 )
#define bit4    ( (0b00100000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 5 )
#define bit2    ( (0b00010000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 4 )
#define bit1    ( (0b00001000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 3 )
#define bit0_25 ( (0b00000100 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 2 )
#define bit0_50 ( (0b00000010 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 1 )
    //float fracPart = (16.0 * bit16) + (8.0 * bit8) + (4.0 * bit4) + (2.0 * bit2) + (1.0 * bit1) + (0.25 * bit0_25) + (0.50 * bit0_50);
    //std::cout << fracPart;
#undef bit16  
#undef bit8
#undef bit4
#undef bit2
#undef bit1
#undef bit0_25 
#undef bit0_50 
}
void ReadUserInput(MODSTRUCTPTR_IN(MODULENAME))
{
    std::cin >> AttenUIDataPtrIn->apiLine;
    AttenUIDataPtrIn->charsRead++;
}
void WriteMenuLine(MODSTRUCTPTR_IN(MODULENAME))
{
    std::cout << AttenUIDataPtrIn->consoleLine;
}
//</moduleIOFunctions>


#endif //!EXAMPLE_ATTEN_UI


#endif // !COMPILE_TESTS


////////////////////////////////////////////////////////////////////////////////
// Finally, an applications entry points call the execution system entry points
// 1) The Main Entry Point
PLATFORM_APP_NAME(PLATFORM_NAME) theApplicationExample;
int main(int argc, char** argv)
{    
    clock_t tlast = clock();
    clock_t tnow, tdelta;

    uint32_t* uSecTicksPtr = &PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecTicks;
    uint32_t* hourTicksPtr = &PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->hourTicks;

    PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteSetup();

    for (;;)
    {
        // WIN32 platfrom doesn't use systick (the OS gets that IRQ)
        // So the exesystem clock must be maintained here
        // and rely on the ctime standard library
        tnow = clock();
        if (tnow >= tlast)
            tdelta = tnow - tlast;
        else
            tdelta = tnow + (LONG_MAX - tlast);
        tlast = tnow;
                
        (*uSecTicksPtr) += tdelta * uSEC_PER_CLOCK;
        if ((*uSecTicksPtr) >= TIME_uS_PER_HR)
        {
            (*uSecTicksPtr) = 0u;
            (*hourTicksPtr)++;
        }
                
        PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteLoop();
    }
    return RETURN_ERROR;
}
// 2) The SysTick Entry Point

/* [] END OF FILE */







