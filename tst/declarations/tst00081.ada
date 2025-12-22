subtype POSITIVE is INTEGER range 1 .. INTEGER'LAST;

type ITEM(NUMBER : POSITIVE) is
    record
        CONTENT : INTEGER;
    end record;
