X : INTEGER;

for X in reverse 1 .. 10 loop
   if X = 6 then
      X := X - 2;
   end if;
end loop;

