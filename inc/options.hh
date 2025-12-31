//=================================================================================================================
//  options.hh -- This structure is a list of static options for the compiler
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-30  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



typedef struct {
    bool trace = false;
    bool dumpSymtab = false;
    bool listing = false;
} Options;


extern Options opts;

