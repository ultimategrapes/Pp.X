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
FINAL_IMAGE=${DISTDIR}/Pp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Pp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/ES_CheckEvents.c ../ECE118/src/ES_Framework.c ../ECE118/src/ES_KeyboardInput.c ../ECE118/src/ES_PostList.c ../ECE118/src/ES_Queue.c ../ECE118/src/ES_TattleTale.c ../ECE118/src/ES_Timers.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/RC_Servo.c ../ECE118/src/pwm.c ../ECE118/src/roach.c ../ECE118/src/serial.c ../ECE118/src/timers.c TemplateService.c ES_Main.c AllEventChecker.c MainHSM.c peashooter.c AlignTapeSubHSM.c AvoidSubHSM.c RideFrontSubHSM.c RideLeftSubHSM.c RideRightSubHSM.c ShootSubHSM.c TraverseFieldSubHSM.c FindBeaconSubHSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/RC_Servo.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/roach.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TemplateService.o ${OBJECTDIR}/ES_Main.o ${OBJECTDIR}/AllEventChecker.o ${OBJECTDIR}/MainHSM.o ${OBJECTDIR}/peashooter.o ${OBJECTDIR}/AlignTapeSubHSM.o ${OBJECTDIR}/AvoidSubHSM.o ${OBJECTDIR}/RideFrontSubHSM.o ${OBJECTDIR}/RideLeftSubHSM.o ${OBJECTDIR}/RideRightSubHSM.o ${OBJECTDIR}/ShootSubHSM.o ${OBJECTDIR}/TraverseFieldSubHSM.o ${OBJECTDIR}/FindBeaconSubHSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1347132459/AD.o.d ${OBJECTDIR}/_ext/1347132459/BOARD.o.d ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d ${OBJECTDIR}/_ext/1347132459/LED.o.d ${OBJECTDIR}/_ext/1347132459/RC_Servo.o.d ${OBJECTDIR}/_ext/1347132459/pwm.o.d ${OBJECTDIR}/_ext/1347132459/roach.o.d ${OBJECTDIR}/_ext/1347132459/serial.o.d ${OBJECTDIR}/_ext/1347132459/timers.o.d ${OBJECTDIR}/TemplateService.o.d ${OBJECTDIR}/ES_Main.o.d ${OBJECTDIR}/AllEventChecker.o.d ${OBJECTDIR}/MainHSM.o.d ${OBJECTDIR}/peashooter.o.d ${OBJECTDIR}/AlignTapeSubHSM.o.d ${OBJECTDIR}/AvoidSubHSM.o.d ${OBJECTDIR}/RideFrontSubHSM.o.d ${OBJECTDIR}/RideLeftSubHSM.o.d ${OBJECTDIR}/RideRightSubHSM.o.d ${OBJECTDIR}/ShootSubHSM.o.d ${OBJECTDIR}/TraverseFieldSubHSM.o.d ${OBJECTDIR}/FindBeaconSubHSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1347132459/AD.o ${OBJECTDIR}/_ext/1347132459/BOARD.o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ${OBJECTDIR}/_ext/1347132459/LED.o ${OBJECTDIR}/_ext/1347132459/RC_Servo.o ${OBJECTDIR}/_ext/1347132459/pwm.o ${OBJECTDIR}/_ext/1347132459/roach.o ${OBJECTDIR}/_ext/1347132459/serial.o ${OBJECTDIR}/_ext/1347132459/timers.o ${OBJECTDIR}/TemplateService.o ${OBJECTDIR}/ES_Main.o ${OBJECTDIR}/AllEventChecker.o ${OBJECTDIR}/MainHSM.o ${OBJECTDIR}/peashooter.o ${OBJECTDIR}/AlignTapeSubHSM.o ${OBJECTDIR}/AvoidSubHSM.o ${OBJECTDIR}/RideFrontSubHSM.o ${OBJECTDIR}/RideLeftSubHSM.o ${OBJECTDIR}/RideRightSubHSM.o ${OBJECTDIR}/ShootSubHSM.o ${OBJECTDIR}/TraverseFieldSubHSM.o ${OBJECTDIR}/FindBeaconSubHSM.o

# Source Files
SOURCEFILES=../ECE118/src/AD.c ../ECE118/src/BOARD.c ../ECE118/src/ES_CheckEvents.c ../ECE118/src/ES_Framework.c ../ECE118/src/ES_KeyboardInput.c ../ECE118/src/ES_PostList.c ../ECE118/src/ES_Queue.c ../ECE118/src/ES_TattleTale.c ../ECE118/src/ES_Timers.c ../ECE118/src/IO_Ports.c ../ECE118/src/LED.c ../ECE118/src/RC_Servo.c ../ECE118/src/pwm.c ../ECE118/src/roach.c ../ECE118/src/serial.c ../ECE118/src/timers.c TemplateService.c ES_Main.c AllEventChecker.c MainHSM.c peashooter.c AlignTapeSubHSM.c AvoidSubHSM.c RideFrontSubHSM.c RideLeftSubHSM.c RideRightSubHSM.c ShootSubHSM.c TraverseFieldSubHSM.c FindBeaconSubHSM.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Pp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="..\ECE118\bootloader320.ld"
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
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/658ea85f4af3cbe01c2c2a40b130da14f52e723c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/331b05e9f9e81d64983bed8d4bc3117fd77e3b0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o: ../ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/f62efe72364acd44d7123ea2f3bcebfa91b97c49 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ../ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_Framework.o: ../ECE118/src/ES_Framework.c  .generated_files/flags/default/44c52cc9803164c9f20ebdc9ddba6bff0fe5a300 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ../ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o: ../ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/da7494788cd1a5eb6666469bba707912c6131840 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ../ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_PostList.o: ../ECE118/src/ES_PostList.c  .generated_files/flags/default/48fa617d85216c747e0d937c1dcd4cb4ac06daab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ../ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_Queue.o: ../ECE118/src/ES_Queue.c  .generated_files/flags/default/3368c0b5a780076c20c719b8a299232443bb2494 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ../ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o: ../ECE118/src/ES_TattleTale.c  .generated_files/flags/default/6e94bd35cf5c469b95678ff21aab8f26fbb88356 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ../ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_Timers.o: ../ECE118/src/ES_Timers.c  .generated_files/flags/default/415a7ed05e11cf654a5f3fc1b1cd9291038dbf7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ../ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/4b2e044a8cca9e5bbe726b468a269fb2213495ff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/9d9cc8f20b644d85b016588f1cb7e2bea895bb8b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/RC_Servo.o: ../ECE118/src/RC_Servo.c  .generated_files/flags/default/cdb0ec5547ac2f3a7431a23b8f75662de7971be7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1347132459/RC_Servo.o ../ECE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/728e9ba05f2b2ffcd4dd7ff0dade6c5121051d7e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/roach.o: ../ECE118/src/roach.c  .generated_files/flags/default/2e1eae1fe1edee40cd52a390ce546495b8b27623 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/roach.o.d" -o ${OBJECTDIR}/_ext/1347132459/roach.o ../ECE118/src/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/e7b7217d01d014bc83cb46540f1356f37d54309c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/bea8fe86f45129df3f2e974f4ee3fba9004c6830 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/TemplateService.o: TemplateService.c  .generated_files/flags/default/d6950782dd1e90ebd55289391f06e8d98b347bdb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/TemplateService.o.d" -o ${OBJECTDIR}/TemplateService.o TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ES_Main.o: ES_Main.c  .generated_files/flags/default/2ca91016fddd3681a9b78e6ded19e0f7bc31a32a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/ES_Main.o.d" -o ${OBJECTDIR}/ES_Main.o ES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/AllEventChecker.o: AllEventChecker.c  .generated_files/flags/default/df5989ea63d213706b76107ceecc9375d9b599c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AllEventChecker.o.d 
	@${RM} ${OBJECTDIR}/AllEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/AllEventChecker.o.d" -o ${OBJECTDIR}/AllEventChecker.o AllEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/MainHSM.o: MainHSM.c  .generated_files/flags/default/bcd5fedee15fe0aac6e6fe29f9bfa6b1420af61b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MainHSM.o.d 
	@${RM} ${OBJECTDIR}/MainHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/MainHSM.o.d" -o ${OBJECTDIR}/MainHSM.o MainHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/peashooter.o: peashooter.c  .generated_files/flags/default/71058c93a99ff61ee65a6aba44ffecd4c1fe0b2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/peashooter.o.d 
	@${RM} ${OBJECTDIR}/peashooter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/peashooter.o.d" -o ${OBJECTDIR}/peashooter.o peashooter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/AlignTapeSubHSM.o: AlignTapeSubHSM.c  .generated_files/flags/default/e082a064b72a95b632560707dd629cd7365ed7f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AlignTapeSubHSM.o.d 
	@${RM} ${OBJECTDIR}/AlignTapeSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/AlignTapeSubHSM.o.d" -o ${OBJECTDIR}/AlignTapeSubHSM.o AlignTapeSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/AvoidSubHSM.o: AvoidSubHSM.c  .generated_files/flags/default/f4178b7fc571641c0bc940b27d9451423c4861c1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AvoidSubHSM.o.d 
	@${RM} ${OBJECTDIR}/AvoidSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/AvoidSubHSM.o.d" -o ${OBJECTDIR}/AvoidSubHSM.o AvoidSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/RideFrontSubHSM.o: RideFrontSubHSM.c  .generated_files/flags/default/ce34b098e8d098da7c71db15ed7248d466b58baa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RideFrontSubHSM.o.d 
	@${RM} ${OBJECTDIR}/RideFrontSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/RideFrontSubHSM.o.d" -o ${OBJECTDIR}/RideFrontSubHSM.o RideFrontSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/RideLeftSubHSM.o: RideLeftSubHSM.c  .generated_files/flags/default/f502fb324f46d8e7d49c5a8cb6763437ce0092f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RideLeftSubHSM.o.d 
	@${RM} ${OBJECTDIR}/RideLeftSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/RideLeftSubHSM.o.d" -o ${OBJECTDIR}/RideLeftSubHSM.o RideLeftSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/RideRightSubHSM.o: RideRightSubHSM.c  .generated_files/flags/default/8c341d45b322f0fdd84e4224113180651e45e393 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RideRightSubHSM.o.d 
	@${RM} ${OBJECTDIR}/RideRightSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/RideRightSubHSM.o.d" -o ${OBJECTDIR}/RideRightSubHSM.o RideRightSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ShootSubHSM.o: ShootSubHSM.c  .generated_files/flags/default/c88e80b0acc950f999581fa7d1afda58232e490c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ShootSubHSM.o.d 
	@${RM} ${OBJECTDIR}/ShootSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/ShootSubHSM.o.d" -o ${OBJECTDIR}/ShootSubHSM.o ShootSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/TraverseFieldSubHSM.o: TraverseFieldSubHSM.c  .generated_files/flags/default/945abb5400ecc18c8100139f941c6ecdbd9db5a8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TraverseFieldSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TraverseFieldSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/TraverseFieldSubHSM.o.d" -o ${OBJECTDIR}/TraverseFieldSubHSM.o TraverseFieldSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FindBeaconSubHSM.o: FindBeaconSubHSM.c  .generated_files/flags/default/b1de875aa0c6862c6c44694e7e8b19cd9156afb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FindBeaconSubHSM.o.d 
	@${RM} ${OBJECTDIR}/FindBeaconSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/FindBeaconSubHSM.o.d" -o ${OBJECTDIR}/FindBeaconSubHSM.o FindBeaconSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
else
${OBJECTDIR}/_ext/1347132459/AD.o: ../ECE118/src/AD.c  .generated_files/flags/default/d44bdd242365773b048d1529d44f415e556c28e5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/AD.o.d" -o ${OBJECTDIR}/_ext/1347132459/AD.o ../ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/BOARD.o: ../ECE118/src/BOARD.c  .generated_files/flags/default/83c1cad91064046857388223ca322d3bca4a7d30 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/BOARD.o.d" -o ${OBJECTDIR}/_ext/1347132459/BOARD.o ../ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o: ../ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/a5a3c9bbd48755ceed61705e63b8853b7a2aa029 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_CheckEvents.o ../ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_Framework.o: ../ECE118/src/ES_Framework.c  .generated_files/flags/default/bb07ceac6ed74de55cd47f9b977cbd3f477bc78 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Framework.o ../ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o: ../ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/6f8c9a351732ed63b22443e29d1670818947061e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_KeyboardInput.o ../ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_PostList.o: ../ECE118/src/ES_PostList.c  .generated_files/flags/default/68e01ccf1e2f85e41dc7a86a78f454c1430c4adb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_PostList.o ../ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_Queue.o: ../ECE118/src/ES_Queue.c  .generated_files/flags/default/b299e3a94b08c2e821682fa985f55bf900a6e6e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Queue.o ../ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o: ../ECE118/src/ES_TattleTale.c  .generated_files/flags/default/b82378e8f4432a26ae2c36111c3c94d1178e9ab4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_TattleTale.o ../ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/ES_Timers.o: ../ECE118/src/ES_Timers.c  .generated_files/flags/default/4ddf157401091366b348ae724f2798d83377810d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/ES_Timers.o ../ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/IO_Ports.o: ../ECE118/src/IO_Ports.c  .generated_files/flags/default/1a4f866923d7b2701c3eab8edf1edb2647a100ab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1347132459/IO_Ports.o ../ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/LED.o: ../ECE118/src/LED.c  .generated_files/flags/default/7374588c074b67e2c8b1f02691fca9b5276d17c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/LED.o.d" -o ${OBJECTDIR}/_ext/1347132459/LED.o ../ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/RC_Servo.o: ../ECE118/src/RC_Servo.c  .generated_files/flags/default/6fbe8aad58485664cc78c394d680ccbd098f1647 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1347132459/RC_Servo.o ../ECE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/pwm.o: ../ECE118/src/pwm.c  .generated_files/flags/default/35d969c777ff1cc2153e7b65f443157c7c78c02e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/pwm.o.d" -o ${OBJECTDIR}/_ext/1347132459/pwm.o ../ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/roach.o: ../ECE118/src/roach.c  .generated_files/flags/default/b6c9c1a66eb35739c72a086b88ad1cbd0516bdf1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/roach.o.d" -o ${OBJECTDIR}/_ext/1347132459/roach.o ../ECE118/src/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/serial.o: ../ECE118/src/serial.c  .generated_files/flags/default/882627cd27496a408b80cc74315dcf1af549a848 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/serial.o.d" -o ${OBJECTDIR}/_ext/1347132459/serial.o ../ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/_ext/1347132459/timers.o: ../ECE118/src/timers.c  .generated_files/flags/default/c55be58243993cadc4c8af00007a724688ec8eaa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1347132459" 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1347132459/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/_ext/1347132459/timers.o.d" -o ${OBJECTDIR}/_ext/1347132459/timers.o ../ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/TemplateService.o: TemplateService.c  .generated_files/flags/default/f7cf0bf13ed42826574a9ea392008929a3b329df .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/TemplateService.o.d" -o ${OBJECTDIR}/TemplateService.o TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ES_Main.o: ES_Main.c  .generated_files/flags/default/807daf1e52a8ef3903660e0c009f8e87243661e5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ES_Main.o.d 
	@${RM} ${OBJECTDIR}/ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/ES_Main.o.d" -o ${OBJECTDIR}/ES_Main.o ES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/AllEventChecker.o: AllEventChecker.c  .generated_files/flags/default/108d360c008807aa430d0c87dd995f4c05d89976 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AllEventChecker.o.d 
	@${RM} ${OBJECTDIR}/AllEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/AllEventChecker.o.d" -o ${OBJECTDIR}/AllEventChecker.o AllEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/MainHSM.o: MainHSM.c  .generated_files/flags/default/baebe4b431cce02725541990358a55788c1ae042 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/MainHSM.o.d 
	@${RM} ${OBJECTDIR}/MainHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/MainHSM.o.d" -o ${OBJECTDIR}/MainHSM.o MainHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/peashooter.o: peashooter.c  .generated_files/flags/default/b83e3871bfab6390df06dee1498189d2a1de8350 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/peashooter.o.d 
	@${RM} ${OBJECTDIR}/peashooter.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/peashooter.o.d" -o ${OBJECTDIR}/peashooter.o peashooter.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/AlignTapeSubHSM.o: AlignTapeSubHSM.c  .generated_files/flags/default/61d907f1b2572bb0e0f2b0b55f5ff48a2c82582a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AlignTapeSubHSM.o.d 
	@${RM} ${OBJECTDIR}/AlignTapeSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/AlignTapeSubHSM.o.d" -o ${OBJECTDIR}/AlignTapeSubHSM.o AlignTapeSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/AvoidSubHSM.o: AvoidSubHSM.c  .generated_files/flags/default/29c0c278441e121b17e5ca604a2705dcdb556c30 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/AvoidSubHSM.o.d 
	@${RM} ${OBJECTDIR}/AvoidSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/AvoidSubHSM.o.d" -o ${OBJECTDIR}/AvoidSubHSM.o AvoidSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/RideFrontSubHSM.o: RideFrontSubHSM.c  .generated_files/flags/default/96fe7141470f35ee52cf3f970657126f3872f218 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RideFrontSubHSM.o.d 
	@${RM} ${OBJECTDIR}/RideFrontSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/RideFrontSubHSM.o.d" -o ${OBJECTDIR}/RideFrontSubHSM.o RideFrontSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/RideLeftSubHSM.o: RideLeftSubHSM.c  .generated_files/flags/default/478200c59fed35b434266d23cf2328da405a65bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RideLeftSubHSM.o.d 
	@${RM} ${OBJECTDIR}/RideLeftSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/RideLeftSubHSM.o.d" -o ${OBJECTDIR}/RideLeftSubHSM.o RideLeftSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/RideRightSubHSM.o: RideRightSubHSM.c  .generated_files/flags/default/31383f0a7ed6e46ea4e7bdbe9e6bbbddbe4e0279 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/RideRightSubHSM.o.d 
	@${RM} ${OBJECTDIR}/RideRightSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/RideRightSubHSM.o.d" -o ${OBJECTDIR}/RideRightSubHSM.o RideRightSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/ShootSubHSM.o: ShootSubHSM.c  .generated_files/flags/default/db1e6d1b0e572629d1ad6da9716bfa64a0dacce0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ShootSubHSM.o.d 
	@${RM} ${OBJECTDIR}/ShootSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/ShootSubHSM.o.d" -o ${OBJECTDIR}/ShootSubHSM.o ShootSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/TraverseFieldSubHSM.o: TraverseFieldSubHSM.c  .generated_files/flags/default/3d10dacf86db12beaa3c21297f7b860db5c73673 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TraverseFieldSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TraverseFieldSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/TraverseFieldSubHSM.o.d" -o ${OBJECTDIR}/TraverseFieldSubHSM.o TraverseFieldSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
${OBJECTDIR}/FindBeaconSubHSM.o: FindBeaconSubHSM.c  .generated_files/flags/default/66b8939d91c67ef630a53ff5e13dc2cef2db50b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FindBeaconSubHSM.o.d 
	@${RM} ${OBJECTDIR}/FindBeaconSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DRUN_HSM -I"C:/Users/asus/Documents/ece118/Pp.X" -I"../ECE118/include" -I"../ECE118/src" -MP -MMD -MF "${OBJECTDIR}/FindBeaconSubHSM.o.d" -o ${OBJECTDIR}/FindBeaconSubHSM.o FindBeaconSubHSM.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)    
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Pp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../ECE118/bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_SIMULATOR=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Pp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	
else
${DISTDIR}/Pp.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../ECE118/bootloader320.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Pp.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml 
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Pp.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
