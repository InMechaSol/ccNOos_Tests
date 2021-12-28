#if PLATFORM_NAME!=Arduino
    error PLATFORM_NAME must be Arduino
#endif


#ifdef REDEFINE_NULLPTR
    #error Must not compile with -DREDEFINE_NULLPTR on Aduino ATMega (maybe others, need to test)
#endif // !REDEFINE_NULLPTR
#ifndef __NOEXCEPTIONS
    #error Must compile with -D__NOEXCEPTIONS on Aduino ATMega (maybe others, need to test)
#endif // !__NOEXCEPTIONS


#include <Arduino.h>
#include <Adafruit_MCP23017.h>
#include <ccNOos_tests_arduino.h>
#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others
#define uSEC_PER_CLOCK (1000u)
#define MAXLINELENGTH (80)

// 0) (Optional) Platform Config and Log Files/Devices
// 1) Platform Setup Function
void platformSetup()
{
    //<platformSetup>
#ifdef __USINGCONSOLEMENU
#ifdef __USINGFLOATPRINTF
        asm(".global _printf_float");
#endif
#endif
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
#ifdef __USINGCONSOLEMENU
// 4) Basic ability for user console input
void GetMenuChars(char* inStringPtr)
{
    int idx = 0;
    if (Serial.available() > 0)
    {
        do {
            inStringPtr[idx++] = Serial.read();
        } while (Serial.available() > 0 && idx < MAXLINELENGTH);
        delay(1);
        do {
            inStringPtr[idx++] = Serial.read();
        } while (Serial.available() > 0 && idx < MAXLINELENGTH);
    }
}
// 5) Basic ability for user console output
void WriteMenuLine(char* outStringPtr)
{
    Serial.write(outStringPtr);
}
// 6) (Optional) Logging Output
void WriteLogLine(char* outStringPtr)
{
    ;
}
// 7) (Optional) Config Input
void ReadConfigLine(char* inStringPtr)
{
    ;

}
// 8) Platform API Functions (From Template?)
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
        *val = (I_32)atol(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_I64(const char* str, I_64* val)
{
    if (isIntegerString((char*)str))
    {
        *val = (I_64)atol(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U8(const char* str, UI_8* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_8)atol(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U16(const char* str, UI_16* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_16)atol(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U32(const char* str, UI_32* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_32)atol(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
UI_8 ATO_U64(const char* str, UI_64* val)
{
    if (isUnsignedIntegerString((char*)str))
    {
        *val = (UI_64)atol(str);
        return ui8TRUE;
    }
    else
        return ui8FALSE;
}
#endif
// 9) Global Execution System Instance
executionSystemClass PLATFORM_EXESYS_NAME(PLATFORM_NAME)(uSEC_PER_CLOCK);
// 10) ExeSys API Functions (From Template?)
UI_32 getuSecTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecTicks;
}
UI_32 getHourTicks()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->hourTicks;
}
UI_32 getuSecPerSysTick()
{
    return PLATFORM_EXESYS_NAME(PLATFORM_NAME).getExeDataPtr()->uSecPerSysTick;
}
