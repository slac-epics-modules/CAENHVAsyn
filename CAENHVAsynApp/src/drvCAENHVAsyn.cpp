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

//const std::string CAENHVAsyn::DriverName_ = "CAENHVAsyn";

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
    DriverName_("CAENHVAsyn"),
    portName_(portName),
    handler(-1)
{
    std::cout << "Initiliziting " << DriverName_ << "..." << std::endl;

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

    // CAENHV_InitSystem
    std::cout << std::endl;
    std::cout << "Calling CAENHV_InitSystem..." << std::endl;
    CAENHVRESULT ret = CAENHV_InitSystem( static_cast<CAENHV_SYSTEM_TYPE_t>(systemType), 
                                          LINKTYPE_TCPIP, const_cast<void*>( static_cast<const void*>( ipAddr.c_str() ) ),
                                          userName.c_str(),
                                          password.c_str(), 
                                          &handler );

    std::stringstream retMessage; 
    retMessage << "CAENHV_InitSystem: " << CAENHV_GetError(handler) << " (num. " << ret << ")";

    if( ret != CAENHV_OK )
        throw std::runtime_error(retMessage.str().c_str());

    std::cout << "Success!" << std::endl;
    std::cout << retMessage.str() << std::endl;

    // Get Crate Map
    std::cout << std::endl;
    std::cout << "Calling CAENHV_GetCrateMap...." << std::endl;
    unsigned short NrOfSlot;
    unsigned short *NrOfChList;
    char *ModelList;
    char *DescriptionList;
    unsigned short *SerNumList;
    unsigned char *FmwRelMinList;
    unsigned char *FmwRelMaxList;
    ret = CAENHV_GetCrateMap(handler, &NrOfSlot, &NrOfChList, &ModelList, &DescriptionList, &SerNumList, &FmwRelMinList, &FmwRelMaxList);

    retMessage.str("");
    retMessage << "CAENHV_GetCrateMap: " << CAENHV_GetError(handler) << " (num. " << ret << ")";

    if( ret != CAENHV_OK )
        throw std::runtime_error(retMessage.str().c_str());

    std::cout << "Success!" << std::endl;
    std::cout << retMessage.str() << std::endl;

    std::cout << "Create Map:" << std::endl;
    char *m = ModelList, *d = ModelList;
    for (std::size_t i(0); i < NrOfSlot; ++i, m += strlen(m) + 1, d += strlen(d) + 1)
    {
        std::cout << "Board " << std::setfill('0')  << std::setw(2) << i << ": ";
        if ( *m == '\0' )
            std::cout << "Not present." << std::endl;
        else
            std::cout << "Model: " << m << ", Description: " <<  d << ", Number of channels: " << unsigned(NrOfChList[i]) << ", Serial Number: " << unsigned(SerNumList[i]) << ", Firmware release: " << unsigned(FmwRelMaxList[i]) << "." << unsigned(FmwRelMinList[i]) << std::endl;
    }

    // Deallocate memory (Use RAII in the future for this)
    free(NrOfChList);
    free(ModelList);
    free(DescriptionList);
    free(SerNumList);
    free(FmwRelMinList);
    free(FmwRelMaxList);

    // Done
    std::cout << std::endl;
    std::cout << "Done initilizing " << DriverName_ << std::endl;
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
