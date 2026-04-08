//===================================================================================================================
// decl-strings.cc -- This file contains all the raw strings for declaration tests
//
//      Copyright (c) 2026 - Adam Clark
//      License: Beerware
//
//  These strings will be used in several tests.  Rather than repeating them, it is better to collect them
//  into a single source and reference them multiple times.
//
//      Date     Tracker  Version  Description
//  -----------  -------  -------  ---------------------------------------------------------------------------------
//  2026-Apr-04  Initial  v0.0.0   Initial Google Tests
//===================================================================================================================



#include "decl-tests.hh"


//
// -- These are all the intended Test Strings which are being used for declarations
//    -----------------------------------------------------------------------------
const std::string DeclTestCode::code[DeclTestCode::Last] = {
// -- Empty undefined test 0 string
R"(
)",
// -- Test 1
R"(COUNT, SUM  : INTEGER;
)",
// -- Test 2
R"(SIZE        : INTEGER range 0 .. 10_000 := 0;
)",
// -- Test 3
R"(SORTED      : BOOLEAN := FALSE;
)",
// -- Test 4
R"(N : constant := 10;
type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
COLOR_TABLE : ARRAY(1 .. N) of COLOR;
)",
// -- Test 5
R"(type BIT_VECTOR is array(INTEGER range <>) of BOOLEAN;
OPTION      : BIT_VECTOR(1 .. 10) := (others => TRUE);
)",
// -- Test 6
R"(LIMIT : constant INTEGER := 10_000;
)",
// -- Test 7
R"(LIMIT : constant := 100;
LOW_LIMIT : constant INTEGER := LIMIT / 10;
)",
// -- Test 8
R"(-- TOLLERANCE : constant REAL := DISPERSION(1.15);
)",
// -- Test 9
R"(PI : constant := 3.14159_26536;
)",
// -- Test 10
R"(PI : constant := 3.14159_26536;
TWO_PI : constant := 2.0 * PI;
)",
// -- Test 11
R"(MAX : constant := 500;
)",
// -- Test 12
R"(POWER_16 : constant := 2 ** 16;
)",
// -- Test 13
R"(ONE, UN, EINS : constant := 1;
)",
// -- Test 14
R"(type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
)",
// -- Test 15
R"(type COLUMN is range 1 .. 72;
)",
// -- Test 16
R"(type TABLE is array(1 .. 10) of INTEGER;
)",
// -- Test 17
R"(type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
subtype RAINBOW is COLOR range RED .. BLUE;
)",
// -- Test 18
R"(type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
subtype RAINBOW is COLOR range RED .. BLUE;
subtype RED_BLUE is RAINBOW;
)",
// -- Test 19
R"(subtype INT is INTEGER;
)",
// -- Test 20
R"(subtype SMALL_INT is INTEGER range -10 .. 10;
)",
// -- Test 21
R"(K : constant := 40;
type COLUMN is range 1 .. 72;
subtype UP_TO_K is COLUMN range 1 .. K;
)",
// -- Test 22
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
subtype SQUARE is MATRIX(1 .. 10, 1 .. 10);
)",
// -- Test 23
R"(type GENDER is (M, F);
type PERSON(SEX : GENDER);
subtype MALE is PERSON(SEX => M);
)",
// -- Test 24
R"(type COORDINATE is new INTEGER;
type LOCAL_COORDINATE is new COORDINATE;
)",
// -- Test 25
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
type MIDWEEK is new DAY range TUE .. THU;
)",
// -- Test 26
R"(subtype POSITIVE is INTEGER range 1 .. INTEGER'LAST;
type COUNTER is new POSITIVE;
)",
// -- Test 27
R"(subtype KEY_MANAGER is INTEGER;
--type SPECIAL_KEY is new KEY_MANAGER.KEY;
)",
// -- Test 28
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
)",
// -- Test 29
R"(type suit is (CLUBS, DIAMONDS, HEARTS, SPADES);
)",
// -- Test 30
R"(type GENDER is (M, F);
)",
// -- Test 31
R"(type LEVEL is (LOW, MEDIUM, URGENT);
)",
// -- Test 32
R"(type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
)",
// -- Test 33
R"(type LIGHT is (RED, AMBER, GREEN);
)",
// -- Test 34
R"(type HEXA is ('A', 'B', 'C', 'D', 'E', 'F');
)",
// -- Test 35
R"(type MIXED is ('A', 'B', '*', B, NONE, '?', '%');
)",
// -- Test 36
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
subtype WEEKDAY is DAY range MON .. FRI;
)",
// -- Test 37
R"(type SUIT is (CLUBS, DIAMONDS, HEARTS, SPADES);
subtype MAJOR is SUIT range HEARTS .. SPADES;
)",
// -- Test 38
R"(type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
subtype RAINBOW is COLOR range RED .. BLUE;
)",
// -- Test 39
R"(type ROMAN_DIGIT is ('I', 'V', 'X', 'L', 'C', 'D', 'M');
)",
// -- Test 40
R"(type PAGE_NUM is range 1 .. 2_000;
)",
// -- Test 41
R"(MAX_LINE_SIZE : constant := 132;
type LINE_SIZE is range 1 .. MAX_LINE_SIZE;
)",
// -- Test 42
R"(subtype SMALL_INT is INTEGER range -10 .. 10;
)",
// -- Test 43
R"(MAX_LINE_SIZE : constant := 132;
type LINE_SIZE is range 1 .. MAX_LINE_SIZE;
subtype COLUMN_PTR is LINE_SIZE range 1 .. 10;
)",
// -- Test 44
R"(MAX : constant := 65535;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;
)",
// -- Test 45
R"(type COEFFICIENT is digits 10 range -1.0 .. 1.0;
)",
// -- Test 46
R"(type MY_REAL is digits 8;
)",
// -- Test 47
R"(type MASS is digits 7 range 0.0 .. 1.0E35;
)",
// -- Test 48
R"(type COEFFICIENT is digits 10 range -1.0 .. 1.0;
subtype SHORT_COEFF is COEFFICIENT digits 5;
)",
// -- Test 49
R"(subtype PROBABILITY is REAL range 0.0 .. 1.0;
)",
// -- Test 50
R"(type VOLT is delta 0.125 range 0.0 .. 255.0;
)",
// -- Test 51
R"(type VOLT is delta 0.125 range 0.0 .. 255.0;
subtype ROUGH_VOLTAGE is VOLT delta 1.0;
)",
// -- Test 52
R"(WORD_LENGTH : constant := 8;
DEL : constant := 1.0 / 2 ** (WORD_LENGTH - 1);
)",
// -- Test 53
R"(DEL : constant := 0.1;
type FRACTION is delta DEL range -1.0 .. 1.0 - DEL;
)",
// -- Test 54
R"(type VECTOR is array(INTEGER range <>) of REAL;
)",
// -- Test 55
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
)",
// -- Test 56
R"(type BIT_VECTOR is array(INTEGER range <>) of BOOLEAN;
)",
// -- Test 57
R"(subtype POSITIVE is INTEGER range 1 .. INTEGER'LAST;
type ROMAN_DIGIT is ('I', 'V', 'X', 'L', 'C', 'D', 'M');
type ROMAN is array(POSITIVE range <>) of ROMAN_DIGIT;
)",
// -- Test 58
R"(type TABLE is array(1 .. 10) of INTEGER;
)",
// -- Test 59
R"(type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
type MY_SCHEDULE is array(DAY) of BOOLEAN;
)",
// -- Test 60
R"(MAX_LINE_SIZE : constant := 132;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;
)",
// -- Test 61
R"(GRID : array(1 .. 80, 1 .. 100) of BOOLEAN;
)",
// -- Test 62
R"(type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
MIX : array(COLOR range RED .. GREEN) of BOOLEAN;
)",
// -- Test 63
R"(MAX_LINE_SIZE : constant := 132;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;
PAGE : array(1 .. 50) of LINE;
)",
// -- Test 64
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
BOARD : MATRIX( 1 .. 8, 1 .. 8);
)",
// -- Test 65
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
RECTANGLE : MATRIX(1 .. 20, 1 .. 30);
)",
// -- Test 66
R"(N : constant := 8;
type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
INVERSE : MATRIX(1 .. N, 1 .. N);
)",
// -- Test 67
R"(type BIT_VECTOR is array(INTEGER range <>) of BOOLEAN;
FILTER : BIT_VECTOR(0 .. 31);
)",
// -- Test 68
R"(type VAR_LINE(LENGTH : INTEGER) is
    record
        IMAGE : STRING(1 .. LENGTH);
    end record;
)",
// -- Test 69
R"(type VAR_LINE(LENGTH : INTEGER) is
    record
        IMAGE : STRING(1 .. LENGTH);
    end record;
NULL_LINE : VAR_LINE(0);
)",
// -- Test 70
R"(STARS : STRING(1 .. 120) := (1 .. 120 => '*');
)",
// -- Test 71
R"(QUESTION : constant STRING := "How many characters?";
)",
// -- Test 72
R"(QUESTION : constant := "Who are you?  ";
ASK_TWICE : constant STRING := QUESTION & QUESTION;
)",
// -- Test 73
R"(subtype POSITIVE is INTEGER range 1 .. INTEGER'LAST;
type ROMAN_DIGIT is ('I', 'V', 'X', 'L', 'C', 'D', 'M');
type ROMAN is array(POSITIVE range <>) of ROMAN_DIGIT;
NINETY_SIX : constant ROMAN := "XCVI";
)",
// -- Test 74
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC);
type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;
)",
// -- Test 75
R"(type COMPLEX is
    record
        RE : REAL := 0.0;
        IM : REAL := 0.0;
    end record;
)",
// -- Test 76
R"(type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC);
type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;
TOMORROW, YESTERDAY : DATE;
)",
// -- Test 77
R"(type COMPLEX is
    record
        RE : REAL := 0.0;
        IM : REAL := 0.0;
    end record;
A, B, C : COMPLEX;
)",
// -- Test 78
R"(MAX : constant := 65535;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;
type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;
)",
// -- Test 79
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
type SQUARE(SIDE : INTEGER) is
    record
        MAT : MATRIX(1 .. SIDE, 1 .. SIDE);
    end record;
)",
// -- Test 80
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

type SQUARE(SIDE : INTEGER) is
    record
        MAT : MATRIX(1 .. SIDE, 1 .. SIDE);
    end record;

type DOUBLE_SQUARE(NUMBER : INTEGER) is
    record
        LEFT : SQUARE(NUMBER);
        RIGHT : SQUARE(NUMBER);
    end record;
)",
// -- Test 81
R"(subtype POSITIVE is INTEGER range 1 .. INTEGER'LAST;

type ITEM(NUMBER : POSITIVE) is
    record
        CONTENT : INTEGER;
    end record;
)",
// -- Test 82
R"(MAX : constant := 65535;

subtype BUFFER_SIZE is INTEGER range 0 .. MAX;

type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;


LARGE : BUFFER(200);
)",
// -- Test 83
R"(MAX : constant := 65535;

subtype BUFFER_SIZE is INTEGER range 0 .. MAX;

type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;

MESSAGE : BUFFER;
)",
// -- Test 84
R"(type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

type SQUARE(SIDE : INTEGER) is
    record
        MAT : MATRIX(1 .. SIDE, 1 .. SIDE);
    end record;

BASIS : SQUARE(5);
)",
// -- Test 85
R"(type DEVICE is (PRINTER, DISK, DRUM);
)",
// -- Test 86
R"(type STATE is (OPEN, CLOSED);
)",
// -- Test 87
R"(PAGE_SIZE : constant := 66;

type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 99;
subtype TRACK_NUMBER is INTEGER range 1 .. 99;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK    : TRACK_NUMBER;
        end case;
    end record;
)",
// -- Test 88
R"(PAGE_SIZE : constant := 66;

type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 99;
subtype TRACK_NUMBER is INTEGER range 1 .. 99;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK    : TRACK_NUMBER;
        end case;
    end record;

subtype DRUM_UNIT is PERIPHERAL(DRUM);
)",
// -- Test 89
R"(PAGE_SIZE : constant := 66;

type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 99;
subtype TRACK_NUMBER is INTEGER range 1 .. 99;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK    : TRACK_NUMBER;
        end case;
    end record;

subtype DISK_UNIT is PERIPHERAL(DISK);
)",
// -- Test 90
R"(PAGE_SIZE : constant := 66;

type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 99;
subtype TRACK_NUMBER is INTEGER range 1 .. 99;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK    : TRACK_NUMBER;
        end case;
    end record;

WRITER : PERIPHERAL(UNIT => PRINTER);
)",
// -- Test 91
R"(PAGE_SIZE : constant := 66;

type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

subtype CYLINDER_INDEX is INTEGER range 1 .. 99;
subtype TRACK_NUMBER is INTEGER range 1 .. 99;

type PERIPHERAL(UNIT : DEVICE := DISK) is
    record
        STATUS : STATE;
        case UNIT is
            when PRINTER =>
                LINE_COUNT : INTEGER range 1 .. PAGE_SIZE;
            when others =>
                CYLINDER : CYLINDER_INDEX;
                TRACK    : TRACK_NUMBER;
        end case;
    end record;

subtype DISK_UNIT is PERIPHERAL(DISK);

ARCHIVE : DISK_UNIT;
)",
// -- Test 92
R"(type CELL;
)",
// -- Test 93
R"(type CELL;
type LINK is access CELL;
)",
// -- Test 94
R"(type CELL;

type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;
)",
// -- Test 95
R"(type CELL;

type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

HEAD : LINK := new CELL'(0, null, null);
)",
// -- Test 96
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
)",
// -- Test 97
R"(type GENDER is (M, F);
type PERSON(SEX : GENDER);
)",
// -- Test 98
R"(type CAR;
)",
// -- Test 99
R"(type GENDER is (M, F);
type PERSON(SEX : GENDER);
type PERSON_NAME is access PERSON;
)",
// -- Test 100
R"(type GENDER is (M, F);

type PERSON(SEX : GENDER);

type PERSON_NAME is access PERSON;

type CAR is
    record
        NUMBER : INTEGER;
        OWNER : PERSON_NAME;
    end record;

type CAR_NAME is access CAR;
)",
// -- Test 101
R"(type GENDER is (M, F);

type PERSON(SEX : GENDER);

type PERSON_NAME is access PERSON;

type CAR is
    record
        NUMBER : INTEGER;
        OWNER : PERSON_NAME;
    end record;
)",
// -- Test 102
R"(type GENDER is (M, F);

type PERSON(SEX : GENDER);

type PERSON_NAME is access PERSON;

type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC);

type DATE is
    record
        DAY : INTEGER range 1 .. 31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;
TOMORROW, YESTERDAY : DATE;

type CAR is
    record
        NUMBER : INTEGER;
        OWNER : PERSON_NAME;
    end record;

type CAR_NAME is access CAR;

type PERSON(SEX : GENDER) is
    record
        NAME : STRING(1 .. 20);
        BIRTH : DATE;
        AGE : INTEGER range 0 .. 130;
        VEHICLE : CAR_NAME;
        case sex is
            when M => WIFE : PERSON_NAME(SEX => F);
            when F => HUSBAND : PERSON_NAME(SEX => M);
        end case;
    end record;
)",
// -- Test 103
R"(type color is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
subtype RAINBOW is COLOR range RED .. BLUE;
)",
// -- Test 104
R"(type COLOR is (WHITE, RED, YELLOW, GREEN, BLUE, BROWN, BLACK);
type CMYK is (CYAN, MAGENTA, YELLOW, BLACK);
)",
// -- Test 105
R"(type DATE;

type DATE is
    record
        YEAR : INTEGER;
        MON  : INTEGER;
        DAY  : INTEGER;
    end record;
)",
// -- Test 106
R"(--
-- -- This is a complete list of examples from Chapter 3
--    --------------------------------------------------


type BIT_VECTOR is array(INTEGER range <>) of BOOLEAN;

COUNT, SUM : INTEGER;
SIZE : INTEGER range 0 .. 10_000 := 0;
SORTED : BOOLEAN := FALSE;

N : constant := 3;
K : constant := 100;

type COLOR is (WHITE, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, BROWN, BLACK);

COLOR_TABLE : array(1 .. N) of COLOR;
--OPTION := BIT_VECTOR(1 .. 10) := (others => TRUE);

LIMIT : constant INTEGER := 10_000;
LOW_LIMIT : constant INTEGER := LIMIT / 10;
--TOLLERANNCE : constant REAL := DISPERSION(1.15);

PI : constant := 3.14159_26536;
TWO_PI : constant := 2 * PI;
MAX : constant := 500;
POWER_16 : constant := 2 ** 16;
ONE, UN, EINS : constant := 1;

type COLUMN is range 1 .. 72;
type TABLE is array(1 .. 10) of INTEGER;
type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;

subtype RAINBOW is COLOR range RED .. PURPLE;
subtype RED_PURPLE is RAINBOW;
subtype INT is INTEGER;
subtype SMALL_INT is INTEGER range -10 .. 10;
subtype UP_TO_K is COLUMN range 1 .. K;
subtype SQUARE_SUB is MATRIX(1 .. 10, 1 .. 10);

type COORDINATE is
    record
        LAT : REAL;
        LONG : REAL;
    end record;

type LOCAL_COORDINATE is new COORDINATE;
type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
type MIDWEEK is new DAY range TUE .. THU;
type POSITIVE is new INTEGER;
type COUNTER is new POSITIVE;
--type SPECIAL_KEY is new KEY_MANAGER.KEY;

type SUIT is (CLUBS, DIAMONDS, HEARTS, SPADES);
type GENDER is (M, F);
type LEVEL is (LOW, MEDIUM, URGENT);
type LIGHT is (RED, AMBER, GREEN);

type HEXA is ('A', 'B', 'C', 'D', 'E', 'F');
type MIXED is ('A', 'B', '*', NONE, '?', '%');

subtype WEEKDAY is DAY range MON .. FRI;
subtype MAJOR is SUIT range HEARTS .. SPADES;

type ROMAN_DIGIT is ('I', 'V', 'X', 'L', 'C', 'D', 'M');

type PAGE_NUM is range 1 .. 2_000;
MAX_LINE_SIZE : constant := 132;
type LINE_SIZE is range 1 .. MAX_LINE_SIZE;

subtype COLUMN_PTR is LINE_SIZE range 1 .. 10;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;

type COEFFICIENT is digits 4 range -1.0 .. 1.0;
type MASS is digits 7 range 0.0 .. 1.0E35;

subtype SHORT_COEFF is COEFFICIENT digits 5;
subtype PROBABILITY is REAL range 0.0 .. 1.0;

type VOLT is delta 0.125 range 0.0 .. 255.0;

subtype ROUGH_VOLTAGE is VOLT delta 1.0;

WORD_LENGTH : constant := 8;

DEL : constant := 1.0 / 2 ** (WORD_LENGTH - 1);
type FRACTION is delta DEL range -1.0 .. 1.0 - DEL;

type VECTOR is array(INTEGER range <>) of REAL;
type ROMAN is array(POSITIVE range <>) of ROMAN_DIGIT;

type SCHEDULE is array(DAY) of BOOLEAN;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;

GRID : array(1 .. 80, 1 .. 100) of BOOLEAN;
MIX : array(COLOR range RED .. GREEN) of BOOLEAN;
PAGE : array(1 .. 50) of LINE;

type MONTH_NAME is (JAN, FEB, MAR, APR, MAY, JUN,
        JUL, AUG, SEP, OCT, NOV, DEC);

type DATE is
    record
        DAY : INTEGER range 1 ..31;
        MONTH : MONTH_NAME;
        YEAR : INTEGER range 0 .. 4000;
    end record;


type COMPLEX is
    record
        RE : REAL := 0.0;
        IM : REAL := 0.0;
    end record;

TOMORROW, YESTERDAY : DATE;
A, B, C : COMPLEX;


type BUFFER(SIZE : BUFFER_SIZE := 100) is
    record
        POS : BUFFER_SIZE := 0;
        VALUE : STRING(1 .. SIZE);
    end record;

type SQUARE(SIDE : INTEGER) is
    record
        MAT : MATRIX(1 .. SIDE, 1 .. SIDE);
    end record;

type DOUBLE_SQUARE(NUMBER : INTEGER) is
    record
        LEFT : SQUARE(NUMBER);
        RIGHT : SQUARE(NUMBER);
    end record;

type ITEM(NUMBER : POSITIVE) is
    record
        CONTENT : INTEGER;
        -- no component depends on the discriminant
    end record;


type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);
type CYLINDER_INDEX is range 1 .. 50;
type TRACK_NUMBER is range 1 .. 120;

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


type FRAME is access MATRIX;
type BUFFER_NAME is access BUFFER;


type CELL;
type LINK is access CELL;

type CELL is
    record
        VALUE : INTEGER;
        SUCC : LINK;
        PRED : LINK;
    end record;

--HEAD : LINK := new CELL'(0, null, null);
HEAD : LINK := new CELL;
NEXT : LINK := HEAD.SUCC;


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

)",
};


