//=================================================================================================================
//  diag.hh -- This is the diagnostic messaging system
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-12  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



//
// -- These are the list of possible diagnostic messages
//    --------------------------------------------------
enum class DiagID {
    TestDiagnistic,
    MissingSemicolon,
};



//
// -- Handle all of the diagnostic messages for the compiler
//    ------------------------------------------------------
class Diagnostics {
private:
    static const std::unordered_map<DiagID, std::string> DiagMsgs;
    int warnings;
    int errors;


    // -- ctor/dtor
public:
    Diagnostics(void) : warnings(0), errors(0) {}
    virtual ~Diagnostics()= default;


    // -- public interface functions
public:
    void Error(SourceLoc_t loc, DiagID id, std::vector<std::string> args = {}) {
        errors ++;
        Emit("error", id, loc, args);
    }
    void Warning(SourceLoc_t loc, DiagID id, std::vector<std::string> args = {}) {
        warnings ++;
        Emit("warning", id, loc, args);
    }
    void Note(SourceLoc_t loc, DiagID id, std::vector<std::string> args = {}) {
        Emit("note", id, loc, args);
    }


private:
    void Emit(const std::string &level, DiagID id, SourceLoc_t loc, const std::vector<std::string> &args);
    std::string Format(std::string tmpl, const std::vector<std::string> args);
};



//
// -- declare the global diagnostics harness
//    --------------------------------------
extern Diagnostics diags;

