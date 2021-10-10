#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=PIC32MZ_Tests.cpp ../../ccNOos/apiCompModule/api_comp_mod.c ../../ccNOos/apiCompModule/api_comp_mod_class.cpp ../../ccNOos/computeModule/compute_module.c ../../ccNOos/computeModule/compute_module_class.cpp ../../ccNOos/consoleMenu/console_menu.c ../../ccNOos/consoleMenu/console_menu_class.cpp ../../ccNOos/deviceCompModule/dev_comp_mod.c ../../ccNOos/deviceCompModule/dev_comp_mod_class.cpp ../../ccNOos/executionSystem/execution_system.c ../../ccNOos/executionSystem/execution_system_class.cpp ../../ccNOos/ioDevice/io_device.c ../../ccNOos/ioDevice/io_device_class.cpp ../../ccNOos/tests/ccNOos_tests.c ../../ccNOos/tests/ccNOos_tests_class.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/PIC32MZ_Tests.o ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o ${OBJECTDIR}/_ext/906818983/compute_module.o ${OBJECTDIR}/_ext/906818983/compute_module_class.o ${OBJECTDIR}/_ext/1423417940/console_menu.o ${OBJECTDIR}/_ext/1423417940/console_menu_class.o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o ${OBJECTDIR}/_ext/1324609859/execution_system.o ${OBJECTDIR}/_ext/1324609859/execution_system_class.o ${OBJECTDIR}/_ext/1921990522/io_device.o ${OBJECTDIR}/_ext/1921990522/io_device_class.o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o
POSSIBLE_DEPFILES=${OBJECTDIR}/PIC32MZ_Tests.o.d ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o.d ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o.d ${OBJECTDIR}/_ext/906818983/compute_module.o.d ${OBJECTDIR}/_ext/906818983/compute_module_class.o.d ${OBJECTDIR}/_ext/1423417940/console_menu.o.d ${OBJECTDIR}/_ext/1423417940/console_menu_class.o.d ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o.d ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o.d ${OBJECTDIR}/_ext/1324609859/execution_system.o.d ${OBJECTDIR}/_ext/1324609859/execution_system_class.o.d ${OBJECTDIR}/_ext/1921990522/io_device.o.d ${OBJECTDIR}/_ext/1921990522/io_device_class.o.d ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/PIC32MZ_Tests.o ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o ${OBJECTDIR}/_ext/906818983/compute_module.o ${OBJECTDIR}/_ext/906818983/compute_module_class.o ${OBJECTDIR}/_ext/1423417940/console_menu.o ${OBJECTDIR}/_ext/1423417940/console_menu_class.o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o ${OBJECTDIR}/_ext/1324609859/execution_system.o ${OBJECTDIR}/_ext/1324609859/execution_system_class.o ${OBJECTDIR}/_ext/1921990522/io_device.o ${OBJECTDIR}/_ext/1921990522/io_device_class.o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o

# Source Files
SOURCEFILES=PIC32MZ_Tests.cpp ../../ccNOos/apiCompModule/api_comp_mod.c ../../ccNOos/apiCompModule/api_comp_mod_class.cpp ../../ccNOos/computeModule/compute_module.c ../../ccNOos/computeModule/compute_module_class.cpp ../../ccNOos/consoleMenu/console_menu.c ../../ccNOos/consoleMenu/console_menu_class.cpp ../../ccNOos/deviceCompModule/dev_comp_mod.c ../../ccNOos/deviceCompModule/dev_comp_mod_class.cpp ../../ccNOos/executionSystem/execution_system.c ../../ccNOos/executionSystem/execution_system_class.cpp ../../ccNOos/ioDevice/io_device.c ../../ccNOos/ioDevice/io_device_class.cpp ../../ccNOos/tests/ccNOos_tests.c ../../ccNOos/tests/ccNOos_tests_class.cpp



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ1024EFE064
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1522225941/api_comp_mod.o: ../../ccNOos/apiCompModule/api_comp_mod.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1522225941" 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o.d 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1522225941/api_comp_mod.o.d" -o ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o ../../ccNOos/apiCompModule/api_comp_mod.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1522225941/api_comp_mod.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/906818983/compute_module.o: ../../ccNOos/computeModule/compute_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/906818983" 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/906818983/compute_module.o.d" -o ${OBJECTDIR}/_ext/906818983/compute_module.o ../../ccNOos/computeModule/compute_module.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/906818983/compute_module.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1423417940/console_menu.o: ../../ccNOos/consoleMenu/console_menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1423417940" 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1423417940/console_menu.o.d" -o ${OBJECTDIR}/_ext/1423417940/console_menu.o ../../ccNOos/consoleMenu/console_menu.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1423417940/console_menu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o: ../../ccNOos/deviceCompModule/dev_comp_mod.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1048286395" 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o.d 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o.d" -o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o ../../ccNOos/deviceCompModule/dev_comp_mod.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324609859/execution_system.o: ../../ccNOos/executionSystem/execution_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1324609859" 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324609859/execution_system.o.d" -o ${OBJECTDIR}/_ext/1324609859/execution_system.o ../../ccNOos/executionSystem/execution_system.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324609859/execution_system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1921990522/io_device.o: ../../ccNOos/ioDevice/io_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1921990522" 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1921990522/io_device.o.d" -o ${OBJECTDIR}/_ext/1921990522/io_device.o ../../ccNOos/ioDevice/io_device.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1921990522/io_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o: ../../ccNOos/tests/ccNOos_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1571702537" 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d" -o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o ../../ccNOos/tests/ccNOos_tests.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/1522225941/api_comp_mod.o: ../../ccNOos/apiCompModule/api_comp_mod.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1522225941" 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o.d 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1522225941/api_comp_mod.o.d" -o ${OBJECTDIR}/_ext/1522225941/api_comp_mod.o ../../ccNOos/apiCompModule/api_comp_mod.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1522225941/api_comp_mod.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/906818983/compute_module.o: ../../ccNOos/computeModule/compute_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/906818983" 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/906818983/compute_module.o.d" -o ${OBJECTDIR}/_ext/906818983/compute_module.o ../../ccNOos/computeModule/compute_module.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/906818983/compute_module.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1423417940/console_menu.o: ../../ccNOos/consoleMenu/console_menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1423417940" 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1423417940/console_menu.o.d" -o ${OBJECTDIR}/_ext/1423417940/console_menu.o ../../ccNOos/consoleMenu/console_menu.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1423417940/console_menu.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o: ../../ccNOos/deviceCompModule/dev_comp_mod.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1048286395" 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o.d 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o.d" -o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o ../../ccNOos/deviceCompModule/dev_comp_mod.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1048286395/dev_comp_mod.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324609859/execution_system.o: ../../ccNOos/executionSystem/execution_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1324609859" 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324609859/execution_system.o.d" -o ${OBJECTDIR}/_ext/1324609859/execution_system.o ../../ccNOos/executionSystem/execution_system.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324609859/execution_system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1921990522/io_device.o: ../../ccNOos/ioDevice/io_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1921990522" 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1921990522/io_device.o.d" -o ${OBJECTDIR}/_ext/1921990522/io_device.o ../../ccNOos/ioDevice/io_device.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1921990522/io_device.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o: ../../ccNOos/tests/ccNOos_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1571702537" 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o 
	${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d" -o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o ../../ccNOos/tests/ccNOos_tests.c    -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/PIC32MZ_Tests.o: PIC32MZ_Tests.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MZ_Tests.o.d 
	@${RM} ${OBJECTDIR}/PIC32MZ_Tests.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/PIC32MZ_Tests.o.d" -o ${OBJECTDIR}/PIC32MZ_Tests.o PIC32MZ_Tests.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/PIC32MZ_Tests.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o: ../../ccNOos/apiCompModule/api_comp_mod_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1522225941" 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o.d" -o ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o ../../ccNOos/apiCompModule/api_comp_mod_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/906818983/compute_module_class.o: ../../ccNOos/computeModule/compute_module_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/906818983" 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/906818983/compute_module_class.o.d" -o ${OBJECTDIR}/_ext/906818983/compute_module_class.o ../../ccNOos/computeModule/compute_module_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/906818983/compute_module_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1423417940/console_menu_class.o: ../../ccNOos/consoleMenu/console_menu_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1423417940" 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1423417940/console_menu_class.o.d" -o ${OBJECTDIR}/_ext/1423417940/console_menu_class.o ../../ccNOos/consoleMenu/console_menu_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1423417940/console_menu_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o: ../../ccNOos/deviceCompModule/dev_comp_mod_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1048286395" 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o.d" -o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o ../../ccNOos/deviceCompModule/dev_comp_mod_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324609859/execution_system_class.o: ../../ccNOos/executionSystem/execution_system_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1324609859" 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1324609859/execution_system_class.o.d" -o ${OBJECTDIR}/_ext/1324609859/execution_system_class.o ../../ccNOos/executionSystem/execution_system_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324609859/execution_system_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1921990522/io_device_class.o: ../../ccNOos/ioDevice/io_device_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1921990522" 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1921990522/io_device_class.o.d" -o ${OBJECTDIR}/_ext/1921990522/io_device_class.o ../../ccNOos/ioDevice/io_device_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1921990522/io_device_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o: ../../ccNOos/tests/ccNOos_tests_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1571702537" 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o.d" -o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o ../../ccNOos/tests/ccNOos_tests_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/PIC32MZ_Tests.o: PIC32MZ_Tests.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PIC32MZ_Tests.o.d 
	@${RM} ${OBJECTDIR}/PIC32MZ_Tests.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/PIC32MZ_Tests.o.d" -o ${OBJECTDIR}/PIC32MZ_Tests.o PIC32MZ_Tests.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/PIC32MZ_Tests.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o: ../../ccNOos/apiCompModule/api_comp_mod_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1522225941" 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o.d" -o ${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o ../../ccNOos/apiCompModule/api_comp_mod_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1522225941/api_comp_mod_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/906818983/compute_module_class.o: ../../ccNOos/computeModule/compute_module_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/906818983" 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/906818983/compute_module_class.o.d" -o ${OBJECTDIR}/_ext/906818983/compute_module_class.o ../../ccNOos/computeModule/compute_module_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/906818983/compute_module_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1423417940/console_menu_class.o: ../../ccNOos/consoleMenu/console_menu_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1423417940" 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1423417940/console_menu_class.o.d" -o ${OBJECTDIR}/_ext/1423417940/console_menu_class.o ../../ccNOos/consoleMenu/console_menu_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1423417940/console_menu_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o: ../../ccNOos/deviceCompModule/dev_comp_mod_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1048286395" 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o.d" -o ${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o ../../ccNOos/deviceCompModule/dev_comp_mod_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1048286395/dev_comp_mod_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324609859/execution_system_class.o: ../../ccNOos/executionSystem/execution_system_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1324609859" 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1324609859/execution_system_class.o.d" -o ${OBJECTDIR}/_ext/1324609859/execution_system_class.o ../../ccNOos/executionSystem/execution_system_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324609859/execution_system_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1921990522/io_device_class.o: ../../ccNOos/ioDevice/io_device_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1921990522" 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1921990522/io_device_class.o.d" -o ${OBJECTDIR}/_ext/1921990522/io_device_class.o ../../ccNOos/ioDevice/io_device_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1921990522/io_device_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o: ../../ccNOos/tests/ccNOos_tests_class.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1571702537" 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o 
	${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o.d" -o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o ../../ccNOos/tests/ccNOos_tests_class.cpp   -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	@${FIXDEPS} "${OBJECTDIR}/_ext/1571702537/ccNOos_tests_class.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIC32MZ_Tests.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
