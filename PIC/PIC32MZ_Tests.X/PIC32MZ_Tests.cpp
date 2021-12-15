/** \file PIC32MZ_Tests.cpp
*   \brief PIC32MZ Implementation of SysTick Example in c++

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
#define PLATFORM_NAME Pic32mz_

#ifndef USING_STDINT
#error Must compile with -DUSING_STDINT on PIC32MZ
#endif // !USING_STDINT
#ifndef USING_CSTDINT
#error Must compile with -DUSING_CSTDINT on PIC32MZ
#endif // !USING_CSTDINT
#ifdef USING_NONSTDINT_SHORTER
#error Must not compile with -DUSING_NONSTDINT_SHORTER on PIC32MZ
#endif // !USING_NONSTDINT_SHORTER
#ifdef USING_NONSTDINT_LONGER
#error Must not compile with -DUSING_NONSTDINT_LONGER on PIC32MZ
#endif // !USING_NONSTDINT_LONGER
#ifdef REDEFINE_NULLPTR
#error Must not compile with -DREDEFINE_NULLPTR on PIC32MZ
#endif // !REDEFINE_NULLPTR
#ifdef __NOEXCEPTIONS
#error Must not compile with -D__NOEXCEPTIONS on PIC32MZ
#endif // !__NOEXCEPTIONS
//</platformConfigChecks>

//<platformIncludes>
#include <xc.h>
#include <cstdio>
#include <cmath>
#include <cstdarg>
#define uSEC_PER_CLOCK (1000u)
//</platformIncludes>

/* Function Prototype for systick isr callback function */
void SysTickISRCallback(void);
#include "../../ccNOos/tests/ccNOos_tests.h"    // all things ccNOos w/tests

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


////////////////////////////////////////////////////////////////////////////////
// Finally, an applications entry points call the execution system entry points
// 1) The Main Entry Point
PLATFORM_APP_NAME(PLATFORM_NAME) theApplicationExample;
int main(int argc, char** argv)
{    
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteMain();
}
// 2) The SysTick Entry Point
void SysTickISRCallback(void)
{
    PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteSysTick();
}
/* [] END OF FILE */


