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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../ccNOos/computeModule/compute_module.c ../../ccNOos/consoleMenu/console_menu.c ../../ccNOos/executionSystem/execution_system.c ../../ccNOos/ioDevice/io_device.c ../../ccNOos/tests/ccNOos_tests.c dsPIC33F_Tests.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/906818983/compute_module.o ${OBJECTDIR}/_ext/1423417940/console_menu.o ${OBJECTDIR}/_ext/1324609859/execution_system.o ${OBJECTDIR}/_ext/1921990522/io_device.o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o ${OBJECTDIR}/dsPIC33F_Tests.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/906818983/compute_module.o.d ${OBJECTDIR}/_ext/1423417940/console_menu.o.d ${OBJECTDIR}/_ext/1324609859/execution_system.o.d ${OBJECTDIR}/_ext/1921990522/io_device.o.d ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d ${OBJECTDIR}/dsPIC33F_Tests.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/906818983/compute_module.o ${OBJECTDIR}/_ext/1423417940/console_menu.o ${OBJECTDIR}/_ext/1324609859/execution_system.o ${OBJECTDIR}/_ext/1921990522/io_device.o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o ${OBJECTDIR}/dsPIC33F_Tests.o

# Source Files
SOURCEFILES=../../ccNOos/computeModule/compute_module.c ../../ccNOos/consoleMenu/console_menu.c ../../ccNOos/executionSystem/execution_system.c ../../ccNOos/ioDevice/io_device.c ../../ccNOos/tests/ccNOos_tests.c dsPIC33F_Tests.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ64MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ64MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/906818983/compute_module.o: ../../ccNOos/computeModule/compute_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/906818983" 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/computeModule/compute_module.c  -o ${OBJECTDIR}/_ext/906818983/compute_module.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/906818983/compute_module.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/906818983/compute_module.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1423417940/console_menu.o: ../../ccNOos/consoleMenu/console_menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1423417940" 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/consoleMenu/console_menu.c  -o ${OBJECTDIR}/_ext/1423417940/console_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1423417940/console_menu.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1423417940/console_menu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324609859/execution_system.o: ../../ccNOos/executionSystem/execution_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1324609859" 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/executionSystem/execution_system.c  -o ${OBJECTDIR}/_ext/1324609859/execution_system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324609859/execution_system.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324609859/execution_system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1921990522/io_device.o: ../../ccNOos/ioDevice/io_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1921990522" 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/ioDevice/io_device.c  -o ${OBJECTDIR}/_ext/1921990522/io_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1921990522/io_device.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1921990522/io_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o: ../../ccNOos/tests/ccNOos_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1571702537" 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/tests/ccNOos_tests.c  -o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsPIC33F_Tests.o: dsPIC33F_Tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsPIC33F_Tests.o.d 
	@${RM} ${OBJECTDIR}/dsPIC33F_Tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsPIC33F_Tests.c  -o ${OBJECTDIR}/dsPIC33F_Tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsPIC33F_Tests.o.d"      -g -D__DEBUG     -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/dsPIC33F_Tests.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/906818983/compute_module.o: ../../ccNOos/computeModule/compute_module.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/906818983" 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o.d 
	@${RM} ${OBJECTDIR}/_ext/906818983/compute_module.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/computeModule/compute_module.c  -o ${OBJECTDIR}/_ext/906818983/compute_module.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/906818983/compute_module.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/906818983/compute_module.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1423417940/console_menu.o: ../../ccNOos/consoleMenu/console_menu.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1423417940" 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o.d 
	@${RM} ${OBJECTDIR}/_ext/1423417940/console_menu.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/consoleMenu/console_menu.c  -o ${OBJECTDIR}/_ext/1423417940/console_menu.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1423417940/console_menu.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1423417940/console_menu.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1324609859/execution_system.o: ../../ccNOos/executionSystem/execution_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1324609859" 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1324609859/execution_system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/executionSystem/execution_system.c  -o ${OBJECTDIR}/_ext/1324609859/execution_system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1324609859/execution_system.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1324609859/execution_system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1921990522/io_device.o: ../../ccNOos/ioDevice/io_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1921990522" 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1921990522/io_device.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/ioDevice/io_device.c  -o ${OBJECTDIR}/_ext/1921990522/io_device.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1921990522/io_device.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1921990522/io_device.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o: ../../ccNOos/tests/ccNOos_tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1571702537" 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d 
	@${RM} ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../ccNOos/tests/ccNOos_tests.c  -o ${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/_ext/1571702537/ccNOos_tests.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dsPIC33F_Tests.o: dsPIC33F_Tests.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dsPIC33F_Tests.o.d 
	@${RM} ${OBJECTDIR}/dsPIC33F_Tests.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dsPIC33F_Tests.c  -o ${OBJECTDIR}/dsPIC33F_Tests.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dsPIC33F_Tests.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	@${FIXDEPS} "${OBJECTDIR}/dsPIC33F_Tests.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG   -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dsPIC33F_Tests.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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
