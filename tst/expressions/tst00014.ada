type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
subtype WEEKDAY is DAY range MON .. FRI;
type SCHEDULE is array(DAY) of BOOLEAN;

MY_SCHEDULE : SCHEDULE;

-----------------------

MY_SCHEDULE(WEEKDAY)

