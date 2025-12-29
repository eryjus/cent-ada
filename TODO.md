# Century Ada Compiler

This project is an implementation of the 1983 specification of the Ada compiler.


## Chapter 3


### Infrastructure
- [x] Redo the symbol table lookups/inserts to conform to new model
- [x] Mark Enums properly against multiple scopes
- [x] Re-evaluate PushScope and PopScope (should pop-scope remove/delete the scope or just point back to the parent?)
- [x] Hide Symbol members and create accessors
- [x] Consider adding a name/level to the scope for debugging
- [x] Print out the symbol table (print name and depth!)
- [x] Hide core language symbols
- [x] Split symbols and scopes (and scope manager?) to separate sources
- [x] Change the unordered map to point 1 name to several symbols
- [x] MarkScope is a problem -- need to be able to checkout and back out any added symbols


### Parsing
- [ ] Clean up different type checks (`subtype_indication`)
- [ ] Deal with Choice


### Early Symbol Table
- [x] Check scopes for all calls to `CheckLocalId()` (***remove and rewrite function?***)
- [x] Redo BOOLEAN as enumeration to match language


### Command Line
- [ ] Add trace to the command line parameters
- [ ] Add symbol table dump to the command line parameters


### Debugging
- [ ] Re-execute all Ch3 tests and evaluate the results


