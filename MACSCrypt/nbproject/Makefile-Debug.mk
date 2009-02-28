#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=

# Macros
PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/MACSCrypt.o \
	${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/des.o \
	${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/des3.o \
	${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/Stdafx.o \
	${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/aes.o \
	${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/AssemblyInfo.o \
	${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/aes3.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/${PLATFORM}/macscrypt

dist/Debug/${PLATFORM}/macscrypt: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/${PLATFORM}
	${LINK.cc} -o dist/Debug/${PLATFORM}/macscrypt ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/MACSCrypt.o: ../../Desktop/Complete\ MACSCrypt/MACSCrypt/MACSCrypt.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/MACSCrypt.o ../../Desktop/Complete\ MACSCrypt/MACSCrypt/MACSCrypt.cpp

${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/des.o: ../../Desktop/Complete\ MACSCrypt/MACSCrypt/des.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/des.o ../../Desktop/Complete\ MACSCrypt/MACSCrypt/des.cpp

${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/des3.o: ../../Desktop/Complete\ MACSCrypt/MACSCrypt/des3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/des3.o ../../Desktop/Complete\ MACSCrypt/MACSCrypt/des3.cpp

${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/Stdafx.o: ../../Desktop/Complete\ MACSCrypt/MACSCrypt/Stdafx.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/Stdafx.o ../../Desktop/Complete\ MACSCrypt/MACSCrypt/Stdafx.cpp

${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/aes.o: ../../Desktop/Complete\ MACSCrypt/MACSCrypt/aes.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/aes.o ../../Desktop/Complete\ MACSCrypt/MACSCrypt/aes.cpp

${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/AssemblyInfo.o: ../../Desktop/Complete\ MACSCrypt/MACSCrypt/AssemblyInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/AssemblyInfo.o ../../Desktop/Complete\ MACSCrypt/MACSCrypt/AssemblyInfo.cpp

${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/aes3.o: ../../Desktop/Complete\ MACSCrypt/MACSCrypt/aes3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/home/Amahdy/NetBeansProjects/MACSCrypt/../../Desktop/Complete_MACSCrypt/MACSCrypt/aes3.o ../../Desktop/Complete\ MACSCrypt/MACSCrypt/aes3.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/${PLATFORM}/macscrypt

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
