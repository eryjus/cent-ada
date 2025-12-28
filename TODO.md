# Century Ada Compiler

This project is an implementation of the 1983 specification of the Ada compiler.


## Chapter 3

- [ ] Check scopes for all calls to `CheckLocalId()` (***remove and rewrite function?***)
- [ ] Create a scope for a record (***still the right thing to do?***)
- [ ] Clean up different type checks (`subtype_indication`)
- [ ] Deal with Choice
- [ ] Print out the symbol table (hide core language symbols?  print name and depth!)
- [ ] Redo the symbol table lookups/inserts to conform to new model
- [ ] Mark Enums properly against multiple scopes
- [ ] Re-evaluate PushScope and PopScope (should pop-scope remove/delete the scope or just point back to the parent?)
- [ ] Consider adding a name/level to the scope for debugging
- [ ] Re-execute all Ch3 tests and evaluate the results
- [ ] Add trace to the command line parameters
- [ ] Add symbol table dump to the command line parameters
- [x] Split symbols and scopes (and scope manager?) to separate sources

