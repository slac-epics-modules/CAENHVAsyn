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


BoardParameterBase::BoardParameterBase(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    handle(h),
    slot(s),
    param(p),
    mode(m)
{
   // Generate mode string representation
   if (mode == PARAM_MODE_WRONLY)
       modeStr = "WO";
   else if (mode == PARAM_MODE_RDONLY)
       modeStr = "RO";
   else if (mode == PARAM_MODE_RDWR)
       modeStr = "RW";
   else
       modeStr = "?";

    std::stringstream temp;

    // Generate the EPICS parameter name
    temp.str("");
    temp << "S" << std::setfill('0') << std::setw(2) << s << "_" \
         << processParamName(param);
    epicsParamName = temp.str();

    // Generate the EPICS record name
    temp.str("");
    temp << "S" << std::setfill('0') << std::setw(2) << s << ":" \
         << processParamName(param);
    epicsRecordName = temp.str();

    // Generate the EPICS description
    temp.str("");
    temp << "'Slot " << s \
         << ", " << param \
         << " (" << modeStr << ")'";
    epicsDesc = temp.str();
}

BoardParameterNumeric IBoardParameterNumeric::create(int h, std::size_t s, const std::string&  p, uint32_t m)
{
    return std::make_shared<IBoardParameterNumeric>(h, s, p, m);
}


IBoardParameterNumeric::IBoardParameterNumeric(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase(h, s, p, m)
{
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


float IBoardParameterNumeric::getVal()
{
    if (mode == PARAM_MODE_WRONLY)
        return 0.0;

    float temp;

    uint16_t tempSlot = slot;
    if ( CAENHV_GetBdParam(handle, 1, &tempSlot, param.c_str(), &temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void IBoardParameterNumeric::setVal(float value)
{
    if (mode == PARAM_MODE_RDONLY)
        return;

    uint16_t tempSlot = slot;
    if ( CAENHV_SetBdParam(handle, 1, &tempSlot, param.c_str(), &value) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));
}

void IBoardParameterNumeric::printInfo(std::ostream& stream) const
{
    stream << "        Param = "     << param \
           << ", Mode  = "           << modeStr \
           << ", Minval = "          << getMinVal() \
           << ", Maxval = "          <<  getMaxVal() \
           << ", Units  = "          << units.c_str() \
           << ", epicsParamName = "  << epicsParamName \
           << ", epicsRecordName = " << epicsRecordName \
           << std::endl;
}


BoardParameterOnOff IBoardParameterOnOff::create(int h, std::size_t s, const std::string&  p, uint32_t m)
{
    return std::make_shared<IBoardParameterOnOff>(h, s, p, m);
}

IBoardParameterOnOff::IBoardParameterOnOff(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase(h, s, p, m)
{
   char temp[30];

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Onstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   onState = temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Offstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    offState = temp;
}

uint32_t IBoardParameterOnOff::getVal()
{
    if (mode == PARAM_MODE_WRONLY)
        return 0;

    uint32_t temp;

    uint16_t temp_slot = slot;
    if ( CAENHV_GetBdParam(handle, 1, &temp_slot, param.c_str(), &temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void IBoardParameterOnOff::setVal(uint32_t value)
{
    if (mode == PARAM_MODE_RDONLY)
        return;

//    char temp[v.size() + 1];
//    strcpy(temp, v.c_str());

    uint16_t tempSlot = slot;
    if ( CAENHV_SetBdParam(handle, 1, &tempSlot, param.c_str(), &value) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));
}

void IBoardParameterOnOff::printInfo(std::ostream& stream) const
{
    stream << "        Param = " << param \
           << ",  Mode = "      << modeStr \
           << ",  On state = "  << getOnState() \
           << ",  Off state = "  << getOffState() \
           << ", epicsParamName = " << epicsParamName \
           << ", epicsRecordName = " << epicsRecordName \
           << std::endl;
}

