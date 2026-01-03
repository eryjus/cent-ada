//=================================================================================================================
//  parser.hh -- Define the structures and classes for the Parser
//
//        Copyright (c)  2025-2026 -- Adam Clark; See LICENSE.md
//
// ---------------------------------------------------------------------------------------------------------------
//
//     Date      Tracker  Version  Pgmr  Description
//  -----------  -------  -------  ----  -------------------------------------------------------------------------
//  2025-Dec-10  Initial   0.0.0   ADCL  Initial version
//
//=================================================================================================================



//
// -- This is the definition of an Id in the Parser
//    ---------------------------------------------
struct Id {
    std::string name;
    SourceLoc_t loc;
};

using IdList = std::vector<Id>;


//
// -- This class will handle the entirety of the parser
//    -------------------------------------------------
class Parser {
private:
    TokenStream &tokens;
    std::vector<std::string> stack;
    ScopeManager scopes;


private:
    class MarkStream {
        MarkStream(const MarkStream &) = delete;
        MarkStream &operator=(const MarkStream &) = delete;


    private:
        TokenStream &ts;
        Diagnostics &diag;
        int saved;
        bool committed;
        size_t chkpt;
        static int depth;
        int errors;
        int warnings;


    public:
        MarkStream(TokenStream &t, Diagnostics &d) :
                ts(t), diag(d), saved(ts.Location()), committed(false), errors(d.Errors()), warnings(d.Warnings()) {
            ++depth;
            chkpt = diag.Checkpoint();
        }

        ~MarkStream() {
            --depth;
            assert(depth >= 0);

            if (!committed) {
                ts.Reset(saved);
                diag.Rollback(chkpt);
                diag.Errors() = errors;
                diag.Warnings() = warnings;
            }

            if (depth == 0) diag.Flush();
        }

    public:
        //
        // -- Parse in a single production has failed this far (typically an optional leading phrase)
        //    and we need to reset to try the latter part.
        //    ---------------------------------------------------------------------------------------
        void Reset(void) { committed = false; ts.Reset(saved); }
        //
        // -- The following member method may be used for any production whether tokens are directly
        //    consumed or not.
        //    ------------------------------------------------------------------------------------
        void Commit(void) { committed = true; }

        //
        // -- The following member method can only be used when no tokens are directly consumed in
        //    the production.  It is provided ONLY for ease of coding in lists of alternative
        //    productions such as `basic_declaration`.
        //    ------------------------------------------------------------------------------------
        bool CommitIf(bool c) { if (c) { committed = true; } else { Reset(); } return c; }
    };


private:
    class MarkScope {
        MarkScope(const MarkScope &) = delete;
        MarkScope &operator=(const MarkScope &) = delete;


    private:
        ScopeManager &mgr;
        bool committed = false;
        size_t stackCkpt;
        size_t scopeCkpt;


    public:
        MarkScope(ScopeManager &m) : mgr(m) {
            stackCkpt = m.stack.size();
            scopeCkpt = m.CurrentScope()->Checkpoint();
        }
        ~MarkScope() {
            if (!committed) {
                // -- roll back any added scopes
                while (mgr.stack.size() > stackCkpt) {
                    { // -- this creates a local scope in the loop to own the pointer for a short time
                        std::unique_ptr<Scope> s = std::move(mgr.stack.back());
                        mgr.stack.pop_back();
                    }

                    // -- should be nothing else to do
                }


                // -- rollback the symbols added in the original scope
                mgr.CurrentScope()->Rollback(scopeCkpt);
            }
        }


    public:
        Scope *Commit(void) { committed = true; return mgr.CurrentScope(); }
    };


private:
    class MarkSymbols {
    private:
        ScopeManager &mgr;
        size_t checkpoint;
        bool committed;

    public:
        MarkSymbols(ScopeManager &m) : mgr(m), checkpoint(mgr.CurrentScope()->Checkpoint()), committed(false) {}
        ~MarkSymbols() {
            if (!committed) {
                mgr.CurrentScope()->Rollback(checkpoint);
            }
        }

    public:
        void Commit(void) { committed = true; }
    };


private:
    class Production {
    private:
        Parser &parser;

    public:
        Production(Parser &parser, std::string p) : parser(parser)
        {
            if (opts.trace) std::cerr << "Entering " << p << " from " << parser.Last() << '\n';
            parser.stack.push_back(std::move(p));
            std::cerr.flush();
        }
        ~Production() {
            if (opts.trace) std::cerr << "Leaving " << parser.Last() << '\n';
            parser.stack.pop_back();
            std::cerr.flush();
        }
    };



public:
    Parser(TokenStream &s) : tokens(s) {}
    virtual ~Parser() = default;


public:
    // -- a token is illegal and if found is an illegal parse -- check only, never consumes
    bool Illegal(TokenType tok) {
        if (tokens.Current() == tok) {
            return true;
        }
        return false;
    }
    // -- a token is optional and if found advance past it
    bool Optional(TokenType tok) {
        if (tokens.Current() == tok) {
            tokens.Advance();
            return true;
        }
        return false;
    }
    // -- a token is required to be next
    bool Require(TokenType tok) {
        if (tokens.Current() == tok) {
            tokens.Advance();
            return true;
        }

        return false;
    }
    // -- DEPRECATED: An identifier is required to be next
    bool RequireIdent(std::string &id) {
        id = "";
        if (tokens.Current() == TokenType::TOK_IDENTIFIER) {
            id = std::get<IdentifierLexeme>(tokens.Payload()).name;
            tokens.Advance();
            return true;
        }
        return false;
    }

    // -- An identifier is required to be next
    bool RequireIdent(Id &id) {
        id.name = "";
        id.loc = tokens.SourceLocation();

        if (tokens.Current() == TokenType::TOK_IDENTIFIER) {
            id.name = std::get<IdentifierLexeme>(tokens.Payload()).name;
            tokens.Advance();
            return true;
        }
        return false;
    }

    std::string Last(void) { if (stack.size() == 0) return "top level"; return stack[stack.size() - 1]; }
    void Push(std::string p) { stack.push_back(p); }
    void Pop(void) { stack.pop_back(); }
    const ScopeManager *Scopes(void) const { return &scopes; }
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
    //
    // -- Productions from Declarations and Types
    //    ---------------------------------------
    bool ParseAccessTypeDefinition(Id &id);
    bool ParseArrayTypeDefinition(Id &id);
    bool ParseBasicDeclaration(void);
    bool ParseBasicDeclarativeItem(void);
    bool ParseBody(void);
    bool ParseChoice(void);
    bool ParseComponentDeclaration(RecordTypeSymbol *rec);
    bool ParseComponentList(RecordTypeSymbol *rec);
    bool ParseComponentSubtypeDefinition(void);
    bool ParseConstrainedArrayDefinition(Id &id);
    bool ParseConstrainedArrayDefinition(IdList *);
    bool ParseConstraint(void);
    bool ParseDeclarativePart(void);
    bool ParseDerivedTypeDefinition(Id &id);
    bool ParseDiscreteRange(void);
    bool ParseDiscriminantAssociation(void);
    bool ParseDiscriminantConstraint(void);
    bool ParseDiscriminantPart(void);
    bool ParseDiscriminantSpecification(void);
    bool ParseEnumerationLiteral(EnumTypeSymbol *type);
    bool ParseEnumerationLiteralSpecification(EnumTypeSymbol *type);
    bool ParseEnumerationTypeDefinition(Id &id);
    bool ParseFixedAccuracyDefinition(void);
    bool ParseFixedPointConstraint(Id &id);
    bool ParseFloatingAccuracyDefinition(void);
    bool ParseFloatingPointConstraint(Id &id);
    bool ParseFullTypeDeclaration(void);
    bool ParseIdentifierList(IdList *ids);
    bool ParseIncompleteTypeDeclaration(void);
    bool ParseIndexConstraint(void);
    bool ParseIndexSubtypeDefinition(void);
    bool ParseIntegerTypeDefinition(Id &id);
    bool ParseLaterDeclarativeItem(void);
    bool ParseNumberDeclaration(void);
    bool ParseObjectDeclaration(void);
    bool ParseProperBody(void);
    bool ParseRange(void);
    bool ParseRangeConstraint(void);
    bool ParseRealTypeDefinition(Id &id);
    bool ParseRecordTypeDefinition(Id &id);
    bool ParseSubtypeDeclaration(void);
    SubtypeIndicationPtr ParseSubtypeIndication(void);
    bool ParseTypeDeclaration(void);
    bool ParseTypeDefinition(Id &id);
    bool ParseTypeMark(void);
    bool ParseUnconstrainedArrayDefinition(Id &id);
    bool ParseVariant(RecordTypeSymbol *rec);
    bool ParseVariantPart(RecordTypeSymbol *rec);
    bool _HelpParseConstrainedArrayDefinition(void);



    //
    // -- Productions from Names and Expressions
    //    --------------------------------------
    bool ParseAggregate(void);                                  // -- Ch 4: in `parse_expr.cc`
    bool ParseAggregateMore(void);                              // -- Ch 4: in `parse_expr.cc`
    bool ParseAllocator(void);                                  // -- Ch 4: in `parse_expr.cc`
    bool ParseAttribute(void);                                  // -- Ch 4: in `parse_expr.cc`
    bool ParseAttributeDesignator(void);                        // -- Ch 4: in `parse_expr.cc`
    bool ParseBinaryAddingOperator(void);                       // -- Ch 4: in `parse_expr.cc`
    bool ParseComponentAssociation(void);                       // -- Ch 4: in `parse_expr.cc`
    bool ParseExpression(void);                                 // -- Ch 4: in `parse_expr.cc`
    bool ParseFactor(void);                                     // -- Ch 4: in `parse_expr.cc`
    bool ParseIndexedComponent(void);                           // -- Ch 4: in `parse_expr.cc`
    bool ParseMultiplyingOperator(void);                        // -- Ch 4: in `parse_expr.cc`
    bool ParseNameNonExpr(Id &id);                              // -- Ch 4: in `parse_expr.cc`
    bool ParseNameExpr(Id &id);                                 // -- Ch 4: in `parse_expr.cc`
    bool ParseName_Base(Id &id);                                // -- Ch 4: in `parse_expr.cc`
    bool ParseName_Postfix(void);                               // -- Ch 4: in `parse_expr.cc`
    bool ParseTypeName(void);
    bool ParseSubtypeName(void);
    bool ParsePrefix(void);                                     // -- Ch 4: in `parse_expr.cc`
    bool ParsePrimary(void);                                    // -- Ch 4: in `parse_expr.cc`
    bool ParseQualifiedExpression(void);                        // -- Ch 4: in `parse_expr.cc`
    bool ParseRelation(void);                                   // -- Ch 4: in `parse_expr.cc`
    bool ParseRelationalOperator(void);                         // -- Ch 4: in `parse_expr.cc`
    bool ParseSelectedComponent(void);                          // -- Ch 4: in `parse_expr.cc`
    bool ParseSelector(void);                                   // -- Ch 4: in `parse_expr.cc`
    bool ParseSimpleExpression(void);                           // -- Ch 4: in `parse_expr.cc`
    bool ParseSimpleName(Id &id);                               // -- Ch 4: in `parse_expr.cc`
    bool ParseSlice(void);                                      // -- Ch 4: in `parse_expr.cc`
    bool ParseTerm(void);                                       // -- Ch 4: in `parse_expr.cc`
    bool ParseTypeConversion(void);                             // -- Ch 4: in `parse_expr.cc`
    bool ParseUnaryAddingOperator(void);                        // -- Ch 4: in `parse_expr.cc`
    bool ParseName_IndexComponentSuffix(void);                  // -- Ch 4: in `parse_expr.cc`
    bool ParseName_SliceSuffix(void);                           // -- Ch 4: in `parse_expr.cc`
    bool ParseName_SelectedComponentSuffix(void);               // -- Ch 4: in `parse_expr.cc`
    bool ParseName_AttributeSuffix(void);                       // -- Ch 4: in `parse_expr.cc`
    bool ParseName_IndexOrSliceSuffix(void);                    // -- Ch 4: in `parse_expr.cc`





    bool ParseFunctionCall(void) { return false; }
    bool ParseOperatorSymbol(void) { return false; }
    bool ParseBodyStub(void) { return false; }
    bool ParseDeferredConstantDeclaration(void) { return false; }
    bool ParseExceptionDeclaration(void) { return false; }
    bool ParseGenericDeclaration(void) { return false; }
    bool ParseGenericInstantiation(void) { return false; }
    bool ParsePackageBody(void) { return false; }
    bool ParsePackageDeclaration(void) { return false; }
    bool ParsePrivateTypeDeclaration(void) { return false; }
    bool ParseRenamingDeclaration(void) { return false; }
    bool ParseRepresentationClause(void) { return false; }
    bool ParseSubprogramBody(void) { return false; }
    bool ParseSubprogramDeclaration(void) { return false; }
    bool ParseTaskBody(void) { return false; }
    bool ParseTaskDeclaration(void) { return false; }
    bool ParseUseClause(void) { return false; }

    bool ParseUniversalStaticExpression(void) { return ParseExpression(); }
    bool ParseRangeAttribute(void) { return ParseAttribute(); }
    bool ParseStaticSimpleExpression(void) { return ParseSimpleExpression(); }
    bool ParseDiscriminantSimpleName(Id &id) { return ParseSimpleName(id); }



    bool ParseComponentSubtypeIndication(void) { return ParseSubtypeIndication() != nullptr; }
    bool ParseDiscreteSubtypeIndication(void) { return ParseSubtypeIndication() != nullptr; }



};




