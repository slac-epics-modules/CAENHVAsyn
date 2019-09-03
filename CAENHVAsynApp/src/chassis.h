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

class SysProp;
template<typename T>
class SysPropT;

class Chassis
{
public:
    Chassis(int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password);
    ~Chassis();

    void printInfo() const;

private:

    int  InitSystem(int systemType, const std::string& ipAddr, const std::string& userName, const std::string& password) const;
    void GetPropList();
    void GetCrateMap();

    // Methods to extract system properties of each type
    void GetSysPropFloat(char* p);
    void GetSysPropU16(char* p);
    void GetSysPropU32(char* p);
    void GetSysPropI16(char* p);
    void GetSysPropI32(char* p);
    void GetSysPropU8(char* p);
    void GetSysPropString(char* p);

    template <typename T>
    void printProperties(const std::string& type, const T& pv) const;

    int handle;

    // Number of slot in the crate
    std::size_t numSlots;

    // Slots in the crate
    std::vector<Board> boards;

    // Chassis properties
    std::map< std::string, float        > fProps;
    std::map< std::string, uint16_t     > u16Props;
    std::map< std::string, uint32_t     > u32Props;
    std::map< std::string, int16_t      > i16Props;
    std::map< std::string, int32_t      > i32Props;
    std::map< std::string, uint8_t      > u8Props;
    std::map< std::string, std::string  > sProps;

    std::map< std::string, SysProp* > props;
};

#endif
