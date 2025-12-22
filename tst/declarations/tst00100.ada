type GENDER is (M, F);

type PERSON(SEX : GENDER);

type PERSON_NAME is access PERSON;

type CAR is
    record
        NUMBER : INTEGER;
        OWNER : PERSON_NAME;
    end record;

type CAR_NAME is access CAR;
