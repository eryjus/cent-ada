//
// -- This file is temporary.  It will hold temp productions
//    required to get the parser working.
//    ------------------------------------------------------

#include "ada.hh"


bool Parser::ParseAttribute(void)
{
    Production p(*this, "attribute");
    Mark m(tokens, diags);

    return false;
}


bool Parser::ParseBodyStub(void)
{
    Production p(*this, "body_stub");
    Mark m(tokens, diags);

    return false;
}


bool Parser::ParseName(void)
{
    Production p(*this, "name");
    Mark m(tokens, diags);

    if (!Require(TOK_IDENTIFIER)) return false;

    m.Commit();
    return true;
}



