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

    std::cout << "      Number of Numeric parameters: " << boardParameterNumerics.size() << std::endl;
    for (std::vector<BoardParameterNumeric>::const_iterator it = boardParameterNumerics.begin(); it != boardParameterNumerics.end(); ++it)
        (*it)->printInfo();

    std::cout << "      Number of OnOff parameters: " << boardParameterOnOffs.size() << std::endl;
    for (std::vector<BoardParameterOnOff>::const_iterator it = boardParameterOnOffs.begin(); it != boardParameterOnOffs.end(); ++it)
        (*it)->printInfo();
    
    std::cout << "    Channel parameters:" << std::endl;
    std::cout << "    ..........................." << std::endl;
    for (std::vector<Channel>::const_iterator it = channels.begin(); it != channels.end(); ++it)
        it->printInfo();
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

    boardParameterNumerics.reserve(MAX_PARAM_NAME);
    boardParameterOnOffs.reserve(MAX_PARAM_NAME);

    for (std::size_t i(0); p[i][0]; ++i)
    {
        uint32_t type, mode;

        if ( CAENHV_GetBdParamProp(handle, slot, p[i], "Type", &type) != CAENHV_OK )
            throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));

        if (CAENHV_GetBdParamProp(handle, slot, p[i], "Mode", &mode) != CAENHV_OK )
            throw std::runtime_error("CAENHV_GetBdParamProp failed: " + std::string(CAENHV_GetError(handle)));


        if (type == PARAM_TYPE_NUMERIC)
            boardParameterNumerics.push_back( IBoardParameterNumeric::create(handle, slot, p[i], mode));
        else if (type == PARAM_TYPE_ONOFF)
            boardParameterOnOffs.push_back( IBoardParameterOnOff::create(handle, slot, p[i], mode));
        else
            //throw std::runtime_error("Parameter type not  supported!");
            std::cout << "Error found when creating a Board Parameter object for pamater '" << p[i] << "'. Unsupported type = " << type << std::endl;
    }

    // Deallocate memory (Use RAII in the future for this)
    free(ParNameList);
}

void Board::GetBoardChannels()
{
    channels.reserve(numChannels);

    for (std::size_t i(0); i < numChannels; ++i)
        channels.emplace_back(handle, slot, i);
}
