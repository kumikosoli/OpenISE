create table spt_monitor
(
    lastrun       datetime not null,
    cpu_busy      int      not null,
    io_busy       int      not null,
    idle          int      not null,
    pack_received int      not null,
    pack_sent     int      not null,
    connections   int      not null,
    pack_errors   int      not null,
    total_read    int      not null,
    total_write   int      not null,
    total_errors  int      not null
)
go

grant select on spt_monitor to [public]
go

