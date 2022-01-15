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

*/

#include "ccNOos_tests.h"

#ifdef COMPILE_TESTS
#include "..\testApps\ccNOos_Tests\Application_Solution.h"
#include "..\testApps\ccNOos_Tests\PlatformApp_Serialization.h"
#else // !COMPILE_TESTS
#ifdef EXAMPLE_SYSTICK
#include "..\testApps\SysTick\Application_Solution.h"
#include "..\testApps\SysTick\PlatformApp_Serialization.h"
#endif // EXAMPLE_SYSTICK
#ifdef EXAMPLE_SATCOM_ACS
#include "..\testApps\SatComACS\Application_Solution.h"
#include "..\testApps\SatComACS\PlatformApp_Serialization.h"
#endif // EXAMPLE_SATCOM_ACS
#endif // !COMPILE_TESTS

#ifdef PLATFORM_NAME
#if PLATFORM_NAME==Win32
#include "Platform_Win32.h"
#elif PLATFORM_NAME==QTCreatorC
#include <Platform_QTCreatorC.h>
#endif
#endif



#ifdef __cplusplus
PLATFORM_APP_CLASS(Mn);
#else
MODdeclareDATA(Mn);
#endif


#ifndef COMPILE_TESTS
///////////////////////////////////////////////////////////////////////
// SysTick Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_SYSTICK


//////////////////////////////////////////////////
// IO Devices Require Platform Implementations of
// of open,close,read,write
// This SysTick Example Application only uses write
// for each of its three application devices
// 1) Minute LED Device Write
void WriteMinLED(MODdeclarePTRIN(Mn))
{
    //<writeMinLEDdevice>
    //LED_Min_Write(sysTickDataPtr->MinLEDvalue); 
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

    std::cout << MODdataPTR(Mn)->time;// << std::fflush;
    //UART_PutString(MODdataPTR(Mn)->time); 
    //</writeSerialdevice>
}
//</moduleIOFunctions>

#endif //!EXAMPLE_SYSTICK

///////////////////////////////////////////////////////////////////////
// Attenuators UI Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_ATTEN_UI

float ModuloFloat(float floatValue, float* intPartPtr)
{
    return modf(floatValue, intPartPtr);
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

///////////////////////////////////////////////////////////////////////
// SatCom ACS Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_SATCOM_ACS




#endif //!EXAMPLE_SATCOM_ACS

///////////////////////////////////////////////////////////////////////
// SatCom Tunable Power Meter Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_POWER_METER

//<moduleIOFunctions>
// platform and application specific io device functions
void WriteSPIDevice(MODdeclarePTRIN(Mn))
{

}
void ReadSPIDevice(MODdeclarePTRIN(Mn))
{

}
void WriteChipSelect(MODdeclarePTRIN(Mn))
{

}
//</moduleIOFunctions>


#endif //!EXAMPLE_SATCOM_ACS

#endif // !COMPILE_TESTS

///////////////////////////////////////////////////////////////////////
// Application Data Instances are Created here (Platform Specific)
#ifdef __cplusplus
theApplicationClass theApplicationExample;
#else
PLATFORM_APP_CTEMPLATE(Mn)
#endif

////////////////////////////////////////////////////////////////////////////////
// Finally, Application Entry Points call ExeSys Entry Points
#ifdef MAIN_C_NOos_Wsystick
C_NOos_MAINnSYSTICK_TEMPLATE(PLATFORM_NAME)
#endif
#ifdef MAIN_CPP_NOos_NOsystick
CPP_OS_MAIN_TEMPLATE
#endif
#ifdef MAIN_C_NOos_NOsystick
C_OS_MAIN_TEMPLATE(PLATFORM_NAME)
#endif


/* [] END OF FILE */







