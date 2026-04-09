create table Stu_Union (
sid int not null,
sname char(20),
age int,
department char(50),
primary key (sid)
)

insert into Stu_Union (sid, sname, age, department)
values (001, 'Cai', 20, 'computer science')

update Stu_Union
set sname='Liu', age=23, department='electronic engineering'
where sid=001

select *
from Stu_Union
where sid=001

insert into Stu_Union (sid, sname, age, department)
values (001, 'Jacky', 22, 'economy')

insert into Stu_Union (sid, sname, age, department)
values (002, 'Michal', 20, 'clinical medicine')

update Stu_Union
set sid=001
where sid=002

create table scholarship (
schoid int not null,
sid int,
amount int,
primary key (schoid),
foreign key (sid) references Stu_Union(sid)
)

insert into scholarship(schoid, sid, amount)
values (01, 001, 1000)

insert into scholarship(schoid, sid, amount)
values (02, 003, 10000)

create table course(
cno int not null,
cname char(50),
chour int,
primary key (cno)
)

insert into course(cno, cname, chour)
values(001, 'database', 32)

insert into course(cno, cname, chour)
values(002, 'algorithm', 32)

insert into course(cno, cname, chour)
values(003, 'data structure', 48)

insert into Stu_Union (sid, sname, age, department)
values (003, 'Kyle', 21, 'art')

insert into Stu_Union (sid, sname, age, department)
values (004, 'Wang', 20, 'computer science')

create table sc(
sno int,
cno int,
grade int,
primary key (sno,cno),
foreign key (sno) references Stu_Union(sid) on delete cascade,
foreign key (cno) references course(cno) on delete cascade,
)

insert into sc(sno, cno, grade)
values(001, 002, 92)

insert into sc(sno, cno, grade)
values(002, 001, 80)

insert into sc(sno, cno, grade)
values(003, 003, 67)

insert into sc(sno, cno, grade)
values(008, 009,70)

delete
from Stu_Union
where sid=001

delete
from course
where cno=003

create table Stu_Card(
card_id int,
sid int,
dormitory char(20),
primary key (card_id),
foreign key (sid) references Stu_Union(sid) on delete cascade
)

insert into Stu_Card(card_id, sid, dormitory)
values(101, 002, 'east01')

insert into Stu_Card(card_id, sid, dormitory)
values(102, 003, 'east01')

insert into Stu_Card(card_id, sid, dormitory)
values(103, 004, 'west02')

create table ICBC_Card(
stu_card_id int,
bank_id int,
money int,
primary key (bank_id),
foreign key (stu_card_id) references Stu_Card(card_id) on delete cascade
)

insert into ICBC_Card(stu_card_id, bank_id, money)
values(101, 2201, 10000)

insert into ICBC_Card(stu_card_id, bank_id, money)
values(102, 2202, 20000)

insert into ICBC_Card(stu_card_id, bank_id, money)
values(103, 2203, 30000)

delete
from Stu_Union
where sid=002

create table teaching_table(
cid int,
tid int,
primary key (cid),
)

create table listening_table(
tid int,
cid int,
primary key (tid),
)

alter table teaching_table
add constraint fk_teaching_teacher_table
foreign key (tid) references listening(tid) on delete no action on update no action

alter table listening_table
add constraint fk_listening_course_table
foreign key (cid) references teaching(cid) on delete no action on update no action








