#ifndef CHASSIS_H
#define CHASSIS_H

/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : chassis.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-20
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

#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <iostream>

#include "CAENHVWrapper.h"
#include "common.h"
#include "board.h"
#include "system_property.h"

class SysProp;
template<typename T>
class SysPropT;

class Chassis
{
public:
    Chassis(int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password);
    ~Chassis();

    void printInfo() const;

    std::vector<SystemPropertyU8>     getSystemPropertyU8s()     { return systemPropertyU8s;     };  
    std::vector<SystemPropertyU16>    getSystemPropertyU16s()    { return systemPropertyU16s;    };  
    std::vector<SystemPropertyU32>    getSystemPropertyU32s()    { return systemPropertyU32s;    };  
    std::vector<SystemPropertyI16>    getSystemPropertyI16s()    { return systemPropertyI16s;    };  
    std::vector<SystemPropertyI32>    getSystemPropertyI32s()    { return systemPropertyI32s;    };  
    std::vector<SystemPropertyFloat>  getSystemPropertyFloats()  { return systemPropertyFloats;  };  
    std::vector<SystemPropertyString> getSystemPropertyStrings() { return systemPropertyStrings; };

    std::vector<Board> getBoards() { return boards; };

private:

    int  InitSystem(int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password) const;
    void GetPropList();
    void GetCrateMap();

    template <typename T>
    void printProperties(const std::string& type, const T& pv) const;

    int handle;

    // Number of slot in the crate
    std::size_t numSlots;

    // Slots in the crate
    std::vector<Board> boards;

    // Chassis properties
    std::vector<SystemPropertyU8>     systemPropertyU8s;
    std::vector<SystemPropertyU16>    systemPropertyU16s;
    std::vector<SystemPropertyU32>    systemPropertyU32s;
    std::vector<SystemPropertyI16>    systemPropertyI16s;
    std::vector<SystemPropertyI32>    systemPropertyI32s;
    std::vector<SystemPropertyFloat>  systemPropertyFloats;
    std::vector<SystemPropertyString> systemPropertyStrings;
};

#endif
