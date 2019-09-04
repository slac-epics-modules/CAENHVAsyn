/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : board.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-30
 * ----------------------------------------------------------------------------
 * Description:
 * CAEN HV Power supplies Board Class
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

#include "board.h"

Board::Board(int h, std::size_t s, std::string m, std::string d, std::size_t n, std::string sn, std::string fw)
:
    handle(h),
    slot(s),
    model(m),
    description(d),
    numChannels(n),
    serialNumber(sn),
    firmwareRelease(fw)
{
    GetBoardParams();
    GetBoardChannels();
}

Board::~Board()
{
std::cout << "Destroying object for board in slot " << slot << "..." << std::endl;
}

void Board::printInfo() const
{
    std::cout << "    Slot: " << slot \
              << ", Model: " << model \
              << ", Description: " <<  description \
              << ", Number of channels: " << numChannels \
              << ", Serial Number: " << serialNumber \
              << ", Firmware release: " << firmwareRelease \
              << std::endl;

    std::cout << "    Board parameters:" << std::endl;
    std::cout << "    ..........................." << std::endl;
    std::cout << "      Number of parameters: " << boardParameters.size() << std::endl;
    for (std::vector<BoardParameter>::const_iterator it = boardParameters.begin(); it != boardParameters.end(); ++it)
        (*it)->printInfo();

    std::cout << "    Channel parameters:" << std::endl;
    std::cout << "    ..........................." << std::endl;
    std::cout << "    Channel: 0 " << std::endl;
    std::cout << "      Number of parameters: " << channelParameters.size() << std::endl;
    for (std::vector<ChannelParameter>::const_iterator it = channelParameters.begin(); it != channelParameters.end(); ++it)
        (*it)->printInfo();

    std::cout << std::endl;
}

void Board::GetBoardParams()
{
    // Get Board Parameter Info
    std::string functionName("GetBoardParams");

    char *ParNameList = (char *)NULL;
    CAENHVRESULT r = CAENHV_GetBdParamInfo(handle, slot, &ParNameList);

    std::stringstream retMessage;
    retMessage << "CAENHV_GetBdParamInfo (slot = " << slot << ") : " << CAENHV_GetError(handle) << " (num. " << r << ")";

    printMessage(functionName, retMessage.str().c_str());

    if ( r != CAENHV_OK )
        return;

    char (*p)[MAX_PARAM_NAME];
    p = (char (*)[MAX_PARAM_NAME])ParNameList;

    boardParameters.reserve(MAX_PARAM_NAME);
    for (std::size_t i(0); p[i][0]; ++i)
    {
        try
        {
            boardParameters.push_back(IBoardParameter::create(handle, slot, p[i]));
        }
        catch(const std::runtime_error& e)
        {
            std::cout << "Error found when creating a Board Parameter object for pamater '" << p[i] << "'"<< std::endl;
            std::cout << e.what() << std::endl;
            std::cout << std::endl;
        }
    }

    // Deallocate memory (Use RAII in the future for this)
    free(ParNameList);
}

void Board::GetBoardChannels()
{
    // Get Board Parameter Info
    std::string functionName("GetBoardChannels");

std::size_t ch(0);
//    for ( std::size_t ch(0); ch < numChannels; ++ch)
//    {
        std::cout << "Reading parameter list for channel " << ch << std::endl;
        char *ParNameList = (char *)NULL;
        int ParNumber(0);
        CAENHVRESULT r = CAENHV_GetChParamInfo(handle, slot, ch, &ParNameList, &ParNumber);

        std::stringstream retMessage;
        retMessage << "CAENHV_GetChParamInfo (slot = " << slot << ") : " << CAENHV_GetError(handle) << " (num. " << r << ")";

        printMessage(functionName, retMessage.str().c_str());

        if ( r != CAENHV_OK )
            return;

        std::cout << "  ParNumber = " << ParNumber << std::endl;

        char (*p)[MAX_PARAM_NAME];
        p = (char (*)[MAX_PARAM_NAME])ParNameList;

        channelParameters.reserve(ParNumber);
        for( std::size_t i(0) ; p[i][0] && i < ParNumber; i++ )
        {
            std::cout << "    - Parameter = " << p[i] << std::endl;
            try
            {
                channelParameters.push_back(IChannelParameter::create(handle, slot, ch, p[i]));
            }
            catch(const std::runtime_error& e)
            {
                std::cout << "Error found when creating a Board Parameter object for pamater '" << p[i] << "'"<< std::endl;
                std::cout << e.what() << std::endl;
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;
//    }

}
