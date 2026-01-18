# Century Ada Compiler

While I am building the AST, there are a fair number of parsing functions which already exist -- and I need to get them all accounted for and complete.  Well, I know me and I will miss something.

Therefore, I have created the following table here to make sure I keep track of what I have done and more importanly what still needs to be done.  It is important to understand that this file is expected to disappear at some point as it will no longer be necessary.


## How I collected this list

I made the choice at some point to split each grammar production into its own source file.  I placed the file into a `ch#` folder which indicates in what chapter I can find the formal definition of the production.  Each production is in a source of its own name.

With this decision, I was able to capitolize and run the following command to extract the file names:

```
find -type f  | awk -F/ '{ print $3 }' | awk -F. ' {print $1} ' | sort
```

The command was run from the `parser` folder.  The raw data from `find` was in the form `./ch#/<name>.cc`.  The first `awk` splits the results by the '/' character and presents the third field (`<name>.cc`).  Then awk was used again to strip the `.cc` from the `<name>`.  While this is more brute force than elegant, it only needed to be collected once.  The results are copied into the table below.


##


| Ch | Production                        | AST Class | `nullptr` | Extra Tasks | DeskCheck |
|:--:|:----------------------------------|:---------:|:---------:|:-----------:|:---------:|
|  3 | access-type-definition            |           |           |             |           |
|  4 | aggregate                         |     ✓     |           |             |           |
|  4 | allocator                         |     ✓     |           |             |           |
|  3 | array-type-definition             |           |           |             |           |
|  4 | attribute                         |     ✓     |           |             |           |
|  4 | attribute-designator              |     ✓     |           |             |           |
|  3 | basic-declaration                 |           |           |             |           |
|  3 | basic-declarative-item            |           |           |             |           |
|  4 | binary-adding-operator            |     ✓     |           |             |           |
|  3 | body                              |           |           |             |           |
|  3 | choice                            |     ✓     |           |             |           |
|  4 | component-association             |     ✓     |           |             |           |
|  3 | component-declaration             |           |           |             |           |
|  3 | component-list                    |           |           |             |           |
|  3 | component-subtype-definition      |           |           |             |           |
|  3 | constrained-array-definition      |           |           |             |           |
|  3 | constraint                        |           |           |             |           |
|  3 | declarative-part                  |           |           |             |           |
|  3 | derived-type-definition           |           |           |             |           |
|  3 | discrete_range                    |     ✓     |           |             |           |
|  3 | discriminant-association          |           |           |             |           |
|  3 | discriminant-constraint           |           |           |             |           |
|  3 | discriminant-part                 |           |           |             |           |
|  3 | discriminant-specification        |           |           |             |           |
|  3 | enumeration-literal               |     ✓     |           |             |           |
|  3 | enumeration-literal-specification |     ✓     |           |             |           |
|  3 | enumeration-type-definition       |     ✓     |           |             |           |
|  4 | expression                        |     ✓     |           |             |           |
|  4 | factor                            |     ✓     |           |             |           |
|  3 | fixed-accuracy-definition         |           |           |             |           |
|  3 | fixed-point-constraint            |     ✓     |           |             |           |
|  3 | floating-accuracy-definition      |           |           |             |           |
|  3 | floating-point-constraint         |     ✓     |           |             |           |
|  3 | full-type-declaration             |     ✓     |           |             |           |
|  3 | identifier-list                   |     ✓     |           |             |           |
|  3 | incomplete-type-declaration       |           |           |             |           |
|  3 | index-constraint                  |           |           |             |           |
|  4 | indexed-component                 |     ✓     |           |             |           |
|  3 | index-subtype_definition          |           |           |             |           |
|  3 | integer-type-definition           |     ✓     |           |             |           |
|  3 | later-declarative-item            |           |           |             |           |
|  4 | multiplying-operator              |     ✓     |           |             |           |
|  4 | name                              |     ✓     |           |             |           |
|  3 | number-declaration                |     ✓     |           |             |           |
|  3 | object-declaration                |     ✓     |           |             |           |
|  4 | prefix                            |     ✓     |           |             |           |
|  4 | primary                           |     ✓     |           |             |           |
|  3 | proper-body                       |           |           |             |           |
|  4 | qualified-expression              |     ✓     |           |             |           |
|  3 | range                             |     ✓     |           |             |           |
|  3 | range-constraint                  |     ✓     |           |             |           |
|  3 | real-type-definition              |           |           |             |           |
|  3 | record-type-definition            |           |           |             |           |
|  4 | relation                          |     ✓     |           |             |           |
|  4 | relational-operator               |     ✓     |           |             |           |
|  4 | selected-component                |     ✓     |           |             |           |
|  4 | selector                          |     ✓     |           |             |           |
|  4 | simple-expression                 |     ✓     |           |             |           |
|  4 | simple-name                       |     ✓     |           |             |           |
|  4 | slice                             |     ✓     |           |             |           |
|  3 | subtype_declaration               |           |           |             |           |
|  3 | subtype-indication                |     ✓     |           |             |           |
|  4 | term                              |     ✓     |           |             |           |
|  4 | type-conversion                   |     ✓     |           |             |           |
|  3 | type-declaration                  |           |           |             |           |
|  3 | type-definition                   |           |           |             |           |
|  3 | type-mark                         |           |           |             |           |
|  4 | unary-adding-operator             |     ✓     |           |             |           |
|  3 | unconstrained-array-definition    |           |           |             |           |
|  3 | variant                           |           |           |             |           |
|  3 | variant-part                      |           |           |             |           |


## Class hierarchy:

ChatGPT recommends:


```
ASTNode : (root)

Decl : ASTNode
  ObjectDecl : Decl
  TypeDecl : Decl
  SubtypeDecl : Decl
  NumberDecl : Decl
  ExceptionDecl : Decl
  RenamingDecl : Decl
  PackageDecl : Decl
  SubprogramDecl : Decl

TypeSpec : ASTNode
  SubtypeIndication : TypeSpec
  ConstrainedArrayType : TypeSpec
  EnumerationTypeSpec : TypeSpec
  RecordTypeSpec : TypeSpec
  AccessTypeSpec : TypeSpec

Stmt : ASTNode
  NullStmt : Stmt
  AssignmentStmt : Stmt
  IfStmt : Stmt
  CaseStmt : Stmt
  LoopStmt : Stmt
  ExitStmt : Stmt
  ReturnStmt : Stmt
  ProcedureCallStmt : Stmt
  BlockStmt : Stmt

Expr : ASTNode
  LiteralExpr : Expr
    IntegerLiteralExpr : LiteralExpr
    RealLiteralExpr : LiteralExpr
    CharLiteralExpr : LiteralExpr
    StringLiteralExpr : LiteralExpr
  NameExpr : Expr
  UnaryExpr : Expr
  BinaryExpr : Expr
  ShortCircuitExpr : Expr
  AggregateExpr : Expr
  QualifiedExpr : Expr

Name : ASTNode
  SimpleName : Name
  SelectedName : Name
  IndexedName : Name
  SliceName : Name
  AttributeName : Name

Constraint : ASTNode
  RangeConstraint : Constraint
  IndexConstraint : Constraint

DiscreteRange : ASTNode
  Range : DiscreteRange
  SubtypeRange : DiscreteRange

Choice : ASTNode
  ChoiceExpr : Choice
  ChoiceRange : Choice
  ChoiceOthers : Choice
```

