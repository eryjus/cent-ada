type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
type SQUARE(SIDE : INTEGER) is
    record
        MAT : MATRIX(1 .. SIDE, 1 .. SIDE);
    end record;
