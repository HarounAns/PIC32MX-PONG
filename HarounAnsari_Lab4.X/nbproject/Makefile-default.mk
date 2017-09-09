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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="../STEP 7/ChrFont0.c" "../STEP 7/FillPat.c" "../STEP 7/OledChar.c" "../STEP 7/OledGrph.c" "../STEP 7/PmodOLED.c" "../STEP 7/delay.c" "../STEP 7/main.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1754701038/ChrFont0.o ${OBJECTDIR}/_ext/1754701038/FillPat.o ${OBJECTDIR}/_ext/1754701038/OledChar.o ${OBJECTDIR}/_ext/1754701038/OledGrph.o ${OBJECTDIR}/_ext/1754701038/PmodOLED.o ${OBJECTDIR}/_ext/1754701038/delay.o ${OBJECTDIR}/_ext/1754701038/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1754701038/ChrFont0.o.d ${OBJECTDIR}/_ext/1754701038/FillPat.o.d ${OBJECTDIR}/_ext/1754701038/OledChar.o.d ${OBJECTDIR}/_ext/1754701038/OledGrph.o.d ${OBJECTDIR}/_ext/1754701038/PmodOLED.o.d ${OBJECTDIR}/_ext/1754701038/delay.o.d ${OBJECTDIR}/_ext/1754701038/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1754701038/ChrFont0.o ${OBJECTDIR}/_ext/1754701038/FillPat.o ${OBJECTDIR}/_ext/1754701038/OledChar.o ${OBJECTDIR}/_ext/1754701038/OledGrph.o ${OBJECTDIR}/_ext/1754701038/PmodOLED.o ${OBJECTDIR}/_ext/1754701038/delay.o ${OBJECTDIR}/_ext/1754701038/main.o

# Source Files
SOURCEFILES=../STEP 7/ChrFont0.c ../STEP 7/FillPat.c ../STEP 7/OledChar.c ../STEP 7/OledGrph.c ../STEP 7/PmodOLED.c ../STEP 7/delay.c ../STEP 7/main.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
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
${OBJECTDIR}/_ext/1754701038/ChrFont0.o: ../STEP\ 7/ChrFont0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/ChrFont0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/ChrFont0.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/ChrFont0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/ChrFont0.o.d" -o ${OBJECTDIR}/_ext/1754701038/ChrFont0.o "../STEP 7/ChrFont0.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/FillPat.o: ../STEP\ 7/FillPat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/FillPat.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/FillPat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/FillPat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/FillPat.o.d" -o ${OBJECTDIR}/_ext/1754701038/FillPat.o "../STEP 7/FillPat.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/OledChar.o: ../STEP\ 7/OledChar.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledChar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledChar.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/OledChar.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/OledChar.o.d" -o ${OBJECTDIR}/_ext/1754701038/OledChar.o "../STEP 7/OledChar.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/OledGrph.o: ../STEP\ 7/OledGrph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledGrph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledGrph.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/OledGrph.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/OledGrph.o.d" -o ${OBJECTDIR}/_ext/1754701038/OledGrph.o "../STEP 7/OledGrph.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/PmodOLED.o: ../STEP\ 7/PmodOLED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/PmodOLED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/PmodOLED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/PmodOLED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/PmodOLED.o.d" -o ${OBJECTDIR}/_ext/1754701038/PmodOLED.o "../STEP 7/PmodOLED.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/delay.o: ../STEP\ 7/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/delay.o.d" -o ${OBJECTDIR}/_ext/1754701038/delay.o "../STEP 7/delay.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/main.o: ../STEP\ 7/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/main.o.d" -o ${OBJECTDIR}/_ext/1754701038/main.o "../STEP 7/main.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/1754701038/ChrFont0.o: ../STEP\ 7/ChrFont0.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/ChrFont0.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/ChrFont0.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/ChrFont0.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/ChrFont0.o.d" -o ${OBJECTDIR}/_ext/1754701038/ChrFont0.o "../STEP 7/ChrFont0.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/FillPat.o: ../STEP\ 7/FillPat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/FillPat.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/FillPat.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/FillPat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/FillPat.o.d" -o ${OBJECTDIR}/_ext/1754701038/FillPat.o "../STEP 7/FillPat.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/OledChar.o: ../STEP\ 7/OledChar.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledChar.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledChar.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/OledChar.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/OledChar.o.d" -o ${OBJECTDIR}/_ext/1754701038/OledChar.o "../STEP 7/OledChar.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/OledGrph.o: ../STEP\ 7/OledGrph.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledGrph.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/OledGrph.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/OledGrph.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/OledGrph.o.d" -o ${OBJECTDIR}/_ext/1754701038/OledGrph.o "../STEP 7/OledGrph.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/PmodOLED.o: ../STEP\ 7/PmodOLED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/PmodOLED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/PmodOLED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/PmodOLED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/PmodOLED.o.d" -o ${OBJECTDIR}/_ext/1754701038/PmodOLED.o "../STEP 7/PmodOLED.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/delay.o: ../STEP\ 7/delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/delay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/delay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/delay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/delay.o.d" -o ${OBJECTDIR}/_ext/1754701038/delay.o "../STEP 7/delay.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1754701038/main.o: ../STEP\ 7/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1754701038" 
	@${RM} ${OBJECTDIR}/_ext/1754701038/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1754701038/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1754701038/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1754701038/main.o.d" -o ${OBJECTDIR}/_ext/1754701038/main.o "../STEP 7/main.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)    -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/HarounAnsari_Lab4.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
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
