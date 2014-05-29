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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Btree/BTree.o \
	${OBJECTDIR}/data/data.o \
	${OBJECTDIR}/data/file/file_manager.o \
	${OBJECTDIR}/data/partida/partida.o \
	${OBJECTDIR}/data/partida/random/random_partida.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/utils/utils.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pra_new

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pra_new: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pra_new ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Btree/BTree.o: Btree/BTree.c 
	${MKDIR} -p ${OBJECTDIR}/Btree
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Btree/BTree.o Btree/BTree.c

${OBJECTDIR}/data/data.o: data/data.c 
	${MKDIR} -p ${OBJECTDIR}/data
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/data.o data/data.c

${OBJECTDIR}/data/file/file_manager.o: data/file/file_manager.c 
	${MKDIR} -p ${OBJECTDIR}/data/file
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/file/file_manager.o data/file/file_manager.c

${OBJECTDIR}/data/partida/partida.o: data/partida/partida.c 
	${MKDIR} -p ${OBJECTDIR}/data/partida
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/partida/partida.o data/partida/partida.c

${OBJECTDIR}/data/partida/random/random_partida.o: data/partida/random/random_partida.c 
	${MKDIR} -p ${OBJECTDIR}/data/partida/random
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/data/partida/random/random_partida.o data/partida/random/random_partida.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/utils/utils.o: utils/utils.c 
	${MKDIR} -p ${OBJECTDIR}/utils
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/utils/utils.o utils/utils.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/pra_new

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
