/** \file SysTickExample.c
*   \brief Template for Platform Specific Implementation of SysTick Example

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
 
  
*/

/////////////////////////////////////////////////////////////////////////
// A main.c file under ccNOos Tests Philosophy will 
// 1) include its platform support header
#include <Platform_PSoC4.h>
// 2) double check the validity of the platform support header
#ifndef PLATFORM_NAME
    #error PLATFORM_NAME must be defined, see examples   
#endif
// 3) a Compile Switch for Running Examples vs Automated Tests
#ifdef COMPILE_TESTS
// 4) all of the ccNOos Tests Automated Tests
    MODdeclareDATA(Mn);
#else
// 5) all of the ccNOos Tests Example Applications
#ifdef EXAMPLE_SYSTICK
///////////////////////////////////////////////////////////////////////
// SysTick Example
///////////////////////////////////////////////////////////////////////
MODdeclareDATA(Mn);

// 1) Minute LED Device Write
void WriteMinLED(MODdeclarePTRIN(Mn))
{
    //<writeMinLEDdevice>
    LED_Min_Write(MODdataPTR(Mn)->MinLEDvalue); 
    //</writeMinLEDdevice>
}
// 2) Second LED Device Write
void WriteSecLED(MODdeclarePTRIN(Mn))
{
    //<writeSecLEDdevice>
    LED_Sec_Write(MODdataPTR(Mn)->SecLEDvalue);
    //</writeSecLEDdevice>
}
// 3) Serial Device Write
void WriteTimeSerial(MODdeclarePTRIN(Mn))
{
    //<writeSerialdevice>
    UART_PutString(MODdataPTR(Mn)->time); 
    //</writeSerialdevice>
}

#endif //!EXAMPLE_SYSTICK
#ifdef EXAMPLE_ATTEN_UI
///////////////////////////////////////////////////////////////////////
// Attenuators UI Example
///////////////////////////////////////////////////////////////////////

//<applicationIncludes>
#include <stdio.h>
#include <math.h>
//</applicationIncludes>

//<applicationDefines>
//</applicationDefines>

//<applicationClass>
MODdeclareDATA(Mn);
//</applicationClass>

float ModuloFloat(float floatValue, float* intPartPtr)
{
    double retVal;
    double dblValue = floatValue;
    double intPartPtrDb;
    retVal =  modf(dblValue, &intPartPtrDb);
    *intPartPtr = (float)(intPartPtrDb);
    return (float)retVal;
}

//<moduleIOFunctions>
// platform and application specific io device functions
void WriteAttenuators(MODdeclarePTRIN(Mn))
{
#define bit16   ( (0b10000000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 7 )
#define bit8    ( (0b01000000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 6 )
#define bit4    ( (0b00100000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 5 )
#define bit2    ( (0b00010000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 4 )
#define bit1    ( (0b00001000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 3 )
#define bit0_25 ( (0b00000100 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 2 )
#define bit0_50 ( (0b00000010 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 1 )
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
//</moduleIOFunctions>


#endif //!EXAMPLE_ATTEN_UI
#endif // !COMPILE_TESTS

///////////////////////////////////////////////////////////////////////
// Application Data Instances are Created here (Platform Specific)
#ifdef __cplusplus
PLATFORM_APP_CPPTEMPLATE(PLATFORM_NAME)
#else
PLATFORM_APP_CTEMPLATE(PLATFORM_NAME, Mn)
#endif

////////////////////////////////////////////////////////////////////////////////
// Finally, Application Entry Points call ExeSys Entry Points
#ifdef MAIN_C_NOos_Wsystick
C_NOos_MAINnSYSTICK_TEMPLATE
#endif
#ifdef MAIN_CPP_NOos_NOsystick
CPP_OS_MAIN_TEMPLATE
#endif
#ifdef MAIN_C_NOos_NOsystick
C_OS_MAIN_TEMPLATE
#endif
#ifdef MAIN_CPP_NOos_NOsystick_Arduino
CPP_MAIN_TEMPLATE_ARDUINO
#endif

/* [] END OF FILE */