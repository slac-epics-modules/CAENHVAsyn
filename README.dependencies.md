# CAENHVAsyn Dependencies

This application depends on the following external packages:
- CAEN HV Wrapper Library

and on the following EPICS modules:
- Asyn

In order to use this module you need to add the following definitions into your IOC application:

## configure/CONFIG_SITE

```
CAENHVWRAPPER_PACKAGE_NAME=CAENHVWrapper
CAENHVWRAPPER_VERSION=CAENHVWrapper-5.82
CAENHVWRAPPER_TOP=$(PACKAGE_SITE_TOP)/$(CAENHVWRAPPER_PACKAGE_NAME)/$(CAENHVWRAPPER_VERSION)
CAENHVWRAPPER_LIB=$(CAENHVWRAPPER_TOP)/$(PKG_ARCH)/lib
CAENHVWRAPPER_INCLUDE=$(CAENHVWRAPPER_TOP)/$PKG_ARCH/include
```

## configure/CONFIG_SITE.Common.rhel6-x86_64

```
PKG_ARCH=$(LINUX_VERSION)-x86_64
```

## configure/RELEASE

```
ASYN_MODULE_VERSION=R4.31-0.1.0
CAENHVASYN_MODULE_VERSION=R1.0.0

ASYN=$(EPICS_MODULES)/asyn/$(ASYN_MODULE_VERSION)
CAENHVASYN=$(EPICS_MODULES)/CAENHVAsyn/$(CAENHVASYN_MODULE_VERSION)
```

## xxxApp/src/Makefile

```
# =====================================================
# Path to "NON EPICS" External PACKAGES: USER INCLUDES
# =====================================================
USR_INCLUDES = $(addprefix -I,$(CAENHVWRAPPER_INCLUDE))
# =====================================================

# ======================================================
# PATH TO "NON EPICS" EXTERNAL PACKAGES: USER LIBRARIES
# ======================================================
caenhvwrapper_DIR = $(CAENHVWRAPPER_LIB)
# ======================================================

# ======================================================
# LINK "NON EPICS" EXTERNAL PACKAGE LIBRARIES STATICALLY
# ======================================================
USR_LIBS_Linux += caenhvwrapper
# ======================================================

# Include dbd files from all support applications:
xxx_DBD += base.dbd
xxx_DBD += asyn.dbd
xxx_DBD += CAENHVAsyn.dbd

# =====================================================
# Link in the libraries from other EPICS modules
# =====================================================
xxx_LIBS += CAENHVAsyn
xxx_LIBS += asyn
```

## xxxApp/Db/Makefile

Include these lines if you want to use the auto-generation of PVs.

```
DB_INSTALLS += $(CAENHVASYN)/db/ai.template
DB_INSTALLS += $(CAENHVASYN)/db/ao.template
DB_INSTALLS += $(CAENHVASYN)/db/bi.template
DB_INSTALLS += $(CAENHVASYN)/db/bo.template
DB_INSTALLS += $(CAENHVASYN)/db/stringin.template
DB_INSTALLS += $(CAENHVASYN)/db/stringout.template
DB_INSTALLS += $(CAENHVASYN)/db/longin.template
DB_INSTALLS += $(CAENHVASYN)/db/longout.template
```