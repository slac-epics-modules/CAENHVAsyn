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

    std::string name = bp->getEpicsParam();
    std::string mode = bp->getMode();
    std::string egu  = bp->getUnits();
    float       min  = bp->getMinVal();
    float       max  = bp->getMaxVal();

    std::cout << "Creating EPICS numeric parameter..." << std::endl;
    std::cout << "EPICS parameter name = " << name << std::endl;
    std::cout << "EPICS parameter Mode = " << mode << std::endl;

    int index;
    createParam(name.c_str(), asynParamFloat64, &index);

    std::cout << "Parameter '" << name << "' created. Index = " << index << std::endl;

    boardParameterNumericList.insert( std::make_pair<int, BoardParameterNumeric>(index, bp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT=" << portName_;
        dbParamsLocal << ",R=" << name;
        dbParamsLocal << ",PARAM=" << name;
        dbParamsLocal << ",DESC=" << name;
        dbParamsLocal << ",EGU=" << egu;
        dbParamsLocal << ",LOPR=" << min;
        dbParamsLocal << ",HOPR=" << max;
        dbParamsLocal << ",SCAN=1 second";

        std::cout << "Loading EPICS record..." << std::endl;

        std::cout << "Loading analog record..." << std::endl;
        dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str()); 
    }
}

void CAENHVAsyn::createBoardParamOnOff(BoardParameterOnOff bp)
{
    bool loadRecord = true;

    std::string name     = bp->getEpicsParam();
    std::string mode     = bp->getMode();
    std::string onLabel  = bp->getOnState();
    std::string offLabel = bp->getOffState();

    std::cout << "Creating EPICS OnOff parameter..." << std::endl;
    std::cout << "EPICS parameter name = " << name << std::endl;
    std::cout << "EPICS parameter Mode = " << mode << std::endl;

    int index;
    createParam(name.c_str(), asynParamUInt32Digital, &index);

    std::cout << "Parameter '" << name << "' created. Index = " << index << std::endl;

    boardParameterOnOffList.insert( std::make_pair<int, BoardParameterOnOff>(index, bp) );

    if (loadRecord)
    {
        std::stringstream dbParamsLocal;

        // Create list of paramater to pass to the  dbLoadRecords function
        dbParamsLocal.str("");
        dbParamsLocal << "PORT=" << portName_;
        dbParamsLocal << ",R=" << name;
        dbParamsLocal << ",PARAM=" << name;
        dbParamsLocal << ",DESC=" << name;
        dbParamsLocal << ",ZNAM=" << onLabel;
        dbParamsLocal << ",ONAM=" << offLabel;
        dbParamsLocal << ",SCAN=1 second";

        std::cout << "Loading EPICS record..." << std::endl;

        std::cout << "Loading analog record..." << std::endl;
        dbLoadRecords("db/bi.template", dbParamsLocal.str().c_str());
    }
}

//void CAENHVAsyn::createBoardParam(const BoardParameter& bp)
//{
//    bool loadRecord = true;
//
//    std::string name = bp->getEpicsParam();
//    std::string mode = bp->getMode();
//    std::string type = bp->getType();
//
//    std::cout << "Creating EPICS parameter..." << std::endl;
//    std::cout << "EPICS parameter name = " << name << std::endl;
//    std::cout << "EPICS parameter Mode = " << mode << std::endl;
//    std::cout << "EPICS parameter Type = " << type << std::endl;
//
//    asynParamType paramType;
//    if (!type.compare("Numeric"))
//    {
//        paramType = asynParamFloat64;
//        std::cout << "Creating Double type parameter..." << std::endl;
//        
//    }
//    else if (!type.compare("OnOff"))
//    {
//        paramType = asynParamOctet;
//        std::cout << "Creating String type parameter..." << std::endl;
//    }
//    else
//    { 
//        std::cout << "Unsupported type..." << std::endl;
//        return;
//    }
//
//    int index;
//    createParam(name.c_str(), paramType, &index);
//
//    boardParameterList.insert( std::make_pair<int, const BoardParameter&>(index, bp) ); 
//    //boardParameterList.insert( std::make_pair<int, int>(index, index+50) ); 
//
//    std::cout << "Parameter '" << name << "' (type = " << paramType << ") created. Index = " << index << std::endl;
//
//    if (loadRecord)
//    {
//        std::stringstream dbParamsLocal;
//
//        // Create list of paramater to pass to the  dbLoadRecords function
//        dbParamsLocal.str("");
//        dbParamsLocal << "PORT=" << portName_;
//        dbParamsLocal << ",R=" << name;
//        dbParamsLocal << ",PARAM=" << name;
//        dbParamsLocal << ",DESC=" << name;
//        dbParamsLocal << ",SCAN=1 second";
//
//        std::cout << "Loading EPICS record..." << std::endl;
//
//        if (!type.compare("Numeric"))
//        {
//            std::cout << "Loading analog record..." << std::endl;
//            dbLoadRecords("db/ai.template", dbParamsLocal.str().c_str()); 
//        }
//        else if (!type.compare("OnOff"))
//        {
//            std::cout << "Loading waveform of chars record..." << std::endl;
//        }
//
//    }
//}

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

    std::vector<Board> b = chassis->getBoards();

    for (std::vector<Board>::iterator boardIt = b.begin(); boardIt != b.end(); ++boardIt)
    {
        std::vector<BoardParameterNumeric> pn = boardIt->getBoardParameterNumerics();
        std::cout << "Number of Numeric Properties = " << pn.size() << std::endl;
        
        for (std::vector<BoardParameterNumeric>::iterator paramIt = pn.begin(); paramIt != pn.end(); ++paramIt)
            createBoardParamNumeric(*paramIt);

        std::vector<BoardParameterOnOff> po = boardIt->getBoardParameterOnOffs();
        std::cout << "Number of OnOff Properties = " << po.size() << std::endl;
        
        for (std::vector<BoardParameterOnOff>::iterator paramIt = po.begin(); paramIt != po.end(); ++paramIt)
            createBoardParamOnOff(*paramIt);
    }
//    std::cout << "First element = " << chassis->getFirstSProps()->first << " = " << chassis->getFirstSProps()->second << std::endl;
//
//   std::vector<BoardParameter> bp0 = chassis->getBoara0dParameters();
//   for (std::vector<BoardParameter>::iterator it = bp0.begin(); it != bp0.end(); ++it)
//   {
//       //std::string ep = (*it)->getEpicsParam();
//       //std::cout << "Board EPICS parameter = " << ep << std::endl;
//
//       //(*it)->printInfo();
//       createBoardParam(*it);
//   }
}

//int CAENHVAsyn::LoadRecord(int regType, const recordParams& rp, const std::stringstream& dbParams)
//{
//    int paramIndex;
//    std::stringstream dbParamsLocal;
//
//    // Create list of paramater to pass to the  dbLoadRecords function
//    dbParamsLocal.str("");
//    dbParamsLocal << "PORT=" << portName_;
//    dbParamsLocal << ",ADDR=" << regType;
//    dbParamsLocal << ",R=" << rp.recName;
//    dbParamsLocal << ",PARAM=" << rp.paramName;
//    dbParamsLocal << ",DESC=" << rp.recDesc;
//    dbParamsLocal << dbParams.str();
//
//    // Create the asyn paramater
//    createParam(regType, rp.paramName.c_str(), rp.paramType, &paramIndex);
//
//    // Create the record
//    dbLoadRecords(rp.recTemplate.c_str(), dbParamsLocal.str().c_str());
//
//    // Write the record name to the PV list file
//    //pvDumpFile->write("%s%*s", rp.recName.c_str(), recordNameLenMax - rp.recName.size() + 4, "");
//    //pvDumpFile->write("# %s (%s)\n", getNameWithoutLeafIndexes(p).c_str(), regInterfaceTypeNames[regType]);
//
//    // Incrfement the number of created records
//    //++recordCount;
//
//    // Return the parameter index
//    return paramIndex;
//}

asynStatus CAENHVAsyn::readFloat64(asynUser *pasynUser, epicsFloat64 *value)
{
    static const char *functionName = "readFloat64";
    int function = pasynUser->reason;
    int status = 0;

    int addr;
    this->getAddress(pasynUser, &addr);

    const char *name;
    getParamName(addr, function, &name);

//    printf("Function = %s, addr = %d, function = %d, name = %s\n", functionName, addr, function, name);
    std::map<int, BoardParameterNumeric>::iterator it = boardParameterNumericList.find(function);

    if (it != boardParameterNumericList.end())
        *value = it->second->getVal();

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
