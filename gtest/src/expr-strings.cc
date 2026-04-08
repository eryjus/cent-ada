//===================================================================================================================
// expr-strings.cc -- This file contains all the raw strings for expressions tests
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//  These strings will be used in several tests.  Rather than repeating them, it is better to collect them
//  into a single source and reference them multiple times.
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-05  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "expr-tests.hh"


//
// -- These are all the intended Test Strings which are being used for expressions
//    ----------------------------------------------------------------------------
const std::string ExprTestCode::code[ExprTestCode::Last] = {
// -- Empty undefined test 0 string
R"(
)",
// -- Test 1
R"(PI : constant := 3.14159_36536;

---------

PI
)",
// -- Test 2
R"(LIMIT : constant INTEGER := 10_000;

-------

LIMIT
)",
// -- Test 3
R"(COUNT, SUM : INTEGER;

-------------

COUNT
)",
// -- Test 4
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

BOARD : MATRIX(1 .. 8, 1 .. 8);

----------

BOARD
)",
// -- Test 5
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

------------------

MATRIX
)",
// -- Test 6
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);

type MY_SCHEDULE is array(DAY) of BOOLEAN;

--------------------------

MY_SCHEDULE(SAT)
)",
// -- Test 7
R"(MAX_LINE_SIZE : constant := 80;

type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;

PAGE : array(1 .. 50) of LINE;

-------------

PAGE(10)
)",
// -- Test 8
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

BOARD : MATRIX(1 .. 8, 1 .. 8);

M : constant := 1;
J : constant := 1;

-------------------------

BOARD(M, J + 1)
)",
// -- Test 9
R"(MAX_LINE_SIZE : constant := 80;

type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;

PAGE : array(1 .. 50) of LINE;

-------------

PAGE(10)(20)
)",
// -- Test 10
R"(STARS : STRING(1 .. 120) := (1 .. 120 => '*');

----------------

STARS(1 .. 15)
)",
// -- Test 11
R"(MAX_LINE_SIZE : constant := 132;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;
PAGE : array(1 .. 50) of LINE;

SIZE : constant := 10;

---------------------------------

PAGE(1 .. 10 + SIZE)
)",
// -- Test 12
R"(MAX_LINE_SIZE : constant := 132;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;
PAGE : array(1 .. 50) of LINE;

L : constant := 10;
A : constant := 1;
B : constant := 5;

------------------------

PAGE(L)(A .. B)
)",
// -- Test 13
R"(STARS : STRING(1 .. 120) := (1 .. 120 => '*');

----------------

STARS(1 .. 0)
)",
// -- Test 14
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
subtype WEEKDAY is DAY range MON .. FRI;
type SCHEDULE is array(DAY) of BOOLEAN;

MY_SCHEDULE : SCHEDULE;

-----------------------

MY_SCHEDULE(WEEKDAY)
)",
// -- Test 15
R"(STARS : STRING(1 .. 120) := (1 .. 120 => '*');

K : constant := 10;

----------------

STARS(5 .. 15)(K)

)",
// -- Test 16
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);

type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;

TOMORROW, YESTERDAY : DATE;

-------------------------

TOMORROW.MONTH
)",
// -- Test 17
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);
type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;
type GENDER is (M, F);
type PERSON(SEX : GENDER);
type CAR;
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
        AGE : INTEGER range 0 .. 130;
        VEHICLE : CAR_NAME;
        case SEX is
            when M => WIFE : PERSON_NAME(SEX => F);
            when F => HUSBAND : PERSON_NAME(SEX => M);
        end case;
    end record;

MY_CAR, YOUR_CAR, NEXT_CAR : CAR_NAME;

---------------------------

NEXT_CAR.OWNER
)",
// -- Test 18
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);
type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;
type GENDER is (M, F);
type PERSON(SEX : GENDER);
type CAR;
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
        AGE : INTEGER range 0 .. 130;
        VEHICLE : CAR_NAME;
        case SEX is
            when M => WIFE : PERSON_NAME(SEX => F);
            when F => HUSBAND : PERSON_NAME(SEX => M);
        end case;
    end record;

MY_CAR, YOUR_CAR, NEXT_CAR : CAR_NAME;

---------------------------

NEXT_CAR.OWNER.AGE
)",
// -- Test 19
R"(type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 50;
subtype TRACK_NUMBER is INTEGER range 1 .. 120;

PAGE_SIZE : constant := 55;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK : TRACK_NUMBER;
        end case;
    end record;


subtype DRUM_UNIT is PERIPHERAL(DRUM);
subtype DISK_UNIT is PERIPHERAL(DISK);

WRITER : PERIPHERAL(UNIT => PRINTER);
ARCHIVE : DISK_UNIT;

---------------------------------------

WRITER.UNIT
)",
// -- Test 20
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);
type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;
type GENDER is (M, F);
type PERSON(SEX : GENDER);
type CAR;
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
        AGE : INTEGER range 0 .. 130;
        VEHICLE : CAR_NAME;
        case SEX is
            when M => WIFE : PERSON_NAME(SEX => F);
            when F => HUSBAND : PERSON_NAME(SEX => M);
        end case;
    end record;

MY_CAR, YOUR_CAR, NEXT_CAR : CAR_NAME;

---------------------------

NEXT_CAR.all
)",
// -- Test 21
R"(type COLOR is (WHITE, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, BROWN, BLACK);

-----------------------

COLOR'FIRST
)",
// -- Test 22
R"(type COLOR is (WHITE, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, BROWN, BLACK);
subtype RAINBOW is COLOR range RED .. PURPLE;

-----------------------

COLOR'BASE'FIRST
)",
// -- Test 23
R"(

----------------------

REAL'DIGITS
)",
// -- Test 24
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

subtype SQUARE is MATRIX(1 .. 10, 1 .. 10);

BOARD : SQUARE(1 .. 8, 1 .. 8);

--------------------------------

BOARD'LAST(2)
)",
// -- Test 25
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

subtype SQUARE is MATRIX(1 .. 10, 1 .. 10);

BOARD : SQUARE(1 .. 8, 1 .. 8);

--------------------------------

BOARD'RANGE(1)
)",
// -- Test 26
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);

type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;

TOMORROW, YESTERDAY : DATE;

-------------------------

DATE'SIZE
)",
// -- Test 27
R"(MAX : constant := 500;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;
type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;

MESSAGE : BUFFER;

------------------------------

MESSAGE'ADDRESS
)",
// -- Test 28
R"(3.14159_26536
)",
// -- Test 29
R"(1_345
)",
// -- Test 30
R"(type SUIT is (CLUBS, DIAMONDS, HEARTS, SPADES);

---------------------------------

CLUBS
)",
// -- Test 31
R"('A'
)",
// -- Test 32
R"("SOME TEXT"
)",
// -- Test 33
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);

---------------------

(4, JUL, 1776)
)",
// -- Test 34
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);

type DATE is
    record
        DAY : INTEGER range 1 ..31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;

---------------------

(DAY => 4, MONTH => JUL, YEAR => 1776)
)",
// -- Test 35
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);

type DATE is
    record
        DAY : INTEGER range 1 ..31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;

---------------------

(MONTH => JUL, DAY => 4, YEAR => 1776)
)",
// -- Test 36
R"(type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 50;
subtype TRACK_NUMBER is INTEGER range 1 .. 120;

PAGE_SIZE : constant := 55;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK : TRACK_NUMBER;
        end case;
    end record;


subtype DRUM_UNIT is PERIPHERAL(DRUM);
subtype DISK_UNIT is PERIPHERAL(DISK);

WRITER : PERIPHERAL(UNIT => PRINTER);
ARCHIVE : DISK_UNIT;

---------------------------------------

(DISK, CLOSED, TRACK => 5, CYLINDER => 12)
)",
// -- Test 37
R"(type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 50;
subtype TRACK_NUMBER is INTEGER range 1 .. 120;

PAGE_SIZE : constant := 55;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK : TRACK_NUMBER;
        end case;
    end record;


subtype DRUM_UNIT is PERIPHERAL(DRUM);
subtype DISK_UNIT is PERIPHERAL(DISK);

WRITER : PERIPHERAL(UNIT => PRINTER);
ARCHIVE : DISK_UNIT;

---------------------------------------

(UNIT => DISK, STATUS => CLOSED, TRACK => 9, CYLINDER => 1)
)",
// -- Test 38
R"(type CELL;
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

(VALUE => 0, SUCC|PRED => new CELL'(0, null, null))
)",
// -- Test 39
R"(

---------------------------

(7, 9, 5, 1, 3, 2, 4, 8, 6, 0)
)",
// -- Test 40
R"(type TABLE is array(1 .. 10) of INTEGER;

---------------------------

TABLE'(5, 8, 4, 1, others => 0)
)",
// -- Test 41
R"(

---------------------------

(1 .. 5 => (1 .. 8 => 0.0))
)",
// -- Test 42
R"(type CELL;
type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

HEAD : LINK := new CELL'(0, null, null);
NEXT : LINK := HEAD.SUCC;

N : constant := 2;

---------------------------

(1 .. N => new CELL)
)",
// -- Test 43
R"(type TABLE is array(1 .. 10) of INTEGER;

----------------------------------------


TABLE'(2 | 4 | 10 => 1, others => 0)
)",
// -- Test 44
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
type SCHEDULE is array(DAY) of BOOLEAN;

----------------------------------------

SCHEDULE'(MON .. FRI => TRUE, others => FALSE)
)",
// -- Test 45
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
type SCHEDULE is array(DAY) of BOOLEAN;

----------------------------------------

SCHEDULE'(WED | SUN => FALSE, others => TRUE)
)",
// -- Test 46
R"(

----------------------------------------

((1.1, 1.2, 1.3), (2.1, 2.2, 2.3))
)",
// -- Test 47
R"(

----------------------------------------

(1 => (1.1, 1.2, 1.3), 2 => (2.1, 2.2, 2.3))
)",
// -- Test 48
R"(

----------------------------------------

(1 => (1 => 1.1, 2 => 1.2, 3 => 1.3), 2 => (1 => 2.1, 2 => 2.2, 3 => 2.3))
)",
// -- Test 49
R"(

----------------------------------------

4.0
)",
// -- Test 50
R"(PI : REAL;

----------------------------------------

PI
)",
// -- Test 51
R"(

----------------------------------------

(1 .. 10 => 0)
)",
// -- Test 52
R"(SUM : INTEGER;

----------------------------------------

SUM
)",
// -- Test 53
R"(

----------------------------------------

INTEGER'LAST
)",
// -- Test 54
R"(X : constant := 90.0;

----------------------------------------

X
--SINE(X)
)",
// -- Test 55
R"(type COLOR is (WHITE, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, BROWN, BLACK);

----------------------------------------

COLOR'(BLUE)
)",
// -- Test 56
R"(M, N : constant := 2.0;

----------------------------------------

REAL(M * N)
)",
// -- Test 57
R"(LINE_COUNT : INTEGER;

----------------------------------------

(LINE_COUNT + 10)
)",
// -- Test 58
R"(VOLUME : REAL := 5.6;

----------------------------------------

VOLUME
)",
// -- Test 59
R"(DESTROYED : constant := TRUE;

----------------------------------------

not DESTROYED
)",
// -- Test 60
R"(LINE_COUNT : constant := 60;

----------------------------------------

2 * LINE_COUNT
)",
// -- Test 61
R"(

----------------------------------------

-4.0
)",
// -- Test 62
R"(A, B, C : constant := 3.6;

----------------------------------------

-4.0 + A
)",
// -- Test 63
R"(A, B, C : constant := 3.6;

----------------------------------------

B ** 2 - 4.0 * A * C
)",
// -- Test 64
R"(PASSWORD : STRING;

----------------------------------------

PASSWORD(1 .. 3) = "BWV"
)",
// -- Test 65
R"(subtype SMALL_INT is INTEGER range 1 .. 255;

----------------------------------------

COUNT in SMALL_INT
)",
// -- Test 66
R"(subtype SMALL_INT is INTEGER range 1 .. 255;

----------------------------------------

COUNT not in SMALL_INT
)",
// -- Test 67
R"(INDEX : constant := 1;
ITEM_HIT : constant := TRUE;

----------------------------------------

INDEX = 0 or ITEM_HIT
)",
// -- Test 68
R"(type WEATHER is (SUNNY, WARM, CLOUDY, RANINY, COLD);

----------------------------------------

(COLD and SUNNY) or WARM
)",
// -- Test 69
R"(A, B, C : constant := 3.6;

----------------------------------------

A ** (B ** C)
)",
// -- Test 70
R"(type WEATHER is (SUNNY, WARM, CLOUDY, RANINY, COLD);

----------------------------------------

not SUNNY or WARM
)",
// -- Test 71
R"(X, Y : constant := 6.0;

----------------------------------------

X > 4.0 and Y > 0.0
)",
// -- Test 72
R"(A : constant := 2;

----------------------------------------

-4.0 * A ** 2
)",
// -- Test 73
R"(A, B : constant := 3.6;

----------------------------------------

abs(1 + A) + B
)",
// -- Test 74
R"(Y : constant := 3;

----------------------------------------

Y ** (-3)
)",
// -- Test 75
R"(A, B, C : constant := 3.6;

----------------------------------------

A / B * C
)",
// -- Test 76
R"(type WEATHER is (SUNNY, WARM, CLOUDY, RANINY, COLD);

----------------------------------------

SUNNY or WARM
)",
// -- Test 77
R"(FILTER : array(1 .. 100) of BOOLEAN;

----------------------------------------

FILTER(1 .. 10) and FILTER(15 .. 24)
)",
// -- Test 78
R"(type GENDER is (M, F);

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

NEXT_CAR.OWNER /= null and then NEXT_CAR.OWNER.AGE > 25
)",
// -- Test 79
R"(N : constant := 1;
A : array (1 .. 10) of REAL;
HIT_VALUE : constant := 9.99;

----------------------------------------

N = 0 or else A(N) = HIT_VALUE
)",
// -- Test 80
R"(X, Y : constant := 1;

----------------------------------------

X /= Y
)",
// -- Test 81
R"(

----------------------------------------

"" < "A" and "A" < "AA"
)",
// -- Test 82
R"(type GENDER is (M, F);

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
)",
// -- Test 83
R"(type GENDER is (M, F);

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

MY_CAR = YOUR_CAR
)",
// -- Test 84
R"(type GENDER is (M, F);

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

MY_CAR.all = YOUR_CAR.all
)",
// -- Test 85
R"(N : constant := 69;

----------------------------------------

N not in 1 .. 10
)",
// -- Test 86
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);

TODAY : DAY;

----------------------------------------

TODAY in MON .. FRI
)",
// -- Test 87
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
subtype WEEKDAY is DAY range MON .. FRI;
TODAY : DAY;

----------------------------------------

TODAY in WEEKDAY
)",
// -- Test 88
R"(type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 50;
subtype TRACK_NUMBER is INTEGER range 1 .. 120;

PAGE_SIZE : constant := 55;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK : TRACK_NUMBER;
        end case;
    end record;

subtype DRUM_UNIT is PERIPHERAL(DRUM);
subtype DISK_UNIT is PERIPHERAL(DISK);

WRITER : PERIPHERAL(UNIT => PRINTER);
ARCHIVE : DISK_UNIT;

----------------------------------------

ARCHIVE in DISK_UNIT
)",
// -- Test 89
R"(Z : constant := 1.0;

----------------------------------------

Z + 0.1
)",
// -- Test 90
R"(

----------------------------------------

"A" & "BCD"
)",
// -- Test 91
R"(

----------------------------------------

'A' & "BCD"
)",
// -- Test 92
R"(

----------------------------------------

'A' & 'A'
)",
// -- Test 93
R"(J : constant := 5.0;

----------------------------------------

REAL(2 * J)
)",
// -- Test 94
R"(

----------------------------------------

INTEGER(1.6)
)",
// -- Test 95
R"(

----------------------------------------

INTEGER(-0.4)
)",
// -- Test 96
R"(type SEQUENCE is array (INTEGER range <>) of INTEGER;
subtype DOZEN is SEQUENCE(1 .. 12);

LEDGER : array(1 .. 100) of INTEGER;

----------------------------------------

SEQUENCE(LEDGER)
)",
// -- Test 97
R"(type SEQUENCE is array (INTEGER range <>) of INTEGER;
subtype DOZEN is SEQUENCE(1 .. 12);

LEDGER : array(1 .. 100) of INTEGER;

----------------------------------------

SEQUENCE(LEDGER(31 .. 42))
)",
// -- Test 98
R"(type SEQUENCE is array (INTEGER range <>) of INTEGER;
subtype DOZEN is SEQUENCE(1 .. 12);

LEDGER : array(1 .. 100) of INTEGER;

----------------------------------------

DOZEN(LEDGER(31 .. 42))
)",
// -- Test 99
R"(X : INTEGER := 2;

----------------------------------------

X + 1 + 2
)",
// -- Test 100
R"(X : INTEGER := 2;

----------------------------------------

1 + 2 + X
)",
// -- Test 101
R"(X : INTEGER := 2;

----------------------------------------

X + (1 + 2)
)",
// -- Test 102
R"(

----------------------------------------

2 = 1 + 1
)",
// -- Test 103
R"(type A is array(1 .. 2) of BOOLEAN;
B : A;

----------------------------------------

A'LENGTH = B'LENGTH
)",
// -- Test 104
R"(X : constant := 3;

----------------------------------------

X = 3 and 1 = 2
)",
// -- Test 105
R"(type MASK is (FIX, DEC, EXP, SIGNIF);
type CODE is (FIX, CLA, DEC, TNZ, SUB);

----------------------------------------

MASK'(DEC)
)",
// -- Test 106
R"(type MASK is (FIX, DEC, EXP, SIGNIF);
type CODE is (FIX, CLA, DEC, TNZ, SUB);

----------------------------------------

CODE'(DEC)
)",
// -- Test 107
R"(type CELL;
type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

HEAD : LINK := new CELL'(0, null, null);
NEXT : LINK := HEAD.SUCC;

----------------------------------

new CELL'(0, null, null)
)",
// -- Test 108
R"(type CELL;
type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

HEAD : LINK := new CELL'(0, null, null);
NEXT : LINK := HEAD.SUCC;

----------------------------------

new CELL'(VALUE => 0, SUCC => null, PRED => null)
)",
// -- Test 109
R"(type CELL;
type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

HEAD : LINK := new CELL'(0, null, null);
NEXT : LINK := HEAD.SUCC;

----------------------------------

new CELL
)",
// -- Test 110
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

----------------------------------

new MATRIX(1 .. 10, 1 .. 20)
)",
// -- Test 111
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

----------------------------------

new MATRIX'(1 .. 10 => (1 .. 20 => 0.0))
)",
// -- Test 112
R"(MAX : constant := 65535;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;
type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;

----------------------------------

new BUFFER(100)
)",
// -- Test 113
R"(MAX : constant := 65535;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;
type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;

----------------------------------

new BUFFER'(SIZE => 80, POS => 0, VALUE => (1 .. 80 => 'A'))
)",
// -- Test 114
R"(

----------------------------------

1 + 1
)",
// -- Test 115
R"(

----------------------------------

abs(-10) * 3
)",
// -- Test 116
R"(subtype POSITIVE is INTEGER range 1 .. INTEGER'LAST;

----------------------

3 = 3
)",
};


