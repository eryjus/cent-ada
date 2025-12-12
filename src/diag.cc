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
    auto it = DiagMsgs.find(id);
    const std::string tmpl = (it == DiagMsgs.end() ? "" : it->second);

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
        std::cerr << loc.filename << ":"
                  << loc.line << ":"
                  << loc.col << ": ";
    }


    std::cerr << level << ": ";
    std::cerr << text << "\n";


    if (loc.valid && loc.sourceLine.size()) {
        std::cerr << "    " << loc.sourceLine << "\n";
        std::cerr << "    " << std::string(loc.col-1, ' ')
                  << "^" << "\n";
    }
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
    { DiagID::TestDiagnistic, "This is a test diag <{0}>"},
    { DiagID::MissingSemicolon, "expected ';' after {0}" },
};



