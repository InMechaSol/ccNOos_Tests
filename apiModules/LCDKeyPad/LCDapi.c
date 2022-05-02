/** \file LCDapi.c
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

void parseLCDKeyPadAPI(struct SatComACSStruct* satcomacsStructPtrIn, struct uiStruct* uiStructPtrIn)
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