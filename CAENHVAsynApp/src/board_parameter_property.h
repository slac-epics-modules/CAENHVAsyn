#ifndef BOARD_PARAMETER_PROPERTY_H
#define BOARD_PARAMETER_PROPERTY_H

/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : board_parameter_property.h 
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-20
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power supplies Board Parameter Property Class
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
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <iostream>

#include "CAENHVWrapper.h"
#include "common.h"

class BoardParameterProperty
{
public:
    BoardParameterProperty(int h, std::size_t s, const std::string& p);
    virtual ~BoardParameterProperty() {};

    virtual void printInfo() const = 0;

protected:
    int         handle;
    std::size_t slot;
    std::string param;
    std::string type;
};

class BoardParameterPropertyNumeric : public BoardParameterProperty
{
public:
    BoardParameterPropertyNumeric(int h, std::size_t s, const std::string& p);
    virtual ~BoardParameterPropertyNumeric() {};

    void printInfo() const;

private:

    std::string getUnits(uint16_t units, uint8_t exp);

    float       minVal;
    float       maxVal;
    std::string units;
    float       value;
};

class BoardParameterPropertyOnoff : public BoardParameterProperty
{
public:
    BoardParameterPropertyOnoff(int h, std::size_t s, const std::string& p);
    virtual ~BoardParameterPropertyOnoff() {};

    void printInfo() const;

private:
    std::string onState;
    std::string offState;
    std::string value;
};

#endif
