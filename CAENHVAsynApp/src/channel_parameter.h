#ifndef CHANNEL_PARAMETER_H
#define CHANNEL_PARAMETER_H

/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : board_parameter.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-20
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power supplies Board Parameter Class
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

#include "board_parameter.h"

// Base class
class IChannelParameter;

// Derivated, template calss
template <typename TypePolicy>
class IChannelParameterTemplate;

// Policy classes 
class ChNumericParameterPolicy;
class ChOnOffParameterPolicy;


// Shared pointer types
typedef std::shared_ptr< IChannelParameter                                     > ChannelParameter;
typedef std::shared_ptr< IChannelParameterTemplate< ChNumericParameterPolicy > > ChannelParameterNumeric;
typedef std::shared_ptr< IChannelParameterTemplate< ChOnOffParameterPolicy   > > ChannelParameterOnOff;


class ChannelParameterBase
{
public: 
    ChannelParameterBase(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m) : handle(h), slot(s), channel(c), param(p), mode(m) {};
    virtual ~ChannelParameterBase() {};

protected:
    int         handle;
    std::size_t slot;
    std::size_t channel;
    std::string param;
    uint32_t    mode;
    std::string type;
    std::string modeStr;
};

class IChannelParameter
{
public:
   IChannelParameter() {};
   virtual ~IChannelParameter() {};

   // Factory method
   static ChannelParameter create(int h, std::size_t s, std::size_t c, const std::string&  p);

   virtual void printInfo() = 0;
};

// Derivate, template class. It uses policies.
template <class TypePolicy>
class IChannelParameterTemplate : public IChannelParameter, TypePolicy
{
public:
    IChannelParameterTemplate(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m) : IChannelParameter(), TypePolicy(h, s, c, p, m)  {};
    ~IChannelParameterTemplate() {};

   virtual void printInfo() { TypePolicy::printInfo(); };

private:
    using TypePolicy::getVal;
    using TypePolicy::setVal;
};

// Policies

class ChNumericParameterPolicy : public ChannelParameterBase
{
public:
    ChNumericParameterPolicy(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m); 
    ~ChNumericParameterPolicy() {};

    float getMinVal()             const { return minVal; };
    float getMaxVal()             const { return maxVal; };
    const std::string& getUnits() const { return units;  };

    virtual void printInfo();

    float getVal();
    void setVal(float v);

private:
    float       minVal;
    float       maxVal;
    std::string units;
    float       value;
};

class  ChOnOffParameterPolicy : public ChannelParameterBase
{
public:
    ChOnOffParameterPolicy(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m);
    ~ChOnOffParameterPolicy() {};

    const std::string& getOnState()  const { return onState;  }; 
    const std::string& getOffState() const { return offState; }; 

    virtual void printInfo();

    std::string getVal();
    void setVal(const std::string& v);

private:
    std::string onState;
    std::string offState;
    std::string value;
};

#endif
