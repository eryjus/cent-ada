type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

BOARD : MATRIX(1 .. 8, 1 .. 8);

M : constant := 1;
J : comstamt := 1;

-------------------------

BOARD(M, J + 1)
