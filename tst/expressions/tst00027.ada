MAX : constant := 500;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;
type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;

MESSAGE : BUFFER;

------------------------------


MESSAGE'ADDRESS

