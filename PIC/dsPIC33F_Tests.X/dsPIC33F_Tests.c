/** \file dsPIC33F_Tests.c
*   \brief dsPIC33F Implementation of SysTick Example

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
//<platformIncludes>
#include "xc.h"           
#include "p33fxxxx.h"
//</platformIncludes>

//<platformAppDefines>
#define LIGHT_OFF (0u)      
/******************************* 
Set device configuration values 
********************************/
_FOSCSEL(FNOSC_FRC);                 // set oscillator mode for FRC ~ 8 Mhz
_FOSC(FCKSM_CSDCMD & OSCIOFNC_ON & POSCMD_NONE);	// use OSCIO pin for RA3
_FWDT(FWDTEN_OFF);									// turn off watchdog
//</platformAppDefines>

/* Function Prototype for systick isr callback function */
void SysTickISRCallback(void);

#include "../../ccNOos/tests/ccNOos_tests.h"    // all things ccNOos w/tests

///////////////////////////////
// Systick example consists of:
// 1) An Execution System
struct executionSystemStruct SysTickExampleSystem;
// 2) A Device Compute Module (systick example module)
struct SysTickExampleDevModStruct sysTickCompMod;
// 3) and IO Devices
//  a. Second Indicator LED Device
//      sysTickCompMod.devArray[0]
//  b. Minute Indicator LED Device
//      sysTickCompMod.devArray[1]
//  c. Time String Indicator Serial Device
//      sysTickCompMod.devArray[2]
 
//////////////////////////////////////////////////
// IO Devices Require Platform Implementations of
// of open,close,read,write
// This SysTick Example Application only uses write
// for each of its three application devices
// 1) Minute LED Device Write
int writeMinLEDdevice()
{
    //<writeMinLEDdevice>
    //LED_Min_Write(sysTickCompMod.MinLEDvalue); 
    return RETURN_SUCCESS;
    //</writeMinLEDdevice>
}
// 2) Second LED Device Write
int writeSecLEDdevice()
{
    //<writeSecLEDdevice>
    LATB = (LATB & (0x7fff)) | ((0x8000)&(sysTickCompMod.SecLEDvalue << 15));
    return RETURN_SUCCESS;
    //</writeSecLEDdevice>
}
// 3) Serial Device Write
int writeSerialdevice()
{
    //<writeSerialdevice>
    //UART_PutString(sysTickCompMod.time); 
    return RETURN_SUCCESS;
    //</writeSerialdevice>
}


////////////////////////////////////////////////////////////
// An Execution System Requires Platform Implementations of:
// 1) Platform Configure Function
int platformSetup()
{      
    //<platformSetup>
    /* 	Initialize ports */
	LATA  = 0x0000; 				// set latch levels
	TRISA = 0x0000; 				// set IO as outputs
	LATB  = 0x0000; 				// set latch levels
	TRISB = 0x0000; 				// set IO as outputs    
    return RETURN_SUCCESS;
    //</platformSetup>
}
// 2) Platform Start Function
int platformStart()
{
    //<platformStart>	
    T1CON = 0;						/* ensure Timer 1 is in reset state */
 	IFS0bits.T1IF = 0;				/* reset Timer 1 interrupt flag */
	IPC0bits.T1IP = 4;				/* set Timer1 interrupt priority level to 4 */
 	IEC0bits.T1IE = 1;				/* enable Timer 1 interrupt */
    
    // if the clock is 8 MHz and prescalar 1:1, 1ms period should be 8000 ticks
	PR1 = 4000;                     /* set Timer 1 period register */
    
	T1CONbits.TCKPS1 = 0;			/* select Timer1 Input Clock Prescale */
	T1CONbits.TCS = 0;			 	/* select timer clock */
	T1CONbits.TON = 1;			 	/* enable Timer 1 and start the count */
    return RETURN_SUCCESS;
    //</platformStart>
}
// 3) Platform Loop Delay Function
void platformLoopDelay()
{    
    //<platformLoopDelay>
    ;               // let it run full throttle, its a machine after all...
    //</platformLoopDelay>
}

////////////////////////////////////////////////////////////
// and the SysTick Example Application Requires:
// 1) Application EntryPoint Structures
struct linkedEntryPointStruct setupListHead = {
    0u,                     // next pointer is zero (end of list)
    &sysTickCompMod,        // SysTick Module Data Structure (address)
    setup_systickExample};  // the setup entry point of SysTick Module
struct linkedEntryPointStruct loopListHead = {
    0u,                     // next pointer is zero (end of list)
    &sysTickCompMod,        // SysTick Module Data Structure (address)
    loop_systickExample};   // the loop entry point of SysTick Module
struct linkedEntryPointStruct systickListHead = {
    0u,                     // next pointer is zero (end of list)
    &sysTickCompMod,        // SysTick Module Data Structure (address)
    0u};                    // no SysTick Entry Point for SysTick Module!
// 2) Application Configuration Function
int applicationConfig()
{    
    // Initialize Execution System for SysTick Example
    SysTickExampleSystem = CreateExecutionSystemStruct(
            &setupListHead,         // Link List into Execution Slot (setup)
            &loopListHead,          // Link List into Execution Slot (loop)
            &systickListHead,       // Link List into Execution Slot (systick)
            1000);                  // Set uS per SysTick to 1000 (1KHz)
    
    // Initialize Device Compute Module for sysTickExample
    sysTickCompMod = CreateSysTickExampleDevModStruct(
        writeMinLEDdevice,          // Link IO Device Write Function (min LED)
        writeSecLEDdevice,          // Link IO Device Write Function (sec LED)
        writeSerialdevice,          // Link IO Device Write Function (Serial)
        &SysTickExampleSystem,      // Link ExeSys Instance
        LIGHT_OFF                   // Set value of IO written for "light off"
        );    
    return RETURN_SUCCESS;
}
////////////////////////////////////////////////////////////////////////////////
// Finally, an applications entry points call the execution system entry points
// 1) The Main Entry Point
int main()
{    
    applicationConfig();
    return ExecuteMain(&SysTickExampleSystem);
}
// 2) The SysTick Entry Point
void SysTickISRCallback(void)
{
    int retval = ExecuteSysTick(&SysTickExampleSystem);
}// The PIC execution system also requires a uniquely named wrapper
void __attribute__((interrupt, auto_psv)) _T1Interrupt( void )
{
    SysTickISRCallback();
 	IFS0bits.T1IF = 0;				/* reset timer interrupt flag	*/
}


/* [] END OF FILE */
