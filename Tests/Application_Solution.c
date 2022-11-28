/** \file Application_Solution.c
*   \brief <a href="https://www.inmechasol.org/" target="_blank">IMS</a>:
		<a href="https://github.com/InMechaSol/ccNOos" target="_blank">ccNOos</a>,
		Implementation for straight C 

    Copyright 2021 <a href="https://www.inmechasol.org/" target="_blank">InMechaSol, Inc</a>    

    Licensed under the Apache License, Version 2.0(the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

Notes:
	(.c includes .h) - for straight C or
	(.cpp includes .c which includes .h) - for C++ wrapped straight C
	*Always compiled to a single compilation unit, either C or CPP, not both

*/
#include "Application_Solution.h"



// Re-usable, portable, cross-platform create() function
MODdeclareCREATE(Mn)(MODdeclareCREATEINS)
{
    MODdeclareSTRUCT(Mn) outStruct;
    int i;
    outStruct.compMod = CreateComputeModuleStruct();    
    outStruct.ConsoleMenu = createuiStruct();
    outStruct.PacketsAPI = createpackAPIStruct();
    outStruct.AutoUpdate = ui8FALSE;
    outStruct.execAPIsMainLoop = ui8TRUE;
    outStruct.execDEVsMainLoop = ui8TRUE;
    for (i = 0; i < 20; i++)
        outStruct.OperationsLog[i] = 0;
    outStruct.OpsLogIndex = 0;
    outStruct.OpsLogSize = 0;
    return outStruct;
}

// Re-usable, portable, cross-platform setup() function
MODdeclareSETUP(Mn)
{
    MODDATAPTR_ERROR_RETURN(Mn);

    // Setup is running in the loop area to handle exceptions...
    IF_MODULE_ERROR(Mn)
    {
        CLEAR_MODULE_ERRORS(Mn);  // do nothing, clear flags        
        
    }
    // Setup is running in the setup area following power on
    else
    {
        linkAPIioDevices(MODdataPTR(Mn));
    }
    return RETURN_SUCCESS;
}
void tryreadMotorData(struct smartMotorStruct* smartMotorStructPtrIn);
void trywriteMotorData(struct smartMotorStruct* smartMotorStructPtrIn);
void tryReadPacketsInterface(MODdeclarePTRIN(Mn));
void tryWritePacketsInterface(MODdeclarePTRIN(Mn));
void tryReadConsoleMenu(MODdeclarePTRIN(Mn));
void tryWriteConsoleMenu(MODdeclarePTRIN(Mn));
// Re-usable, portable, cross-platform loop() function
MODdeclareLOOP(Mn)
{
    int i;
    MODDATAPTR_ERROR_RETURN(Mn);
    
    // read api devices  
    if (MODdataPTR(Mn)->execAPIsMainLoop == ui8TRUE)
    {
        tryReadPacketsInterface(MODdataPTR(Mn));
        tryReadConsoleMenu(MODdataPTR(Mn));
    }
    // read  devices

    // process 
    switch (MODdataPTR(Mn)->TestMode[iCURRENT])
    {
    case noOSTests_uninitialized:  break;
    case noOSTests_inprogress:  break;
    case noOSTests_done:  break;
    default:  break;
    }
    MODdataPTR(Mn)->TestMode[iLAST] = MODdataPTR(Mn)->TestMode[iCURRENT];

    // write   devices
    

    // write api devices
    if (MODdataPTR(Mn)->execAPIsMainLoop == ui8TRUE)
    {
        tryWritePacketsInterface(MODdataPTR(Mn));       

        if (MODdataPTR(Mn)->ConsoleMenu.devptr->triggerWriteOperation != ui8TRUE)
        {
            MODdataPTR(Mn)->AutoUpdateNow = getMillis();
            if (MODdataPTR(Mn)->AutoUpdate == ui8TRUE)
            {
                if (MODdataPTR(Mn)->AutoUpdateNow - MODdataPTR(Mn)->AutoUptateThen > 1000)
                {
                    MODdataPTR(Mn)->ConsoleMenu.devptr->triggerWriteOperation = ui8TRUE;
                    MODdataPTR(Mn)->AutoUptateThen = getMillis();
                }
                if (getMillis() - MODdataPTR(Mn)->AutoUpdateOnAt > 3600000)
                    MODdataPTR(Mn)->AutoUpdate = ui8FALSE;
            }
            else
                MODdataPTR(Mn)->AutoUpdateOnAt = getMillis();
            
        }

        tryWriteConsoleMenu(MODdataPTR(Mn));
    }
    return RETURN_SUCCESS;
}

MODdeclareSYSTICK(Mn) { ; }  // do nothing in the systick area



MODdeclarePRINTm(Mn)
{
    MODDATAPTR_RETURN(Mn);
    switch ((enum currentMenuNode)uiStructPtrIn->currentMenuIndex)
    {
    case cM_MainMenu:
        printccNOosTestsConsoleAPI(MODdataPTR(Mn), uiStructPtrIn);
        break;
    }
}


MODdeclarePARSEi(Mn)
{
    MODDATAPTR_RETURN(Mn);
    parseConsoleKeyPadAPI(ccNOosTestsDataPtrIn, uiStructPtrIn);
    if (uiStructPtrIn->currentUserLevel > uiLevel_Observer)
    {
        parseccNOosTestsConsoleAPI(ccNOosTestsDataPtrIn, uiStructPtrIn);
    }
    parseUserLevel(uiStructPtrIn);
    if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Help") == ui8TRUE)
        uiStructPtrIn->showHelp = ui8TRUE;
}


void tryReadPacketsInterface(MODdeclarePTRIN(Mn))
{
    //MODparseINPUT(Mn)(&MODdataPTR(Mn)->compMod, &MODdataPTR(Mn)->PacketsAPI);
}
void tryWritePacketsInterface(MODdeclarePTRIN(Mn))
{
    //MODprintMENU(Mn)(&MODdataPTR(Mn)->compMod, &MODdataPTR(Mn)->PacketsAPI);
}

#define IODEVPTR (MODdataPTR(Mn)->ConsoleMenu.devptr)
#define MENU (MODdataPTR(Mn)->ConsoleMenu)
void tryReadConsoleMenu(MODdeclarePTRIN(Mn))
{
    if (IODEVPTR != nullptr)
    {
        GetMenuChars(&MENU);
        if (IODEVPTR->newDataReadIn)
        {
            MODparseINPUT(Mn)(&MODdataPTR(Mn)->compMod, &MENU);

            IODEVPTR->triggerWriteOperation = ui8TRUE;
            IODEVPTR->newDataReadIn = ui8FALSE;
        }
    }
}
void tryWriteConsoleMenu(MODdeclarePTRIN(Mn))
{
    if (MENU.devptr->triggerWriteOperation)
    {
        MODdataPTR(Mn)->AutoUptateThen = getMillis();
        MENU.lines2print = 1;
        MENU.linesprinted = 0;
        MENU.clearScreen = ui8TRUE;
        OPENDOWHILE((&(MENU)))
            MODprintMENU(Mn)(&MODdataPTR(Mn)->compMod, &MENU);
        CLOSEDOWHILE((&(MENU)))
        MENU.lines2print = 1;
        MENU.linesprinted = 0;
        OPENDOWHILE((&(MENU)))
            MODprintMENU(Mn)(&MODdataPTR(Mn)->compMod, &MENU);
        CLOSEDOWHILE((&(MENU)))
        MENU.lines2print = 1;
        MENU.linesprinted = 0;
        OPENDOWHILE((&(MENU)))
            MODprintMENU(Mn)(&MODdataPTR(Mn)->compMod, &MENU);
        CLOSEDOWHILE((&(MENU)))
        MENU.lines2print = 1;
        MENU.linesprinted = 0;
        OPENDOWHILE((&(MENU)))
            MODprintMENU(Mn)(&MODdataPTR(Mn)->compMod, &MENU);
        CLOSEDOWHILE((&(MENU)))
            MENU.lines2print = 1;
        MENU.linesprinted = 0;
        OPENDOWHILE((&(MENU)))
            MODprintMENU(Mn)(&MODdataPTR(Mn)->compMod, &MENU);
        CLOSEDOWHILE((&(MENU)))
        MENU.lines2print = 1;
        MENU.linesprinted = 0;
        OPENDOWHILE((&(MENU)))
        writeUIHelpString(&MENU);
        CLOSEDOWHILE((&(MENU)))
        MENU.showPrompt = ui8TRUE;
        MENU.devptr->outbuff.charbuff[0] = 0x00;
        WriteMenuLine(&MENU);

        MENU.devptr->triggerWriteOperation = ui8FALSE;
    }
}
#undef IODEVPTR
#undef MENU

// IQ Smart Motors only send/receive one parameter per message, following a read/process/write model
// its necessary to used a phased processing model for communications.
// a read must be preceeded by a write to request the data
#define MOTCOMMTIMEOUT (50) // ms to trigger comms recovery actions for the smart motors
void tryreadMotorData(struct smartMotorStruct* smartMotorStructPtrIn)
{
    UI_32 DeltaMS = 0;
    UI_32 NowMS = 0;
    switch (smartMotorStructPtrIn->MotorsCommPhase)
    {
    case 1:// position reply
    case 3:// velocity reply
    case 5:// current reply
    case 7:// temperature reply or PWMCmd reply
        // read 
        readMotorData(smartMotorStructPtrIn);
        // parse 
        if (smartMotorStructPtrIn->devptr->newDataReadIn == ui8TRUE)
        {
            smartMotorStructPtrIn->devptr->newDataReadIn = ui8FALSE;
            parseMotorData(smartMotorStructPtrIn);
            // advance comm state
            smartMotorStructPtrIn->MotorsCommPhase++;
        }
        else // protect with timeout
        {           
            NowMS = getMillis();
            if (NowMS >= smartMotorStructPtrIn->millisThen)
                DeltaMS = NowMS - smartMotorStructPtrIn->millisThen;
            else
                DeltaMS = NowMS + (0xffffffff - smartMotorStructPtrIn->millisThen);
            
            if (DeltaMS > MOTCOMMTIMEOUT)
            {
                smartMotorStructPtrIn->Connected = ui8FALSE;
                smartMotorStructPtrIn->MotorsCommPhase = 0;
            }
        }
        break;
    
    default: break;
    }
}
void trywriteMotorData(struct smartMotorStruct* smartMotorStructPtrIn)
{
    int i;
    switch (smartMotorStructPtrIn->MotorsCommPhase)
    {
    case 0:// request position  
        smartMotorStructPtrIn->millisNow = getMillis();
        if (smartMotorStructPtrIn->millisNow >= smartMotorStructPtrIn->millisThen)
            smartMotorStructPtrIn->millisThentoNow = smartMotorStructPtrIn->millisNow - smartMotorStructPtrIn->millisThen;
        else
            smartMotorStructPtrIn->millisThentoNow = smartMotorStructPtrIn->millisNow + (0xffffffff - smartMotorStructPtrIn->millisThen);
        smartMotorStructPtrIn->millisThen = smartMotorStructPtrIn->millisNow;



        if (smartMotorStructPtrIn->millisThentoNow > 0)
        {

#ifdef EVENODDMOTORS
            if (smartMotorStructPtrIn->Connected != ui8TRUE)
            {
                if (smartMotorStructPtrIn->ModuleID == 0)
                    smartMotorStructPtrIn->ModuleID = 1;
                else
                    smartMotorStructPtrIn->ModuleID = 0;
            }            
#endif
            if (smartMotorStructPtrIn->CommPeriodAbsoluteMinimum > smartMotorStructPtrIn->millisThentoNow)
            {
                smartMotorStructPtrIn->CommPeriodAbsoluteMinimum = smartMotorStructPtrIn->millisThentoNow;
            }
            if (smartMotorStructPtrIn->CommPeriodAbsoluteMaximum < smartMotorStructPtrIn->millisThentoNow)
            {
                smartMotorStructPtrIn->CommPeriodAbsoluteMaximum = smartMotorStructPtrIn->millisThentoNow;
            }
            smartMotorStructPtrIn->CommPeriodAvgs[smartMotorStructPtrIn->PeridoAvgSampleIndex++] = smartMotorStructPtrIn->millisThentoNow;
            if (smartMotorStructPtrIn->PeridoAvgSampleIndex >= PeriodAvgSamples)
                smartMotorStructPtrIn->PeridoAvgSampleIndex = 0;
            if (smartMotorStructPtrIn->PeriodAvgSampleSize < PeriodAvgSamples)
                smartMotorStructPtrIn->PeriodAvgSampleSize++;
            smartMotorStructPtrIn->CommPeriodAccumulation = 0;
            for (i = 0; i < smartMotorStructPtrIn->PeriodAvgSampleSize; i++)
            {
                smartMotorStructPtrIn->CommPeriodAccumulation += smartMotorStructPtrIn->CommPeriodAvgs[i];
            }
            if (smartMotorStructPtrIn->PeriodAvgSampleSize > 0)
                smartMotorStructPtrIn->CommPeriodAverage = smartMotorStructPtrIn->CommPeriodAccumulation / smartMotorStructPtrIn->PeriodAvgSampleSize;
            else
                smartMotorStructPtrIn->CommPeriodAverage = 0;
        }


    case 2:// request velocity
    case 4:// request current
    case 6:// request temperature or request pwm command
    case 8:// set current limit
    case 9:// set coast mode or set pwm command
        // package msg
        packageMotorData(smartMotorStructPtrIn);
        // send msg
        writeMotorData(smartMotorStructPtrIn);
        // advance comm state
        smartMotorStructPtrIn->devptr->numbytesReadIn = 0;
        if (smartMotorStructPtrIn->MotorsCommPhase == 9)
            smartMotorStructPtrIn->MotorsCommPhase = 0;
        else
            smartMotorStructPtrIn->MotorsCommPhase++;
        break;
    default: break;
    }
}