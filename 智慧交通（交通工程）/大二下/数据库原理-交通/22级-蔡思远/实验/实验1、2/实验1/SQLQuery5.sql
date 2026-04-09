/*create table PERSON (P# nchar(10) primary key,
Pname nchar(10),
Sage smallint check (Sage>18)
)

create table ROOM (R# nchar(10) primary key,
Rname nchar(10),
Rarea nchar(10))

create table PR (P# nchar(10),
R# nchar(10),
Sdate int,
primary key(P#, R#),
foreign key(P#) references PERSON(P#),
foreign key(R#) references ROOM(R#)
)*/

/*alter table PERSON add Ptype char(10)*/

/*alter table PERSON drop constraint [CK__PERSON__Sage__5165187F]*/

/*alter table PERSON add constraint CK_Sage check (Sage>18)*/

--alter table ROOM alter column Rname nchar(40)

--alter table ROOM drop column Rarea

--select name from  sys.foreign_key_columns f join sys.objects o on f.constraint_object_id=o.object_id where f.parent_object_id=object_id('PR')

--alter table PR drop constraint FK__PR__P#__5629CD9C,FK__PR__R#__571DF1D5

create index idx_room_r# on ROOM(R# DESC)

create index idx_person_p# on PERSON(P# ASC)

create unique index idx_person_pname on PERSON(Pname ASC)

drop index idx_person_p# on PERSON