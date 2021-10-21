/*******************************************************************************
* File: main.c
*
* Version: 1.0
*
* Description:
*  This example project demonstrates the basic operation of the System Tick
*  Timer: periodic LED triggering - every second and minute.
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>

#if(CY_PSOC4)
    #define LIGHT_OFF                       (1u)
    #define LIGHT_ON                        (0u)
#else
    #define LIGHT_OFF                       (0u)
    #define LIGHT_ON                        (1u)
#endif /* (CY_PSOC4) */

/* Function Prototype for systick isr callback function */
void SysTickISRCallback(void);

///////////////////////////////////////////////////////////////////////
// Platform Configuration
///////////////////////////////////////////////////////////////////////
#include "../../ccNOos/tests/ccNOos_tests.h"    // all things ccNOos w/tests

///////////////////////////////
// Systick example consists of:
// 1) An Execution System
struct executionSystemStruct psoc4SysTickExampleSystem;
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
// IO Devices Require Platform Implementations of: 
// 1) Minute LED Device Write
int writeMinLEDdevice(){LED_Min_Write(sysTickCompMod.MinLEDvalue); return RETURN_SUCCESS;}
// 2) Second LED Device Write
int writeSecLEDdevice(){LED_Sec_Write(sysTickCompMod.SecLEDvalue); return RETURN_SUCCESS;}
// 3) Serial Device Write
int writeSerialdevice(){UART_PutString(sysTickCompMod.time); return RETURN_SUCCESS;}


////////////////////////////////////////////////////////////
// An Execution System Requires Platform Implementations of:
// 1) Platform Configure Function
int platformSetup()
{
    /* Enable global interrupts. */
    CyGlobalIntEnable;    
    
    return RETURN_SUCCESS;
}
// 2) Platform Start Function
int platformStart()
{
    /* Configure the SysTick timer to generate interrupt every 1 ms
    * and start its operation. Call the function before assigning the
    * callbacks as it calls CySysTickInit() during first run that 
    * re-initializes the callback addresses to the NULL pointers.
    */
    CySysTickStart();

    /* Find unused callback slot and assign the callback. */
    for (int i = 0u; i < (int)CY_SYS_SYST_NUM_OF_CALLBACKS; ++i)
    {
        if (CySysTickGetCallback(i) == NULL)
        {
            /* Set callback */
            CySysTickSetCallback(i, SysTickISRCallback);
            break;
        }
    }
    return RETURN_SUCCESS;
}
// 3) Platform Loop Delay Function
void platformLoopDelay()
{
    //CyDelay(1);
    ;
}
// 4) Application Configuration Function
struct linkedEntryPointStruct setupListHead = {0u, &sysTickCompMod, setup_systickExample};
struct linkedEntryPointStruct loopListHead = {0u, &sysTickCompMod, loop_systickExample};
struct linkedEntryPointStruct systickListHead = {0u, &sysTickCompMod, 0u};
int applicationConfig()
{    
    // Initialize Execution System for SysTick Example on PSoC4
    psoc4SysTickExampleSystem = CreateExecutionSystemStruct(&setupListHead,&loopListHead,&systickListHead, 1000);
    
    // Initialize Device Compute Module for sysTickExample
    sysTickCompMod = CreateSysTickExampleDevModStruct(
        writeMinLEDdevice,
        writeSecLEDdevice,
        writeSerialdevice,
        &psoc4SysTickExampleSystem
        );
    
    return RETURN_SUCCESS;
}


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  Starts the SysTick timer and sets the callback function that will be called
*  on SysTick interrupt. Updates timing variables at one millisecond rate and
*  prints the system time to the UART once every second in the main loop.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
int main()
{    
    applicationConfig();
    return ExecuteMain(&psoc4SysTickExampleSystem);
}


/*******************************************************************************
* Function Name: SysTickISRCallback
********************************************************************************
*
* Summary:
*  This API is called from SysTick timer interrupt handler to update the
*  millisecond counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SysTickISRCallback(void)
{
    int retval = ExecuteSysTick(&psoc4SysTickExampleSystem);
}


/* [] END OF FILE */
