#ifndef DRV_CAEN_HV_ASYN_H
#define DRV_CAEN_HV_ASYN_H

/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : drvCAENHVAsyn.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-07-23
 * ----------------------------------------------------------------------------
 * Description:
 * EPICS Module for CAEN HV Power supplies
 * ----------------------------------------------------------------------------
 * This file is part of l2MpsAsyn. It is subject to
 * the license terms in the LICENSE.txt file found in the top-level directory
 * of this distribution and at:
    * https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
 * No part of l2MpsAsyn, including this file, may be
 * copied, modified, propagated, or distributed except according to the terms
 * contained in the LICENSE.txt file.
 * ----------------------------------------------------------------------------
**/

#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <utility>
#include <iostream>
#include <fstream>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <epicsTypes.h>
#include <epicsTime.h>
#include <epicsThread.h>
#include <epicsString.h>
#include <epicsTimer.h>
#include <epicsMutex.h>
#include <epicsEvent.h>
#include <iocsh.h>
#include <dbAccess.h>
#include <dbStaticLib.h>
#include "asynPortDriver.h"
#include <epicsExport.h>

#include "CAENHVWrapper.h"
#include "common.h"
#include "chassis.h"

#define MAX_SIGNALS (3)
#define NUM_PARAMS (1500)

class CAENHVAsyn : public asynPortDriver
{
    public:
        CAENHVAsyn(const std::string& portName, int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password);

        // Methods that we override from asynPortDriver
        virtual asynStatus readFloat64        (asynUser *pasynUser, epicsFloat64 *value);
        virtual asynStatus writeFloat64       (asynUser *pasynUser, epicsFloat64 value);
        virtual asynStatus readUInt32Digital  (asynUser *pasynUser, epicsUInt32 *value, epicsUInt32 mask);
        virtual asynStatus writeUInt32Digital (asynUser *pasynUser, epicsUInt32 value, epicsUInt32 mask);
        virtual asynStatus readOctet          (asynUser *pasynUser, char *value, size_t maxChars, size_t *nActual, int *eomReason);
        virtual asynStatus writeOctet         (asynUser *pasynUser, const char *value, size_t maxChars, size_t *nActual);
        virtual asynStatus readInt32          (asynUser *pasynUser, epicsInt32 *value);
        virtual asynStatus writeInt32         (asynUser *pasynUser, epicsInt32 value);

        // EPICS record prefix. Use for autogeneration of PVs.
        static std::string epicsPrefix;
        // Chassis information output file location
        static std::string chassisInfoFilePath;

    private:

        // Methods to create system property EPICS paramater and records
        void createSystemPropertyU8(SystemPropertyU8);
        void createSystemPropertyU16(SystemPropertyU16);
        void createSystemPropertyU32(SystemPropertyU32);
        void createSystemPropertyI16(SystemPropertyI16);
        void createSystemPropertyI32(SystemPropertyI32);
        void createSystemPropertyString(SystemPropertyString);
        void createSystemPropertyFloat(SystemPropertyFloat);

        // Methods to create board parameter EPICS paramater and records
        void createBoardParamNumeric(BoardParameterNumeric bp);
        void createBoardParamOnOff(BoardParameterOnOff bp);

        // Methods to create channel parameteer EPICS paramater and records
        void createChannelParamNumeric(ChannelParameterNumeric cp);
        void createChannelParamOnOff(ChannelParameterOnOff cp);

        const std::string driverName_;
        std::string portName_;
        Chassis *chassis;

       // System property lists
       std::map<int, SystemPropertyU8>      systemPropertyU8List;
       std::map<int, SystemPropertyU16>     systemPropertyU16List;
       std::map<int, SystemPropertyU32>     systemPropertyU32List;
       std::map<int, SystemPropertyI16>     systemPropertyI16List;
       std::map<int, SystemPropertyI32>     systemPropertyI32List;
       std::map<int, SystemPropertyString>  systemPropertyStringList;
       std::map<int, SystemPropertyFloat>   systemPropertyFloatList;

       // Board parameter lists
       std::map<int, BoardParameterNumeric> boardParameterNumericList;
       std::map<int, BoardParameterOnOff>   boardParameterOnOffList;

       // Channel parameter lists
       std::map<int, ChannelParameterNumeric> channelParameterNumericList;
       std::map<int, ChannelParameterOnOff>   channelParameterOnOffList;
};


class CAENHVAsynFileRAII
{
public:
    CAENHVAsynFileRAII(const std::string& name) { printf("Opening file\n"); file.open(name); };
    ~CAENHVAsynFileRAII() { printf("Closing file\n"); file.close(); };

    //std::ostream& operator<< (std::ostream& stream) { return file << stream; };
    //std::istream& operator>> (std::istream& stream) { stream >> file; return stream; };
    CAENHVAsynFileRAII& operator>>(const CAENHVAsynFileRAII& rhs) { return *this; };

private:
    std::ofstream file;
};

#endif
