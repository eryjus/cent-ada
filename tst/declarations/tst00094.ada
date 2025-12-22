type CELL;

type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

