subtype POSITIVE is INTEGER range 1 .. INTEGER'LAST;
type ROMAN_DIGIT is ('I', 'V', 'X', 'L', 'C', 'D', 'M');
type ROMAN is array(POSITIVE range <>) of ROMAN_DIGIT;