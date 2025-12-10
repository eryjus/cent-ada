//=================================================================================================================
//  ada.hh -- This is the global header file for the entire compiler
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-03  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#pragma once



//
// -- Include standard libraries
//    --------------------------
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>



//
// -- Inlcude the tokens and then clean up some types
//    -----------------------------------------------
#include "tokens.hh"
typedef int TokenType_t;
typedef union YYSTYPE yystype_t;



//
// -- Include the other headers
//    -------------------------
#include "tstream.hh"



//
// -- some global variables
//    ---------------------
extern std::string strVal;
extern int column;
extern TokenStream *tokens;


