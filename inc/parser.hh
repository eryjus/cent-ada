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
    bool ParseAccessTypeDefinition(void);
    bool ParseArrayTypeDefinition(const std::string &id);
    bool ParseBasicDeclaration(void);
    bool ParseBasicDeclarativeItem(void);
    bool ParseBody(void);
    bool ParseChoice(void);
    bool ParseComponentDeclaration(void);
    bool ParseComponentList(void);
    bool ParseComponentSubtypeDefinition(void);
    bool ParseConstrainedArrayDefinition(const std::string &id);
    bool ParseConstrainedArrayDefinition(IdList *);
    bool ParseConstraint(void);
    bool ParseDeclarativePart(void);
    bool ParseDerivedTypeDefinition(const std::string &id);
    bool ParseDiscreteRange(void);
    bool ParseDiscriminantAssociation(void);
    bool ParseDiscriminantConstraint(void);
    bool ParseDiscriminantPart(void);
    bool ParseDiscriminantSpecification(void);
    bool ParseEnumerationLiteral(EnumTypeSymbol *type);
    bool ParseEnumerationLiteralSpecification(EnumTypeSymbol *type);
    bool ParseEnumerationTypeDefinition(const std::string &id);
    bool ParseFixedAccuracyDefinition(void);
    bool ParseFixedPointConstraint(void);
    bool ParseFloatingAccuracyDefinition(void);
    bool ParseFloatingPointConstraint(void);
    bool ParseFullTypeDeclaration(void);
    bool ParseIdentifierList(IdList *ids);
    bool ParseIncompleteTypeDeclaration(void);
    bool ParseIndexConstraint(void);
    bool ParseIndexSubtypeDefinition(void);
    bool ParseIntegerTypeDefinition(void);
    bool ParseLaterDeclarativeItem(void);
    bool ParseNumberDeclaration(void);
    bool ParseObjectDeclaration(void);
    bool ParseProperBody(void);
    bool ParseRange(void);
    bool ParseRangeConstraint(void);
    bool ParseRealTypeDefinition(void);
    bool ParseRecordTypeDefinition(void);
    bool ParseSubtypeDeclaration(void);
    bool ParseSubtypeIndication(void);
    bool ParseTypeDeclaration(void);
    bool ParseTypeDefinition(const std::string &id);
    bool ParseTypeMark(void);
    bool ParseUnconstrainedArrayDefinition(const std::string &id);
    bool ParseVariant(void);
    bool ParseVariantPart(void);
    bool _HelpParseConstrainedArrayDefinition(void);




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
    bool ParseNameNonExpr(std::string &id);                     // -- Ch 4: in `parse_expr.cc`
    bool ParseNameExpr(std::string &id);                        // -- Ch 4: in `parse_expr.cc`
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

    bool ParseUniversalStaticExpression(void) { return ParseExpression(); }
    bool ParseRangeAttribute(void) { return ParseAttribute(); }
    bool ParseStaticSimpleExpression(void) { return ParseSimpleExpression(); }
    bool ParseDiscriminantSimpleName(std::string &id) { return ParseSimpleName(id); }



    bool ParseComponentSubtypeIndication(void) { return ParseSubtypeIndication(); }
    bool ParseDiscreteSubtypeIndication(void) { return ParseSubtypeIndication(); }



    bool ParseTypeName(void) {
        std::string id;
        if (!ParseNameNonExpr(id)) return false;
        const std::vector<Symbol *> *vec = scopes.Lookup(id);
        if (!vec || vec->empty()) return false;
        for (int i = 0; i < vec->size(); i ++) {
            if (vec->at(i)->kind == Symbol::SymbolKind::Type) return true;
        }

        return false;
    }
    bool ParseSubtypeName(void) {
        std::string id;
        if (!ParseNameNonExpr(id)) return false;
        const std::vector<Symbol *> *vec = scopes.Lookup(id);
        if (!vec || vec->empty()) return false;
        for (int i = 0; i < vec->size(); i ++) {
            if (vec->at(i)->kind == Symbol::SymbolKind::Type) {
                TypeSymbol *tp = static_cast<TypeSymbol *>(vec->at(i));
                if (tp->category == TypeSymbol::TypeCategory::Subtype) {
                    return true;
                }
            }
        }

        return false;
    }

};




