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

BoardParameter2 IBoardParameter::create(int h, std::size_t s, const std::string&  p)
{
    uint32_t type, mode;

    if ( CAENHV_GetBdParamProp(h, s, p.c_str(), "Type", &type) != CAENHV_OK )
        throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(h)));

    if (CAENHV_GetBdParamProp(h, s, p.c_str(), "Mode", &mode) != CAENHV_OK )
        throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(h)));

    
    if (type == PARAM_TYPE_NUMERIC)
        return std::make_shared< IBoardParameterTemplate< NumericParameterPolicy  > >(h, s, p, mode);
    else if (type == PARAM_TYPE_ONOFF)
        return std::make_shared< IBoardParameterTemplate< OnOffParameterPolicy > >(h, s, p, mode);
    else
        throw std::runtime_error("Parameter type not  supported!");

}


NumericParameterPolicy::NumericParameterPolicy(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase(h, s, p, m)
{

   type = "Numeric";

   float temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Minval", &temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   minVal = temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Maxval", &temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   maxVal = temp;

   // Extract uints
   uint16_t u;
   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Unit", &u ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   uint8_t e;
   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Exp", &e ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    std::string temp_units;

    if (e == 6)
        temp_units = "M";
    else if (e == 3) 
        temp_units = "k";
    else if (e == -3) 
        temp_units = "m";
    else if (e == -6) 
        temp_units = "u";

    if (u == PARAM_UN_NONE)
        temp_units = "";
    else if (u == PARAM_UN_AMPERE)
        temp_units += "A";
    else if (u == PARAM_UN_VOLT)
        temp_units += "V";
    else if (u == PARAM_UN_WATT)
        temp_units += "W";
    else if (u == PARAM_UN_CELSIUS)
        temp_units += "C";
    else if (u == PARAM_UN_HERTZ)
        temp_units += "Hz";
    else if (u == PARAM_UN_BAR)
        temp_units += "Bar";
    else if (u == PARAM_UN_VPS)
        temp_units += "VPS";
    else if (u == PARAM_UN_SECOND)
        temp_units += "s";
    else if (u == PARAM_UN_RPM)
        temp_units += "rpm";
    else if (u == PARAM_UN_COUNT)
        temp_units += "count";
    else if (u == PARAM_UN_BIT)
        temp_units += "mit";
    else
        temp_units =  "???";

    units = temp_units;
}


float NumericParameterPolicy::getVal()
{
    if (mode == PARAM_MODE_WRONLY)
        return 0.0;

    float temp;
   
    uint16_t tempSlot = slot;
    if ( CAENHV_GetBdParam(handle, 1, &tempSlot, param.c_str(), &temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void NumericParameterPolicy::setVal(float v)
{
    if (mode == PARAM_MODE_RDONLY)
        return;

    uint16_t tempSlot = slot;
    if ( CAENHV_SetBdParam(handle, 1, &tempSlot, param.c_str(), &v) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));
}

void NumericParameterPolicy::printInfo()
{
    std::cout << "      Type: = " << type << std::endl;
    std::cout << "      Properties:" << std::endl;
    std::cout << "        - Minval = " << getMinVal() << std::endl;
    std::cout << "        - Maxval = " <<  getMaxVal() << std::endl;
    std::cout << "        - Units  = " << units.c_str() << std::endl;
    std::cout << "        - Value  = " << getVal() << std::endl;
    std::cout << std::endl;
}

    std::string s("");


OnOffParameterPolicy::OnOffParameterPolicy(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase(h, s, p, m)
{
   type = "OnOff";

   char temp[30];

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Onstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   onState = temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Offstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    offState = temp;

}

std::string OnOffParameterPolicy::getVal()
{
    if (mode == PARAM_MODE_WRONLY)
        return "";

    char temp[30];

    uint16_t temp_slot = slot;
    if ( CAENHV_GetBdParam(handle, 1, &temp_slot, param.c_str(), temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void OnOffParameterPolicy::setVal(const std::string& v)
{
    if (mode == PARAM_MODE_RDONLY)
        return;

    char temp[v.size() + 1];
    strcpy(temp, v.c_str());

    uint16_t tempSlot = slot;
    if ( CAENHV_SetBdParam(handle, 1, &tempSlot, param.c_str(), temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

}

void OnOffParameterPolicy::printInfo()
{
    std::cout << "      Type: " << type << std::endl;
    std::cout << "      Properties:" << std::endl;
    std::cout << "        - On state  = " << getOnState()  << std::endl;
    std::cout << "        - Off state = " << getOffState() << std::endl;
    std::cout << "        - Value     = " << getVal() << std::endl;
    std::cout << std::endl;
}

