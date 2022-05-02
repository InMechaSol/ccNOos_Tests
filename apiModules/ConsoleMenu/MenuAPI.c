/** \file MenuAPI.c
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

#include "LCDapi.h"

void writeUIHelpString(struct uiStruct* uiStructPtrIn)
{
	if (uiStructPtrIn == nullptr)
	{
		uiStructPtrIn->lines2print = 0;
		return;
	}
	if (uiStructPtrIn->showHelp == ui8TRUE)
	{
		OPENSWITCH(uiStructPtrIn)
        case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "Help", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\n%sSatComACS; \tto display Main Menu", cursorString(0)   END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\n%sTerminal; \tto display Terminal Menu", cursorString(0)    END_MENU_LN;
		case 3:
			PRINT_MENU_LN   "\n%sDevices; \tto display Devices Menu", cursorString(0)   END_MENU_LN;
		case 4:
			PRINT_MENU_LN  "\n%sHelp; \tto display This View", cursorString(0)    END_MENU_LN;
		case 5:
			PRINT_MENU_LN  "\n%sUserLevel:Operator; \n\tto set current user level", cursorString(0)    END_MENU_LN;
		case 6:
			PRINT_MENU_LN  "\n%s; \t\tto Refresh Current View", cursorString(0)    END_MENU_LN;
		case 7:
			PRINT_MENU_LN  "\n%s %s - %s ", terminalSlashes(), xstr(Mn), "Key Pad Help"   END_MENU_LN;
		case 8:
			PRINT_MENU_LN  "\n%s7  Home\t8  Up", cursorString(0)    END_MENU_LN;
		case 9:
			PRINT_MENU_LN  "\n%s4  Back\t5  Action    6  Forward", cursorString(0)   END_MENU_LN;
		case 10:
			PRINT_MENU_LN  "\n%s1  Main\t2  Down", cursorString(0)    END_MENU_LN;
		default:
			uiStructPtrIn->showHelp = ui8FALSE;
		CLOSESWITCH(uiStructPtrIn)

	}
	else
		uiStructPtrIn->lines2print = 0;
}
const char* terminalPromptString(int userLevelIndex)
{
	switch ((enum uiAccessLevel)userLevelIndex)
	{
	case  uiLevel_Developer: return "\n(Developer)>>";
	case  uiLevel_Administrator: return "\n(Administrator)>>";
	case  uiLevel_Operator: return "\n(Operator)>>";
	case  uiLevel_Observer: return "\n(Observer)>>";
	default: return "\n>>";
	}
}

void parseUserLevel(struct uiStruct* uiStructPtrIn)
{
	
	OPENIF("UserLevel", uiStructPtrIn->currentMenuIndex)
		
		if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Developer") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Developer;
		else if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Operator") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Operator;
		else if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Administrator") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Administrator;
		else if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Observer") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Observer;

	CLOSEIF("UserLevel", uiStructPtrIn->currentMenuIndex)
}

void goParsedAction(enum currentMenuAction theCurrentAction, struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	switch (theCurrentAction)
	{
	case cA_Down:uiStructPtrIn->cursorIndex++;		break;
	case cA_Up:uiStructPtrIn->cursorIndex--;		break;
	case cA_Forward:								break;
	case cA_Back:									break;
	case cA_Enter:									break;
	case cA_Status:									break;
	}
}

void parseConsoleKeyPadAPI(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	enum currentMenuAction theCurrentAction = cA_NoAction;
	// Down
	KEYIF("2", cA_Down)
	// Up
	KEYIF("8", cA_Up);
	// Forward
	KEYIF("6", cA_Forward);
	// Back
	KEYIF("4", cA_Back);
	// Enter
	KEYIF("5", cA_Enter);
	// Status
	KEYIF("7", cA_Status);
	goParsedAction(theCurrentAction, satcomacsStructPtrIn, uiStructPtrIn);
	
}
// SatComACS
void parseGroupSatComACS(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	if (uiStructPtrIn == &satcomacsStructPtrIn->ConsoleMenu)
	{
		parseConsoleKeyPadAPI(satcomacsStructPtrIn, uiStructPtrIn);
		if (uiStructPtrIn->currentUserLevel > uiLevel_Observer)
		{
			parseTerminalMenuAPI(&satcomacsStructPtrIn->Terminal, uiStructPtrIn);
			parseAPTMenuAPI(&satcomacsStructPtrIn->APT, uiStructPtrIn);
			parseTPMMenuAPI(&satcomacsStructPtrIn->TPM, uiStructPtrIn);
			parseTxRxMenuAPI(&satcomacsStructPtrIn->TxRx, uiStructPtrIn);
		}
		parseUserLevel(uiStructPtrIn);
		if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Help") == ui8TRUE)
			uiStructPtrIn->showHelp = ui8TRUE;
	}
	else if (uiStructPtrIn == &satcomacsStructPtrIn->LCDKeyPad)
	{
		parseLCDKeyPadAPI(satcomacsStructPtrIn, uiStructPtrIn);
	}	
}
void parseSatComACSMenuAPI(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	//(Status) SatComACS; to see cM_MainMenu screen
	OPENIF("SatComACS", cM_MainMenu)
		//(Status) SatComACS:Terminal:State; 
		//(Command) SatComACS:Terminal:State:antState_init;
		//(Command) SatComACS:APT:GPS:Connected:0;		
		parseGroupSatComACS(satcomacsStructPtrIn, uiStructPtrIn);
	CLOSEIF("SatComACS", cM_MainMenu)
	//(Status) Terminal:State; 
	//(Command) Terminal:State:antState_init;
	//(Command) APT:GPS:Connected:0;		
	parseGroupSatComACS(satcomacsStructPtrIn, uiStructPtrIn);
}
void writeSatComACSMenuScreenConsole(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{	
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "Main", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\n%sTerminal", cursorString(uiStructPtrIn->cursorIndex == 0)   END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\n%sDevices", cursorString(uiStructPtrIn->cursorIndex == 1)    END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\n%sExecution System", cursorString(uiStructPtrIn->cursorIndex == 2)    END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeSatComACSMenuScreenLCDBig(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s - %s Menu", xstr(Mn), "Main"   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\n%sTerminal", cursorString(uiStructPtrIn->cursorIndex == 0)   END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\n%sDevices", cursorString(uiStructPtrIn->cursorIndex == 1)    END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeSatComACSMenuScreenLCDSmall(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
				case 0:
					PRINT_MENU_LN  "\n%sTerminal", cursorString(uiStructPtrIn->cursorIndex == 0)   END_MENU_LN;
				case 1:
					PRINT_MENU_LN  "\n%sDevices", cursorString(uiStructPtrIn->cursorIndex == 1)    END_MENU_LN;
				default:
					CLOSESWITCH(uiStructPtrIn)
}
void writeSatComACSMenuScreen(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	if(uiStructPtrIn!=nullptr)
	switch (uiStructPtrIn->viewFormatIndex)
	{
	case cV_Console: writeSatComACSMenuScreenConsole(satcomacsStructPtrIn, uiStructPtrIn); break;
	case cv_LCD4_40: writeSatComACSMenuScreenLCDBig(satcomacsStructPtrIn, uiStructPtrIn); break;
	case cv_LCD2_40: writeSatComACSMenuScreenLCDSmall(satcomacsStructPtrIn, uiStructPtrIn); break;
	}
}

// SatComACS:Devices
void parseSatComACSDevicesMenuAPI(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	parseSatComACSMenuAPI(satcomacsStructPtrIn, uiStructPtrIn);
}
void writeSatComACSDevicesMenuScreenConsole(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "Devices", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\n%sAPT WMM Device", cursorString(uiStructPtrIn->cursorIndex == 0)		END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\n%sTPM Device", cursorString(uiStructPtrIn->cursorIndex == 1)			END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\n%sTxRx Device", cursorString(uiStructPtrIn->cursorIndex == 2)		END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeSatComACSDevicesMenuScreenLCDBig(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s - %s Menu ", xstr(Mn), "Devices"   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\n%sAPT WMM Device", cursorString(uiStructPtrIn->cursorIndex == 0)		END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\n%sTPM Device", cursorString(uiStructPtrIn->cursorIndex == 1)			END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\n%sTxRx Device", cursorString(uiStructPtrIn->cursorIndex == 2)		END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeSatComACSDevicesMenuScreenLCDSmall(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "Devices", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\n%sAPT WMM Device", cursorString(uiStructPtrIn->cursorIndex == 0)		END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeSatComACSDevicesMenuScreen(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	if (uiStructPtrIn != nullptr)
	switch (uiStructPtrIn->viewFormatIndex)
	{
	case cV_Console: writeSatComACSDevicesMenuScreenConsole(satcomacsStructPtrIn, uiStructPtrIn); break;
	case cv_LCD4_40: writeSatComACSDevicesMenuScreenLCDBig(satcomacsStructPtrIn, uiStructPtrIn); break;
	case cv_LCD2_40: writeSatComACSDevicesMenuScreenLCDSmall(satcomacsStructPtrIn, uiStructPtrIn); break;
	}
}

// SatComControl: antennaStruct
const char* currentStateString(struct antennaStruct* terminalStructPtrIn)
{
	switch (terminalStructPtrIn->State)
	{
	case antState_init: return "Initialization";
	case antState_NotAcquired: return "Not Acquiring";
	case antState_Acquiring: return "Acquiring";
	case antState_Acquired: return "Acquired";
	case antState_Error: return "Error";
	default: return "Invalid State!";
	}
}
void parseTerminalMenuAPI(struct antennaStruct* terminalStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	//(Status) Terminal; to see cM_Terminal screen
	OPENIF("Terminal", cM_Terminal)	
		//(Status) Terminal:State; 
		//(Command) Terminal:State:antState_init;
		//(Command) Terminal:TargetSatellite:UpLinkFreq_kHz:2100000.0;		
	CLOSEIF("Terminal", cM_Terminal)
}
void writeTerminalMenuScreenConsole(struct antennaStruct* terminalStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "Terminal", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\nCurrent State: %s", currentStateString(terminalStructPtrIn)						END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\n%sGeo-Location", cursorString(uiStructPtrIn->cursorIndex == 0)					END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\n%sAttitude and Position", cursorString(uiStructPtrIn->cursorIndex == 1)			END_MENU_LN;
		case 4:
			PRINT_MENU_LN  "\n%sSatCom System", cursorString(uiStructPtrIn->cursorIndex == 2)					END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeTerminalMenuScreenLCDSmall(struct antennaStruct* terminalStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s - %s Menu ", xstr(Mn), "Terminal"   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\nCurrent State: %s", currentStateString(terminalStructPtrIn)						END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\n%sGeo-Location", cursorString(uiStructPtrIn->cursorIndex == 0)					END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\n%sAttitude and Position", cursorString(uiStructPtrIn->cursorIndex == 1)			END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeTerminalMenuScreenLCDBig(struct antennaStruct* terminalStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s - %s Menu ", xstr(Mn), "Terminal"   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\nCurrent State: %s", currentStateString(terminalStructPtrIn)						END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeTerminalMenuScreen(struct antennaStruct* terminalStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	if (uiStructPtrIn != nullptr)
	switch (uiStructPtrIn->viewFormatIndex)
	{
	case cV_Console: writeTerminalMenuScreenConsole(terminalStructPtrIn, uiStructPtrIn); break;
	case cv_LCD4_40: writeTerminalMenuScreenLCDBig(terminalStructPtrIn, uiStructPtrIn); break;
	case cv_LCD2_40: writeTerminalMenuScreenLCDSmall(terminalStructPtrIn, uiStructPtrIn); break;
	}
}

// TxRx Module
void parseGroupTxRx(struct txRxStruct* txRxStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	int iComma = 0;
	if (uiStructPtrIn->devptr->newDataReadIn){
		for (int i = uiStructPtrIn->parseIndex; i < charBuffMax; i++){
			if (uiStructPtrIn->devptr->inbuff.charbuff[i] == ';') {
				iComma = i; break;
	}	}	}
	if (iComma > 0)
	{
		uiStructPtrIn->devptr->inbuff.charbuff[iComma] = 0x00;

		OPENIF("T1", cM_devTXRX)
			//(Command) T1:val; 		
			if (ATO_F(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], &txRxStructPtrIn->AttenuatorValues[0].DATCMD))
				txRxStructPtrIn->AttenuatorNeedsWriting[0] = ui8TRUE;			
		CLOSEIF("T1", cM_devTXRX)	

		OPENIF("T2", cM_devTXRX)
			//(Command) T2:val; 	
			if (ATO_F(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], &txRxStructPtrIn->AttenuatorValues[2].DATCMD))
				txRxStructPtrIn->AttenuatorNeedsWriting[2] = ui8TRUE;
		CLOSEIF("T2", cM_devTXRX)

		OPENIF("R", cM_devTXRX)
			//(Command) R:val; 	
			if (ATO_F(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], &txRxStructPtrIn->AttenuatorValues[1].DATCMD))
				txRxStructPtrIn->AttenuatorNeedsWriting[1] = ui8TRUE;
		CLOSEIF("R", cM_devTXRX)

		OPENIF("M1", cM_devTXRX)
			//(Command) M1:val; 		
			if (ATO_U8(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], &txRxStructPtrIn->MDMSwitchStates[0]))
				txRxStructPtrIn->MDMSwitchNeedsWriting[0] = ui8TRUE;
		CLOSEIF("M1", cM_devTXRX)

		OPENIF("M2", cM_devTXRX)
			//(Command) M2:val; 		
			if (ATO_U8(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], &txRxStructPtrIn->MDMSwitchStates[1]))
				txRxStructPtrIn->MDMSwitchNeedsWriting[1] = ui8TRUE;
		CLOSEIF("M2", cM_devTXRX)

		OPENIF("M3", cM_devTXRX)
			//(Command) M3:val; 		
			if (ATO_U8(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], &txRxStructPtrIn->MDMSwitchStates[2]))
				txRxStructPtrIn->MDMSwitchNeedsWriting[2] = ui8TRUE;
		CLOSEIF("M3", cM_devTXRX)

		OPENIF("M4", cM_devTXRX)
			//(Command) M4:val; 		
			if (ATO_U8(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], &txRxStructPtrIn->MDMSwitchStates[3]))
				txRxStructPtrIn->MDMSwitchNeedsWriting[3] = ui8TRUE;
		CLOSEIF("M4", cM_devTXRX)

		uiStructPtrIn->devptr->inbuff.charbuff[iComma] = ';';
		//uiStructPtrIn->currentMenuIndex = cM_devTXRX;
	}
}
void parseTxRxMenuAPI(struct txRxStruct* txRxStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	//(Status) TxRx; to see cM_TxRx screen
	OPENIF("TxRx", cM_devTXRX)
		//(Status) TxRx:; 
		//(Command) TxRx::;
		//(Command) TxRx:::;	
		parseGroupTxRx(txRxStructPtrIn, uiStructPtrIn);
	CLOSEIF("TxRx", cM_devTXRX)
	parseGroupTxRx(txRxStructPtrIn, uiStructPtrIn);
}
const char* switchOpenClosedString(UI_8 openClose)
{
	if (openClose)
		return "open";
	else
		return "closed";
}
void writeTxRxMenuScreenConsole(struct txRxStruct* txRxStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "TxRx", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\nCurrent Attenuation Tx1: %6.2f dB", txRxStructPtrIn->AttenuatorValues[0].DATCMD      END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\nCurrent Attenuation Rx:  %6.2f dB", txRxStructPtrIn->AttenuatorValues[1].DATCMD      END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\nCurrent Attenuation Tx2: %6.2f dB", txRxStructPtrIn->AttenuatorValues[2].DATCMD      END_MENU_LN;
		case 4:
			PRINT_MENU_LN  "\n-----------------------------------"      END_MENU_LN;
		case 5:
			PRINT_MENU_LN  "\nModem Switch State M1: %s  ", switchOpenClosedString(txRxStructPtrIn->MDMSwitchStates[0] )     END_MENU_LN;
		case 6:
			PRINT_MENU_LN  "\nModem Switch State M2: %s   ", switchOpenClosedString(txRxStructPtrIn->MDMSwitchStates[1] )     END_MENU_LN;
		case 7:
			PRINT_MENU_LN  "\nModem Switch State M3: %s ", switchOpenClosedString(txRxStructPtrIn->MDMSwitchStates[2] )     END_MENU_LN;
		case 8:
			PRINT_MENU_LN  "\nModem Switch State M4: %s ", switchOpenClosedString(txRxStructPtrIn->MDMSwitchStates[3] )     END_MENU_LN;
		case 9:
			PRINT_MENU_LN  "\n//////////////////////////////////"      END_MENU_LN;
		case 10:
			PRINT_MENU_LN  "\n\"T1:22.75;\" set Tx1 to 22.75"      END_MENU_LN;
		case 11:
			PRINT_MENU_LN  "\n\"R:21.00;\"  set Rx  to 21.00"      END_MENU_LN;
		case 12:
			PRINT_MENU_LN  "\n\"T2:19.25;\" set Tx2 to 19.25"      END_MENU_LN;
		case 13:
			PRINT_MENU_LN  "\n\"M1:1;\"     set Mdm1Sw open"      END_MENU_LN;
		case 14:
			PRINT_MENU_LN  "\n\"M4:0;\"     set Mdm4Sw closed"      END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeTxRxMenuScreenLCDBig(struct txRxStruct* txRxStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "TxRx", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\nCurrent Attenuation Tx1: %6.2f dB", txRxStructPtrIn->AttenuatorValues[0]      END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\nCurrent Attenuation Rx:  %6.2f dB", txRxStructPtrIn->AttenuatorValues[1]      END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\nCurrent Attenuation Tx2: %6.2f dB", txRxStructPtrIn->AttenuatorValues[2]      END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeTxRxMenuScreenLCDSmall(struct txRxStruct* txRxStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 1:
			PRINT_MENU_LN  "\nCurrent Attenuation Tx1: %6.2f dB", txRxStructPtrIn->AttenuatorValues[0]      END_MENU_LN;
			//case 3:
			//	PRINT_MENU_LN  "\nCurrent Attenuation Rx:  %6.2f dB", txRxStructPtrIn->AttenuatorValues[1]      END_MENU_LN;
		case 2:
			PRINT_MENU_LN  "\nCurrent Attenuation Tx2: %6.2f dB", txRxStructPtrIn->AttenuatorValues[2]      END_MENU_LN;
		default:
	CLOSESWITCH(uiStructPtrIn)
}
void writeTxRxMenuScreen(struct txRxStruct* txRxStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	if (uiStructPtrIn != nullptr)
	switch (uiStructPtrIn->viewFormatIndex)
	{
	case cV_Console: writeTxRxMenuScreenConsole(txRxStructPtrIn, uiStructPtrIn); break;
	case cv_LCD4_40: writeTxRxMenuScreenLCDBig(txRxStructPtrIn, uiStructPtrIn); break;
	case cv_LCD2_40: writeTxRxMenuScreenLCDSmall(txRxStructPtrIn, uiStructPtrIn); break;
	}
}

// APT Module
void parseAPTMenuAPI(struct aptStruct* aptStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	//(Status) APT; to see cM_TxRx screen
	OPENIF("APT", cM_devAPT)
		//(Status) APT:; 
		//(Command) APT::;
		//(Command) APT:::;		
	CLOSEIF("APT", cM_devAPT)
}
void writeAPTMenuScreenConsole(struct aptStruct* aptStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
	case 0:
		PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "APT", terminalSlashes()	END_MENU_LN;
	case 1:
		PRINT_MENU_LN  "\nLatitude: \t\t%8.4f", aptStructPtrIn->GPS.data.lattitude						END_MENU_LN;
	case 2:
		PRINT_MENU_LN  "\nLongitude: \t\t%8.4f", aptStructPtrIn->GPS.data.longitude						END_MENU_LN;
	case 3:
		PRINT_MENU_LN  "\nAltitude: \t\t%8.0f", aptStructPtrIn->GPS.data.altitude						END_MENU_LN;
	case 4:
		PRINT_MENU_LN  "\nDate/Time (UTC): %2i/%2i/%4i %6.0f", aptStructPtrIn->GPS.data.month, aptStructPtrIn->GPS.data.day, aptStructPtrIn->GPS.data.year, aptStructPtrIn->GPS.data.utctime  END_MENU_LN;
	case 5:
		PRINT_MENU_LN  "\nMagnetic Declination: \t%6.2f", 0.0											END_MENU_LN;
	case 6:
		PRINT_MENU_LN  "\nAzimuth Heading: \t%6.2f", aptStructPtrIn->eCompass.data.yaw					END_MENU_LN;
	case 7:
		PRINT_MENU_LN  "\nElevation Pitch: \t%6.2f", aptStructPtrIn->eCompass.data.pitch				END_MENU_LN;
	case 8:
		PRINT_MENU_LN  "\nAPT Roll: \t\t%6.2f", aptStructPtrIn->eCompass.data.roll						END_MENU_LN;
	default:
		CLOSESWITCH(uiStructPtrIn)
}
void writeAPTMenuScreenLCDBig(struct aptStruct* aptStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
	case 0:
		PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "APT", terminalSlashes()	END_MENU_LN;
	case 1:
		PRINT_MENU_LN  "\nLatitude: \t\t%8.4f", aptStructPtrIn->GPS.data.lattitude						END_MENU_LN;
	case 2:
		PRINT_MENU_LN  "\nLongitude: \t\t%8.4f", aptStructPtrIn->GPS.data.longitude						END_MENU_LN;
	case 3:
		PRINT_MENU_LN  "\nAltitude: \t\t%8.0f", aptStructPtrIn->GPS.data.altitude						END_MENU_LN;
	default:
		CLOSESWITCH(uiStructPtrIn)
}
void writeAPTMenuScreenLCDSmall(struct aptStruct* aptStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
	case 0:
		PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "APT", terminalSlashes()	END_MENU_LN;
	case 1:
		PRINT_MENU_LN  "\nLatitude: \t\t%8.4f", aptStructPtrIn->GPS.data.lattitude						END_MENU_LN;
	default:
		CLOSESWITCH(uiStructPtrIn)
}
void writeAPTMenuScreen(struct aptStruct* aptStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	if (uiStructPtrIn != nullptr)
	switch (uiStructPtrIn->viewFormatIndex)
	{
	case cV_Console: writeAPTMenuScreenConsole(aptStructPtrIn, uiStructPtrIn); break;
	case cv_LCD4_40: writeAPTMenuScreenLCDBig(aptStructPtrIn, uiStructPtrIn); break;
	case cv_LCD2_40: writeAPTMenuScreenLCDSmall(aptStructPtrIn, uiStructPtrIn); break;
	}
	
}

// TPM Module
void parseTPMMenuAPI(struct tpmStruct* tpmStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	//(Status) APT; to see cM_TxRx screen
	OPENIF("TPM", cM_devTPM)
		//(Status) TPM:; 
		//(Command) TPM::;
		//(Command) TPM:::;		
	CLOSEIF("TPM", cM_devTPM)
}
void writeTPMMenuScreenConsole(struct tpmStruct* tpmStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
	case 0:
		PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "TPM", terminalSlashes()   END_MENU_LN;
	case 1:
		PRINT_MENU_LN  "\nDesired Center   (MHz): %9.4f", tpmStructPtrIn->freqConverter.data.DesiredCenterFreqMHz			END_MENU_LN;
	case 2:
		PRINT_MENU_LN  "\nRequired LO      (MHz): %9.4f", tpmStructPtrIn->freqConverter.data.RequiredLOFreqMHz	END_MENU_LN;
	case 3:
		PRINT_MENU_LN  "\nLocked on LO     (0/1):    %1d", tpmStructPtrIn->freqConverter.data.LockedOnRequiredLOFreq						END_MENU_LN;
	case 4:
		PRINT_MENU_LN  "\nPower Filter BW  (MHz):  %3.0f", tpmStructPtrIn->powerMeter.data.BandwidthMHz  END_MENU_LN;
	case 5:
		PRINT_MENU_LN  "\nPower In-Band    (dBm):  %6.2f", tpmStructPtrIn->powerMeter.data.PowerMeasuredinBanddB 		END_MENU_LN;
	case 6:
		PRINT_MENU_LN  "\nADC Reading Good (0/1):    %1d", tpmStructPtrIn->powerMeter.data.value_good					END_MENU_LN;
	case 7:
		PRINT_MENU_LN  "\nADC Value             : %4d", tpmStructPtrIn->powerMeter.data.current_value				END_MENU_LN;
	default:
		CLOSESWITCH(uiStructPtrIn)
}
void writeTPMMenuScreenLCDBig(struct tpmStruct* tpmStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
	case 0:
		PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "TPM", terminalSlashes()   END_MENU_LN;
	case 1:
		PRINT_MENU_LN  "\nDesired Center   (MHz): %9.4f", tpmStructPtrIn->freqConverter.data.DesiredCenterFreqMHz			END_MENU_LN;
	case 2:
		PRINT_MENU_LN  "\nRequired LO      (MHz): %9.4f", tpmStructPtrIn->freqConverter.data.RequiredLOFreqMHz	END_MENU_LN;
	case 3:
		PRINT_MENU_LN  "\nLocked on LO     (0/1):    %1d", tpmStructPtrIn->freqConverter.data.LockedOnRequiredLOFreq						END_MENU_LN;
	default:
		CLOSESWITCH(uiStructPtrIn)
}
void writeTPMMenuScreenLCDSmall(struct tpmStruct* tpmStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
	case 0:
		PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "TPM", terminalSlashes()   END_MENU_LN;
	case 1:
		PRINT_MENU_LN  "\nDesired Center   (MHz): %9.4f", tpmStructPtrIn->freqConverter.data.DesiredCenterFreqMHz			END_MENU_LN;
	default:
		CLOSESWITCH(uiStructPtrIn)
}
void writeTPMMenuScreen(struct tpmStruct* tpmStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	if (uiStructPtrIn != nullptr)
	switch (uiStructPtrIn->viewFormatIndex)
	{
	case cV_Console: writeTPMMenuScreenConsole(tpmStructPtrIn, uiStructPtrIn); break;
	case cv_LCD4_40: writeTPMMenuScreenLCDBig(tpmStructPtrIn, uiStructPtrIn); break;
	case cv_LCD2_40: writeTPMMenuScreenLCDSmall(tpmStructPtrIn, uiStructPtrIn); break;
	}
	
}
