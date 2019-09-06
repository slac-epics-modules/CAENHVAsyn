/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : system_property.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-09-04
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power supplies System Property Class
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

#include "system_property.h"

SystemPropertyBase::SystemPropertyBase(int h, const std::string&  p, uint32_t m)
:
    handle(h),
    prop(p),
    mode(m)
{
    // Generate mode string
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
    temp << "C_" << processParamName(prop);
    epicsParamName = temp.str();

    // Generate the EPICS record name
    temp.str("");
    temp << "C:" << processParamName(prop);
    epicsRecordName = temp.str();

    // Generate the EPICS description
    temp.str("");
    temp << "'Chassis, " << prop << " (" << modeStr << ")'";
    epicsDesc = temp.str();

};

void SystemPropertyBase::printInfo(std::ostream& stream) const
{
    stream << "      Name = "   << prop \
           << ", handle = "     << handle \
           << ", mode = "       << mode \
           << ", epicsParamName = " << epicsParamName \
           << ", epicsRecordName = " << epicsRecordName \
           << std::endl;
}

// U8 class
SystemPropertyU8 ISystemPropertyU8::create(int h, const std::string&  p, uint32_t m)
{
    return std::make_shared<ISystemPropertyU8>(h, p, m);
}

ISystemPropertyU8::ISystemPropertyU8(int h, const std::string&  p, uint32_t m)
:
    SystemPropertyBase(h,p,m)
{
}

uint8_t ISystemPropertyU8::getVal()
{

    if (mode == SYSPROP_MODE_WRONLY)
        return 0;

    uint8_t temp;

    CAENHVRESULT r = CAENHV_GetSysProp(handle, prop.c_str(), &temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_GetSysProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void ISystemPropertyU8::setVal(uint8_t v)
{

    if (mode == SYSPROP_MODE_RDONLY)
        return;

    CAENHVRESULT r = CAENHV_SetSysProp(handle, prop.c_str(), &v);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_SetSysProp failed: " + std::string(CAENHV_GetError(handle)));
}

// U16 class
SystemPropertyU16 ISystemPropertyU16::create(int h, const std::string&  p, uint32_t m)
{
    return std::make_shared<ISystemPropertyU16>(h, p, m);
}

ISystemPropertyU16::ISystemPropertyU16(int h, const std::string&  p, uint32_t m)
:
    SystemPropertyBase(h,p,m)
{
}

uint16_t ISystemPropertyU16::getVal()
{

    if (mode == SYSPROP_MODE_WRONLY)
        return 0;

    uint16_t temp;

    CAENHVRESULT r = CAENHV_GetSysProp(handle, prop.c_str(), &temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_GetSysProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void ISystemPropertyU16::setVal(uint16_t v)
{

    if (mode == SYSPROP_MODE_RDONLY)
        return;

    CAENHVRESULT r = CAENHV_SetSysProp(handle, prop.c_str(), &v);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_SetSysProp failed: " + std::string(CAENHV_GetError(handle)));
}

// U32 class
SystemPropertyU32 ISystemPropertyU32::create(int h, const std::string&  p, uint32_t m)
{
    return std::make_shared<ISystemPropertyU32>(h, p, m);
}

ISystemPropertyU32::ISystemPropertyU32(int h, const std::string&  p, uint32_t m)
:
    SystemPropertyBase(h,p,m)
{
}

uint32_t ISystemPropertyU32::getVal()
{

    if (mode == SYSPROP_MODE_WRONLY)
        return 0;

    uint32_t temp;

    CAENHVRESULT r = CAENHV_GetSysProp(handle, prop.c_str(), &temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_GetSysProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void ISystemPropertyU32::setVal(uint32_t v)
{

    if (mode == SYSPROP_MODE_RDONLY)
        return;

    CAENHVRESULT r = CAENHV_SetSysProp(handle, prop.c_str(), &v);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_SetSysProp failed: " + std::string(CAENHV_GetError(handle)));
}

// I16 class
SystemPropertyI16 ISystemPropertyI16::create(int h, const std::string&  p, uint32_t m)
{
    return std::make_shared<ISystemPropertyI16>(h, p, m);
}

ISystemPropertyI16::ISystemPropertyI16(int h, const std::string&  p, uint32_t m)
:
    SystemPropertyBase(h,p,m)
{
}

int16_t ISystemPropertyI16::getVal()
{

    if (mode == SYSPROP_MODE_WRONLY)
        return 0;

    int16_t temp;

    CAENHVRESULT r = CAENHV_GetSysProp(handle, prop.c_str(), &temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_GetSysProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void ISystemPropertyI16::setVal(int16_t v)
{

    if (mode == SYSPROP_MODE_RDONLY)
        return;

    CAENHVRESULT r = CAENHV_SetSysProp(handle, prop.c_str(), &v);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_SetSysProp failed: " + std::string(CAENHV_GetError(handle)));
}

// I32 class
SystemPropertyI32 ISystemPropertyI32::create(int h, const std::string&  p, uint32_t m)
{
    return std::make_shared<ISystemPropertyI32>(h, p, m);
}

ISystemPropertyI32::ISystemPropertyI32(int h, const std::string&  p, uint32_t m)
:
    SystemPropertyBase(h,p,m)
{
}

int32_t ISystemPropertyI32::getVal()
{

    if (mode == SYSPROP_MODE_WRONLY)
        return 0;

    int32_t temp;

    CAENHVRESULT r = CAENHV_GetSysProp(handle, prop.c_str(), &temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_GetSysProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void ISystemPropertyI32::setVal(int32_t v)
{

    if (mode == SYSPROP_MODE_RDONLY)
        return;

    CAENHVRESULT r = CAENHV_SetSysProp(handle, prop.c_str(), &v);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_SetSysProp failed: " + std::string(CAENHV_GetError(handle)));
}

// String class
SystemPropertyString ISystemPropertyString::create(int h, const std::string&  p, uint32_t m)
{
    return std::make_shared<ISystemPropertyString>(h, p, m);
}

ISystemPropertyString::ISystemPropertyString(int h, const std::string&  p, uint32_t m)
:
    SystemPropertyBase(h,p,m)
{
}

std::string ISystemPropertyString::getVal()
{

    if (mode == SYSPROP_MODE_WRONLY)
        return "";

    char temp[4096];

    CAENHVRESULT r = CAENHV_GetSysProp(handle, prop.c_str(), temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_GetSysProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void ISystemPropertyString::setVal(const std::string& v)
{

    if (mode == SYSPROP_MODE_RDONLY)
        return;

    char temp[v.size() + 1];
    strcpy(temp, v.c_str());

    CAENHVRESULT r = CAENHV_SetSysProp(handle, prop.c_str(), temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_SetSysProp failed: " + std::string(CAENHV_GetError(handle)));
}

// Float class
SystemPropertyFloat ISystemPropertyFloat::create(int h, const std::string&  p, uint32_t m)
{
    return std::make_shared<ISystemPropertyFloat>(h, p, m);
}

ISystemPropertyFloat::ISystemPropertyFloat(int h, const std::string&  p, uint32_t m)
:
    SystemPropertyBase(h,p,m)
{
}

float ISystemPropertyFloat::getVal()
{

    if (mode == SYSPROP_MODE_WRONLY)
        return 0.0;

    float temp;

    CAENHVRESULT r = CAENHV_GetSysProp(handle, prop.c_str(), &temp);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_GetSysProp failed: " + std::string(CAENHV_GetError(handle)));

    return temp;
}

void ISystemPropertyFloat::setVal(float v)
{

    if (mode == SYSPROP_MODE_RDONLY)
        return;

    CAENHVRESULT r = CAENHV_SetSysProp(handle, prop.c_str(), &v);

    if ( r != CAENHV_OK && r != CAENHV_GETPROPNOTIMPL && r != CAENHV_NOTGETPROP )
        throw std::runtime_error("CAENHV_SetSysProp failed: " + std::string(CAENHV_GetError(handle)));
}
