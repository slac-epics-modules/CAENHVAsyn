#ifndef BOARD_PARAMETER_H
#define BOARD_PARAMETER_H

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
#include <algorithm>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <iostream>

#include "CAENHVWrapper.h"
#include "common.h"



class BoardParameterBase;
class IBoardParameterNumeric;
class IBoardParameterOnOff;

// Shared pointer types
typedef std::shared_ptr< IBoardParameterNumeric > BoardParameterNumeric;
typedef std::shared_ptr< IBoardParameterOnOff   > BoardParameterOnOff;


class BoardParameterBase
{
public: 
    BoardParameterBase(int h, std::size_t s, const std::string&  p, uint32_t m) : handle(h), slot(s), param(p), mode(m) 
    {
        // Generate the EPICS parameter name
        // - Remove white spaces from the parameter name
        std::string tempParamName(param);
        tempParamName.erase(std::remove_if(tempParamName.begin(), tempParamName.end(), isspace), tempParamName.end());
        // - Convert parameter name to upper case
        std::transform(tempParamName.begin(), tempParamName.end(), tempParamName.begin(), ::toupper);
        // - Generate name as S<slot_number>_<parameter name, uppercase, without spaces>
        std::stringstream temp;
        temp.str("");
        temp << "S" << s << "_" << tempParamName;
        epicsParam = temp.str();
    };
    virtual ~BoardParameterBase() {};

    std::string getMode()       { return modeStr;    }; 
    std::string getEpicsParam() { return epicsParam; };

protected:
    int         handle;
    std::size_t slot;
    std::string param;
    uint32_t    mode;
    std::string modeStr;
    std::string epicsParam;
};

class IBoardParameterNumeric : public BoardParameterBase
{
public:
    IBoardParameterNumeric(int h, std::size_t s, const std::string&  p, uint32_t m); 
    ~IBoardParameterNumeric() {};

    // Factory method
    static BoardParameterNumeric create(int h, std::size_t s, const std::string&  p, uint32_t m);

    float       getMinVal() const { return minVal; };
    float       getMaxVal() const { return maxVal; };
    std::string getUnits()  const { return units;  };

    virtual void printInfo();

    float getVal();
    void setVal(float v);

private:
    float       minVal;
    float       maxVal;
    std::string units;
    float       value;
};

class  IBoardParameterOnOff : public BoardParameterBase
{
public:
    IBoardParameterOnOff(int h, std::size_t s, const std::string&  p, uint32_t m);
    ~IBoardParameterOnOff() {};

    // Factory method
    static BoardParameterOnOff create(int h, std::size_t s, const std::string&  p, uint32_t m);

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
