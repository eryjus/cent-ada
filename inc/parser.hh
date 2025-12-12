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


private:
    class Mark {
    private:
        TokenStream &ts;
        int saved;
        bool committed;

    public:
        Mark(TokenStream &t) : ts(t), saved(ts.Location()), committed(false) {}
        ~Mark() { if (!committed) ts.Reset(saved); }

    public:
        void Commit(void) { committed = true; }
    };



public:
    Parser(TokenStream &s) : tokens(s) {}
    virtual ~Parser() = default;


public:
    // -- a token is optional and if found advance past it
    bool Optional(TokenType_t tok) {
        if (tokens.Current() != tok) return false;
        tokens.Advance();
        return true;
    }
    // -- a token is required to be next
    bool Require(TokenType_t tok) {
        if (tokens.Current() != tok) return false;
        tokens.Advance();
        return true;
    }


public:
    bool ParseAccessTypeDefinition(void);                       // -- Ch 3
    bool ParseArrayTypeDefinition(void);                        // -- Ch 3
    bool ParseAttribute(void) { return false; }
    bool ParseBasicDeclaration(void);                           // -- Ch 3
    bool ParseBasicDeclarativeItem(void);                       // -- Ch 3
    bool ParseBody(void);                                       // -- Ch 3
    bool ParseBodyStub(void) { return false; }
    bool ParseChoice(void);                                     // -- Ch 3
    bool ParseComponentDeclaration(void);                       // -- Ch 3
    bool ParseComponentList(void);                              // -- Ch 3
    bool ParseComponentSubtypeDefinition(void);                 // -- Ch 3
    bool ParseConstrainedArrayDefinition(void);                 // -- Ch 3
    bool ParseConstrant(void);                                  // -- Ch 3
    bool ParseConstrinedArrayDefinition(void) { return false; }
    bool ParseDeclarativePart(void);                            // -- Ch 3
    bool ParseDeferredConstantDeclaration(void) { return false; }
    bool ParseDerivedTypeDefinition(void);                      // -- Ch 3
    bool ParseDiscreteRange(void);                              // -- Ch 3
    bool ParseDiscriminantAssociation(void);                    // -- Ch 3
    bool ParseDiscriminantConstraint(void);                     // -- Ch 3
    bool ParseDiscriminantPart(void);                           // -- Ch 3
    bool ParseDiscriminantSpecification(void);                  // -- Ch 3
    bool ParseEnumerationLiteral(void);                         // -- Ch 3
    bool ParseEnumerationLiteralSpecification(void);            // -- Ch 3
    bool ParseEnumerationTypeDefinition(void);                  // -- Ch 3
    bool ParseExpeptionDeclaration(void) { return false; }
    bool ParseExpression(void) { return false; }
    bool ParseFixedAccuracyDefinition(void);                    // -- Ch 3
    bool ParseFixedPointConstraint(void);                       // -- Ch 3
    bool ParseFloatingAccuracyDefinition(void);                 // -- Ch 3
    bool ParseFloatingPointConstraint(void);                    // -- Ch 3
    bool ParseFullTypeDeclaration(void);                        // -- Ch 3
    bool ParseGenericDeclaration(void) { return false; }
    bool ParseGenericInstantiation(void) { return false; }
    bool ParseIdentifierList(void);                             // -- Ch 3
    bool ParseIncompleteTypeDeclaration(void);                  // -- Ch 3
    bool ParseIndexConstraint(void);                            // -- Ch 3
    bool ParseIndexSubtypeDefinition(void);                     // -- Ch 3
    bool ParseIntegerTypeDefinition(void);                      // -- Ch 3
    bool ParseLaterDeclarativeItem(void);                       // -- Ch 3
    bool ParseName(void) { return false; }
    bool ParseNumberDeclaration(void);                          // -- Ch 3
    bool ParseObjectDeclaration(void);                          // -- Ch 3
    bool ParsePackageBody(void) { return false; }
    bool ParsePackageDeclaration(void) { return false; }
    bool ParsePrivateTypeDeclaration(void) { return false; }
    bool ParseProperBody(void);                                 // -- Ch 3
    bool ParseRange(void);                                      // -- Ch 3
    bool ParseRangeConstraint(void);                            // -- Ch 3
    bool ParseRealTypeDefinition(void);                         // -- Ch 3
    bool ParseRecordTypeDefinition(void);                       // -- Ch 3
    bool ParseRenamingDeclaration(void) { return false; }
    bool ParseRepresentationClause(void) { return false; }
    bool ParseSimpleExpression(void) { return false; }
    bool ParseSimpleName(void) { return false; }
    bool ParseSubprogramBody(void) { return false; }
    bool ParseSubprogramDeclaration(void) { return false; }
    bool ParseSubtypeDeclaration(void);                         // -- Ch 3
    bool ParseSubtypeIndication(void);                          // -- Ch 3
    bool ParseTaskBody(void) { return false; }
    bool ParseTaskDeclaration(void) { return false; }
    bool ParseTypeDeclaration(void);                            // -- Ch 3
    bool ParseTypeDefinition(void);                             // -- Ch 3
    bool ParseTypeMark(void);                                   // -- Ch 3
    bool ParseUnconstrainedArrayDefinition(void);               // -- Ch 3
    bool ParseUseClause(void) { return false; }
    bool ParseVariant(void);                                    // -- Ch 3
    bool ParseVariantPart(void);                                // -- Ch 3
};




