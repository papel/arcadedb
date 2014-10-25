create table roms (
    romname varchar(20) primary key,
    name varchar(100),
    parent varchar(20), --romname
    board varchar(20),
    year integer,
    size integer,
    has_chd boolean,
    sample_set varchar(20), --romname
    works boolean default false,
    fba boolean default false,
    genre varchar(40),
    mature boolean,
    nplayers integer,
    version integer
);

