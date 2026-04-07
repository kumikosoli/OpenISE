create database 图书管理;
 
use 图书管理;

create table admin(
adminname varchar(50) primary key,
password varchar(50),
asfz varchar(50),
atel varchar(50),
azw varchar(50)
);

create table cbs(
cbsbh varchar(50) primary key,
mz varchar(50),
fzr varchar(50),
lxdh varchar(50),
jtwz varchar(50)
);

create table sjlb(
bh varchar(50) primary key,
mc varchar(50),
bz varchar(50)
);

create table sj(
sjbh varchar(50) primary key,
sm varchar(50),
cbsbh varchar(50),
foreign key(cbsbh) references cbs(cbsbh),
dj float default 0,
zz varchar(50),
lbbh varchar(50),
foreign key(lbbh) references sjlb(bh),
gcsl int,
kjsl int,
sfkj varchar(50) check (sfkj in ('是','否'))
);

create table usera(
ubh varchar(50) primary key,
xm varchar(50),
xb varchar(50) check (xb in ('男','女')),
dh varchar(50),
jtdz varchar(50),
upwd varchar(50)
);

create table jyxx(
jybh varchar(50) primary key,
sjbh varchar(50),
foreign key(sjbh) references sj(sjbh),
ubh varchar(50),
foreign key(ubh) references usera(ubh),
jysj date,
jyts int,
ghsj date
);

CREATE TRIGGER trg_ReturnBook  
ON jyxx  
AFTER UPDATE  
AS  
BEGIN  
        UPDATE sj  
        SET kjsl = kjsl + 1  where sjbh=(select sjbh from deleted);
END;

CREATE TRIGGER trg_addjBook  
ON jyxx  
AFTER insert  
AS  
BEGIN  
        UPDATE sj  
        SET kjsl = kjsl - 1  where sjbh=(select sjbh from inserted);
END;

select usera.xm,jyxx.* from usera,jyxx where jyxx.ubh=usera.ubh;

select * from usera where xm like '张%_';

select cbs.mz,sj.* from cbs,sj where cbs.cbsbh=sj.cbsbh;

create view va
as
select usera.xm,jyxx.* from usera,jyxx where jyxx.ubh=usera.ubh;

insert into usera values
('1','张三','男','13048573645','学院路1号','123'),
('2','李四','男','13048573641','学院路2号','123'),
('3','王五','女','13048573642','学院路3号','123');

insert into admin values
('admin','123','45937462534364839','1283744362','管理员'),
('admia','123','45937462534364831','1283744361','管理员'),
('admib','123','45937462534364832','1283744363','管理员'),
('admic','123','45937462534364833','1283744364','管理员'),
('admid','123','45937462534364834','1283744365','管理员');

insert into sjlb values
('1','传统',null),
('2','神话',null),
('3','悬疑',null),
('4','都市',null);

insert into cbs values
('1','中国出版社','张大奕','111-111-111','北京路1号'),
('2','儿童出版社','王雪','111-111-112','北京路2号'),
('3','兴业出版社','薛兴业','111-111-113','北京路3号'),
('4','爱好出版社','李学','111-111-114','北京路4号');

insert into sj values
('1','西游记','1',19.9,'吴承恩','1'),
('2','十宗罪','3',19.9,'蜘蛛','2');

insert into jyxx values
('1','1','1',getdate(),1,null),
('2','1','2','2023-03-15',2,getdate());

