/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : drvCAENHVAsyn.cpp
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

#include "drvCAENHVAsyn.h"

CAENHVAsyn::CAENHVAsyn(const std::string& portName, int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password)
:
    asynPortDriver(
        portName.c_str(),
        MAX_SIGNALS,
        NUM_PARAMS,
        asynInt32Mask | asynDrvUserMask | asynInt16ArrayMask | asynInt32ArrayMask | asynOctetMask | \
        asynFloat64ArrayMask | asynUInt32DigitalMask | asynFloat64Mask,                             // Interface Mask
        asynInt16ArrayMask | asynInt32ArrayMask | asynInt32Mask | asynUInt32DigitalMask,            // Interrupt Mask
        ASYN_MULTIDEVICE | ASYN_CANBLOCK,                                                           // asynFlags
        1,                                                                                          // Autoconnect
        0,                                                                                          // Default priority
        0),                                                                                         // Default stack size
    driverName_("CAENHVAsyn"),
    portName_(portName)
{
    // Check parameters
    if ( portName_.empty() )
        throw std::runtime_error("The port name must be defined");

    if ( userName.empty() )
        throw std::runtime_error("The user name must be defined");

    if ( ipAddr.empty() )
        throw std::runtime_error("The IP address must be defined");
    else
    {
        unsigned char buf[sizeof(struct in6_addr)];
        if (!inet_pton(AF_INET, ipAddr.c_str(), buf))
            throw std::runtime_error("Invalid IP address");
    }

    // Only SYx527 are supported at the 
    if ( (systemType < 0) || (systemType > 3) )
        throw std::runtime_error("Unsupported system type. Only supported types are SYx527 (0-3)");

    chassis = new Chassis(systemType, ipAddr, userName, password);

    std::cout << std::endl;
    chassis->printInfo();
}

int CAENHVAsyn::LoadRecord(int regType, const recordParams& rp, const std::stringstream& dbParams)
{
    int paramIndex;
    std::stringstream dbParamsLocal;

    // Create list of paramater to pass to the  dbLoadRecords function
    dbParamsLocal.str("");
    dbParamsLocal << "PORT=" << portName_;
    dbParamsLocal << ",ADDR=" << regType;
    dbParamsLocal << ",R=" << rp.recName;
    dbParamsLocal << ",PARAM=" << rp.paramName;
    dbParamsLocal << ",DESC=" << rp.recDesc;
    dbParamsLocal << dbParams.str();

    // Create the asyn paramater
    createParam(regType, rp.paramName.c_str(), rp.paramType, &paramIndex);

    // Create the record
    dbLoadRecords(rp.recTemplate.c_str(), dbParamsLocal.str().c_str());

    // Write the record name to the PV list file
    //pvDumpFile->write("%s%*s", rp.recName.c_str(), recordNameLenMax - rp.recName.size() + 4, "");
    //pvDumpFile->write("# %s (%s)\n", getNameWithoutLeafIndexes(p).c_str(), regInterfaceTypeNames[regType]);

    // Incrfement the number of created records
    //++recordCount;

    // Return the parameter index
    return paramIndex;
}

////////////////////////////////////
// Driver configuration functions //
////////////////////////////////////

// CAENHVAsynConfig
extern "C" int CAENHVAsynConfig(const char* portName, int systemType, char* ipAddr, const char* userName, const char* password)
{
    new CAENHVAsyn(portName, systemType, ipAddr, userName, password);

    return asynSuccess;
}

static const iocshArg confArg0 = { "portName",   iocshArgString };
static const iocshArg confArg1 = { "systemType", iocshArgInt    };
static const iocshArg confArg2 = { "ipAddr",     iocshArgString };
static const iocshArg confArg3 = { "userName",   iocshArgString };
static const iocshArg confArg4 = { "password",   iocshArgString };

static const iocshArg * const confArgs[] =
{
    &confArg0,
    &confArg1,
    &confArg2,
    &confArg3,
    &confArg4
};

static const iocshFuncDef configFuncDef = {"CAENHVAsynConfig", 5, confArgs};

static void configCallFunc(const iocshArgBuf *args)
{
    CAENHVAsynConfig(args[0].sval, args[1].ival, args[2].sval, args[3].sval, args[4].sval);
}

// iocshRegister
void drvCAENHVAsynRegister(void)
{
    iocshRegister(&configFuncDef, configCallFunc);
}

extern "C" 
{
    epicsExportRegistrar(drvCAENHVAsynRegister);
}
