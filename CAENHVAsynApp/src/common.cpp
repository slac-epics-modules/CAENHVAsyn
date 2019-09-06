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
