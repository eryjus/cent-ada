SWAP:
    declare
        X : INTEGER := 9;
        Y : INTEGER := 6;
        TEMP : INTEGER;
    begin
        TEMP := X;
        X := Y;
        Y := TEMP;
    end swap;
