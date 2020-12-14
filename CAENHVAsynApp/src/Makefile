TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

USR_CXXFLAGS_Linux += -std=c++0x

# CAENHVAsyn.dbd will be created from CAENHVAsynInclude.dbd and installed
DBD += CAENHVAsyn.dbd

INC += drvCAENHVAsyn.h

LIBRARY_IOC += CAENHVAsyn
CAENHVAsyn_SRCS += drvCAENHVAsyn.cpp
CAENHVAsyn_SRCS += common.cpp
CAENHVAsyn_SRCS += crate.cpp
CAENHVAsyn_SRCS += system_property.cpp
CAENHVAsyn_SRCS += board.cpp
CAENHVAsyn_SRCS += board_parameter.cpp
CAENHVAsyn_SRCS += channel.cpp
CAENHVAsyn_SRCS += channel_parameter.cpp
CAENHVAsyn_LIBS += asyn
CAENHVAsyn_LIBS_WIN32 += $(EPICS_BASE_IOC_LIBS)
CAENHVAsyn_SYS_LIBS_WIN32 += ws2_32

## this library can be used to replace caenhvwrapper shared library
## to enable simulation
LIBRARY_IOC += CAENHVWrapperSim
CAENHVWrapperSim_SRCS += CAENHVWrapper_sim.cpp
CAENHVWrapperSim_LIBS += $(EPICS_BASE_IOC_LIBS)
CAENHVWrapperSim_SYS_LIBS_WIN32 += ws2_32

#=====================================================
# Path to "NON EPICS" External PACKAGES: USER INCLUDES
#======================================================

USR_INCLUDES = $(addprefix -I,$(CAENHVWRAPPER_INCLUDE))
caenhvwrapper_DIR = $(CAENHVWRAPPER_LIB)
CAENHVAsyn_LIBS_Linux += caenhvwrapper
CAENHVAsyn_LIBS_WIN32 += caenhvwrapper

BIN_INSTALLS_WIN32 += $(wildcard $(CAENHVWRAPPER_DLL)/*.dll)
LIB_INSTALLS_WIN32 += $(wildcard $(CAENHVWRAPPER_LIB)/*.lib)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

