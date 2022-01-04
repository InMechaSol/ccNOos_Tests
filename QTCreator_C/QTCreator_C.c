/////////////////////////////////////////////////////////////////////////
// A main.c file under ccNOos Tests Philosophy will
// 1) include its platform support header
#include <Platform_QTCreatorC.h>
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
///
//<applicationIncludes>
#include <math.h>
//</applicationIncludes>

//<applicationDefines>
#define LIGHT_OFF (0u)      // 1-PSoC4, 0-most others
//</applicationDefines>

//<applicationClass>
MODdeclareDATA(Mn);
//</applicationClass>

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
    //LED_Min_Write(MODdataPTR(Mn)->MinLEDvalue);
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
    printf("%s",MODdataPTR(Mn)->time);// << std::fflush;
    fflush(stdout);
    //UART_PutString(sysTickDataPtr->time);
    //</writeSerialdevice>
}
//</moduleIOFunctions>


//<moduleSerializationFunctions>
// 4) Serialization of Time String
//void SerializeTimeString(MODdeclarePTRIN(Mn))
//{
//    int retval = sprintf(MODdataPTR(Mn)->time, "\r%02u:%02u:%02u",
//        (int)(MODdataPTR(Mn)->hrCount % 100),
//        (int)(MODdataPTR(Mn)->minCount % TIME_MIN_PER_HR),
//        (int)(MODdataPTR(Mn)->secCount % TIME_SEC_PER_MIN)
//    );
//    //sysTickDataPtr->time[retval] = 0x00;
//}
//</moduleSerializationFunctions>

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


//void ReadUserInput(MODdeclarePTRIN(Mn))
//{
//    GetMenuChars(&MODdataPTR(Mn)->apiLine[0]);
//    MODdataPTR(Mn)->charsRead++;
//}

//</moduleIOFunctions>



#endif //!EXAMPLE_ATTEN_UI

///////////////////////////////////////////////////////////////////////
// SatCom Tunable Power Meter Example
///////////////////////////////////////////////////////////////////////
#ifdef EXAMPLE_POWER_METER


//<applicationIncludes>
//</applicationIncludes>

//<applicationDefines>
//</applicationDefines>

//<applicationClass>
MODdeclareDATA(Mn);
//</applicationClass>

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
