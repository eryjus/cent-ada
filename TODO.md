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
- [x] BUG: Change the ID string for type definitions to ID -- clean up loc reference
- [x] FEATURE: Handle adding components into the symbol table
- [x] REFACTOR: Determine what to do with YYSTYPE


### Parsing
- [x] BUG: Clean up different type checks (`subtype_indication`)


### Early Symbol Table
- [x] BUG: Remove rederences to `make_unique<Symbol>`
- [x] BUG: Fix symbol table handling of an incomplete type (`make_unique<Symbol>`)


### Command Line
- [x] FEATURE: Add trace to the command line parameters
- [x] FEATURE: Add symbol table dump to the command line parameters


### Debugging
- [x] BUG: Solve test #70
- [x] BUG: Re-execute all Ch3 tests and evaluate the results




## Chapter 4


### Infrastructure
- [x] REFACTOR: Refactor `parse-expr` into separate files like Ch3
- [ ] BUG: Check for the following in each parser source (EXTRA TASKS):
  * MarkStream m ==> is used correctly?
  * (done) Remove all `m.CommitIf()` references & function
  * Check all return types and make sure they are appropriate
  * Check all versions of `loc` to be `parseLoc`
  * Check all functions to use `astLoc` -- is there a better construct?
  * Check for unused `Id &` parameters
  * Make sure all locals are initialized
- [ ] BUG: Correct IdList * to unique_ptr
- [ ] BUG: Canonicalize `tokens`


### Parsing
- [ ] BUG: Deal with Choice better
- [ ] BUG: Deal with Aggregate better
- [ ] BUG: Deal with Attribute better


### Debugging
- [ ] BUG: Develop and run all Ch4 tests from the book


