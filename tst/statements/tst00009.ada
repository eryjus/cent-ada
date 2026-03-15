type MONTH_NAME is (JANUARY, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY,
        AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER);
MONTH : MONTH_NAME;
DAY : INTEGER range 1 .. 31;
YEAR : INTEGER;

DAY := DAY + 1;

if MONTH = JANUARY and DAY > 31 then
    MONTH := FEBRUARY;
    DAY := DAY - 31;
elsif MONTH = FEBRUARY and DAY > 28 and YEAR mod 4 = 0 and YEAR mod 100 /= 0 then
    MONTH := MARCH;
    DAY := DAY - 28;
elsif MONTH = FEBRUARY and DAY > 29 then
    MONTH := MARCH;
    DAY := DAY - 29;
elsif MONTH = MARCH and DAY > 31 then
   MONTH := APRIL;
   DAY := DAY - 31;
elsif MONTH = APRIL and DAY > 30 then
   MONTH := MAY;
   DAY := DAY - 30;
elsif MONTH = MAY and DAY > 31 then
   MONTH := JUNE;
   DAY := DAY - 31;
elsif MONTH = JUNE and DAY > 30 then
   MONTH := JULY;
   DAY := DAY - 30;
elsif MONTH = JULY and DAY > 31 then
   MONTH := AUGUST;
   DAY := DAY - 31;
elsif MONTH = AUGUST and DAY > 31 then
   MONTH := SEPTEMBER;
   DAY := DAY - 31;
elsif MONTH = SEPTEMBER and DAY > 30 then
   MONTH := OCTOBER;
   DAY := DAY - 30;
elsif MONTH = OCTOBER and DAY > 31 then
   MONTH := NOVEMBER;
   DAY := DAY - 31;
elsif MONTH = NOVEMBER and DAY > 30 then
   MONTH := DECEMBER;
   DAY := DAY - 30;
elsif MONTH = DECEMBER and DAY > 31 then
   MONTH := JANUARY;
   DAY := DAY - 31;
end if;

