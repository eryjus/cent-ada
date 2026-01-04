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


| Production                        | AST Node Defined | AST Node Constructed | Final Output Confirmed |
|:----------------------------------|:----------------:|:--------------------:|:----------------------:|
| access-type-definition            |                  |                      |                        |
| aggregate                         |                  |                      |                        |
| allocator                         |                  |                      |                        |
| array-type-definition             |                  |                      |                        |
| attribute                         |                  |                      |                        |
| attribute-designator              |                  |                      |                        |
| basic-declaration                 |                  |                      |                        |
| basic-declarative-item            |                  |                      |                        |
| binary-adding-operator            |                  |                      |                        |
| body                              |                  |                      |                        |
| choice                            |                  |                      |                        |
| component-association             |                  |                      |                        |
| component-declaration             |                  |                      |                        |
| component-list                    |                  |                      |                        |
| component-subtype-definition      |                  |                      |                        |
| constrained-array-definition      |                  |                      |                        |
| constraint                        |                  |                      |                        |
| declarative-part                  |                  |                      |                        |
| derived-type-definition           |                  |                      |                        |
| discrete_range                    |                  |                      |                        |
| discriminant-association          |                  |                      |                        |
| discriminant-constraint           |                  |                      |                        |
| discriminant-part                 |                  |                      |                        |
| discriminant-specification        |                  |                      |                        |
| enumeration-literal               |                  |                      |                        |
| enumeration-literal-specification |                  |                      |                        |
| enumeration-type-definition       |                  |                      |                        |
| expression                        |                  |                      |                        |
| factor                            |                  |                      |                        |
| fixed-accuracy-definition         |                  |                      |                        |
| fixed-point-constraint            |                  |                      |                        |
| floating-accuracy-definition      |                  |                      |                        |
| floating-point-constraint         |                  |                      |                        |
| full-type-declaration             |                  |                      |                        |
| identifier-list                   |        ✓         |          ✓           |                        |
| incomplete-type-declaration       |                  |                      |                        |
| index-constraint                  |                  |                      |                        |
| indexed-component                 |                  |                      |                        |
| index-subtype_definition          |                  |                      |                        |
| integer-type-definition           |                  |                      |                        |
| later-declarative-item            |                  |                      |                        |
| multiplying-operator              |                  |                      |                        |
| name                              |                  |                      |                        |
| number-declaration                |        ✓         |                      |                        |
| object-declaration                |        ✓         |                      |                        |
| prefix                            |                  |                      |                        |
| primary                           |                  |                      |                        |
| proper-body                       |                  |                      |                        |
| qualified-expression              |                  |                      |                        |
| range                             |                  |                      |                        |
| range-constraint                  |                  |                      |                        |
| real-type-definition              |                  |                      |                        |
| record-type-definition            |                  |                      |                        |
| relation                          |                  |                      |                        |
| relational-operator               |                  |                      |                        |
| selected-component                |                  |                      |                        |
| selector                          |                  |                      |                        |
| simple-expression                 |                  |                      |                        |
| simple-name                       |                  |                      |                        |
| slice                             |                  |                      |                        |
| subtype_declaration               |                  |                      |                        |
| subtype-indication                |         ✓        |                      |                        |
| term                              |                  |                      |                        |
| type-conversion                   |                  |                      |                        |
| type-declaration                  |                  |                      |                        |
| type-definition                   |                  |                      |                        |
| type-mark                         |                  |                      |                        |
| unary-adding-operator             |                  |                      |                        |
| unconstrained-array-definition    |                  |                      |                        |
| variant                           |                  |                      |                        |
| variant-part                      |                  |                      |                        |