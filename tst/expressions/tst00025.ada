type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

subtype SQUARE is MATRIX(1 .. 10, 1 .. 10);

BOARD : SQUARE(1 .. 8, 1 .. 8);

--------------------------------

BOARD'RANGE(1)


