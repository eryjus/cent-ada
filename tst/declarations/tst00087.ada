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
