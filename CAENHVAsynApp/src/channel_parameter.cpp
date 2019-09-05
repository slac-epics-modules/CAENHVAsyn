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

#include "channel_parameter.h"


ChannelParameterBase::ChannelParameterBase(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m)
: 
    handle(h), 
    slot(s), 
    channel(c), 
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
    temp << "S" << s << "_" << "C" << channel << "_" << processParamName(param);
    epicsParamName = temp.str();

    // Generate the EPICS record name
    temp.str("");
    temp << "S" << s << ":" << "C" << channel << ":" << processParamName(param);
    epicsRecordName = temp.str();

    // Generate the EPICS description
    temp.str("");
    temp << "'Slot " << s <<  ", Ch " << channel <<  ", " << param << " (" << modeStr << ")'";
    epicsDesc = temp.str();

}

ChannelParameterNumeric IChannelParameterNumeric::create(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m)
{
    return std::make_shared<IChannelParameterNumeric>(h, s, c, p, m);
}

IChannelParameterNumeric::IChannelParameterNumeric(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m)
:
    ChannelParameterBase(h, s, c, p, m)
{
   float temp;

   if ( CAENHV_GetChParamProp(handle, slot, channel, param.c_str(), "Minval", &temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   minVal = temp;

   if ( CAENHV_GetChParamProp(handle, slot, channel, param.c_str(), "Maxval", &temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   maxVal = temp;

   // Extract uints
   uint16_t u;
   if ( CAENHV_GetChParamProp(handle, slot, channel, param.c_str(), "Unit", &u ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   uint8_t e;
   if ( CAENHV_GetChParamProp(handle, slot, channel, param.c_str(), "Exp", &e ) != CAENHV_OK )
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


float IChannelParameterNumeric::getVal() const
{
    if (mode == PARAM_MODE_WRONLY)
        return 0.0;

    float temp;
   
    uint16_t temp_chs = channel;
    if ( CAENHV_GetChParam(handle, slot, param.c_str(), 1, &temp_chs, &temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetChParam failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void IChannelParameterNumeric::setVal(float value)
{
    if (mode == PARAM_MODE_RDONLY)
        return;

    uint16_t temp_chs = channel;
    if ( CAENHV_SetChParam(handle, slot, param.c_str(), 1, &temp_chs, &value) != CAENHV_OK )
           throw std::runtime_error("CAENHV_SetChParam failed: " + std::string(CAENHV_GetError(handle)));
}

void IChannelParameterNumeric::printInfo() const
{
    std::cout << "          Param = " << param \
              << ", Mode  = "     << modeStr \
              << ", Minval = "    << getMinVal() \
              << ", Maxval = "    <<  getMaxVal() \
              << ", Units = "    << units.c_str() \
              << ", Value = "    << getVal() \
              << ", epicsParamName = " << epicsParamName \
              << ", epicsRecordName = " << epicsRecordName \
              << std::endl;
}

ChannelParameterOnOff IChannelParameterOnOff::create(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m)
{
    return std::make_shared<IChannelParameterOnOff>(h, s, c, p, m);
}

IChannelParameterOnOff::IChannelParameterOnOff(int h, std::size_t s, std::size_t c, const std::string&  p, uint32_t m)
:
    ChannelParameterBase(h, s, c, p, m)
{
   char temp[30];

   if ( CAENHV_GetChParamProp(handle, slot, channel, param.c_str(), "Onstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   onState = temp;

   if ( CAENHV_GetChParamProp(handle, slot, channel, param.c_str(), "Offstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    offState = temp;

}

uint32_t IChannelParameterOnOff::getVal() const
{
    if (mode == PARAM_MODE_WRONLY)
        return 0;

    uint32_t temp;

    uint16_t temp_chs = channel;
    if ( CAENHV_GetChParam(handle, slot, param.c_str(), 1, &temp_chs, &temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetChParam failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void IChannelParameterOnOff::setVal(uint32_t value)
{
    if (mode == PARAM_MODE_RDONLY)
        return;

    uint16_t temp_chs = channel;
    if ( CAENHV_SetChParam(handle, slot, param.c_str(), 1, &temp_chs, &value) != CAENHV_OK )
           throw std::runtime_error("CAENHV_SetChParam failed: " + std::string(CAENHV_GetError(handle)));
}

void IChannelParameterOnOff::printInfo() const
{
    std::cout << "          Param = " << param \
              << ", Mode = " << modeStr \
              << ", On state = " << getOnState() \
              << ", Off state = " << getOffState() \
              << ", Value = " << getVal() \
              << ", epicsParamName = " << epicsParamName \
              << ", epicsRecordName = " << epicsRecordName \
              << std::endl;
}

