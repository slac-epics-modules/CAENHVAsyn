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

// Default value for the EPICS record prefix is an empty string,
// which means that the autogeration is disabled.
std::string CAENHVAsyn::epicsPrefix;
std::string CAENHVAsyn::chassisInfoFilePath = "/tmp/";

void CAENHVAsyn::createBoardParamNumeric(BoardParameterNumeric bp)
{
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

    if (!epicsPrefix.empty())
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "P="      << CAENHVAsyn::epicsPrefix;
        dbParamsLocal << ",PORT="   << portName_;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",EGU="   << egu;
        dbParamsLocal << ",LOPR="  << min;
        dbParamsLocal << ",HOPR="  << max;

        if ( (!mode.compare("RW")) || (!mode.compare("RO")) )
        {
            dbParamsLocal << ",SCAN=1 second";
            dbParamsLocal << ",R=" << recordName << ":Rd";
            dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str());
        }

        if ( (!mode.compare("RW")) || (!mode.compare("WO")) )
        {
            dbParamsLocal << ",DRVL=" << min;
            dbParamsLocal << ",DRVH=" << max;
            dbParamsLocal << ",R="    << recordName << ":St";
            dbLoadRecords("db/ao.template", dbParamsLocal.str().c_str());
        }

    }
}

void CAENHVAsyn::createBoardParamOnOff(BoardParameterOnOff bp)
{
    std::string paramName  = bp->getEpicsParamName();
    std::string recordName = bp->getEpicsRecordName();
    std::string desc       = bp->getEpicsDesc();
    std::string mode       = bp->getMode();
    std::string onLabel    = bp->getOnState();
    std::string offLabel   = bp->getOffState();

    int index;
    createParam(paramName.c_str(), asynParamUInt32Digital, &index);

    boardParameterOnOffList.insert( std::make_pair<int, BoardParameterOnOff>(index, bp) );

    if (!epicsPrefix.empty())
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "P="      << CAENHVAsyn::epicsPrefix;
        dbParamsLocal << ",PORT="   << portName_;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",ZNAM="  << onLabel;
        dbParamsLocal << ",ONAM="  << offLabel;

        if ( (!mode.compare("RW")) || (!mode.compare("RO")) )
        {
            dbParamsLocal << ",SCAN=1 second";
            dbParamsLocal << ",R=" << recordName << ":Rd";
            dbLoadRecords("db/bi.template", dbParamsLocal.str().c_str());
        }

        if ( (!mode.compare("RW")) || (!mode.compare("WO")) )
        {
            dbParamsLocal << ",R="    << recordName << ":St";
            dbLoadRecords("db/bo.template", dbParamsLocal.str().c_str());
        }
    }
}



void CAENHVAsyn::createChannelParamNumeric(ChannelParameterNumeric cp)
{
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

    if (!epicsPrefix.empty())
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "P="      << CAENHVAsyn::epicsPrefix;
        dbParamsLocal << ",PORT="   << portName_;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",EGU="   << egu;
        dbParamsLocal << ",LOPR="  << min;
        dbParamsLocal << ",HOPR="  << max;

        if ( (!mode.compare("RW")) || (!mode.compare("RO")) )
        {
            dbParamsLocal << ",SCAN=1 second";
            dbParamsLocal << ",R=" << recordName << ":Rd";
            dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str());
        }

        if ( (!mode.compare("RW")) || (!mode.compare("WO")) )
        {
            dbParamsLocal << ",DRVL=" << min;
            dbParamsLocal << ",DRVH=" << max;
            dbParamsLocal << ",R="    << recordName << ":St";
            dbLoadRecords("db/ao.template", dbParamsLocal.str().c_str());
        }
    }
}

void CAENHVAsyn::createChannelParamOnOff(ChannelParameterOnOff cp)
{
    std::string paramName  = cp->getEpicsParamName();
    std::string recordName = cp->getEpicsRecordName();
    std::string desc       = cp->getEpicsDesc();
    std::string mode       = cp->getMode();
    std::string onLabel    = cp->getOnState();
    std::string offLabel   = cp->getOffState();

    int index;
    createParam(paramName.c_str(), asynParamUInt32Digital, &index);


    channelParameterOnOffList.insert( std::make_pair<int, ChannelParameterOnOff>(index, cp) );

    if (!epicsPrefix.empty())
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "P="      << CAENHVAsyn::epicsPrefix;
        dbParamsLocal << ",PORT="   << portName_;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",ZNAM="  << onLabel;
        dbParamsLocal << ",ONAM="  << offLabel;

        if ( (!mode.compare("RW")) || (!mode.compare("RO")) )
        {
            dbParamsLocal << ",SCAN=1 second";
            dbParamsLocal << ",R=" << recordName << ":Rd";
            dbLoadRecords("db/bi.template", dbParamsLocal.str().c_str());
        }

        if ( (!mode.compare("RW")) || (!mode.compare("WO")) )
        {
            dbParamsLocal << ",R="    << recordName << ":St";
            dbLoadRecords("db/bo.template", dbParamsLocal.str().c_str());
        }
    }
}

void CAENHVAsyn::createSystemPropertyInteger(SystemPropertyInteger sp)
{
    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamInt32, &index);

    systemPropertyIntegerList.insert( std::make_pair<int, SystemPropertyInteger>(index, sp) );

    if (!epicsPrefix.empty())
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "P="      << CAENHVAsyn::epicsPrefix;
        dbParamsLocal << ",PORT="   << portName_;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;

        if ( (!mode.compare("RW")) || (!mode.compare("RO")) )
        {
            dbParamsLocal << ",R=" << recordName << ":Rd";
            dbParamsLocal << ",SCAN=1 second";
            dbLoadRecords("db/longin.template", dbParamsLocal.str().c_str());
        }

        if ( (!mode.compare("RW")) || (!mode.compare("WO")) )
        {
            dbParamsLocal << ",R=" << recordName << ":St";
            dbLoadRecords("db/longout.template", dbParamsLocal.str().c_str());
        }
    }
}

void CAENHVAsyn::createSystemPropertyString(SystemPropertyString sp)
{
    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamOctet, &index);

    systemPropertyStringList.insert( std::make_pair<int, SystemPropertyString>(index, sp) );

    if (!epicsPrefix.empty())
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "P="      << CAENHVAsyn::epicsPrefix;
        dbParamsLocal << ",PORT="   << portName_;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",NELM=4096";

        if ( (!mode.compare("RW")) || (!mode.compare("RO")) )
        {
            dbParamsLocal << ",R=" << recordName << ":Rd";
            dbParamsLocal << ",SCAN=1 second";
            dbLoadRecords("db/stringin.template", dbParamsLocal.str().c_str());
        }

        if ( (!mode.compare("RW")) || (!mode.compare("WO")) )
        {
            dbParamsLocal << ",R=" << recordName << ":St";
            dbLoadRecords("db/stringout.template", dbParamsLocal.str().c_str());
        }
    }
}

void CAENHVAsyn::createSystemPropertyFloat(SystemPropertyFloat sp)
{
    std::string paramName  = sp->getEpicsParamName();
    std::string recordName = sp->getEpicsRecordName();
    std::string desc       = sp->getEpicsDesc();
    std::string mode       = sp->getMode();

    int index;
    createParam(paramName.c_str(), asynParamFloat64, &index);

    systemPropertyFloatList.insert( std::make_pair<int, SystemPropertyFloat>(index, sp) );

    if (!epicsPrefix.empty())
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "P="      << CAENHVAsyn::epicsPrefix;
        dbParamsLocal << ",PORT="   << portName_;
        dbParamsLocal << ",PARAM=" << paramName;
        dbParamsLocal << ",DESC="  << desc;
        dbParamsLocal << ",EGU=";
        dbParamsLocal << ",LOPR=";
        dbParamsLocal << ",HOPR=";

        if ( (!mode.compare("RW")) || (!mode.compare("RO")) )
        {
            dbParamsLocal << ",SCAN=1 second";
            dbParamsLocal << ",R=" << recordName << ":Rd";
            dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str());
        }

        if ( (!mode.compare("RW")) || (!mode.compare("WO")) )
        {
            dbParamsLocal << ",DRVL=";
            dbParamsLocal << ",DRVH=";
            dbParamsLocal << ",R=" << recordName << ":St";
            dbLoadRecords("db/ao.template", dbParamsLocal.str().c_str());
        }
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

    // Create a Chassis object
    chassis = new Chassis(systemType, ipAddr, userName, password);

    // Print Chassis information
    //chassis->printInfo(std::cout);

    // Print Chassis information to a temporal file
    // This need to be reimplemented using RAII...
    // Also, the user should be able to override the output location
    std::string infoFileName(chassisInfoFilePath + this->driverName_ + "_" + this->portName_ + "_chassisInfo.txt");
    std::ofstream infoFile;

    std::cout << "Dumping chassis information on '" << infoFileName << "'... ";
    infoFile.open(infoFileName);
    chassis->printInfo(infoFile);
    infoFile.close();
    std::cout  << "Done" << std::endl;

    if (epicsPrefix.empty())
        std::cout << "Autogeneration of PVs is disabled." << std::endl;
    else
        std::cout << "Autogeneration of PVs is enabled with prefix '" << epicsPrefix << "'" << std::endl;

    // System properties
    {
        std::vector<SystemPropertyString> s = chassis->getSystemPropertyStrings();
        for (std::vector<SystemPropertyString>::iterator it = s.begin(); it != s.end(); ++it)
            createSystemPropertyString(*it);
    }

    {
        std::vector<SystemPropertyInteger> s = chassis->getSystemPropertyIntegers();
        for (std::vector<SystemPropertyInteger>::iterator it = s.begin(); it != s.end(); ++it)
            createSystemPropertyInteger(*it);
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
    static std::string method("readInt32");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, SystemPropertyInteger>::iterator spIt;

    if ((spIt = systemPropertyIntegerList.find(function)) != systemPropertyIntegerList.end())
        *value = spIt->second->getVal();
    else
        status = asynPortDriver::readInt32(pasynUser, value);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : read '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, *value);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while reading, status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, status);

        return asynError;
    }
}

asynStatus CAENHVAsyn::writeInt32(asynUser *pasynUser, epicsInt32 value)
{
    static std::string method("writeInt32");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, SystemPropertyInteger>::iterator spIt;

    if ((spIt = systemPropertyIntegerList.find(function)) != systemPropertyIntegerList.end())
        spIt->second->setVal(value);
    else
        status = asynPortDriver::writeInt32(pasynUser, value);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : set to '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while writting '%d', status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value, status);

        return asynError;
    }
}

asynStatus CAENHVAsyn::readFloat64(asynUser *pasynUser, epicsFloat64 *value)
{
    static std::string method("readFloat64");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, ChannelParameterNumeric>::iterator cpIt;
    std::map<int, BoardParameterNumeric>::iterator   bpIt;

    if ((cpIt = channelParameterNumericList.find(function)) != channelParameterNumericList.end())
        *value = cpIt->second->getVal();
    else if ((bpIt = boardParameterNumericList.find(function)) != boardParameterNumericList.end())
        *value = bpIt->second->getVal();
    else
        status = asynPortDriver::readFloat64(pasynUser, value);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : read '%f'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, *value);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while reading, status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, status);

        return asynError;
    }
}

asynStatus CAENHVAsyn::writeFloat64(asynUser *pasynUser, epicsFloat64 value)
{
    static std::string method("writeFloat64");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, ChannelParameterNumeric>::iterator cpIt;
    std::map<int, BoardParameterNumeric>::iterator   bpIt;

    if ((cpIt = channelParameterNumericList.find(function)) != channelParameterNumericList.end())
        cpIt->second->setVal(value);
    else if ((bpIt = boardParameterNumericList.find(function)) != boardParameterNumericList.end())
        bpIt->second->setVal(value);
    else
        status = asynPortDriver::writeFloat64(pasynUser, value);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : set to '%f'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while writting '%f', status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value, status);

        return asynError;
    }
}

asynStatus CAENHVAsyn::readUInt32Digital(asynUser *pasynUser, epicsUInt32 *value, epicsUInt32 mask)
{
    static std::string method("readUInt32Digital");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, BoardParameterOnOff>::iterator bpIt;
    std::map<int, ChannelParameterOnOff>::iterator cpIt;

    if ((bpIt = boardParameterOnOffList.find(function )) != boardParameterOnOffList.end())
    {
       uint32_t temp = bpIt->second->getVal();
       temp &= mask;
       *value = temp;
    }
    else if ((cpIt = channelParameterOnOffList.find(function )) != channelParameterOnOffList.end())
    {
       uint32_t temp = cpIt->second->getVal();
       temp &= mask;
       *value = temp;
    }
    else
        status = asynPortDriver::readUInt32Digital(pasynUser, value, mask);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : read '%d', mask '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, *value, mask);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while reading, mask '%d', status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, mask, status);

        return asynError;
    }
}


asynStatus CAENHVAsyn::writeUInt32Digital(asynUser *pasynUser, epicsUInt32 value, epicsUInt32 mask)
{
    static std::string method("writeUInt32Digital");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    epicsUInt32 val(0);
    val &= ~mask;
    val |= value;

    std::map<int, BoardParameterOnOff>::iterator bpIt;
    std::map<int, ChannelParameterOnOff>::iterator cpIt;

    if ( ( bpIt = boardParameterOnOffList.find(function) ) != boardParameterOnOffList.end() )
    {
        bpIt->second->setVal(val);
    }
    else if ( ( cpIt = channelParameterOnOffList.find(function ) ) != channelParameterOnOffList.end() )
    {
        cpIt->second->setVal(val);
    }
    else
        status = asynPortDriver::writeUInt32Digital(pasynUser, value, mask);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : set to '%d', mask '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value, mask);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while writting '%d', mask '%d', status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value, mask, status);

        return asynError;
    }
}

asynStatus CAENHVAsyn::readOctet(asynUser *pasynUser, char *value, size_t maxChars, size_t *nActual, int *eomReason)
{
    static std::string method("readOctet");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, SystemPropertyString>::iterator spIt;

    if ( ( spIt = systemPropertyStringList.find(function) ) != systemPropertyStringList.end() )
    {
        std::string temp = spIt->second->getVal();
        strcpy(value, temp.c_str());
        *nActual = temp.length() + 1;
    }
    else
        status = asynPortDriver::readOctet(pasynUser, value, maxChars, nActual, eomReason);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : read '%s', maxChars '%zu', nActual '%zu'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value, maxChars, *nActual);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while reading, maxChars '%zu', status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, maxChars, status);

        return asynError;
    }
}

asynStatus CAENHVAsyn::writeOctet(asynUser *pasynUser, const char *value, size_t maxChars, size_t *nActual)
{
    static std::string method("writeOctet");
    int function(pasynUser->reason);
    int status(0);

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

    std::map<int, SystemPropertyString>::iterator spIt;

    if ( ( spIt = systemPropertyStringList.find(function) ) != systemPropertyStringList.end() )
    {
        std::string temp(value);
        spIt->second->setVal(temp);
        *nActual = temp.size();
    }
    else
        status = asynPortDriver::writeOctet(pasynUser, value, maxChars, nActual);

    if (0 == status)
    {
        asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : set to '%s', maxChars '%zu', nActual '%zu'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value, maxChars, *nActual);

        return asynSuccess;
    }
    else
    {
         asynPrint(pasynUser, ASYN_TRACE_ERROR, \
                    "Driver '%s', Port '%s', Method '%s', Function number '%d', parameter '%s' : Error while writting '%s', maxChars '%zu', status '%d'\n", \
                    this->driverName_.c_str(), this->portName_.c_str(), method.c_str(), function, name, value, maxChars, status);

        return asynError;
    }
}

////////////////////////////////////
// Driver configuration functions //
////////////////////////////////////

// + CAENHVAsynConfig //
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
// - CAENHVAsynConfig //

// + CAENHVAsynSetEpicsPrefix //
extern "C" int CAENHVAsynSetEpicsPrefix(const char *prefix)
{
    if ( ( ! prefix ) || ( prefix[0] == '\0' ) )
        return 0;

    CAENHVAsyn::epicsPrefix = prefix;

    return 0;
}

static const iocshArg epicsPrefixArg0 = { "Prefix", iocshArgString };

static const iocshArg * const epicsPrefixArgs[] =
{
    &epicsPrefixArg0
};

static const iocshFuncDef epicsPrefixFuncDef = { "CAENHVAsynSetEpicsPrefix", 1, epicsPrefixArgs };

static void epicsPrefixCallFunc(const iocshArgBuf *args)
{
    CAENHVAsynSetEpicsPrefix(args[0].sval);
}
// - CAENHVAsynSetEpicsPrefix //

// iocshRegister
void drvCAENHVAsynRegister(void)
{
    iocshRegister( &configFuncDef,      configCallFunc      );
    iocshRegister( &epicsPrefixFuncDef, epicsPrefixCallFunc );
}

extern "C"
{
    epicsExportRegistrar(drvCAENHVAsynRegister);
}
