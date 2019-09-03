/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : board_parameter_property.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-30
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

#include "board_parameter_property.h"

BoardParameterProperty::BoardParameterProperty(int h, std::size_t s, const std::string& p)
:
    handle(h),
    slot(s),
    param(p)
{
}

BoardParameterPropertyNumeric::BoardParameterPropertyNumeric(int h, std::size_t s, const std::string& p)
:
    BoardParameterProperty(h, s, p)
{
    type = "Numeric";

   float temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Minval", &temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   minVal = temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Maxval", &temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    maxVal = temp;

   uint16_t u;
   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Unit", &u ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));
 
   uint8_t e;
   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Exp", &e ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   units = getUnits(u, e);

    unsigned short tempSlot = slot;
    if ( CAENHV_GetBdParam(handle, 1, &tempSlot, param.c_str(), &temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    value = temp;
}

std::string BoardParameterPropertyNumeric::getUnits(uint16_t units, uint8_t exp)
{
    std::string s("");

    switch(exp)
    {
        case 6:
            s = "M";
            break;
            
        case 3:
            s = "k";
            break;
            
        case -3:
            s = "m";
            break;
            
        case -6:
            s = "u";
            break;
    }

    switch(units)
    {
        case PARAM_UN_NONE:
            return "";

        case PARAM_UN_AMPERE:
            s += "A";
            break;

        case PARAM_UN_VOLT:
            s += "V";
            break;

        case PARAM_UN_WATT:
            s += "W";
            break;

        case PARAM_UN_CELSIUS:
            s += "C";
            break;

        case PARAM_UN_HERTZ:
            s += "Hz";
            break;

        case PARAM_UN_BAR:
            s += "Bar";
            break;

        case PARAM_UN_VPS:
            s += "VPS";
            break;

        case PARAM_UN_SECOND:
            s += "s";
            break;

        case PARAM_UN_RPM:
            s += "rpm";
            break;

        case PARAM_UN_COUNT:
            s += "counts";
            break;

        case PARAM_UN_BIT:
            s += "bit";
            break;

        default:
            return "???";
    }

    return s;
}

void BoardParameterPropertyNumeric::printInfo() const
{
    std::cout << "      Type: " << type << std::endl;
    std::cout << "      Properties:" << std::endl;
    std::cout << "        - Minval = " << minVal << std::endl;
    std::cout << "        - Maxval = " << maxVal << std::endl;
    std::cout << "        - Units  = " << units.c_str() << std::endl;
    std::cout << "        - Value  = " << value << std::endl;
}

BoardParameterPropertyOnoff::BoardParameterPropertyOnoff(int h, std::size_t s, const std::string& p)
:
    BoardParameterProperty(h, s, p)
{
    type = "Numeric";

   char temp[30]; 
   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Onstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   onState = temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Offstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    offState = temp;

    uint16_t temp_slot = slot;
    if ( CAENHV_GetBdParam(handle, 1, &temp_slot, param.c_str(), temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    value = temp;
}

void BoardParameterPropertyOnoff::printInfo() const
{
    std::cout << "      Type: " << type << std::endl;
    std::cout << "      Properties:" << std::endl;
    std::cout << "        - On state  = " << onState  << std::endl;
    std::cout << "        - Off state = " << offState << std::endl;
    std::cout << "        - Value     = " << value << std::endl;
}
