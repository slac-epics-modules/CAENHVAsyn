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

// Base class for all parameter types
template<typename T>
BoardParameterBase<T>::BoardParameterBase(int h, std::size_t s, const std::string&  p, uint32_t m)
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

template<typename T>
T BoardParameterBase<T>::getVal() const
{
    if (mode == PARAM_MODE_WRONLY)
        return T();

    T temp;

    uint16_t tempSlot = slot;
    if ( CAENHV_GetBdParam(handle, 1, &tempSlot, param.c_str(), &temp) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

template<typename T>
void BoardParameterBase<T>::setVal(T value) const
{
    if (mode == PARAM_MODE_RDONLY)
        return;

    uint16_t tempSlot = slot;
    if ( CAENHV_SetBdParam(handle, 1, &tempSlot, param.c_str(), &value) != CAENHV_OK )
           throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));
}
template<typename T>
void BoardParameterBase<T>::printInfo(std::ostream& stream) const
{
    stream << "        Param = "     << param \
           << ", Mode = "            << modeStr \
           << ", Value = " << getVal() \
           << ", epicsParamName = "  << epicsParamName \
           << ", epicsRecordName = " << epicsRecordName \
           << std::endl;
}

// Class for Numeric parameters
BoardParameterNumeric IBoardParameterNumeric::create(int h, std::size_t s, const std::string&  p, uint32_t m)
{
    return std::make_shared<IBoardParameterNumeric>(h, s, p, m);
}

IBoardParameterNumeric::IBoardParameterNumeric(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase<float>(h, s, p, m)
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

   int8_t e;
   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Exp", &e ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   units = processUnits(u, e);
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

// Class for OnOff parameters
BoardParameterOnOff IBoardParameterOnOff::create(int h, std::size_t s, const std::string&  p, uint32_t m)
{
    return std::make_shared<IBoardParameterOnOff>(h, s, p, m);
}

IBoardParameterOnOff::IBoardParameterOnOff(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase<uint32_t>(h, s, p, m)
{
   char temp[30];

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Onstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

   onState = temp;

   if ( CAENHV_GetBdParamProp(handle, slot, param.c_str(), "Offstate", temp ) != CAENHV_OK )
       throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

    offState = temp;
}

void IBoardParameterOnOff::printInfo(std::ostream& stream) const
{
    stream << "        Param = "     << param \
           << ",  Mode = "           << modeStr \
           << ",  On state = "       << getOnState() \
           << ",  Off state = "      << getOffState() \
           << ", epicsParamName = "  << epicsParamName \
           << ", epicsRecordName = " << epicsRecordName \
           << std::endl;
}

// Class for ChStatus parameters
IBoardParameterChStatus::IBoardParameterChStatus(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase<uint32_t>(h, s, p, m)
{
}

BoardParameterChStatus IBoardParameterChStatus::create(int h, std::size_t s, const std::string&  p, uint32_t m)
{
    return std::make_shared<IBoardParameterChStatus>(h, s, p, m);
}

// Class for BdStatus parameters
IBoardParameterBdStatus::IBoardParameterBdStatus(int h, std::size_t s, const std::string&  p, uint32_t m)
:
    BoardParameterBase<uint32_t>(h, s, p, m)
{
}

BoardParameterBdStatus IBoardParameterBdStatus::create(int h, std::size_t s, const std::string&  p, uint32_t m)
{
    return std::make_shared<IBoardParameterBdStatus>(h, s, p, m);
}