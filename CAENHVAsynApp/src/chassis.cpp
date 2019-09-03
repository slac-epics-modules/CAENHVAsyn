/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : chassis.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-30
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power Supplies Chassis Class
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

#include "chassis.h"

void Chassis::GetPropList()
{
    std::string functionName("GetPropList");

    unsigned short NumProp;
    char *PropNameList;
    CAENHVRESULT r =  CAENHV_GetSysPropList(handle, &NumProp, &PropNameList);

    std::stringstream retMessage;
    retMessage << "CAENHV_GetSysPropList: " << CAENHV_GetError(handle) << " (num. " << r << ")";

    printMessage(functionName, retMessage.str().c_str());

    if ( r != CAENHV_OK )
        return;

    char* p = PropNameList;


    for (std::size_t i(0); i < NumProp; ++i, p += strlen(p) + 1)
    {
        // Get Property info
        unsigned PropMode;
        unsigned PropType;
        if ( CAENHV_GetSysPropInfo(handle, p, &PropMode, &PropType) == CAENHV_OK )
        {
            switch( PropType )
            {
                case SYSPROP_TYPE_STR:
                    GetSysPropString(p);
                    break; 
                
                case SYSPROP_TYPE_REAL:
                    GetSysPropFloat(p);
                    break; 
                
                case SYSPROP_TYPE_UINT2:
                    GetSysPropU16(p);
                    break; 
                
                case SYSPROP_TYPE_UINT4:
                    GetSysPropU32(p);
                    break; 
                
                case SYSPROP_TYPE_INT2:
                    GetSysPropI16(p);
                    break; 
                
                case SYSPROP_TYPE_INT4:
                    GetSysPropI32(p);
                    break; 
                
                case SYSPROP_TYPE_BOOLEAN:
                    GetSysPropU8(p);
                    break; 
            }

        }
    }
       
    free(PropNameList);
}

void Chassis::GetSysPropFloat(char* p)
{
    float v;
    CAENHVRESULT r = CAENHV_GetSysProp(handle, p, &v);

    if ( r == CAENHV_OK || r == CAENHV_GETPROPNOTIMPL || r == CAENHV_NOTGETPROP )
    {
        fProps.insert(std::make_pair<std::string, float>(p, v));
    }
    else
    {
        std::cout << "Failed to get system property: " << p << std::endl;
        std::cout << CAENHV_GetError(handle) << std::endl;
        std::cout << std::endl;
    }
}

void Chassis::GetSysPropU16(char* p)
{
    uint16_t v;
    CAENHVRESULT r = CAENHV_GetSysProp(handle, p, &v);

    if ( r == CAENHV_OK || r == CAENHV_GETPROPNOTIMPL || r == CAENHV_NOTGETPROP )
    {
        u16Props.insert(std::make_pair<std::string, uint16_t>(p, v));
    }
    else
    {
        std::cout << "Failed to get system property: " << p << std::endl;
        std::cout << CAENHV_GetError(handle) << std::endl;
        std::cout << std::endl;
    }
}

void Chassis::GetSysPropU32(char* p)
{
    uint32_t v;
    CAENHVRESULT r = CAENHV_GetSysProp(handle, p, &v);

    if ( r == CAENHV_OK || r == CAENHV_GETPROPNOTIMPL || r == CAENHV_NOTGETPROP )
    {
        u32Props.insert(std::make_pair<std::string, uint32_t>(p, v));
    }
    else
    {
        std::cout << "Failed to get system property: " << p << std::endl;
        std::cout << CAENHV_GetError(handle) << std::endl;
        std::cout << std::endl;
    }
}

void Chassis::GetSysPropI16(char* p)
{
    int16_t v;
    CAENHVRESULT r = CAENHV_GetSysProp(handle, p, &v);

    if ( r == CAENHV_OK || r == CAENHV_GETPROPNOTIMPL || r == CAENHV_NOTGETPROP )
    {
        i16Props.insert(std::make_pair<std::string, int16_t>(p, v));
    }
    else
    {
        std::cout << "Failed to get system property: " << p << std::endl;
        std::cout << CAENHV_GetError(handle) << std::endl;
        std::cout << std::endl;
    }
}

void Chassis::GetSysPropI32(char* p)
{
    int32_t v;
    CAENHVRESULT r = CAENHV_GetSysProp(handle, p, &v);

    if ( r == CAENHV_OK || r == CAENHV_GETPROPNOTIMPL || r == CAENHV_NOTGETPROP )
    {
        i32Props.insert(std::make_pair<std::string, int32_t>(p, v));
    }
    else
    {
        std::cout << "Failed to get system property: " << p << std::endl;
        std::cout << CAENHV_GetError(handle) << std::endl;
        std::cout << std::endl;
    }
}

void Chassis::GetSysPropU8(char* p)
{
    uint8_t v;
    CAENHVRESULT r = CAENHV_GetSysProp(handle, p, &v);

    if ( r == CAENHV_OK || r == CAENHV_GETPROPNOTIMPL || r == CAENHV_NOTGETPROP )
    {
        u8Props.insert(std::make_pair<std::string, uint8_t>(p, v));
    }
    else
    {
        std::cout << "Failed to get system property: " << p << std::endl;
        std::cout << CAENHV_GetError(handle) << std::endl;
        std::cout << std::endl;
    }
}

void Chassis::GetSysPropString(char* p)
{
    char aux[4096];
    CAENHVRESULT r = CAENHV_GetSysProp(handle, p, aux);

    if ( r == CAENHV_OK || r == CAENHV_GETPROPNOTIMPL || r == CAENHV_NOTGETPROP )
    {
        sProps.insert(std::make_pair<std::string, std::string>(p, aux));
    }
    else
    {
        std::cout << "Failed to get system property: " << p << std::endl;
        std::cout << CAENHV_GetError(handle) << std::endl;
        std::cout << std::endl;
    }
}

void Chassis::GetCrateMap()
{
    // Get Crate Map
    std::string functionName("GetCrateMap");

    unsigned short NrOfSlot;
    unsigned short *NrOfChList;
    char *ModelList;
    char *DescriptionList;
    unsigned short *SerNumList;
    unsigned char *FmwRelMinList;
    unsigned char *FmwRelMaxList;

    CAENHVRESULT r = CAENHV_GetCrateMap(handle, &NrOfSlot, &NrOfChList, &ModelList, &DescriptionList, &SerNumList, &FmwRelMinList, &FmwRelMaxList);

    std::stringstream retMessage;
    retMessage << "CAENHV_GetCrateMap: " << CAENHV_GetError(handle) << " (num. " << r << ")";

    printMessage(functionName, retMessage.str().c_str());

    if ( r != CAENHV_OK )
        return;


    numSlots = NrOfSlot;
    boards.reserve(numSlots);
    char *m = ModelList, *d = ModelList;

    for (std::size_t i(0); i < NrOfSlot; ++i, m += strlen(m) + 1, d += strlen(d) + 1)
    {
        if ( *m != '\0' )
        {
            std::stringstream sn, fw;
    
            // Process the serial number
            sn.str("");
            sn << SerNumList[i];

            // Process the firmware release number
            fw.str("");
            fw << unsigned(FmwRelMaxList[i]) << "." << unsigned(FmwRelMinList[i]);

            // Create a new Slot object and add it to the vector
            boards.emplace_back(handle, i, m, d, NrOfChList[i], sn.str(), fw.str());
        }
    }

    // Deallocate memory (Use RAII in the future for this)
    free(NrOfChList);
    free(ModelList);
    free(DescriptionList);
    free(SerNumList);
    free(FmwRelMinList);
    free(FmwRelMaxList);
}

Chassis::Chassis(int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password)
:
  handle(-1)
{
    handle = InitSystem(systemType, ipAddr, userName, password);
    GetPropList();
    GetCrateMap();
}

Chassis::~Chassis()
{
}

int Chassis::InitSystem(int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password) const
{
    int h;
    std::string functionName("initSystem");

    CAENHVRESULT r = CAENHV_InitSystem( static_cast<CAENHV_SYSTEM_TYPE_t>(systemType), 
                                        LINKTYPE_TCPIP, 
                                        const_cast<void*>( static_cast<const void*>( ipAddr.c_str() ) ),
                                        userName.c_str(),
                                        password.c_str(), 
                                        &h );

    std::stringstream retMessage; 
    retMessage << "CAENHV_InitSystem: " << CAENHV_GetError(h) << " (num. " << r << ")";

    printMessage(functionName, retMessage.str());

    if( r != CAENHV_OK )
        throw std::runtime_error(retMessage.str().c_str());

    return h;
}


void Chassis::printInfo() const
{
    std::cout << "===========================" << std::endl;;
    std::cout << "Chassis object information:" << std::endl;;
    std::cout << "===========================" << std::endl;;
    std::cout << "  handle = " << handle << std::endl;
    std::cout << "  Number of slots: " << numSlots << std::endl;

    std::cout << std::endl;
    std::cout << "  Properties:" << std::endl;;
    std::cout << "  ---------------------------" << std::endl;

    printProperties("float",    fProps);
    printProperties("uint16_t", u16Props);
    printProperties("uint32_t", u32Props);
    printProperties("int16_t",  i16Props);
    printProperties("int32_t",  i32Props);
    printProperties("uint8_t",  u8Props);
    printProperties("string",   sProps);

    std::cout << std::endl;
    std::cout << "  Board information: " << std::endl;
    std::cout << "  ---------------------------" << std::endl;
    std::cout << "    Number of boards: " << boards.size() << std::endl;
    for (std::vector<Board>::const_iterator it = boards.begin(); it != boards.end(); ++it)
        it->printInfo();

    std::cout << "===========================" << std::endl;;
    std::cout << std::endl;
}

template <typename T>
void Chassis::printProperties(const std::string& type, const T& pv) const
{
    std::size_t n(pv.size());
    std::cout << "    Number of properties of type " << type << ": " << n << std::endl;
    if (n)
        for (auto it = pv.begin(); it != pv.end(); ++it)
            std::cout << "    - " << it->first << " = " << it->second << std::endl;
}
