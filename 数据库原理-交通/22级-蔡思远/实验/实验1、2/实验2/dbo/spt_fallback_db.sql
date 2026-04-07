create table spt_fallback_db
(
    xserver_name       varchar(30) not null,
    xdttm_ins          datetime    not null,
    xdttm_last_ins_upd datetime    not null,
    xfallback_dbid     smallint,
    name               varchar(30) not null,
    dbid               smallint    not null,
    status             smallint    not null,
    version            smallint    not null
)
go

grant select on spt_fallback_db to [public]
go

