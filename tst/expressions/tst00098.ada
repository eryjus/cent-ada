type SEQUENCE is array (INTEGER range <>) of INTEGER;
subtype DOZEN is SEQUENCE(1 .. 12);

LEDGER : array(1 .. 100) of INTEGER;

----------------------------------------

DOZEN(LEDGER(31 .. 42))
