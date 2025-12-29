//=================================================================================================================
//  parser.cc -- Miscellaneous functions and variables for the parser
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-27  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



#include "ada.hh"



//
// -- This statically declaraed member in the Mark class needs a physical memory location
//    -----------------------------------------------------------------------------------
int Parser::MarkStream::depth = 0;
bool Parser::Production::trace = false;



