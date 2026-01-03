type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
subtype WEEKDAY is DAY range MON .. FRI;
TODAY : DAY;

----------------------------------------

TODAY in WEEKDAY

