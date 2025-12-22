
type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC);
type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;
