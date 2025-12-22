//
// -- This file is temporary.  It will hold temp productions
//    required to get the parser working.
//    ------------------------------------------------------

#include "ada.hh"


bool Parser::ParseAttribute(void)
{
    Production p(*this, "attribute");
    MarkStream m(tokens, diags);

    return false;
}


bool Parser::ParseBodyStub(void)
{
    Production p(*this, "body_stub");
    MarkStream m(tokens, diags);

    return false;
}


bool Parser::ParseName(std::string &id)
{
    Production p(*this, "name");
    MarkStream m(tokens, diags);

    if (!RequireIdent(id)) return false;

    m.Commit();
    return true;
}



