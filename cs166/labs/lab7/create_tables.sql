drop table part_nyc;
create table part_nyc (part_number integer, 
                       supplier integer, 
                       color integer, 
                       on_hand integer, 
                       desct text); 
                       
drop table part_sfo;
create table part_sfo (part_number integer, 
                       supplier integer,
                       color integer, 
                       on_hand integer, 
                       desct text); 

drop table supplier; 
create table supplier (supplier_id integer,
                       supplier_name varchar(20));
insert into supplier values (0, 'Bob');
insert into supplier values (1, 'Ted');
insert into supplier values (2, 'Carol');
insert into supplier values (3, 'Alice');
insert into supplier values (4, 'Jerry');
insert into supplier values (5, 'Mickey');
insert into supplier values (6, 'Phil');
insert into supplier values (7, 'Vince');
insert into supplier values (8, 'Bill');
insert into supplier values (9, 'Donna');

                       
drop table color; 
create table color (color_id integer, 
                    color_name varchar(20));
insert into color values (0, 'Red'); 
insert into color values (1, 'Green');

COPY part_nyc (part_number, supplier, color, on_hand, desct)

FROM '../../lab7/part_nyc.dat'

WITH DELIMITER ';';

COPY part_sfo (part_number, supplier, color, on_hand, desct)

FROM '../../lab7/part_sfo.dat'

WITH DELIMITER ',';
