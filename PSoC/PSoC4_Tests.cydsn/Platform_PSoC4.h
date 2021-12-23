/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
//<platformConfigChecks>

#if PLATFORM_NAME!=PSoC4
    error PLATFORM_NAME must be PSoC4 
#endif

#ifdef REDEFINE_NULLPTR
    #error Must not compile with -DREDEFINE_NULLPTR on PSoC4
#endif // !REDEFINE_NULLPTR

//</platformConfigChecks>

//<platformIncludes>
#include <project.h>      // for PSoC
//</platformIncludes>

//<platformAppDefines>
#define LIGHT_OFF (1u)      // 1-PSoC4, 0-most others
//</platformAppDefines>

/* Function Prototype for systick isr callback function */
void SysTickISRCallback(void);

///////////////////////////////////////////////////////////////////////
// Platform Configuration
///////////////////////////////////////////////////////////////////////
#include "../../ccNOos/tests/ccNOos_tests.h"    // all things ccNOos w/tests
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>
#define uSEC_PER_CLOCK (1000000/CLOCKS_PER_SEC)
#define MAXLINELENGTH (80)

void platformSetup()
{      
    //<platformSetup>
    /* Enable global interrupts. */
    CyGlobalIntEnable;
    //</platformSetup>
}
// 2) Platform Start Function
void platformStart()
{
    //<platformStart>
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

void GetMenuChars(char* inStringPtr)
{
//    int ch = 0;
//    int retVal = 1;
//    while(ch < MAXLINELENGTH)
//    {
//        retVal = read(STDIN_FILENO, &inStringPtr[ch], 1);
//        ch++;
//        if  (
//            inStringPtr[ch-1] == '\n' ||
//            retVal < 1
//            )
//            break;
//    }
//    inStringPtr[ch] = 0x00;
}
void WriteMenuLine(char* outStringPtr)
{
//    int retVal = printf(outStringPtr);
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
UI_8 ATO_F(const char* str, float* val)
{
    if (isNumberString((char*)str))
    {
        *val = (float)atof(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_D(const char* str, double* val)
{
    if (isNumberString((char*)str))
    {
        *val = atof(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_I8(const char* str, I_8* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (I_8)atoi(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_I16(const char* str, I_16* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (I_16)atoi(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_I32(const char* str, I_32* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (I_32)atoll(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_I64(const char* str, I_64* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (I_64)atoll(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U8(const char* str, UI_8* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_8)atoll(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U16(const char* str, UI_16* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_16)atoll(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U32(const char* str, UI_32* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_32)atoll(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U64(const char* str, UI_64* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_64)atoll(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}

PLATFORM_EXESYS_DECLARE(PLATFORM_NAME);

// and 4) Module API Functions
UI_32 getuSecTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).uSecTicks;
}
UI_32 getHourTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).hourTicks;
}
//</moduleAPIFunctions>
/* [] END OF FILE */
