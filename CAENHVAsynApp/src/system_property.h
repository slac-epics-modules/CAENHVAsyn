#ifndef SYSTEM_PROPERTY_H
#define SYSTEM_PROPERTY_H

/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : system_property.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-09-04
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power supplies System Property Class
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
#include <memory>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <iostream>

#include "CAENHVWrapper.h"
#include "common.h"


class ISystemPropertyFloat;
class ISystemPropertyU16;
class ISystemPropertyU32;
class ISystemPropertyI16;
class ISystemPropertyI32;
class ISystemPropertyU8;
class ISystemPropertyString;

typedef std::shared_ptr< ISystemPropertyFloat  > SystemPropertyFloat;
typedef std::shared_ptr< ISystemPropertyU16    > SystemPropertyU16;
typedef std::shared_ptr< ISystemPropertyU32    > SystemPropertyU32;
typedef std::shared_ptr< ISystemPropertyI16    > SystemPropertyI16;
typedef std::shared_ptr< ISystemPropertyI32    > SystemPropertyI32;
typedef std::shared_ptr< ISystemPropertyU8     > SystemPropertyU8;
typedef std::shared_ptr< ISystemPropertyString > SystemPropertyString;

class SystemPropertyBase
{
public:
    SystemPropertyBase(int h, const std::string&  p, uint32_t m);
    virtual ~SystemPropertyBase() {};

    std::string getMode()            { return modeStr;    };
    std::string getEpicsParamName()  { return epicsParamName;  };
    std::string getEpicsRecordName() { return epicsRecordName; };
    std::string getEpicsDesc()       { return epicsDesc;       };

    void printInfo() const;

protected:
    int         handle;
    std::string prop;
    uint32_t    mode;
    std::string modeStr;
    std::string epicsParamName;
    std::string epicsRecordName;
    std::string epicsDesc;
};

class ISystemPropertyString : public SystemPropertyBase
{
public:
    ISystemPropertyString(int h, const std::string&  p, uint32_t m);
    ~ISystemPropertyString() {};

    // Factory method
    static SystemPropertyString create(int h, const std::string&  p, uint32_t m);

    std::string getVal();
    void        setVal(const std::string& v);
};

class ISystemPropertyU8 : public SystemPropertyBase
{
public:
    ISystemPropertyU8(int h, const std::string&  p, uint32_t m);
    ~ISystemPropertyU8() {};

    // Factory method
    static SystemPropertyU8 create(int h, const std::string&  p, uint32_t m);

    uint8_t getVal();
    void     setVal(const uint8_t& v);
};

class ISystemPropertyU16 : public SystemPropertyBase
{
public:
    ISystemPropertyU16(int h, const std::string&  p, uint32_t m);
    ~ISystemPropertyU16() {};

    // Factory method
    static SystemPropertyU16 create(int h, const std::string&  p, uint32_t m);

    uint16_t getVal();
    void     setVal(const uint16_t& v);
};

class ISystemPropertyU32 : public SystemPropertyBase
{
public:
    ISystemPropertyU32(int h, const std::string&  p, uint32_t m);
    ~ISystemPropertyU32() {};

    // Factory method
    static SystemPropertyU32 create(int h, const std::string&  p, uint32_t m);

    uint32_t getVal();
    void     setVal(const uint16_t& v);
};

class ISystemPropertyI16 : public SystemPropertyBase
{
public:
    ISystemPropertyI16(int h, const std::string&  p, uint32_t m);
    ~ISystemPropertyI16() {};

    // Factory method
    static SystemPropertyI16 create(int h, const std::string&  p, uint32_t m);

    int16_t getVal();
    void    setVal(const uint16_t& v);
};

class ISystemPropertyI32 : public SystemPropertyBase
{
public:
    ISystemPropertyI32(int h, const std::string&  p, uint32_t m);
    ~ISystemPropertyI32() {};

    // Factory method
    static SystemPropertyI32 create(int h, const std::string&  p, uint32_t m);

    int32_t getVal();
    void    setVal(const uint16_t& v);
};

class ISystemPropertyFloat : public SystemPropertyBase
{
public:
    ISystemPropertyFloat(int h, const std::string&  p, uint32_t m);
    ~ISystemPropertyFloat() {};

    // Factory method
    static SystemPropertyFloat create(int h, const std::string&  p, uint32_t m);

    float getVal();
    void  setVal(const float& v);
};

#endif
