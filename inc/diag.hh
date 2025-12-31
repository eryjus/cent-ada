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
// -- a forward declaration needed to keep the compiler quite
//    -------------------------------------------------------
class Parser;


//
// -- These are the list of possible diagnostic messages
//    --------------------------------------------------
enum class DiagID {
    UnexpectedEOF,
    UnexpectedToken,
    MissingSemicolon,
    MissingRightParen,
    MissingEnd,
    MissingEndingTag,
    MissingRecordComponentDefinitions,
    MissingExpression,
    InvalidChoiceInVariant,
    DuplicateName,
    DuplicateName2,
    UnknownName,
    ExtraComma,
    ExtraSemicolon,
    ExtraVertialBar,
    InvalidRangeConstraint,
    InvalidName,
    UnknownError,
};



//
// -- Handle all of the diagnostic messages for the compiler
//    ------------------------------------------------------
class Diagnostics {
private:
    Parser *parser;
    static const std::unordered_map<DiagID, std::string> DiagMsgs;
    std::vector<std::string> msgQueue;
    int warnings;
    int errors;


    // -- ctor/dtor
public:
    Diagnostics(void) : parser(nullptr), warnings(0), errors(0) {}
    virtual ~Diagnostics()= default;

    void SetParser(Parser *p) { parser = p; }


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
    void Debug(std::string s) { std::cerr << s << '\n'; }


private:
    void Emit(const std::string &level, DiagID id, SourceLoc_t loc, const std::vector<std::string> &args);
    std::string Format(std::string tmpl, const std::vector<std::string> args);


public:
    void Queue(std::string msg) { msgQueue.push_back(msg); }
    size_t Checkpoint(void) const { return msgQueue.size(); }
    void Rollback(size_t loc) { assert(loc <= msgQueue.size()); msgQueue.resize(loc); }
    void Flush(void) {
        for (const auto &m : msgQueue) { assert(!m.empty()); }
        for (auto m : msgQueue) { std::cerr << m; } msgQueue.clear();
    }
    int &Errors(void) { return errors; }
    int &Warnings(void) { return warnings; }
};



//
// -- declare the global diagnostics harness
//    --------------------------------------
extern Diagnostics diags;

