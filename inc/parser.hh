//=================================================================================================================
//  parser.hh -- Define the structures and classes for the Parser
//
//        Copyright (c)  2025      -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-10  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================




//
// -- This class will handle the entirety of the parser
//    -------------------------------------------------
class Parser {
private:
    TokenStream &tokens;
    std::vector<std::string> stack;


private:
    class Mark {
    private:
        TokenStream &ts;
        Diagnostics &diag;
        int saved;
        bool committed;
        size_t chkpt;
        static int depth;


    public:
        Mark(TokenStream &t, Diagnostics &d) : ts(t), diag(d), saved(ts.Location()), committed(false) {
            ++depth;
            chkpt = diag.Checkpoint();
        }

        ~Mark() {
            --depth;
            assert(depth >= 0);

            if (!committed) {
                ts.Reset(saved);
                diag.Rollback(chkpt);
            }

            if (depth == 0) diag.Flush();
        }

    public:
        //
        // -- The following member method may be used for any production whether tokens are directly
        //    consumed or not.
        //    ------------------------------------------------------------------------------------
        void Commit(void) { std::cerr << "Accepted\n"; committed = true; }

        //
        // -- The following member method can only be used when no tokens are directly consumed in
        //    the production.  It is provided ONLY for ease of coding in lists of alternative
        //    productions such as `basic_declaration`.
        //    ------------------------------------------------------------------------------------
        bool CommitAlternative(bool c) { if (c) committed = true; std::cerr << "Accepted\n"; return c; }
    };


private:
    class Production {
    private:
        Parser &parser;
        static bool trace;

    public:
        Production(Parser &parser, std::string p) : parser(parser) {
            if (trace) std::cerr << "Entering " << p << " from " << parser.Last() << '\n';
            parser.stack.push_back(std::move(p));
        }
        ~Production() {
            if (trace) std::cerr << "Leaving " << parser.Last() << '\n';
            parser.stack.pop_back();
        }


    public:
        static void SetTrace(bool t) { trace = t; }
    };



public:
    Parser(TokenStream &s) : tokens(s) {}
    virtual ~Parser() = default;


public:
    // -- a token is optional and if found advance past it
    bool Optional(TokenType_t tok) {
        if (tokens.Current() == tok) {
            tokens.Advance();
            return true;
        }
        return false;
    }
    // -- a token is required to be next
    bool Require(TokenType_t tok) {
        if (tokens.Current() == tok) {
            tokens.Advance();
            return true;
        }

        return false;
    }

    void SetTrace(bool t) { Production::SetTrace(t); }
    std::string Last(void) { if (stack.size() == 0) return "top level"; return stack[stack.size() - 1]; }
    void Push(std::string p) { stack.push_back(p); }
    void Pop(void) { stack.pop_back(); }
    std::string UnwindStack(void) {
        std::string rv = "";
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
            rv += "  in production `";
            rv += *it;
            rv += "`\n";
        }

        return rv;
    }


public:
    bool ParseAccessTypeDefinition(void);                       // -- Ch 3
    bool ParseArrayTypeDefinition(void);                        // -- Ch 3
    bool ParseBasicDeclaration(void);                           // -- Ch 3
    bool ParseBasicDeclarativeItem(void);                       // -- Ch 3
    bool ParseBody(void);                                       // -- Ch 3
    bool ParseChoice(void);                                     // -- Ch 3
    bool ParseComponentDeclaration(void);                       // -- Ch 3
    bool ParseComponentList(void);                              // -- Ch 3
    bool ParseComponentSubtypeDefinition(void);                 // -- Ch 3
    bool ParseConstrainedArrayDefinition(void);                 // -- Ch 3
    bool ParseConstraint(void);                                 // -- Ch 3
    bool ParseDeclarativePart(void);                            // -- Ch 3
    bool ParseDerivedTypeDefinition(void);                      // -- Ch 3
    bool ParseDiscreteRange(void);                              // -- Ch 3
    bool ParseDiscriminantAssociation(void);                    // -- Ch 3
    bool ParseDiscriminantConstraint(void);                     // -- Ch 3
    bool ParseDiscriminantPart(void);                           // -- Ch 3
    bool ParseDiscriminantSpecification(void);                  // -- Ch 3
    bool ParseEnumerationLiteral(void);                         // -- Ch 3
    bool ParseEnumerationLiteralSpecification(void);            // -- Ch 3
    bool ParseEnumerationTypeDefinition(void);                  // -- Ch 3
    bool ParseFixedAccuracyDefinition(void);                    // -- Ch 3
    bool ParseFixedPointConstraint(void);                       // -- Ch 3
    bool ParseFloatingAccuracyDefinition(void);                 // -- Ch 3
    bool ParseFloatingPointConstraint(void);                    // -- Ch 3
    bool ParseFullTypeDeclaration(void);                        // -- Ch 3
    bool ParseIdentifierList(void);                             // -- Ch 3
    bool ParseIncompleteTypeDeclaration(void);                  // -- Ch 3
    bool ParseIndexConstraint(void);                            // -- Ch 3
    bool ParseIndexSubtypeDefinition(void);                     // -- Ch 3
    bool ParseIntegerTypeDefinition(void);                      // -- Ch 3
    bool ParseLaterDeclarativeItem(void);                       // -- Ch 3
    bool ParseNumberDeclaration(void);                          // -- Ch 3
    bool ParseObjectDeclaration(void);                          // -- Ch 3
    bool ParseProperBody(void);                                 // -- Ch 3
    bool ParseRange(void);                                      // -- Ch 3
    bool ParseRangeConstraint(void);                            // -- Ch 3
    bool ParseRealTypeDefinition(void);                         // -- Ch 3
    bool ParseRecordTypeDefinition(void);                       // -- Ch 3
    bool ParseSubtypeDeclaration(void);                         // -- Ch 3
    bool ParseSubtypeIndication(void);                          // -- Ch 3
    bool ParseTypeDeclaration(void);                            // -- Ch 3
    bool ParseTypeDefinition(void);                             // -- Ch 3
    bool ParseTypeMark(void);                                   // -- Ch 3
    bool ParseUnconstrainedArrayDefinition(void);               // -- Ch 3
    bool ParseVariant(void);                                    // -- Ch 3
    bool ParseVariantPart(void);                                // -- Ch 3


    bool ParseAttribute(void);
    bool ParseBodyStub(void);
    bool ParseDeferredConstantDeclaration(void) { return false; }
    bool ParseExceptionDeclaration(void) { return false; }
    bool ParseExpression(void) { tokens.Advance(); return true; }
    bool ParseGenericDeclaration(void) { return false; }
    bool ParseGenericInstantiation(void) { return false; }
    bool ParseName(void);
    bool ParsePackageBody(void) { return false; }
    bool ParsePackageDeclaration(void) { return false; }
    bool ParsePrivateTypeDeclaration(void) { return false; }
    bool ParseRenamingDeclaration(void) { return false; }
    bool ParseRepresentationClause(void) { return false; }
    bool ParseSimpleExpression(void) { tokens.Advance(); return true; }
    bool ParseSimpleName(void) { return ParseName(); }
    bool ParseSubprogramBody(void) { return false; }
    bool ParseSubprogramDeclaration(void) { return false; }
    bool ParseTaskBody(void) { return false; }
    bool ParseTaskDeclaration(void) { return false; }
    bool ParseUseClause(void) { return false; }

};




