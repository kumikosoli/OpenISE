select sname
from STUDENTS
where grade='2004'
order by sid ASC

select (score-60)*0.1+1
from CHOICES
where score >= 60

select cname
from COURSES
where hour=48 or hour=64

select cid
from COURSES
where cname like '%data%'

select distinct cid
from CHOICES

select MIN(salary)
from TEACHERS

select T.tid, AVG(CO.score) as avg_score
from TEACHERS T join CHOICES CO on T.tid=CO.tid
group by T.tid

select count(distinct sid)
from CHOICES
group by cid
order by count(distinct sid) DESC

select sid
from CHOICES
group by sid
having count(cid)>=6

select cname, score
from CHOICES, COURSES
where CHOICES.cid=COURSES.cid and CHOICES.cid=899996700

select distinct sid
from CHOICES, COURSES
where CHOICES.cid in
(select cid
from COURSES
where cname='database')

select cid, count(*)
from CHOICES
group by cid

select cid
from CHOICES
group by cid
having count(*)>=6

select sid
from CHOICES as COX
where not exists
(select *
from CHOICES as COY
where COY.sid=800009026 and not exists
(select *
from CHOICES COZ
where COZ.sid=COX.sid and COZ.cid=COY.cid))

select score
from CHOICES
where sid=800009026

select sid
from CHOICES
where cid in
(select cid
from COURSES
where cname='java')
intersect
select sid
from CHOICES
where cid in
(select cid
from COURSES
where cname='c++')

select sid
from CHOICES
where cid in
(select cid
from COURSES
where cname='database')
except
select sid
from CHOICES
where cid in
(select cid
from COURSES
where cname='java')

select sname
from STUDENTS
join
(select sid
from CHOICES
group by sid
having count(cid)>
(select avg(counts)
from
(select count(cid) as counts
from CHOICES
group by sid) as sub)) as subb on subb.sid=STUDENTS.sid

select sid, avg(score)
from CHOICES
group by sid
having avg(score) > 80

select email
from STUDENTS join (
select sid
from CHOICES
group by sid
having count(cid) = (
select min(counts)
from (
select count(cid) counts
from CHOICES
group by sid) as sub)) as subb on subb.sid=STUDENTS.sid

select sid
from CHOICES
where score=(
select max(algo_score)
from (
select score algo_score
from CHOICES
where cid=(
select cid
from COURSES
where cname='algorithm')) as sub)

select count(*)
from(
select sid
from CHOICES
where cid=(
select cid
from COURSES
where cname='data structure')
intersect
select sid
from CHOICES
where cid=(
select cid
from COURSES
where cname='algorithm')) as sub

select count(*)
from CHOICES
where sid=895624871 and score>80

select count(counts_q)/count(counts_all)*100
from (
select count(sid) counts_q
from CHOICES
where tid=200017039 and score>=60) as sub, (
select count(sid) counts_all
from CHOICES
where tid=200017039) as subb


















