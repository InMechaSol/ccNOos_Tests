/** \file WIN32_Console.cpp
*   \brief WIN32 Console Implementation of SysTick Example in c++

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
//</platformConfigChecks>

//<platformIncludes>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <thread>
#include "../ccNOos/tests/ccNOos_tests.h"
//</platformIncludes>

//<platformAppDefines>
#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others
//</platformAppDefines>

/* Function Prototype for systick isr callback function */
//void SysTickISRCallback(void);


#define USEC_PER_TICK (1000u)

class PIC32MZ_SysTickApplication
{
public:
    linkedEntryPointClass setupListHead;
    linkedEntryPointClass loopListHead;
    linkedEntryPointClass systickListHead;
    linkedEntryPointClass exceptionListHead;
    SysTickExample_class sysTickCompMod;
    executionSystemClass SysTickExecutionSystem;
    PIC32MZ_SysTickApplication() :
        sysTickCompMod(LIGHT_OFF),
        setupListHead(&sysTickCompMod, nullptr),
        loopListHead(&sysTickCompMod, nullptr),
        systickListHead(nullptr, nullptr),
        exceptionListHead(&sysTickCompMod, nullptr),
        SysTickExecutionSystem(
            &setupListHead,
            &loopListHead,
            &systickListHead,
            &exceptionListHead,
            USEC_PER_TICK
        )
    {
        ;
    }
};

PIC32MZ_SysTickApplication theSysTickExample;

//////////////////////////////////////////////////
// IO Devices Require Platform Implementations of
// of open,close,read,write
// This SysTick Example Application only uses write
// for each of its three application devices
// 1) Minute LED Device Write
void WriteMinLED(struct SysTickStruct* sysTickDataPtr)
{
    //<writeMinLEDdevice>
    //LED_Min_Write(sysTickDataPtr->MinLEDvalue); 
    //</writeMinLEDdevice>
}
// 2) Second LED Device Write
void WriteSecLED(struct SysTickStruct* sysTickDataPtr)
{
    //<writeSecLEDdevice>
    //LED_Sec_Write(sysTickDataPtr->SecLEDvalue);
    //</writeSecLEDdevice>
}
// 3) Serial Device Write
void WriteTimeSerial(struct SysTickStruct* sysTickDataPtr)
{
    //<writeSerialdevice>

    std::cout << sysTickDataPtr->time;// << std::fflush;
    //UART_PutString(sysTickDataPtr->time); 
    //</writeSerialdevice>
}
// 4) Serialization of Time String
void SerializeTimeString(struct SysTickStruct* sysTickDataPtr)
{
    int retval = sprintf_s(sysTickDataPtr->time, "\r%02u:%02u:%02u",
        (int)(sysTickDataPtr->hrCount % 100),
        (int)(sysTickDataPtr->minCount % TIME_MIN_PER_HR),
        (int)(sysTickDataPtr->secCount % TIME_SEC_PER_MIN)
    );
    //sysTickDataPtr->time[retval] = 0x00;
}

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
////////////////////////////////////////////////////////////////////////////////
// and 4) Module API Functions
uint32_t getuSecTicks()
{
    return theSysTickExample.SysTickExecutionSystem.getExeDataPtr()->uSecTicks;
}
uint32_t getHourTicks()
{
    return theSysTickExample.SysTickExecutionSystem.getExeDataPtr()->hourTicks;
}

////////////////////////////////////////////////////////////////////////////////
// Finally, an applications entry points call the execution system entry points
// 1) The Main Entry Point
#define uSEC_PER_CLOCK (1000000/CLOCKS_PER_SEC)

int main(int argc, char** argv)
{
    clock_t tlast = clock();
    clock_t tnow, tdelta;
    uint32_t* uSecTicksPtr = &theSysTickExample.SysTickExecutionSystem.getExeDataPtr()->uSecTicks;
    uint32_t* hourTicksPtr = &theSysTickExample.SysTickExecutionSystem.getExeDataPtr()->hourTicks;
    theSysTickExample.SysTickExecutionSystem.ExecuteSetup();
    for (;;)
    {
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
                
        theSysTickExample.SysTickExecutionSystem.ExecuteLoop();
    }
    return RETURN_ERROR;
}
// 2) The SysTick Entry Point

/* [] END OF FILE */







