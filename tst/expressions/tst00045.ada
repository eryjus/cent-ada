type DAY is (MON, TUE, WED, THU, FRI, SAT, SUN);
type SCHEDULE is array(DAY) of BOOLEAN;

----------------------------------------

SCHEDULE'(WED | SUN => FALSE, others => TRUE)

