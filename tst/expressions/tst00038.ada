type CELL;
type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

HEAD : LINK := new CELL'(0, null, null);
NEXT : LINK := HEAD.SUCC;

----------------------------

(VALUE => 0, SUCC|PREC => new CELL`(0, null, null))


