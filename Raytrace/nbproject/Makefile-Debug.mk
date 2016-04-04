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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/b7aea6c5/BoundingBox.o \
	${OBJECTDIR}/_ext/b7aea6c5/Light.o \
	${OBJECTDIR}/_ext/b7aea6c5/MeshObject.o \
	${OBJECTDIR}/_ext/b7aea6c5/OBJParser.o \
	${OBJECTDIR}/_ext/b7aea6c5/Ray.o \
	${OBJECTDIR}/_ext/b7aea6c5/RayTracer.o \
	${OBJECTDIR}/_ext/b7aea6c5/bmp_io.o \
	${OBJECTDIR}/_ext/b7aea6c5/main.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytrace

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytrace: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytrace ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/b7aea6c5/BoundingBox.o: ../util/Basic/src/BoundingBox.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/BoundingBox.o ../util/Basic/src/BoundingBox.cpp

${OBJECTDIR}/_ext/b7aea6c5/Light.o: ../util/Basic/src/Light.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/Light.o ../util/Basic/src/Light.cpp

${OBJECTDIR}/_ext/b7aea6c5/MeshObject.o: ../util/Basic/src/MeshObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/MeshObject.o ../util/Basic/src/MeshObject.cpp

${OBJECTDIR}/_ext/b7aea6c5/OBJParser.o: ../util/Basic/src/OBJParser.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/OBJParser.o ../util/Basic/src/OBJParser.cpp

${OBJECTDIR}/_ext/b7aea6c5/Ray.o: ../util/Basic/src/Ray.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/Ray.o ../util/Basic/src/Ray.cpp

${OBJECTDIR}/_ext/b7aea6c5/RayTracer.o: ../util/Basic/src/RayTracer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/RayTracer.o ../util/Basic/src/RayTracer.cpp

${OBJECTDIR}/_ext/b7aea6c5/bmp_io.o: ../util/Basic/src/bmp_io.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/bmp_io.o ../util/Basic/src/bmp_io.cpp

${OBJECTDIR}/_ext/b7aea6c5/main.o: ../util/Basic/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/b7aea6c5
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b7aea6c5/main.o ../util/Basic/src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/raytrace

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
