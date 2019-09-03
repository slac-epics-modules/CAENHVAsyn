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
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <iostream>

#include "CAENHVWrapper.h"
#include "common.h"
#include "board_parameter_property.h"

class BoardParameter
{
public:
    BoardParameter(int h, std::size_t s, const std::string&  p);
    ~BoardParameter();

    void printInfo() const;

private:
    int                     handle;
    std::size_t             slot;
    std::string             param;
    uint32_t                type;
    uint32_t                mode; 
    BoardParameterProperty* boardParameterProperties;
};

#endif
