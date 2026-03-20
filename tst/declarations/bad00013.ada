--
-- -- Invalid Choice
--    --------------

type color is (RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE);

type test(var : color := BLUE) is
    record
        case var is
            when RED => length : INTEGER;
            when 1 - + 2 => width : INTEGER;
        end case;
    end record;
