# Test harness refit

This not contains a list of things that need to be reviewed:

## Scanner tests

- [ ] Is an underline a valid token on its own?  If not, remove the token match.
- [ ] Make sure TOK_ERROR passes an error message.  May need to fix upstream.  The error message in the YYSTYPE variant needs to include the DiagID as well as a constructed message.
- [ ] Create some nagative scan rules to match and issue errors.
- [ ] Trailing # missing in number.
- [ ] Error Tokens need to be recognized when parsing an ident, number, etc..



