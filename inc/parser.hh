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
    ScopeManager scopes;


private:
    typedef struct Id {
        std::string name;
        SourceLoc_t loc;
    } Id;

    typedef std::vector<Id> IdList;

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
        bool CommitIf(bool c) { if (c) { committed = true; } return c; }
    };


private:
    class MarkScope {
        MarkScope(const MarkScope &) = delete;
        MarkScope &operator=(const MarkScope &) = delete;


    private:
        ScopeManager &mgr;


    public:
        MarkScope(ScopeManager &m, Scope::Kind kind) : mgr(m) { mgr.PushScope(kind); }
        ~MarkScope() { mgr.PopScope(); }


    public:
        std::unique_ptr<Scope> Commit(void) { return std::move(mgr.ClaimCurrentScope()); }
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
        static bool trace;

    public:
        Production(Parser &parser, std::string p) : parser(parser) {
            if (trace) std::cerr << "Entering " << p << " from " << parser.Last() << '\n';
            parser.stack.push_back(std::move(p));
            std::cerr.flush();
        }
        ~Production() {
            if (trace) std::cerr << "Leaving " << parser.Last() << '\n';
            parser.stack.pop_back();
            std::cerr.flush();
        }


    public:
        static void SetTrace(bool t) { trace = t; }
    };



public:
    Parser(TokenStream &s) : tokens(s) {}
    virtual ~Parser() = default;


public:
    // -- a token is illegal and if found is an illegal parse -- check only, never consumes
    bool Illegal(TokenType_t tok) {
        if (tokens.Current() == tok) {
            return true;
        }
        return false;
    }
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
    // -- An identifier is required to be next
    bool RequireIdent(std::string &id) {
        id = "";
        if (tokens.Current() == TOK_IDENTIFIER) {
            id = *(tokens.Payload().ident);
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

    void CheckLocalId(std::string &id, SourceLoc_t loc, SymbolKind kind) {
        if (scopes.IsLocalDefined(id)) {
            Symbol *sym = scopes.CurrentScope()->LocalLookup(id);

            if (kind == SymbolKind::Type && sym->kind == SymbolKind::IncompleteType) {
                sym->kind = kind;
                return;
            }

            diags.Error(loc, DiagID::DuplicateName, { id } );
            diags.Note(scopes.CurrentScope()->LocalLookup(id)->loc, DiagID::DuplicateName2);
        } else {
            std::unique_ptr<Symbol> sym = std::make_unique<Symbol>(id, kind, loc);
            scopes.Declare(std::move(sym));
        }
    }


public:
    bool ParseAccessTypeDefinition(void);                       // -- Ch 3: in `parse_decl.cc`
    bool ParseArrayTypeDefinition(void);                        // -- Ch 3: in `parse_decl.cc`
    bool ParseBasicDeclaration(void);                           // -- Ch 3: in `parse_decl.cc`
    bool ParseBasicDeclarativeItem(void);                       // -- Ch 3: in `parse_decl.cc`
    bool ParseBody(void);                                       // -- Ch 3: in `parse_decl.cc`
    bool ParseChoice(void);                                     // -- Ch 3: in `parse_decl.cc`
    bool ParseComponentDeclaration(void);                       // -- Ch 3: in `parse_decl.cc`
    bool ParseComponentList(void);                              // -- Ch 3: in `parse_decl.cc`
    bool ParseComponentSubtypeDefinition(void);                 // -- Ch 3: in `parse_decl.cc`
    bool ParseConstrainedArrayDefinition(void);                 // -- Ch 3: in `parse_decl.cc`
    bool ParseConstraint(void);                                 // -- Ch 3: in `parse_decl.cc`
    bool ParseDeclarativePart(void);                            // -- Ch 3: in `parse_decl.cc`
    bool ParseDerivedTypeDefinition(void);                      // -- Ch 3: in `parse_decl.cc`
    bool ParseDiscreteRange(void);                              // -- Ch 3: in `parse_decl.cc`
    bool ParseDiscriminantAssociation(void);                    // -- Ch 3: in `parse_decl.cc`
    bool ParseDiscriminantConstraint(void);                     // -- Ch 3: in `parse_decl.cc`
    bool ParseDiscriminantPart(void);                           // -- Ch 3: in `parse_decl.cc`
    bool ParseDiscriminantSpecification(void);                  // -- Ch 3: in `parse_decl.cc`
    bool ParseEnumerationLiteral(void);                         // -- Ch 3: in `parse_decl.cc`
    bool ParseEnumerationLiteralSpecification(void);            // -- Ch 3: in `parse_decl.cc`
    bool ParseEnumerationTypeDefinition(void);                  // -- Ch 3: in `parse_decl.cc`
    bool ParseFixedAccuracyDefinition(void);                    // -- Ch 3: in `parse_decl.cc`
    bool ParseFixedPointConstraint(void);                       // -- Ch 3: in `parse_decl.cc`
    bool ParseFloatingAccuracyDefinition(void);                 // -- Ch 3: in `parse_decl.cc`
    bool ParseFloatingPointConstraint(void);                    // -- Ch 3: in `parse_decl.cc`
    bool ParseFullTypeDeclaration(void);                        // -- Ch 3: in `parse_decl.cc`
    bool ParseIdentifierList(IdList *ids);                      // -- Ch 3: in `parse_decl.cc`
    bool ParseIncompleteTypeDeclaration(void);                  // -- Ch 3: in `parse_decl.cc`
    bool ParseIndexConstraint(void);                            // -- Ch 3: in `parse_decl.cc`
    bool ParseIndexSubtypeDefinition(void);                     // -- Ch 3: in `parse_decl.cc`
    bool ParseIntegerTypeDefinition(void);                      // -- Ch 3: in `parse_decl.cc`
    bool ParseLaterDeclarativeItem(void);                       // -- Ch 3: in `parse_decl.cc`
    bool ParseNumberDeclaration(void);                          // -- Ch 3: in `parse_decl.cc`
    bool ParseObjectDeclaration(void);                          // -- Ch 3: in `parse_decl.cc`
    bool ParseProperBody(void);                                 // -- Ch 3: in `parse_decl.cc`
    bool ParseRange(void);                                      // -- Ch 3: in `parse_decl.cc`
    bool ParseRangeConstraint(void);                            // -- Ch 3: in `parse_decl.cc`
    bool ParseRealTypeDefinition(void);                         // -- Ch 3: in `parse_decl.cc`
    bool ParseRecordTypeDefinition(void);                       // -- Ch 3: in `parse_decl.cc`
    bool ParseSubtypeDeclaration(void);                         // -- Ch 3: in `parse_decl.cc`
    bool ParseSubtypeIndication(void);                          // -- Ch 3: in `parse_decl.cc`
    bool ParseTypeDeclaration(void);                            // -- Ch 3: in `parse_decl.cc`
    bool ParseTypeDefinition(void);                             // -- Ch 3: in `parse_decl.cc`
    bool ParseTypeMark(void);                                   // -- Ch 3: in `parse_decl.cc`
    bool ParseUnconstrainedArrayDefinition(void);               // -- Ch 3: in `parse_decl.cc`
    bool ParseVariant(void);                                    // -- Ch 3: in `parse_decl.cc`
    bool ParseVariantPart(void);                                // -- Ch 3: in `parse_decl.cc`

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
    bool ParseNameNonExpr(std::string &id);                            // -- Ch 4: in `parse_expr.cc`
    bool ParseNameExpr(std::string &id);                            // -- Ch 4: in `parse_expr.cc`
    bool ParseName_Base(std::string &id);                       // -- Ch 4: in `parse_expr.cc`
    bool ParseName_Postfix(void);                               // -- Ch 4: in `parse_expr.cc`
    bool ParsePrefix(void);                                     // -- Ch 4: in `parse_expr.cc`
    bool ParsePrimary(void);                                    // -- Ch 4: in `parse_expr.cc`
    bool ParseQualifiedExpression(void);                        // -- Ch 4: in `parse_expr.cc`
    bool ParseRelation(void);                                   // -- Ch 4: in `parse_expr.cc`
    bool ParseRelationalOperator(void);                         // -- Ch 4: in `parse_expr.cc`
    bool ParseSelectedComponent(void);                          // -- Ch 4: in `parse_expr.cc`
    bool ParseSelector(void);                                   // -- Ch 4: in `parse_expr.cc`
    bool ParseSimpleExpression(void);                           // -- Ch 4: in `parse_expr.cc`
    bool ParseSimpleName(std::string &id);                      // -- Ch 4: in `parse_expr.cc`
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

};




