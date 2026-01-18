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
    bool _HelpParseConstrainedArrayDefinition(void);
    bool ParseAccessTypeDefinition(Id &id);
    bool ParseArrayTypeDefinition(Id &id);
    bool ParseBasicDeclarativeItem(void);
    bool ParseBody(void);
    bool ParseComponentDeclaration(RecordTypeSymbol *rec);
    bool ParseComponentList(RecordTypeSymbol *rec);
    bool ParseComponentSubtypeDefinition(void);
    bool ParseConstrainedArrayDefinition(Id &id);
    bool ParseConstrainedArrayDefinition(IdList *);
    bool ParseConstraint(void);
    bool ParseDeclarativePart(void);
    bool ParseDerivedTypeDefinition(Id &id);
    bool ParseDiscriminantAssociation(void);
    bool ParseDiscriminantConstraint(void);
    bool ParseDiscriminantPart(void);
    bool ParseDiscriminantSpecification(void);
    ExprPtr ParseFixedAccuracyDefinition(void);
    ExprPtr ParseFloatingAccuracyDefinition(void);
    bool ParseIncompleteTypeDeclaration(void);
    bool ParseIndexSubtypeDefinition(void);
    bool ParseLaterDeclarativeItem(void);
    bool ParseProperBody(void);
    NumericTypeSpecPtr ParseRealTypeDefinition(Id &id);
    bool ParseRecordTypeDefinition(Id &id);
    bool ParseSubtypeDeclaration(void);
    bool ParseTypeDeclaration(void);
    bool ParseTypeDefinition(Id &id);
    bool ParseUnconstrainedArrayDefinition(Id &id);
    bool ParseVariant(RecordTypeSymbol *rec);
    bool ParseVariantPart(RecordTypeSymbol *rec);
    ChoicePtr ParseChoice(void);
    DiscreteRangePtr ParseDiscreteRange(void);
    DiscreteRangePtr ParseRange(void);
    Id ParseEnumerationLiteral(EnumTypeSymbol *type);
    Id ParseEnumerationLiteralSpecification(EnumTypeSymbol *type);
    Id ParseTypeMark(void);
    IdListPtr ParseIdentifierList(void);
    NodePtr ParseBasicDeclaration(void);
    NumberDeclarationPtr ParseNumberDeclaration(void);
    NumericTypeSpecPtr ParseFixedPointConstraint(Id &id);
    NumericTypeSpecPtr ParseFloatingPointConstraint(Id &id);
    ObjectDeclarationPtr ParseObjectDeclaration(void);
    RangeConstraintPtr ParseRangeConstraint(void);
    std::unique_ptr<std::vector<DiscreteRangePtr>> ParseIndexConstraint(void);
    SubtypeIndicationPtr ParseSubtypeIndication(void);
    TypeDeclPtr ParseFullTypeDeclaration(void);
    TypeSpecPtr ParseEnumerationTypeDefinition(Id &id);
    TypeSpecPtr ParseIntegerTypeDefinition(Id &id);



    //
    // -- Productions from Names and Expressions
    //    --------------------------------------
    AllocatorExprPtr ParseAllocator(void);
    AttributeNamePtr ParseAttribute(void);
    BinaryOper ParseBinaryAddingOperator(void);
    BinaryOper ParseMultiplyingOperator(void);
    BinaryOper ParseRelationalOperator(void);
    ComponentAssociationPtr ParseComponentAssociation(void);
    ExprPtr ParseAggregate(void);
    ExprPtr ParseExpression(void);
    ExprPtr ParseFactor(void);
    ExprPtr ParsePrimary(void);
    ExprPtr ParseRelation(void);
    ExprPtr ParseSimpleExpression(void);
    ExprPtr ParseTerm(void);
    ExprPtr ParseTypeConversion(void);
    Id ParseSubtypeName(void);
    Id ParseTypeName(void);
    IndexedNamePtr ParseIndexedComponent(void);
    NamePtr ParseAttributeDesignator(NamePtr &);
    NamePtr ParseName_AttributeSuffix(NamePtr &);
    NamePtr ParseName_Base(void);
    NamePtr ParseName_IndexComponentSuffix(NamePtr &prefix);
    NamePtr ParseName_IndexOrSliceSuffix(NamePtr &prefix);
    NamePtr ParseName_Postfix(NamePtr &prefix);
    NamePtr ParseName_SelectedComponentSuffix(NamePtr &prefix);
    NamePtr ParseName_SliceSuffix(NamePtr &prefix);
    NamePtr ParseNameExpr(void);
    NamePtr ParseNameNonExpr(void);
    NamePtr ParsePrefix(void);
    NamePtr ParseSimpleName(void);
    QualifiedExprPtr ParseQualifiedExpression(void);
    SelectedNamePtr ParseSelectedComponent(void);
    SelectedNamePtr ParseSelector(NamePtr &prefix);
    SliceNamePtr ParseSlice(void);
    UnaryOper ParseUnaryAddingOperator(void);





    NamePtr ParseFunctionCall(void) { return nullptr; }
    NamePtr ParseOperatorSymbol(void) { return nullptr; }
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

    ExprPtr ParseUniversalStaticExpression(void) { return std::move(ParseExpression()); }
    AttributeNamePtr ParseRangeAttribute(void) { return std::move(ParseAttribute()); }
    ExprPtr ParseStaticSimpleExpression(void) { return std::move(ParseSimpleExpression()); }
    NamePtr ParseDiscriminantSimpleName(void) { return std::move(ParseSimpleName()); }



    bool ParseComponentSubtypeIndication(void) { return ParseSubtypeIndication() != nullptr; }
    DiscreteRangePtr ParseDiscreteSubtypeIndication(void);



};



using IdList = std::vector<Id>;
using IdListPtr = std::unique_ptr<IdList>;

