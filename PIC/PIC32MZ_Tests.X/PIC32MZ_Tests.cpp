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
#include "../../ccNOos/tests/ccNOos_tests.h"    // all things ccNOos w/tests
#include <cstdio>
#include <cmath>
//</platformIncludes>

//<platformAppDefines>
#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others
//</platformAppDefines>

/* Function Prototype for systick isr callback function */
void SysTickISRCallback(void);


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
    PIC32MZ_SysTickApplication():
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
    {;}
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
    //UART_PutString(sysTickDataPtr->time); 
    //</writeSerialdevice>
}
// 4) Serialization of Time String
void SerializeTimeString(struct SysTickStruct* sysTickDataPtr)
{
    sprintf(sysTickDataPtr->time, "\r%02u:%02u:%02u", 
                    (int)(sysTickDataPtr->hrCount % 100), 
                    (int)(sysTickDataPtr->minCount % TIME_MIN_PER_HR),
                    (int)(sysTickDataPtr->secCount % TIME_SEC_PER_MIN)
                    );
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
    //CyDelay(1);   // on PSoc, only if desired
    ;               // let it run full throttle, its a machine after all...
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
int main(int argc, char** argv)
{    
    return theSysTickExample.SysTickExecutionSystem.ExecuteMain();
}
// 2) The SysTick Entry Point
void SysTickISRCallback(void)
{
    theSysTickExample.SysTickExecutionSystem.ExecuteSysTick();
}
/* [] END OF FILE */


