//=================================================================================================================
//  diag.cc -- This is the implementation of the diagnostic messaging system
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


#include "ada.hh"



//
// -- This is the global diagnostics harness
//    --------------------------------------
Diagnostics diags;



//
// -- Emit a diagnostic message
//    -------------------------
void Diagnostics::Emit(const std::string &level, DiagID id, SourceLoc_t loc, const std::vector<std::string> &args)
{
    assert(DiagMsgs.find(id) != DiagMsgs.end());

    auto it = DiagMsgs.find(id);
    const std::string tmpl = (it == DiagMsgs.end() ? "" : it->second);
    std::string msg = "";

    if (tmpl == "") {
        std::cerr << "internal error: unknown diagnostic ID "
                  << static_cast<int>(id) << "\n";
        return;
    }


    std::string text;
    try {
        text = Format(tmpl, args);  // e.g. replaces {0}, {1}, ...
    } catch (const std::exception &ex) {
        std::cerr << "internal error formatting diagnostic "
                  << static_cast<int>(id) << ": "
                  << ex.what() << "\n";
        return;
    }


    if (loc.valid) {
        msg += loc.filename;
        msg += ":";
        msg += std::to_string(loc.line);
        msg += ":";
        msg += std::to_string(loc.col);
        msg += ": ";
    }


    msg += level;
    msg += ": ";
    msg += text;
    msg += "\n";


    if (loc.valid && loc.sourceLine.size()) {
        msg += "    ";
        msg += loc.sourceLine;
        msg += "\n";
        msg += "    ";
        msg += std::string(loc.col - 1, ' ');
        msg += "^";
        msg += "\n";
    }


    if (parser) msg += parser->UnwindStack();

    Queue(std::string("\e[31;1m") + msg + std::string("\e[0m"));
}



//
// -- Format a diagnostic message
//    ---------------------------
std::string Diagnostics::Format(std::string tmpl, const std::vector<std::string> args)
{
    const std::string &fmt = tmpl;
    std::string out;
    out.reserve(fmt.size() + args.size() * 8);

    for (size_t i = 0; i < fmt.size(); ++i) {
        if (fmt[i] == '{') {
            // Look for closing }
            size_t start = i + 1;
            size_t end = fmt.find('}', start);
            if (end == std::string::npos) {
                // Unmatched '{' — emit literally
                out += '{';
                continue;
            }

            // Extract inside of { ... }
            std::string index_str = fmt.substr(start, end - start);

            // Try parsing number
            bool valid = true;
            int idx = 0;
            if (!index_str.empty()) {
                for (char c : index_str) {
                    if (c < '0' || c > '9') {
                        valid = false;
                        break;
                    }

                    idx = idx * 10 + (c - '0');
                }
            } else {
                valid = false;
            }

            if (valid && idx >= 0 && (size_t)idx < args.size()) {
                out += args[idx];   // substitute argument
            } else {
                // Unknown placeholder—emit literally
                out += '{';
                out += index_str;
                out += '}';
            }

            i = end;   // Skip to '}'
        } else {
            out += fmt[i];
        }
    }

    return out;
}



//
// -- The last thing in this source will be the list of messages
//    ----------------------------------------------------------
const std::unordered_map<DiagID, std::string> Diagnostics::DiagMsgs = {
    { DiagID::UnexpectedEOF, "unexpected EOF in `{0}`" },
    { DiagID::UnexpectedToken, "unexpected token in `{0}`; expected {1}" },
    { DiagID::MissingSemicolon, "expected ';' after {0}" },
    { DiagID::MissingRightParen, "expected ')' after {0}" },
    { DiagID::MissingEnd, "expected 'end' after {0}" },
    { DiagID::MissingEndingTag, "after an 'end', expected to see {0}" },
    { DiagID::MissingRecordComponentDefinitions, "a record definition requires at least 1 component" },
    { DiagID::MissingExpression, "Missing an expression after {0}" },
    { DiagID::InvalidChoiceInVariant, "invalid choice in variant" },
    { DiagID::DuplicateName, "duplicate name '{0}' in the same scope" },
    { DiagID::DuplicateName2, "the previous declaration was here" },
    { DiagID::UnknownName, "the name '{0}' is not known" },
    { DiagID::ExtraComma, "extra comma (,) in {0}"},
    { DiagID::ExtraSemicolon, "extra semicolon (;) in {0}"},
    { DiagID::ExtraVertialBar, "extra vertical bar (|) in {0}"},
    { DiagID::InvalidRangeConstraint, "invalid range constraint" },
    { DiagID::InvalidName, "invalid name {0} in {1}" },
};



