MAX_LINE_SIZE : constant := 132;
type LINE is array(1 .. MAX_LINE_SIZE) of CHARACTER;
PAGE : array(1 .. 50) of LINE;

L : constant := 10;
A : constant := 1;
B : constant := 5;


------------------------


PAGE(L)(A .. B)


