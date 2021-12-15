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

//<platformConfigChecks>
#define PLATFORM_NAME Arduino

#ifndef USING_STDINT
#error Must compile with -DUSING_STDINT on Arduino platforms (maybe others, need to test)
#endif // !USING_STDINT
#ifndef __NOEXCEPTIONS
#error Must compile with -D__NOEXCEPTIONS on Aduino ATMega (maybe others, need to test)
#endif // !__NOEXCEPTIONS
#ifdef USING_CSTDINT
#error Must not compile with -DUSING_CSTDINT on Aduino ATMega (maybe others, need to test)
#endif // !USING_CSTDINT
#ifdef USING_NONSTDINT_SHORTER
#error Must not compile with -DUSING_NONSTDINT_SHORTER on Aduino ATMega (maybe others, need to test)
#endif // !USING_NONSTDINT_SHORTER
#ifdef USING_NONSTDINT_LONGER
#error Must not compile with -DUSING_NONSTDINT_LONGER on Aduino ATMega (maybe others, need to test)
#endif // !USING_NONSTDINT_LONGER
#ifdef REDEFINE_NULLPTR
#error Must not compile with -DREDEFINE_NULLPTR on Aduino ATMega (maybe others, need to test)
#endif // !REDEFINE_NULLPTR
//</platformConfigChecks>


//<platformIncludes>
#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#include <ccNOos_tests_arduino.h>
/* Function Prototype for systick isr callback function */
//void SysTickISRCallback(void);
#define uSEC_PER_CLOCK (1000u)

//</platformIncludes>

////////////////////////////////////////////////////////////
// An Execution System Requires Platform Implementations of:
// 1) Platform Configure Function

void platformSetup()
{
    //<platformSetup>
    Serial.begin(115200);
    Wire.begin();
    
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
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
    ;
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
        *val = (int32_t)atol(str);
        return true;
    }
    else
        return false;
}
bool ATO_I64(const char* str, int64_t* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (int64_t)atol(str);
        return true;
    }
    else
        return false;
}
bool ATO_U8(const char* str, uint8_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint8_t)atol(str);
        return true;
    }
    else
        return false;
}
bool ATO_U16(const char* str, uint16_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint16_t)atol(str);
        return true;
    }
    else
        return false;
}
bool ATO_U32(const char* str, uint32_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint32_t)atol(str);
        return true;
    }
    else
        return false;
}
bool ATO_U64(const char* str, uint64_t* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (uint64_t)atol(str);
        return true;
    }
    else
        return false;
}



///////////////////////////////////////////////////////////////////////
// SysTick Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_SYSTICK
//<applicationIncludes>
//</applicationIncludes>

//<applicationDefines>
#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others
//</applicationDefines>


//<applicationClass>
PLATFORM_APP_CLASS_SYSTICK(PLATFORM_NAME, MODULENAME);
//</applicationClass>

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
    Serial.write(SysTickClockDataPtrIn->time);
    //std::cout << sysTickDataPtr->time;// << std::fflush;
    //UART_PutString(sysTickDataPtr->time); 
    //</writeSerialdevice>
}
// 4) Serialization of Time String
void SerializeTimeString(MODSTRUCTPTR_IN(MODULENAME))
{
    int retval = sprintf(SysTickClockDataPtrIn->time, "\r%02u:%02u:%02u\n",
        (int)(SysTickClockDataPtrIn->hrCount % 100),
        (int)(SysTickClockDataPtrIn->minCount % TIME_MIN_PER_HR),
        (int)(SysTickClockDataPtrIn->secCount % TIME_SEC_PER_MIN)
    );
    //sysTickDataPtr->time[retval] = 0x00;
}


#endif



///////////////////////////////////////////////////////////////////////
// Attenuators UI Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_ATTEN_UI


//<applicationIncludes>
//</applicationIncludes>

//<applicationDefines>
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

//</applicationDefines>

//<applicationClass>
PLATFORM_APP_CLASS_ATTEN_UI(PLATFORM_NAME, MODULENAME);
//</applicationClass>

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
void WriteAttenuators(MODSTRUCTPTR_IN(MODULENAME))
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
    
#define bit16   ( (0b10000000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 7 )
#define bit8    ( (0b01000000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 6 )
#define bit4    ( (0b00100000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 5 )
#define bit2    ( (0b00010000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 4 )
#define bit1    ( (0b00001000 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 3 )
#define bit0_25 ( (0b00000100 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 2 )
#define bit0_50 ( (0b00000010 & AttenUIDataPtrIn->CMD_AttenuatorBits) >> 1 )

switch (AttenUIDataPtrIn->INDEX_Attenuator) {
    case 0:
        SETPIN_TX_C16(bit16);
        SETPIN_TX_C8(bit8);
        SETPIN_TX_C4(bit4);
        SETPIN_TX_C2(bit2);
        SETPIN_TX_C1(bit1);
        SETPIN_TX_C0_25(bit0_25);
        SETPIN_TX_C0_50(bit0_50);
        //SETPIN_TX_LE(0x01);
        //delay(1);
        //SETPIN_TX_LE(0x00);
        break;
    case 1:
        SETPIN_RX_C16(bit16);
        SETPIN_RX_C8(bit8);
        SETPIN_RX_C4(bit4);
        SETPIN_RX_C2(bit2);
        SETPIN_RX_C1(bit1);
        SETPIN_RX_C0_25(bit0_25);
        SETPIN_RX_C0_50(bit0_50);
        //SETPIN_RX_LE(0x01);
        //delay(1);
        //SETPIN_RX_LE(0x00);
        break;
    case 2:
        SETPIN_XX_C16(bit16);
        SETPIN_XX_C8(bit8);
        SETPIN_XX_C4(bit4);
        SETPIN_XX_C2(bit2);
        SETPIN_XX_C1(bit1);
        SETPIN_XX_C0_25(bit0_25);
        SETPIN_XX_C0_50(bit0_50);
        //SETPIN_XX_LE(0x01);
        //delay(1);
        //SETPIN_XX_LE(0x00);
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
void ReadUserInput(MODSTRUCTPTR_IN(MODULENAME))
{
    if (Serial.available() > 0)
    {
        AttenUIDataPtrIn->charsRead = 0u;
        do {
            AttenUIDataPtrIn->apiLine[AttenUIDataPtrIn->charsRead++] = Serial.read();
            delay(1);
        } while (Serial.available() > 0 && AttenUIDataPtrIn->charsRead < CONSOLE_LINE_LEN);
        
        SETPIN_XX_LE(0x01);
        SETPIN_RX_LE(0x01);
        SETPIN_TX_LE(0x01);
    }
        
}
void WriteMenuLine(MODSTRUCTPTR_IN(MODULENAME))
{
    Serial.write(AttenUIDataPtrIn->consoleLine);
}
//</moduleIOFunctions>


#endif //!EXAMPLE_ATTEN_UI



////////////////////////////////////////////////////////////////////////////////
// Finally, an applications entry points call the execution system entry points
// 1) The Main Entry Points (setup and loop)
PLATFORM_APP_NAME(PLATFORM_NAME) theApplicationExample;
unsigned long tlast;
unsigned long tnow, tdelta;
uint32_t* uSecTicksPtr;
uint32_t* hourTicksPtr;

void setup() {
    //asm(".global _printf_float");
    tlast = millis();
    tnow, tdelta;
    uSecTicksPtr = &PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecTicks;
    hourTicksPtr = &PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->hourTicks;
    PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteSetup();

}

void loop() 
{
    // Arduino platfrom doesn't use systick (maybe could but, future option)
    // So the exesystem clock must be maintained here
    // and rely on the arduino library
    tnow = millis();
    if (tnow >= tlast)
        tdelta = tnow - tlast;
    else
        tdelta = tnow + (0xffffffff - tlast);
    tlast = tnow;

    (*uSecTicksPtr) += tdelta * uSEC_PER_CLOCK;
    if ((*uSecTicksPtr) >= TIME_uS_PER_HR)
    {
        (*uSecTicksPtr) = 0u;
        (*hourTicksPtr)++;
    }

    PLATFORM_EXESYS_NAME(PLATFORM_NAME).ExecuteLoop();

}

// 2) The SysTick Entry Point

/* [] END OF FILE */