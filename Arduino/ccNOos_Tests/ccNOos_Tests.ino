/** \file ccNOos_Tests.ino
*   \brief Arduino Implementation of ccNOos_Tests in c++

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
   <platformConfigChecks> - Compiler Configuration Checks
   <platformIncludes> - The platform specific header includes
   <platformAppDefines> - Constants of the application, unique to the platform
   <writeMinLEDdevice> - IO Write Function for Minute LED
   <writeSecLEDdevice> - IO Write Function for Second LED
   <writeSerialdevice> - IO Write Function for Time String Output
   <platformSetup> - Base Execution System Setup
   <platformStart> - Executed after platformSetup and all Modules Setup,
                                                     but before any modules Loop
   <platformLoopDelay> - Define "rest" between main loop cycles

   .ino means arduino...

   Remember to set compiler flags in platform.txt !!!
   compiler.cpp.extra_flags= -DUSING_STDINT -D__NOEXCEPTIONS

*/

#include "Platform_Arduino.h"

#ifdef COMPILE_TESTS

PLATFORM_APP_CLASS(PLATFORM_NAME, Mn);

#else

///////////////////////////////////////////////////////////////////////
// SysTick Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_SYSTICK

#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others


PLATFORM_APP_CLASS(PLATFORM_NAME, Mn);


//<moduleIOFunctions>
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
    Serial.write("\r");
    Serial.write(MODdataPTR(Mn)->time);// << std::fflush;
    Serial.write("\n");
    //UART_PutString(MODdataPTR(Mn)->time); 
    //</writeSerialdevice>
}
//</moduleIOFunctions>


//<moduleSerializationFunctions>
// 4) Serialization of Time String
//void SerializeTimeString(MODdeclarePTRIN(Mn))
//{
//    int retval = SN_PrintF(MODdataPTR(Mn)->time, 9, "\r%02u:%02u:%02u",
//        (int)(MODdataPTR(Mn)->hrCount % 100),
//        (int)(MODdataPTR(Mn)->minCount % TIME_MIN_PER_HR),
//        (int)(MODdataPTR(Mn)->secCount % TIME_SEC_PER_MIN)
//    );
//    //sysTickDataPtr->time[retval] = 0x00;
//}
//</moduleSerializationFunctions>

#endif //!EXAMPLE_SYSTICK

///////////////////////////////////////////////////////////////////////
// Attenuators UI Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_ATTEN_UI


#define SETPIN_TX_C16(high_low)    IC1.digitalWrite(0, high_low)
#define SETPIN_TX_C8(high_low)     IC1.digitalWrite(1, high_low)
#define SETPIN_TX_C4(high_low)     IC1.digitalWrite(2, high_low)
#define SETPIN_TX_C2(high_low)     IC1.digitalWrite(3, high_low)
#define SETPIN_TX_C1(high_low)     IC1.digitalWrite(4, high_low)
#define SETPIN_TX_C0_25(high_low)  IC1.digitalWrite(5, high_low)
#define SETPIN_TX_C0_50(high_low)  IC1.digitalWrite(6, high_low)
#define SETPIN_TX_LE(high_low)     IC1.digitalWrite(14, high_low) 

#define SETPIN_RX_C16(high_low)    IC1.digitalWrite(7, high_low)
#define SETPIN_RX_C8(high_low)     IC1.digitalWrite(8, high_low)
#define SETPIN_RX_C4(high_low)     IC1.digitalWrite(9, high_low)
#define SETPIN_RX_C2(high_low)     IC1.digitalWrite(10, high_low)
#define SETPIN_RX_C1(high_low)     IC1.digitalWrite(11, high_low)
#define SETPIN_RX_C0_25(high_low)  IC1.digitalWrite(12, high_low)
#define SETPIN_RX_C0_50(high_low)  IC1.digitalWrite(13, high_low)
#define SETPIN_RX_LE(high_low)     IC1.digitalWrite(15, high_low) 

#define SETPIN_XX_C16(high_low)    
#define SETPIN_XX_C8(high_low)     
#define SETPIN_XX_C4(high_low)     
#define SETPIN_XX_C2(high_low)     
#define SETPIN_XX_C1(high_low)     
#define SETPIN_XX_C0_25(high_low)  
#define SETPIN_XX_C0_50(high_low)  
#define SETPIN_XX_LE(high_low)  


PLATFORM_APP_CLASS(PLATFORM_NAME, Mn);


float ModuloFloat(float floatValue, float* intPartPtr)
{
    double intPart, fracPart;
    fracPart = modf(floatValue, &intPart);
    *intPartPtr = (float)intPart;
    return (float)fracPart;
}

// Application Specific, Platform modifications
#define IC1Addr 0x27
bool runOnce = true;
Adafruit_MCP23017 IC1;
//<moduleIOFunctions>
// platform and application specific io device functions
void WriteAttenuators(MODdeclarePTRIN(Mn))
{
    if (runOnce)
    {
        runOnce = false;
        IC1.begin(IC1Addr);
        IC1.pinMode(0, OUTPUT);
        IC1.pinMode(1, OUTPUT);
        IC1.pinMode(2, OUTPUT);
        IC1.pinMode(3, OUTPUT);
        IC1.pinMode(4, OUTPUT);
        IC1.pinMode(5, OUTPUT);
        IC1.pinMode(6, OUTPUT);
        IC1.pinMode(7, OUTPUT);
        IC1.pinMode(8, OUTPUT);
        IC1.pinMode(9, OUTPUT);
        IC1.pinMode(10, OUTPUT);
        IC1.pinMode(11, OUTPUT);
        IC1.pinMode(12, OUTPUT);
        IC1.pinMode(13, OUTPUT);
        IC1.pinMode(14, OUTPUT);
        IC1.pinMode(15, OUTPUT);
    }
    
#define bit16   ( (0b10000000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 7 )
#define bit8    ( (0b01000000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 6 )
#define bit4    ( (0b00100000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 5 )
#define bit2    ( (0b00010000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 4 )
#define bit1    ( (0b00001000 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 3 )
#define bit0_25 ( (0b00000100 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 2 )
#define bit0_50 ( (0b00000010 & MODdataPTR(Mn)->CMD_AttenuatorBits) >> 1 )

switch (AttenUIDataPtrIn->INDEX_Attenuator) {
    case 0:
        SETPIN_TX_C16(bit16);
        SETPIN_TX_C8(bit8);
        SETPIN_TX_C4(bit4);
        SETPIN_TX_C2(bit2);
        SETPIN_TX_C1(bit1);
        SETPIN_TX_C0_25(bit0_25);
        SETPIN_TX_C0_50(bit0_50);
        SETPIN_TX_LE(0x01);
        delay(1);
        SETPIN_TX_LE(0x00);
        break;
    case 1:
        SETPIN_RX_C16(bit16);
        SETPIN_RX_C8(bit8);
        SETPIN_RX_C4(bit4);
        SETPIN_RX_C2(bit2);
        SETPIN_RX_C1(bit1);
        SETPIN_RX_C0_25(bit0_25);
        SETPIN_RX_C0_50(bit0_50);
        SETPIN_RX_LE(0x01);
        delay(1);
        SETPIN_RX_LE(0x00);
        break;
    case 2:
        SETPIN_XX_C16(bit16);
        SETPIN_XX_C8(bit8);
        SETPIN_XX_C4(bit4);
        SETPIN_XX_C2(bit2);
        SETPIN_XX_C1(bit1);
        SETPIN_XX_C0_25(bit0_25);
        SETPIN_XX_C0_50(bit0_50);
        SETPIN_XX_LE(0x01);
        delay(1);
        SETPIN_XX_LE(0x00);
        break;
    default:
        break;
    }

#undef bit16  
#undef bit8
#undef bit4
#undef bit2
#undef bit1
#undef bit0_25 
#undef bit0_50 
}


//void ReadUserInput(MODdeclarePTRIN(Mn))
//{
//    if (Serial.available() > 0)
//    {
//        MODdataPTR(Mn)->charsRead = 0u;
//        do {
//            MODdataPTR(Mn)->apiLine[MODdataPTR(Mn)->charsRead++] = Serial.read();
//            delay(1);
//        } while (Serial.available() > 0 && MODdataPTR(Mn)->charsRead < CONSOLE_LINE_LEN);
//        
//        SETPIN_XX_LE(0x01);
//        SETPIN_RX_LE(0x01);
//        SETPIN_TX_LE(0x01);
//    }
//        
//}
void WriteMenuLine(MODdeclarePTRIN(Mn))
{
    Serial.write(MODdataPTR(Mn)->consoleLine);
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
C_NOos_MAINnSYSTICK_TEMPLATE(PLATFORM_NAME)
#endif
#ifdef MAIN_CPP_NOos_NOsystick
CPP_OS_MAIN_TEMPLATE(PLATFORM_NAME)
#endif
#ifdef MAIN_C_NOos_NOsystick
C_OS_MAIN_TEMPLATE(PLATFORM_NAME)
#endif
#ifdef MAIN_C_NOos_NOsystick
C_OS_MAIN_TEMPLATE(PLATFORM_NAME)
#endif
#ifdef MAIN_CPP_NOos_NOsystick_Arduino
CPP_MAIN_TEMPLATE_ARDUINO(PLATFORM_NAME)
//ccNOosVersionsTemplate
//unsigned long tlast;
//unsigned long tnow, tdelta;
//uint32_t* uSecTicksPtr;
//uint32_t* hourTicksPtr;
//void setup() {
//    
//        asm(".global _printf_float"); 
//        tlast = millis(); 
//        tnow, tdelta; 
//        uSecTicksPtr = &PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecTicks;
//        hourTicksPtr = &PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->hourTicks;
//        PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteSetup();
//}
//
//void loop()
//    {
//        tnow = millis(); 
//        if (tnow >= tlast)
//            tdelta = tnow - tlast; 
//        else
//            tdelta = tnow + (0xffffffff - tlast); 
//            tlast = tnow; 
//            
//            (*uSecTicksPtr) += tdelta * uSEC_PER_CLOCK; 
//            if ((*uSecTicksPtr) >= TIME_uS_PER_HR)
//            {
//                (*uSecTicksPtr) = 0u; 
//                (*hourTicksPtr)++; 
//            }
//                
//                PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteLoop();
//    }
#endif

////////////////////////////////////////////////////////////////////////////////
// Finally, an applications entry points call the execution system entry points
// 1) The Main Entry Points (setup and loop)


// 2) The SysTick Entry Point

/* [] END OF FILE */