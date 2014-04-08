--David Klein
--860880864
--Lab 5


SELECT p.pid
FROM parts p, catalog c
WHERE p.pid=c.pid AND c.cost < 10;

SELECT p.pname
FROM parts p, catalog c
WHERE p.pid=c.pid AND c.cost < 10;

SELECT s.address
FROM suppliers s, parts p, catalog c
WHERE s.sid=c.sid AND p.pid=c.pid AND p.pname='Fire Hydrant Cap';

SELECT s.sname
FROM suppliers s, parts p, catalog c
WHERE s.sid=c.sid AND p.pid=c.pid AND p.color='green';

SELECT s1.sname, p.pname
FROM suppliers s1, suppliers s2, parts p, catalog c1, catalog c2
WHERE s1.sid=c1.sid AND s2.sid=c2.sid AND p.pid=c1.pid AND p.pid=c2.pid;
