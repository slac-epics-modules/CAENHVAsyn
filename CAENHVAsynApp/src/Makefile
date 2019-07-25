TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

# CAENHVAsyn.dbd will be created from CAENHVAsynInclude.dbd and installed
DBD += CAENHVAsyn.dbd

INC += drvCAENHVAsyn.h

LIBRARY_IOC += CAENHVAsyn
LIB_SRCS += drvCAENHVAsyn.cpp
LIB_LIBS += asyn

#=====================================================
# Path to "NON EPICS" External PACKAGES: USER INCLUDES
#======================================================
USR_INCLUDES = $(addprefix -I,$(CAENHVWRAPPER_INCLUDE))
caenhvwrapper_DIR = $(CAENHVWRAPPER_LIB)
USR_LIBS_Linux += caenhvwrapper
#======================================================

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

