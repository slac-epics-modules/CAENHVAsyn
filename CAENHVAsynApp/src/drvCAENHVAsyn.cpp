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
    handle(-1)
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
                                          &handle );

    std::stringstream retMessage; 
    retMessage << "CAENHV_InitSystem: " << CAENHV_GetError(handle) << " (num. " << ret << ")";

    if( ret != CAENHV_OK )
        throw std::runtime_error(retMessage.str().c_str());

    std::cout << "Success!" << std::endl;
    std::cout << retMessage.str() << std::endl;

    // Get System Property List
    std::cout << std::endl;
    std::cout << "Calling CAENHV_GetSysPropList...." << std::endl;
    unsigned short NumProp;
    char *PropNameList;

    ret = CAENHV_GetSysPropList(handle, &NumProp, &PropNameList);

    retMessage.str("");
    retMessage << "CAENHV_GetSysPropList: " << CAENHV_GetError(handle) << " (num. " << ret << ")";

    if( ret != CAENHV_OK )
        throw std::runtime_error(retMessage.str().c_str());

    std::cout << "Success!" << std::endl;
    std::cout << retMessage.str() << std::endl;

    std::cout << "Property List:" << std::endl;
    std::cout << std::left << std::setw(20) << std::setfill(' ') << "Name";
    std::cout << std::left << std::setw(10) << std::setfill(' ') << "Mode";
    std::cout << std::left << std::setw(10) << std::setfill(' ') << "Type";
    std::cout << std::left << std::setw(10) << std::setfill(' ') << "Value";
    std::cout << std::endl;

    char* p = PropNameList;
    for (std::size_t i(0); i < NumProp; ++i, p += strlen(p) + 1)
    {

        // Print property name
        std::cout << std::left << std::setw(20) << std::setfill(' ') << p;

        // Get Property info
        unsigned PropMode;
        unsigned PropType;
        CAENHVRESULT ret1 = CAENHV_GetSysPropInfo(handle, p, &PropMode, &PropType);

        if ( ret1 != CAENHV_OK )
        {
            retMessage.str("");
            retMessage << "Error: " << CAENHV_GetError(handle) << " (num. " << ret << ")";
            std::cout << std::left << std::setw(20) << std::setfill(' ') << retMessage.str();
        }
	else
        {
            std::cout << std::left << std::setw(10) << std::setfill(' ') << unsigned(PropMode);
            std::cout << std::left << std::setw(10) << std::setfill(' ') << unsigned(PropType);
        }

        // Get Property value
        union   {
            char            cBuff[4096];
            float           fBuff;
            unsigned short  ui2Buff;
            unsigned long   ui4Buff;
            short           i2Buff;
            long            i4Buff;
            unsigned        bBuff;
        } app;

        CAENHVRESULT ret2 = CAENHV_GetSysProp(handle, p, &app);

        if ( ret2 != CAENHV_OK && ret2 != CAENHV_GETPROPNOTIMPL && ret2 != CAENHV_NOTGETPROP )
        {
            retMessage.str("");
            retMessage << "Error: " << CAENHV_GetError(handle) << " (num. " << ret << ")";
            std::cout << std::left << std::setw(20) << std::setfill(' ') << retMessage.str();
        }
        else
        {
            std::cout << std::left << std::setw(10) << std::setfill(' ');
            switch( PropType )
            {
                case SYSPROP_TYPE_STR:
                    std::cout << app.cBuff;
                    break;
            
                case SYSPROP_TYPE_REAL:
                    std::cout << app.fBuff;
                    break;
            
                case SYSPROP_TYPE_UINT2:
                    std::cout << app.ui2Buff;
                    break;
            
                case SYSPROP_TYPE_UINT4:
                    std::cout << app.ui4Buff;
                    break;
            
                case SYSPROP_TYPE_INT2:
                    std::cout << app.i2Buff;
                    break;
            
                case SYSPROP_TYPE_INT4:
                    std::cout << app.i4Buff;
                    break;
            
                case SYSPROP_TYPE_BOOLEAN:
                    std::cout << app.bBuff;
                    break;
            }

        }

        std::cout << std::endl;

    }

    // Deallocate memory (Use RAII in the future for this)
    free(PropNameList);

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
    ret = CAENHV_GetCrateMap(handle, &NrOfSlot, &NrOfChList, &ModelList, &DescriptionList, &SerNumList, &FmwRelMinList, &FmwRelMaxList);

    retMessage.str("");
    retMessage << "CAENHV_GetCrateMap: " << CAENHV_GetError(handle) << " (num. " << ret << ")";

    if( ret != CAENHV_OK )
        throw std::runtime_error(retMessage.str().c_str());

    std::cout << "Success!" << std::endl;
    std::cout << retMessage.str() << std::endl;

    std::cout << "Create Map:" << std::endl;
    char *m = ModelList, *d = ModelList;
    for (std::size_t i(0); i < NrOfSlot; ++i, m += strlen(m) + 1, d += strlen(d) + 1)
    {
        std::cout << "Board " << std::setfill('0')  << std::setw(2) << i << ": " << std::setfill(' ');
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

    // Get Board Parameter Info
    std::cout << std::endl;
    char *ParNameList;
    std::cout << "Calling CAENHV_GetBdParamInfo...." << std::endl;
    ret = CAENHV_GetBdParamInfo(handle, 0, &ParNameList);

    if( ret != CAENHV_OK )
    {
        retMessage.str("");
        retMessage << "CAENHV_GetCrateMap: " << CAENHV_GetError(handle) << " (num. " << ret << ")";
        std::cout << retMessage.str() << std::endl;
    }
    else
    {
        char (*p)[MAX_PARAM_NAME];
        p = (char (*)[MAX_PARAM_NAME])ParNameList;

        for (std::size_t i(0); p[i][0]; ++i)
        {
            std::cout << "Property name: " << p[i] << std::endl;

            //typedef struct ParPropTag
            //{
            //    unsigned long   Type, Mode;
            //    float           MinVal, MaxVal;
            //    unsigned short  Unit;
            //    short           Exp;
            //    char            OnState[30], OffState[30];
            //} ParProp;

            //ParProp pp;
            unsigned long Type, Mode;
            CAENHVRESULT ret1 = CAENHV_GetBdParamProp(handle, 0, p[i], "Type", &Type);
   
            std::cout << "Type = ";
            if ( ret1 != CAENHV_OK )
                std::cout << "Error: " << CAENHV_GetError(handle) << " (num. " << ret1 << ")" << std::endl;
            else
                std::cout << unsigned(Type) << std::endl;

            ret1 = CAENHV_GetBdParamProp(handle, 0, p[i], "Mode", &Mode);

            std::cout << "Mode = ";
            if ( ret1 != CAENHV_OK )
                std::cout << "Error: " << CAENHV_GetError(handle) << " (num. " << ret1 << ")" << std::endl;
            else
                std::cout << unsigned(Mode) << std::endl;

            switch(Type)
            {
                case PARAM_TYPE_NUMERIC:
                    {
                        std::vector<std::string> eppl ( {"Minval", "Maxval"} );

                        for (std::vector<std::string>::iterator it = eppl.begin(); it != eppl.end(); ++it)
                        {
                            float f;
                            ret1 = CAENHV_GetBdParamProp(handle, 0, p[i], it->c_str(), &f) != CAENHV_OK;
                            if ( ret1 != CAENHV_OK )
                                std::cout << "Error: " << CAENHV_GetError(handle) << " (num. " << ret1 << ")" << std::endl;
                            else
                                std::cout << *it << " = " << f << std::endl;
                        }

                        {
                            float val;
                            unsigned short* SlotList = (unsigned short*)malloc(1 *  sizeof(unsigned short));
                            SlotList[0] = 0;
                       
                            ret1 = CAENHV_GetBdParam(handle, 1, SlotList, p[i], &val);
                            if ( ret1 != CAENHV_OK )
                                std::cout << "Error: " << CAENHV_GetError(handle) << " (num. " << ret1 << ")" << std::endl;
                            else
                                std::cout << "Value = " << val << std::endl;
                        }

                        std::cout << std::endl;
                    }
                    break;
                case PARAM_TYPE_ONOFF:
                    {
                        std::vector<std::string> eppl ( {"Onstate", "Offstate"} );
                        for (std::vector<std::string>::iterator it = eppl.begin(); it != eppl.end(); ++it)
                        {
                            char c[30];
                            ret1 = CAENHV_GetBdParamProp(handle, 0, p[i], it->c_str(), c) != CAENHV_OK;
                            if ( ret1 != CAENHV_OK )
                                std::cout << "Error: " << CAENHV_GetError(handle) << " (num. " << ret1 << ")" << std::endl;
                            else
                                std::cout << *it << " = " << c << std::endl;
                        }

                        {
                            char val[30];
                            unsigned short* SlotList = (unsigned short*)malloc(1 *  sizeof(unsigned short));
                            SlotList[0] = 0;
                       
                            ret1 = CAENHV_GetBdParam(handle, 1, SlotList, p[i], val);
                            if ( ret1 != CAENHV_OK )
                                std::cout << "Error: " << CAENHV_GetError(handle) << " (num. " << ret1 << ")" << std::endl;
                            else
                                std::cout << "Value = " << val << std::endl;
                        }
                    }
                    break;
                case PARAM_TYPE_BDSTATUS:
                        {
                            unsigned val;
                            unsigned short* SlotList = (unsigned short*)malloc(1 *  sizeof(unsigned short));
                            SlotList[0] = 0;
                       
                            ret1 = CAENHV_GetBdParam(handle, 1, SlotList, p[i], &val);
                            if ( ret1 != CAENHV_OK )
                                std::cout << "Error: " << CAENHV_GetError(handle) << " (num. " << ret1 << ")" << std::endl;
                            else
                                std::cout << "Value = " << std::bitset<32>(val) << std::endl;
                        }
                    break;
                default:
                    break;
            }

        }
    }

    // Deallocate memory (Use RAII in the future for this)
    free(ParNameList);
 
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
