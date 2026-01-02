MAX_LINE_SIZE : constant := 132;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;
PAGE : array(1 .. 50) of LINE;

SIZE : constant := 10;

---------------------------------

PAGE(1 .. 10 + SIZE)

