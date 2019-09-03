/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : board_parameter.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-30
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

#include "board_parameter.h"

BoardParameter::BoardParameter(int h, std::size_t s, const std::string& p)
:
    handle(h),
    slot(s),
    param(p),
    type(0),
    mode(0)
{
    // This should be a 'unsigned long'. type, which in this architecture is 'uint64_t'.
    // However, I was receiving random number on the upper 4 bytes, so I had to use an
    // 'uint32_t' data type instead.
    uint32_t aux;

    if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Type", &aux) != CAENHV_OK )
        throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    type = aux;

    if (CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Mode", &aux) != CAENHV_OK )
        throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    mode = aux;

    if (type == PARAM_TYPE_NUMERIC)
          boardParameterProperties = new BoardParameterPropertyNumeric(handle, slot, param.c_str());
    else if (type == PARAM_TYPE_ONOFF)
        boardParameterProperties = new BoardParameterPropertyOnoff(handle, slot, param.c_str());
}

BoardParameter::~BoardParameter()
{
}

void BoardParameter::printInfo() const
{
    std::cout << "      Name = " << param \
              << ", Type = "     << type \
              << ", Mode = "     << mode \
              << ", Handle = "   << handle \
              << ", Slot = "     << slot
              << std::endl;
              boardParameterProperties->printInfo();
              std::cout << std::endl;
}
