--
-- -- This is a complete list of examples from Chapter 3
--    --------------------------------------------------


COUNT, SUM : INTEGER;
SIZE : INTEGER range 0 .. 10_000 := 0;
SORTED : BOOLEAN := FALSE;
COLOR_TABLE : array(1 .. N) of COLOR;
OPTION := BIT_VECTOR(1 .. 10) := (others => TRUE);

LIMIT : constant INTEGER := 10_000;
LOW_LIMIT : constant INTEGER := LIMIT / 10;
TOLLERANNCE : constant REAL := DISPERSION(1.15);

PI : constant := 3.14159_26536;
TWO_PI : constant := 2 * PI;
MAX : constant := 500;
POWER_16 : constant 2 ** 16;
ONE, UN, EINS : constant := 1;

type COLOR is (WHITE, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, BROWN, BLACK);
type COLUMN is range 1 .. 72;
type TABLE is array(1 .. 10) of INTEGER;

subtype RAINBOW is COLOR range RED .. PURPLE;
subtype RED_PURPLE is RAINBOW;
subtype INT is INTEGER;
subtype SMALL_INT is INTEGER range -10 .. 10;
subtype UP_TO_K is COLUMN range 1 .. K;
subtype SQUARE is MATRIX(1 .. 10, 1 .. 10);
subtype MAKE is PERSON(SEX => M);

type LOCAL_COORDINATE is new COORDINATE;
type MIDWEEK is new DAY range TUE .. THU;
type COUNTER is new POSITIVE;
type SPECIAL_KEY is new KEY_MANAGER.KEY;

type DAY is (MON, TUE, WED, THU, FRI, SAT, SUB);
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
type LINE_SIZE is range 1 .. MAX_LINE_SIZE;

subtype COLUMN_PTR is LINE_SIZE range 1 .. 10;
subtype BUFFER_SIZE is INTEGER range 0 .. MAX;

type COEFFICIENT is digits range -1.0 .. 1.0;
type MASS is digits 7 range 0.0 .. 1.0E35;

subtype SHORT_COEFF is COEFFICIENT digits 5;
subtype PROBABILITY is REAL range 0.0 .. 1.0;

type VOLT is delta 0.125 range 0.0 .. 255.0;

subtype ROUGH_VOLTAGE is VOLT delta 1.0;

DEL : constant := 1.0 / 2 ** (WORD_LENGTH - 1);
type FRACTION is delta DEL range -1.0 .. 1.0 - DEL;

type VECTOR is array(INTEGER range <>) of REAL;
type MATRIX is array(INTEGER range <>, INTEGER range <>) of REAL;
type BIT_VECTOR is array(INTEGER range <>) of BOOLEAN;
type ROMAN is array(POSITIVE range <>) of ROMAN_DIGIT;

type TABLE is array(1 .. 10) of INTEGER;
type SCHEDULE is array(DAY) of BOOLEAN;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;

GRID : array(1 .. 80, 1 .. 100) of BOOLEAN;
MIX : array(COLOR range RED .. GREEN) of BOOLEAN;
PAGE : array(1 .. 50) of LINE;

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


type DEVINCE is (PRINTER, DISK, DRUM);
type STAT is (OPEN, CLOSED);

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
sybtype DISK_UNIT is PERIPHERAL(DISK);

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

HEAD : LINK := new CELL'(0, null, null);
NEXT : LINK := HEAD.SUCC;


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
        AGE : INTEGER range 1 .. 130;
        VEHICLE : CAR_NAME;
        case SEX is
            when M => WIFE : PERSON_NAME(SEX => F);
            when F => HUSBAND : PERSON_NAME(SEX => M);
        end case;
    end record;


MY_CAR, YOUR_CAR, NEXT_CAR : CAR_NAME;


