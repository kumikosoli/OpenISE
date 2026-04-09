create table MSreplication_options
(
    optname          sysname not null,
    value            bit     not null,
    major_version    int     not null,
    minor_version    int     not null,
    revision         int     not null,
    install_failures int     not null
)
go

