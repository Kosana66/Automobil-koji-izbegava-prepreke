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
FINAL_IMAGE=${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=newmain.c adc_module/adc.c timer_module/timer.c uart_module/uart.c pwm_module/pwm.c digital_sensors/HCSR.c motor_module/motor.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/newmain.o ${OBJECTDIR}/adc_module/adc.o ${OBJECTDIR}/timer_module/timer.o ${OBJECTDIR}/uart_module/uart.o ${OBJECTDIR}/pwm_module/pwm.o ${OBJECTDIR}/digital_sensors/HCSR.o ${OBJECTDIR}/motor_module/motor.o
POSSIBLE_DEPFILES=${OBJECTDIR}/newmain.o.d ${OBJECTDIR}/adc_module/adc.o.d ${OBJECTDIR}/timer_module/timer.o.d ${OBJECTDIR}/uart_module/uart.o.d ${OBJECTDIR}/pwm_module/pwm.o.d ${OBJECTDIR}/digital_sensors/HCSR.o.d ${OBJECTDIR}/motor_module/motor.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/newmain.o ${OBJECTDIR}/adc_module/adc.o ${OBJECTDIR}/timer_module/timer.o ${OBJECTDIR}/uart_module/uart.o ${OBJECTDIR}/pwm_module/pwm.o ${OBJECTDIR}/digital_sensors/HCSR.o ${OBJECTDIR}/motor_module/motor.o

# Source Files
SOURCEFILES=newmain.c adc_module/adc.c timer_module/timer.c uart_module/uart.c pwm_module/pwm.c digital_sensors/HCSR.c motor_module/motor.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=30F4013
MP_LINKER_FILE_OPTION=,--script=p30F4013.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/62ded4558a7ce497feef80e9561e6bd8865caf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  newmain.c  -o ${OBJECTDIR}/newmain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/newmain.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adc_module/adc.o: adc_module/adc.c  .generated_files/flags/default/50909d80f60996147d276766f7dd9f3b591b2358 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adc_module" 
	@${RM} ${OBJECTDIR}/adc_module/adc.o.d 
	@${RM} ${OBJECTDIR}/adc_module/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adc_module/adc.c  -o ${OBJECTDIR}/adc_module/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc_module/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timer_module/timer.o: timer_module/timer.c  .generated_files/flags/default/8bbab60d7742b88e85d4e6b9ec7eba0fa7564662 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/timer_module" 
	@${RM} ${OBJECTDIR}/timer_module/timer.o.d 
	@${RM} ${OBJECTDIR}/timer_module/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer_module/timer.c  -o ${OBJECTDIR}/timer_module/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer_module/timer.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uart_module/uart.o: uart_module/uart.c  .generated_files/flags/default/7acf897c60f2a04d483bb3f9df56fbfc5c90d711 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/uart_module" 
	@${RM} ${OBJECTDIR}/uart_module/uart.o.d 
	@${RM} ${OBJECTDIR}/uart_module/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart_module/uart.c  -o ${OBJECTDIR}/uart_module/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uart_module/uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pwm_module/pwm.o: pwm_module/pwm.c  .generated_files/flags/default/5db9eb9250b16c793c8f8143062d11299f61dccb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pwm_module" 
	@${RM} ${OBJECTDIR}/pwm_module/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm_module/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm_module/pwm.c  -o ${OBJECTDIR}/pwm_module/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm_module/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/digital_sensors/HCSR.o: digital_sensors/HCSR.c  .generated_files/flags/default/9592cfefa0db9bfec61b1d8ec8fe39b4e9c3a6d5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/digital_sensors" 
	@${RM} ${OBJECTDIR}/digital_sensors/HCSR.o.d 
	@${RM} ${OBJECTDIR}/digital_sensors/HCSR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  digital_sensors/HCSR.c  -o ${OBJECTDIR}/digital_sensors/HCSR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/digital_sensors/HCSR.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/motor_module/motor.o: motor_module/motor.c  .generated_files/flags/default/f2cdca97ffddb73691b22492a8d23341bdc3855d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/motor_module" 
	@${RM} ${OBJECTDIR}/motor_module/motor.o.d 
	@${RM} ${OBJECTDIR}/motor_module/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_module/motor.c  -o ${OBJECTDIR}/motor_module/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/motor_module/motor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
else
${OBJECTDIR}/newmain.o: newmain.c  .generated_files/flags/default/5ddf4d40cb49c6f7a3ad49073fa706b9aca8f452 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/newmain.o.d 
	@${RM} ${OBJECTDIR}/newmain.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  newmain.c  -o ${OBJECTDIR}/newmain.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/newmain.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/adc_module/adc.o: adc_module/adc.c  .generated_files/flags/default/dc56746cf7e22bfa543a54f7dcb80d7196ec0d3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/adc_module" 
	@${RM} ${OBJECTDIR}/adc_module/adc.o.d 
	@${RM} ${OBJECTDIR}/adc_module/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  adc_module/adc.c  -o ${OBJECTDIR}/adc_module/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/adc_module/adc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/timer_module/timer.o: timer_module/timer.c  .generated_files/flags/default/6d5d4a8670a90d51e3869be5cbd9a31a718a8574 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/timer_module" 
	@${RM} ${OBJECTDIR}/timer_module/timer.o.d 
	@${RM} ${OBJECTDIR}/timer_module/timer.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  timer_module/timer.c  -o ${OBJECTDIR}/timer_module/timer.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/timer_module/timer.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/uart_module/uart.o: uart_module/uart.c  .generated_files/flags/default/e3d11b3f1887c58573f005d28e26a311cbf369a2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/uart_module" 
	@${RM} ${OBJECTDIR}/uart_module/uart.o.d 
	@${RM} ${OBJECTDIR}/uart_module/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  uart_module/uart.c  -o ${OBJECTDIR}/uart_module/uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/uart_module/uart.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/pwm_module/pwm.o: pwm_module/pwm.c  .generated_files/flags/default/cb4e94fb19c06676f276a0d6b24c46bf2c48c9ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/pwm_module" 
	@${RM} ${OBJECTDIR}/pwm_module/pwm.o.d 
	@${RM} ${OBJECTDIR}/pwm_module/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  pwm_module/pwm.c  -o ${OBJECTDIR}/pwm_module/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/pwm_module/pwm.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/digital_sensors/HCSR.o: digital_sensors/HCSR.c  .generated_files/flags/default/b7329f2c85687703abae6a51dc1483ee2c2648f3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/digital_sensors" 
	@${RM} ${OBJECTDIR}/digital_sensors/HCSR.o.d 
	@${RM} ${OBJECTDIR}/digital_sensors/HCSR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  digital_sensors/HCSR.c  -o ${OBJECTDIR}/digital_sensors/HCSR.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/digital_sensors/HCSR.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
${OBJECTDIR}/motor_module/motor.o: motor_module/motor.c  .generated_files/flags/default/a2f26f522b3e1da80282b247400903ab370bf80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/motor_module" 
	@${RM} ${OBJECTDIR}/motor_module/motor.o.d 
	@${RM} ${OBJECTDIR}/motor_module/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  motor_module/motor.c  -o ${OBJECTDIR}/motor_module/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MP -MMD -MF "${OBJECTDIR}/motor_module/motor.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off    -mdfp="${DFP_DIR}/xc16"
	
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
${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	
else
${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o ${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,${DISTDIR}/memoryfile.xml$(MP_EXTRA_LD_POST)  -mdfp="${DFP_DIR}/xc16" 
	${MP_CC_DIR}\\xc16-bin2hex ${DISTDIR}/Firmware.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf   -mdfp="${DFP_DIR}/xc16" 
	
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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
