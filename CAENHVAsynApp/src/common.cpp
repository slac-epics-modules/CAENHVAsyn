/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : common.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-30
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power Supplies Common Functions
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

#include "common.h"

void printMessage(const std::string& f, const std::string& s)
{
    //printf("Driver '%s', port '%s', function '%s' : %s\n",
    //    CAENHVAsyn::driverName_.c_str(), CAENHVAsyn::portName_.c_str(), f.c_str(), s.c_str());
    printf("function '%s' : %s\n", f.c_str(), s.c_str());
}

std::string processParamName(std::string name)
{
    // Make a copy
    std::string temp(name);

    // Remove white spaces from the parameter name
    temp.erase(std::remove_if(temp.begin(), temp.end(), isspace), temp.end());

    // Convert parameter name to upper case
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

    return temp;
}

std::string processMode(uint32_t mode)
{
    if (mode == PARAM_MODE_WRONLY)
        return "WO";
    else if (mode == PARAM_MODE_RDONLY)
        return  "RO";
    else if (mode == PARAM_MODE_RDWR)
        return  "RW";
    else
        return  "?";
}

std::string processUnits(uint16_t units, int8_t exp)
{
    std::string temp_units;

    if (exp == 6)
        temp_units = "M";
    else if (exp == 3)
        temp_units = "k";
    else if (exp == -3)
        temp_units = "m";
    else if (exp == -6)
        temp_units = "u";

    if (units == PARAM_UN_NONE)
        temp_units = "";
    else if (units == PARAM_UN_AMPERE)
        temp_units += "A";
    else if (units == PARAM_UN_VOLT)
        temp_units += "V";
    else if (units == PARAM_UN_WATT)
        temp_units += "W";
    else if (units == PARAM_UN_CELSIUS)
        temp_units += "C";
    else if (units == PARAM_UN_HERTZ)
        temp_units += "Hz";
    else if (units == PARAM_UN_BAR)
        temp_units += "Bar";
    else if (units == PARAM_UN_VPS)
        temp_units += "VPS";
    else if (units == PARAM_UN_SECOND)
        temp_units += "s";
    else if (units == PARAM_UN_RPM)
        temp_units += "rpm";
    else if (units == PARAM_UN_COUNT)
        temp_units += "count";
    else if (units == PARAM_UN_BIT)
        temp_units += "mit";
    else
        temp_units =  "???";

    return temp_units;
}
