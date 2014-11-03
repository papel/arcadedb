--Creation of the table
----------------------------------------
create table roms (
    romname varchar(20) primary key,
    name varchar(100),
    parent varchar(20), --romname
    board varchar(20),
    year integer,
    manufacturer varchar(50),
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

--View of boards
----------------------------------------
create view boards as
select
    board,
    coalesce(sum(size)/1000, 0) as total_size,
    cast(coalesce(avg(size), 0) as integer) as avg,
    count(*) as num_games,
    min(case when year > 1950 then year end) as first_year,
    max(case when year > 1950 then year end) as last_year,
    100*cast(sum(case when works then 1 else 0 end) as float)/count(*) as working,
    --bool_or(fba) as fba
    max(case when fba then 1 else 0 end) as fba
from roms where parent is null
group by board
order by board;

--View of genres
----------------------------------------
create view genres as
select genre, count(*), sum(size)/1000 from roms
where parent is null group by genre order by genre;
