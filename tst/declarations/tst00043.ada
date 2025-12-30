MAX_LINE_SIZE : constant := 132;
type LINE_SIZE is range 1 .. MAX_LINE_SIZE;
subtype COLUMN_PTR is LINE_SIZE range 1 .. 10;
