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
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <iostream>
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

//// Argument list passed to load a record
//struct recordParams
//{
//    std::string recName;
//    std::string recDesc;
//    std::string recTemplate;
//    std::string paramName;
//    asynParamType paramType;
//};

class CAENHVAsyn : public asynPortDriver
{
    public:
        CAENHVAsyn(const std::string& portName, int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password);

        // Methods that we override from asynPortDriver
        virtual asynStatus readFloat64       (asynUser *pasynUser, epicsFloat64 *value);
        virtual asynStatus readUInt32Digital (asynUser *pasynUser, epicsUInt32 *value, epicsUInt32 mask);

    private:
        //int LoadRecord(int regType, const recordParams& rp, const std::stringstream& dbParams);

        //void createBoardParam(const BoardParameter& bp);
        void createBoardParamNumeric(BoardParameterNumeric bp);
        void createBoardParamOnOff(BoardParameterOnOff bp);

        const std::string driverName_;
        std::string portName_;
        Chassis *chassis;

       std::map<int, BoardParameterNumeric> boardParameterNumericList;
       std::map<int, BoardParameterOnOff>   boardParameterOnOffList;

       //std::map<int, const BoardParameter&> boardParameterList;
       //std::map<int, int> boardParameterList;
};

#endif
