#ifndef BOARD_PARAMETER_2_H
#define BOARD_PARAMETER_2_H

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


// Base class
class IBoardParameter;

// Derivated, template calss
template <typename TypePolicy>
class IBoardParameterTemplate;

// Policy classes 
class NumericParameterPolicy;
class OnOffParameterPolicy;


// Shared pointer types
typedef std::shared_ptr< IBoardParameter                                                    > BoardParameter2;
typedef std::shared_ptr< IBoardParameterTemplate< NumericParameterPolicy > > BoardParameterNumeric;
typedef std::shared_ptr< IBoardParameterTemplate< OnOffParameterPolicy   > > BoardParameterOnOff;


class BoardParameterBase
{
public: 
    BoardParameterBase(int h, std::size_t s, const std::string&  p, uint32_t m) : handle(h), slot(s), param(p), mode(m) {};
    virtual ~BoardParameterBase() {};

protected:
    int         handle;
    std::size_t slot;
    std::string param;
    uint32_t    mode;
    std::string type;
};

class IBoardParameter
{
public:
    IBoardParameter() {};
    virtual ~IBoardParameter() {};

    // Factory method
    static BoardParameter2 create(int h, std::size_t s, const std::string&  p);

    virtual void printInfo() = 0;
};

// Derivate, template class. It uses policies.
template <class TypePolicy>
class IBoardParameterTemplate : public IBoardParameter, TypePolicy
{
public:
    IBoardParameterTemplate(int h, std::size_t s, const std::string&  p, uint32_t m) : IBoardParameter(), TypePolicy(h, s, p, m)  {};
    ~IBoardParameterTemplate() {};

   virtual void printInfo() { TypePolicy::printInfo(); };

private:
    using TypePolicy::getVal;
    using TypePolicy::setVal;
};

// Policies

class NumericParameterPolicy : public BoardParameterBase
{
public:
    NumericParameterPolicy(int h, std::size_t s, const std::string&  p, uint32_t m); 
    ~NumericParameterPolicy() {};

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

class  OnOffParameterPolicy : public BoardParameterBase
{
public:
    OnOffParameterPolicy(int h, std::size_t s, const std::string&  p, uint32_t m);
    ~OnOffParameterPolicy() {};

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
