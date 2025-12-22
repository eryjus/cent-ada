type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

type SQUARE(SIDE : INTEGER) is
    record
        MAT : MATRIX(1 .. SIDE, 1 .. SIDE);
    end record;

type DOUBLE_SQUARE(NUMBER : INTEGER) is
    record
        LEFT : SQUARE(NUMBER);
        RIGHT : SQUARE(NUMBER);
    end record;

