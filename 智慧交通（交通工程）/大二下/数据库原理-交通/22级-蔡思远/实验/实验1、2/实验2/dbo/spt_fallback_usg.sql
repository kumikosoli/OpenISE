create table spt_fallback_usg
(
    xserver_name       varchar(30) not null,
    xdttm_ins          datetime    not null,
    xdttm_last_ins_upd datetime    not null,
    xfallback_vstart   int,
    dbid               smallint    not null,
    segmap             int         not null,
    lstart             int         not null,
    sizepg             int         not null,
    vstart             int         not null
)
go

grant select on spt_fallback_usg to [public]
go

