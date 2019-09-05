/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : channel.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-09-04
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power supplies Channel Class
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

#include "channel.h"

Channel::Channel(int h, std::size_t s, std::size_t c)
:
    handle(h),
    slot(s),
    channel(c)
{
    GetChannelParams();
}

void Channel::printInfo() const
{
    std::cout << "    Channel parameters:" << std::endl;
    std::cout << "    ..........................." << std::endl;
    std::cout << "    Slot:    " << slot << std::endl;
    std::cout << "    Channel: " << channel << std::endl;
    //std::cout << "      Number of parameters: " << channelParameters.size() << std::endl;
    //for (std::vector<ChannelParameter>::const_iterator it = channelParameters.begin(); it != channelParameters.end(); ++it)
    //    (*it)->printInfo();

    std::cout << "      Number of Numeric parameters: " << channelParameterNumerics.size() << std::endl;
    for (std::vector<ChannelParameterNumeric>::const_iterator it = channelParameterNumerics.begin(); it != channelParameterNumerics.end(); ++it)
        (*it)->printInfo();

    std::cout << "      Number of OnOff parameters: " << channelParameterOnOffs.size() << std::endl;
    for (std::vector<ChannelParameterOnOff>::const_iterator it = channelParameterOnOffs.begin(); it != channelParameterOnOffs.end(); ++it)
        (*it)->printInfo();

    std::cout << std::endl;
}

void Channel::GetChannelParams()
{
    // Get Channel Parameter Info
    std::string functionName("GetChannelParams");

    char *ParNameList = (char *)NULL;
    int ParNumber(0);
    CAENHVRESULT r = CAENHV_GetChParamInfo(handle, slot, channel, &ParNameList, &ParNumber);

    std::stringstream retMessage;
    retMessage << "CAENHV_GetChParamInfo (slot = " << slot << ") : " << CAENHV_GetError(handle) << " (num. " << r << ")";

    printMessage(functionName, retMessage.str().c_str());

    if ( r != CAENHV_OK )
        return;

    char (*p)[MAX_PARAM_NAME];
    p = (char (*)[MAX_PARAM_NAME])ParNameList;


    channelParameterNumerics.reserve(ParNumber);
    channelParameterOnOffs.reserve(ParNumber);
    for( std::size_t i(0) ; p[i][0] && i < ParNumber; i++ )
    {

        uint32_t type, mode;
    
        if ( CAENHV_GetChParamProp(handle, slot, channel, p[i], "Type", &type) != CAENHV_OK )
            throw std::runtime_error("CAENHV_GetChParamProp failed: " + std::string(CAENHV_GetError(handle)));
    
        if (CAENHV_GetChParamProp(handle, slot, channel, p[i], "Mode", &mode) != CAENHV_OK )
            throw std::runtime_error("CAENHV_GetChParamProp failed: " + std::string(CAENHV_GetError(handle)));

        if (type == PARAM_TYPE_NUMERIC)
            channelParameterNumerics.push_back( IChannelParameterNumeric::create(handle, slot, channel, p[i], mode));
        else if (type == PARAM_TYPE_ONOFF)
            channelParameterOnOffs.push_back( IChannelParameterOnOff::create(handle, slot, channel, p[i], mode));
        else
        {
            //throw std::runtime_error("Parameter type not  supported!");
            std::cout << "Error found when creating a Board Parameter object for pamater '" << p[i] << "'"<< std::endl;
            std::cout << std::endl;
        }
    }

    // Deallocate memory (Use RAII in the future for this)
    free(ParNameList);
}
