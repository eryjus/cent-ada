type GENDER is (M, F);
type PERSON(SEX : GENDER);
subtype MALE is PERSON(SEX => M);
