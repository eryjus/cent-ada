type VAR_LINE(LENGTH : INTEGER) is
    record
        IMAGE : STRING(1 .. LENGTH);
    end record;

NULL_LINE : VAR_LINE(0);
