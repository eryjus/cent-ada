type DEVICE is (PRINTER, DISK, DRUM);
type STATE is (OPEN, CLOSED);

type CYLINDER_INDEX is INTEGER range (1 .. 50);
type TRACK_NUMBER is INTEGER range (1 .. 120);

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
