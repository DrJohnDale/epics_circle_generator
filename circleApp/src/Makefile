TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = circle
# circle.dbd will be created and installed
DBD += circle.dbd

# circle.dbd will be made up from these files:
circle_DBD += base.dbd

# Include dbd files from all support applications:
circle_DBD += randomNumber.dbd

# Add all the support libraries needed by this IOC
#circle_LIBS += xxx

# circle_registerRecordDeviceDriver.cpp derives from circle.dbd
circle_SRCS += circle_registerRecordDeviceDriver.cpp
circle_SRCS += randomNumber.c

# Build the main IOC entry point on workstation OSs.
circle_SRCS_DEFAULT += circleMain.cpp
circle_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#circle_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
circle_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

