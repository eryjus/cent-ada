type GENDER is (M, F);


type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC);
type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;

type CAR;
type PERSON(SEX : GENDER);

type PERSON_NAME is access PERSON;
type CAR_NAME is access CAR;

type CAR is
    record
        NUMBER : INTEGER;
        OWNER : PERSON_NAME;
    end record;

type PERSON(SEX : GENDER) is
    record
        NAME : STRING(1 .. 20);
        BIRTH : DATE;
        AGE : INTEGER range 1 .. 130;
        VEHICLE : CAR_NAME;
        case SEX is
            when M => WIFE : PERSON_NAME(SEX => F);
            when F => HUSBAND : PERSON_NAME(SEX => M);
        end case;
    end record;


MY_CAR, YOUR_CAR, NEXT_CAR : CAR_NAME;


subtype MALE is PERSON(SEX => M);


----------------------------------------

MY_CAR = null


