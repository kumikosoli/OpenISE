create table spt_fallback_dev
(
    xserver_name       varchar(30)  not null,
    xdttm_ins          datetime     not null,
    xdttm_last_ins_upd datetime     not null,
    xfallback_low      int,
    xfallback_drive    char(2),
    low                int          not null,
    high               int          not null,
    status             smallint     not null,
    name               varchar(30)  not null,
    phyname            varchar(127) not null
)
go

grant select on spt_fallback_dev to [public]
go

