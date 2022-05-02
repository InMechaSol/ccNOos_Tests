/** \file TPMmodule.h
*   \brief <a href="https://www.inmechasol.org/" target="_blank">IMS</a>:
		<a href="https://github.com/InMechaSol/ccNOos" target="_blank">ccNOos</a>,
		Declarations for straight C and C++ 

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

#ifndef __TPM_MOD_H__
#define __TPM_MOD_H__  

#include "ADRF6650.h"
#include "LTC2360.h" 


// TPM Module Data Structure
struct freqConvStruct
{
    struct devicedatastruct* devptr;
    struct ADRF6650DataStruct data;
    UI_8 newFreqConvData;    
};
struct freqConvStruct createfreqConvStruct();
void readFreqConv(struct freqConvStruct* freqConvStructPtrIn);
void writeFreqConv(struct freqConvStruct* freqConvStructPtrIn);

struct powerMeterStruct
{
    struct devicedatastruct* devptr;    
    struct LTC2360DataStruct data;
    UI_8 newPowerMeterValue;
};
struct powerMeterStruct createPowerMeterStruct();
void readPowerMeter(struct powerMeterStruct* powerMeterStructPtrIn);
void writePowerMeter(struct powerMeterStruct* powerMeterStructPtrIn);

struct tpmStruct
{
    struct freqConvStruct freqConverter;
    struct powerMeterStruct powerMeter;    
};
struct tpmStruct createtpmStruct();
void tryReadTPMData(struct tpmStruct* tpmStructPtrIn);
void tryWriteTPMData(struct tpmStruct* tpmStructPtrIn);


#ifdef __USINGCONSOLEMENU

void parseTPMMenuAPI(struct tpmStruct* tpmStructPtrIn, struct uiStruct* uiStructPtrIn);
void writeTPMMenuScreen(struct tpmStruct* tpmStructPtrIn, struct uiStruct* uiStructPtrIn);
void writeTPMLogLine(struct tpmStruct* tpmStructPtrIn, struct logStruct* logStructPtrIn);
void parseTPMConfigLine(struct tpmStruct* tpmStructPtrIn, struct configStruct* configStructPtrIn);

#endif

#ifdef __cplusplus



#endif // !__cplusplus
#endif // !__TPM_MOD_H__
