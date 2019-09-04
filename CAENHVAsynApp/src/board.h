#ifndef BOARD_H
#define BOARD_H

/**
 *-----------------------------------------------------------------------------
 * Title      : CAEN HV Asyn module
 * ----------------------------------------------------------------------------
 * File       : board.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2019-08-20
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

#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <bitset>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <vector>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <arpa/inet.h>
#include <iostream>

#include "CAENHVWrapper.h"
#include "common.h"
#include "board_parameter.h"

class Board
{
public:
    Board(int h, std::size_t s, std::string m, std::string d, std::size_t n, std::string sn, std::string fw);
    ~Board();

    void printInfo() const;
private:

    void GetBoardParams();

    int                         handle;
    std::size_t                 slot;
    std::string                 model;
    std::string                 description;
    std::size_t                 numChannels;
    std::string                 serialNumber;
    std::string                 firmwareRelease;
    std::vector<BoardParameter2> boardParameters2;
};

#endif
