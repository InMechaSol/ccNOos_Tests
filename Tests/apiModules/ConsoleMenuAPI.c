/** \file ConsoleMenuAPI.c
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

#include "ConsoleMenuAPI.h"

// Constant String Functions for Menu Display
const char* OpHistoryString(int atIndex)
{
	switch (atIndex)
	{
	case 1: return "Open";
	case 2: return "Close";
	case 3: return "Stop";
	case 4: return "PWM+";
	case 5: return "PWM-";
	case 6: return "PWM0";
	case 7: return "Push";
	case 8: return "Hold";
	default: return " ";
	}
}
const char* ccNOosTestsModeString(enum enumNOosTestsMode TestsModeIn)
{
	switch (TestsModeIn)
	{
		case noOSTests_uninitialized: return "uninitialized";
		case noOSTests_inprogress: return "in progress";
		case noOSTests_done: return "done";
		default: return "invalid mode";
	}
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

// The Help Menu String Generator
void writeUIHelpString(struct uiStruct* uiStructPtrIn)
{
//\\\\\ ccGripper - Help Menu \\\\\
//	Stop;         to Trigger Stop Move
//	UserLevel : Operator;
//				  to Promote User to Operator Level
//	Open;         to Trigger Open Move
//	Close;        to Trigger Close Move
//	Latch;        to Attempt Latch of High / Low Limits
//	AutoUpdate;   to Enable AutoUpdate of this Screen
//	Help;         to display This View
//	;             to Refresh Current View
//\\\\\ ccGripper - Key Pad Help
//	7  Home       8  Up
//	4  Back       5  Action    6  Forward
//	1  Main       2  Down

	if (uiStructPtrIn == nullptr)
	{
		return;
	}
	if (uiStructPtrIn->showHelp == ui8TRUE)
	{
		OPENSWITCH(uiStructPtrIn)
		case 0:
			PRINT_MENU_LN  "\n%s %s - %s Menu %s", terminalSlashes(), xstr(Mn), "Help", terminalSlashes()   END_MENU_LN;
		case 1:
			PRINT_MENU_LN  "\n%sStop; \tto Trigger Stop Move", cursorString(0)    END_MENU_LN;
		case 2: 
			PRINT_MENU_LN "\n\%sUserLevel:Operator; \n\t\tto Promote User to Operator Level", cursorString(0) END_MENU_LN;
		case 3:
			PRINT_MENU_LN  "\n%sOpen; \tto Trigger Open Move", cursorString(0)   END_MENU_LN;
		case 4:
			PRINT_MENU_LN  "\n%sClose; \tto Trigger Close Move", cursorString(0)    END_MENU_LN;
		case 5:
			PRINT_MENU_LN  "\n%sLatch; \tto Attempt Latch of High/Low Limits", cursorString(0)    END_MENU_LN;
		case 6:
			PRINT_MENU_LN  "\n%sAutoUpdate; \tto Enable AutoUpdate of this Screen", cursorString(0)    END_MENU_LN;
		
		case 7:
			PRINT_MENU_LN  "\n%sHelp; \tto display This View", cursorString(0)    END_MENU_LN;
		case 8:
			PRINT_MENU_LN  "\n%s; \t\tto Refresh Current View", cursorString(0)    END_MENU_LN;
		case 9:
			PRINT_MENU_LN  "\n%s %s - %s ", terminalSlashes(), xstr(Mn), "Key Pad Help"   END_MENU_LN;
		case 10:
			PRINT_MENU_LN  "\n%s7  Home\t8  Up", cursorString(0)    END_MENU_LN;
		case 11:
			PRINT_MENU_LN  "\n%s4  Back\t5  Action    6  Forward", cursorString(0)   END_MENU_LN;
		case 12:
			PRINT_MENU_LN  "\n%s1  Main\t2  Down", cursorString(0)    END_MENU_LN;
		default:
			uiStructPtrIn->showHelp = ui8FALSE;
		CLOSESWITCH(uiStructPtrIn)

	}
	else
		uiStructPtrIn->lines2print = 0;
}

// Printing
#define HISTORYINDEX(DISPLEN, LOGINDEX, LOGMAXSIZE) { \
	for (i = 1; i <= DISPLEN; i++) \
	{ \
		jj[i - 1] = LOGINDEX - (i-1)-1; \
		if (jj[i - 1] < 0) \
			jj[i - 1] = LOGMAXSIZE + jj[i - 1]; \
	} \
}

void printccNOosTestsConsoleAPI(struct ccNOosTestsStruct* NOosTestsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENSWITCH(uiStructPtrIn)
		case 0://Intelligent Gripper FW v0.1.0-dev 26OCT2022
			PRINT_MENU_LN "\nccNOos Tests FW v%s %s", ccNOosTests_VerString(), ccNOosTests_VerDateString()  END_MENU_LN;
		
		
		default:
	CLOSESWITCH(uiStructPtrIn)

}

// Parsing - Common
void parseUserLevel(struct uiStruct* uiStructPtrIn)
{

	OPENIF("UserLevel", uiStructPtrIn->currentMenuIndex)

		if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Operator") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Operator;
		else if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Observer") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Observer;

	CLOSEIF("UserLevel", uiStructPtrIn->currentMenuIndex)
}
void goParsedAction(enum currentMenuAction theCurrentAction, struct ccNOosTestsStruct* NOosTestsStructPtrIn, struct uiStruct* uiStructPtrIn)
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
void parseConsoleKeyPadAPI(struct ccNOosTestsStruct* NOosTestsStructPtrIn, struct uiStruct* uiStructPtrIn)
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
	goParsedAction(theCurrentAction, NOosTestsStructPtrIn, uiStructPtrIn);

}
void parseccNOosTestsConsoleAPI(struct ccNOosTestsStruct* NOosTestsStructPtrIn, struct uiStruct* uiStructPtrIn)
{
	OPENIF("RunTest", uiStructPtrIn->currentMenuIndex)

		if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Operator") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Operator;
		else if (stringMatchCaseSensitive(&uiStructPtrIn->devptr->inbuff.charbuff[uiStructPtrIn->parseIndex], "Observer") == ui8TRUE)
			uiStructPtrIn->currentUserLevel = uiLevel_Observer;

	CLOSEIF("RunTest", uiStructPtrIn->currentMenuIndex)

}
// Parsing - Modules
