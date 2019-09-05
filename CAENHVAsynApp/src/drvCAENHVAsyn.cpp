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


void CAENHVAsyn::createBoardParamNumeric(BoardParameterNumeric bp)
{
    bool loadRecord = true;

    std::string paramName  = bp->getEpicsParamName();
    std::string recordName = bp->getEpicsRecordName();
    std::string desc       = bp->getEpicsDesc();
    std::string mode       = bp->getMode();
    std::string egu        = bp->getUnits();
    float       min        = bp->getMinVal();
    float       max        = bp->getMaxVal();

    int index;
    createParam(paramName.c_str(), asynParamFloat64, &index);

    boardParameterNumericList.insert( std::make_pair<int, BoardParameterNumeric>(index, bp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",EGU="   << egu;
        dbParamsLocal << ",LOPR="  << min;
        dbParamsLocal << ",HOPR="  << max;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str()); 
    }
}

void CAENHVAsyn::createBoardParamOnOff(BoardParameterOnOff bp)
{
    bool loadRecord = true;

    std::string paramName  = bp->getEpicsParamName();
    std::string recordName = bp->getEpicsRecordName();
    std::string desc       = bp->getEpicsDesc();
    std::string mode       = bp->getMode();
    std::string onLabel    = bp->getOnState();
    std::string offLabel   = bp->getOffState();

    int index;
    createParam(paramName.c_str(), asynParamUInt32Digital, &index);

    boardParameterOnOffList.insert( std::make_pair<int, BoardParameterOnOff>(index, bp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",ZNAM="  << onLabel;
        dbParamsLocal << ",ONAM="  << offLabel;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/bi.template", dbParamsLocal.str().c_str());
    }
}



void CAENHVAsyn::createChannelParamNumeric(ChannelParameterNumeric cp)
{
    bool loadRecord = true;

    std::string paramName  = cp->getEpicsParamName();
    std::string recordName = cp->getEpicsRecordName();
    std::string desc       = cp->getEpicsDesc();
    std::string mode       = cp->getMode();
    std::string egu        = cp->getUnits();
    float       min        = cp->getMinVal();
    float       max        = cp->getMaxVal();

    int index;
    createParam(paramName.c_str(), asynParamFloat64, &index);

    channelParameterNumericList.insert( std::make_pair<int, ChannelParameterNumeric>(index, cp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",EGU="   << egu;
        dbParamsLocal << ",LOPR="  << min;
        dbParamsLocal << ",HOPR="  << max;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str());
    }
}

void CAENHVAsyn::createChannelParamOnOff(ChannelParameterOnOff cp)
{
    bool loadRecord = true;

    std::string paramName  = cp->getEpicsParamName();
    std::string recordName = cp->getEpicsRecordName();
    std::string desc       = cp->getEpicsDesc();
    std::string mode       = cp->getMode();
    std::string onLabel    = cp->getOnState();
    std::string offLabel   = cp->getOffState();

    int index;
    createParam(paramName.c_str(), asynParamUInt32Digital, &index);


    channelParameterOnOffList.insert( std::make_pair<int, ChannelParameterOnOff>(index, cp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",ZNAM="  << onLabel;
        dbParamsLocal << ",ONAM="  << offLabel;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/bi.template", dbParamsLocal.str().c_str());
    }
}


void CAENHVAsyn::createSystemPropertyU8(SystemPropertyU8 sp)
{
    bool loadRecord = true;

    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamInt32, &index);

    systemPropertyU8List.insert( std::make_pair<int, SystemPropertyU8>(index, sp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/longin.template", dbParamsLocal.str().c_str());
    }
}

void CAENHVAsyn::createSystemPropertyU16(SystemPropertyU16 sp)
{
    bool loadRecord = true;

    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamInt32, &index);

    systemPropertyU16List.insert( std::make_pair<int, SystemPropertyU16>(index, sp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/longin.template", dbParamsLocal.str().c_str());
    }
}

void CAENHVAsyn::createSystemPropertyU32(SystemPropertyU32 sp)
{
    bool loadRecord = true;

    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamInt32, &index);

    systemPropertyU32List.insert( std::make_pair<int, SystemPropertyU32>(index, sp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/longin.template", dbParamsLocal.str().c_str());
    }
}

void CAENHVAsyn::createSystemPropertyI16(SystemPropertyI16 sp)
{
    bool loadRecord = true;

    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamInt32, &index);

    systemPropertyI16List.insert( std::make_pair<int, SystemPropertyI16>(index, sp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/longin.template", dbParamsLocal.str().c_str());
    }
}

void CAENHVAsyn::createSystemPropertyI32(SystemPropertyI32 sp)
{
    bool loadRecord = true;

    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamInt32, &index);

    systemPropertyI32List.insert( std::make_pair<int, SystemPropertyI32>(index, sp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/longin.template", dbParamsLocal.str().c_str());
    }
}

void CAENHVAsyn::createSystemPropertyString(SystemPropertyString sp)
{
    bool loadRecord = true;

    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamOctet, &index);

    systemPropertyStringList.insert( std::make_pair<int, SystemPropertyString>(index, sp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",NELM=4096";
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/string.template", dbParamsLocal.str().c_str());
    }
}

void CAENHVAsyn::createSystemPropertyFloat(SystemPropertyFloat sp)
{
    bool loadRecord = true;

    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamFloat64, &index);

    systemPropertyFloatList.insert( std::make_pair<int, SystemPropertyFloat>(index, sp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT="   << portName_;
        dbParamsLocal << ",R="     << recordName;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",EGU=";
        dbParamsLocal << ",LOPR=";
        dbParamsLocal << ",HOPR=";
        dbParamsLocal << ",SCAN=1 second";

        dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str());
    }
}

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

    // System properties
    {
        std::vector<SystemPropertyString> s = chassis->getSystemPropertyStrings();
        for (std::vector<SystemPropertyString>::iterator it = s.begin(); it != s.end(); ++it)
            createSystemPropertyString(*it);
    }

    {
        std::vector<SystemPropertyU16> s = chassis->getSystemPropertyU16s();
        for (std::vector<SystemPropertyU16>::iterator it = s.begin(); it != s.end(); ++it)
            createSystemPropertyU16(*it);
    }

    {
        std::vector<SystemPropertyU32> s = chassis->getSystemPropertyU32s();
        for (std::vector<SystemPropertyU32>::iterator it = s.begin(); it != s.end(); ++it)
            createSystemPropertyU32(*it);
    }

    {
        std::vector<SystemPropertyI16> s = chassis->getSystemPropertyI16s();
        for (std::vector<SystemPropertyI16>::iterator it = s.begin(); it != s.end(); ++it)
            createSystemPropertyI16(*it);
    }

    {
        std::vector<SystemPropertyI32> s = chassis->getSystemPropertyI32s();
        for (std::vector<SystemPropertyI32>::iterator it = s.begin(); it != s.end(); ++it)
            createSystemPropertyI32(*it);
    }

    // Boards
    std::vector<Board> b = chassis->getBoards();

    for (std::vector<Board>::iterator boardIt = b.begin(); boardIt != b.end(); ++boardIt)
    {
        std::vector<BoardParameterNumeric> pn = boardIt->getBoardParameterNumerics();
        
        for (std::vector<BoardParameterNumeric>::iterator paramIt = pn.begin(); paramIt != pn.end(); ++paramIt)
            createBoardParamNumeric(*paramIt);

        std::vector<BoardParameterOnOff> po = boardIt->getBoardParameterOnOffs();
        
        for (std::vector<BoardParameterOnOff>::iterator paramIt = po.begin(); paramIt != po.end(); ++paramIt)
            createBoardParamOnOff(*paramIt);

        std::vector<Channel> c = boardIt->getChannels();

        for(std::vector<Channel>::iterator channelIt = c.begin(); channelIt != c.end(); ++channelIt)
        {
            std::vector<ChannelParameterNumeric> cpn = channelIt->getChannelParameterNumerics();
            for (std::vector<ChannelParameterNumeric>::iterator paramIt = cpn.begin(); paramIt != cpn.end(); ++paramIt)
                createChannelParamNumeric(*paramIt);
        
            std::vector<ChannelParameterOnOff> cpo = channelIt->getChannelParameterOnOffs();
            for (std::vector<ChannelParameterOnOff>::iterator paramIt = cpo.begin(); paramIt != cpo.end(); ++paramIt)
                createChannelParamOnOff(*paramIt);
        }
    }
}



asynStatus CAENHVAsyn::readInt32(asynUser *pasynUser, epicsInt32 *value)
{
    static const char *functionName = "readInt32";
    int function = pasynUser->reason;
    int status = 0;

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

//    printf("Function = %s, addr = %d, function = %d, name = %s\n", functionName, addr, function, name);

    std::map<int, SystemPropertyU16>::iterator u16_it;
    std::map<int, SystemPropertyU32>::iterator u32_it;
    std::map<int, SystemPropertyI16>::iterator i16_it;
    std::map<int, SystemPropertyI32>::iterator i32_it;


    if ((u16_it = systemPropertyU16List.find(function)) != systemPropertyU16List.end())
        *value = u16_it->second->getVal();
    else if ((u32_it = systemPropertyU32List.find(function)) != systemPropertyU32List.end())
        *value = u32_it->second->getVal();
    else if ((i16_it = systemPropertyI16List.find(function)) != systemPropertyI16List.end())
        *value = i16_it->second->getVal();
    else if ((i32_it = systemPropertyI32List.find(function)) != systemPropertyI32List.end())
        *value = i32_it->second->getVal();

    return (status==0) ? asynSuccess : asynError;    
}

asynStatus CAENHVAsyn::readFloat64(asynUser *pasynUser, epicsFloat64 *value)
{
    static const char *functionName = "readFloat64";
    int function = pasynUser->reason;
    int status = 0;

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, ChannelParameterNumeric>::iterator cpIt; 
    std::map<int, BoardParameterNumeric>::iterator   bpIt;

//    printf("Function = %s, addr = %d, function = %d, name = %s\n", functionName, addr, function, name);

    if ((cpIt = channelParameterNumericList.find(function)) != channelParameterNumericList.end())
        *value = cpIt->second->getVal();
    else if ((bpIt = boardParameterNumericList.find(function)) != boardParameterNumericList.end())
        *value = bpIt->second->getVal();

    //std::map<int, BoardParameterNumeric>::iterator it = boardParameterNumericList.find(function);
    //if (it != boardParameterNumericList.end())

    return (status==0) ? asynSuccess : asynError;
}

asynStatus CAENHVAsyn::readUInt32Digital(asynUser *pasynUser, epicsUInt32 *value, epicsUInt32 mask)
{

    static const char *functionName = "readUInt32Digital";
    int function = pasynUser->reason;
    int status = 0;

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    //printf("Function = %s, addr = %d, function = %d, name = %s\n", functionName, addr, function, name);

    std::map<int, BoardParameterOnOff>::iterator it = boardParameterOnOffList.find(function);

    if (it != boardParameterOnOffList.end())
    {
       // To be done... 
       // At the memoment the getVal() returns an empty string
    }

    return (status==0) ? asynSuccess : asynError;
}

asynStatus CAENHVAsyn::readOctet(asynUser *pasynUser, char *value, size_t maxChars, size_t *nActual, int *eomReason)
{
    static const char *functionName = "readOctet";
    int function = pasynUser->reason;
    int status = 0;

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    //printf("Function = %s, addr = %d, function = %d, name = %s\n", functionName, addr, function, name);
    std::map<int, SystemPropertyString>::iterator it =  systemPropertyStringList.find(function);

    if (it != systemPropertyStringList.end())
    {
        std::string temp = it->second->getVal();
        strcpy(value, temp.c_str());
        *nActual = temp.length() + 1;
    }

    return (status==0) ? asynSuccess : asynError;
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
