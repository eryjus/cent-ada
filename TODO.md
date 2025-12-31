# Century Ada Compiler

This project is an implementation of the 1983 specification of the Ada compiler.


## Tags

* feature
* bugfix
* hotfix
* experiment
* refactor
* wip


## Chapter 3


### Infrastructure
- [ ] BUG: Change the ID string for type definitions to ID -- clean up loc reference
- [ ] FEATURE: Handle adding components into the symbol table
- [ ] REFACTOR: Determine what to do with YYSTYPE


### Parsing
- [ ] BUG: Clean up different type checks (`subtype_indication`)
- [ ] BUG: Deal with Choice
- [ ] BUG: Deal with Aggregate better
- [ ] BUG: Deal with Attribute better


### Early Symbol Table
(nothing here)


### Command Line
- [x] FEATURE: Add trace to the command line parameters
- [x] FEATURE: Add symbol table dump to the command line parameters


### Debugging
- [ ] BUG: Solve test #70
- [ ] BUG: Solve test #95, #96
- [ ] BUG: Re-execute all Ch3 tests and evaluate the results




## Chapter 4


### Infrastructure
- [ ] REFACTOR: Refactor `parse-expr` into separate files like Ch3


### Debugging
- [ ] BUG: Develop and run all Ch4 tests from the book