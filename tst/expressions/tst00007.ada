MAX_LINE_SIZE : constant := 80;

type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;

PAGE : array(1 .. 50) of LINE;

-------------

PAGE(10)
