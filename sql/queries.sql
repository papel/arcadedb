
--List of boards
----------------------------------------
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
    max(case when has_chd then 1 else 0 end) as haschd
from roms where parent is null
group by board
--having first_year >= 1994
--having avg > 10000000
--having working >= 5
order by board;
--order by total_size desc;
--order by avg desc;
--order by first_year;


--List of genres
----------------------------------------
select genre, count(*), sum(size)/1000 from roms
where parent is null group by genre order by genre;


--Clones that work but the parent does not
----------------------------------------
select * from roms
where works and parent in (
    select romname from roms where parent is null and not works
);


--Requires samples
----------------------------------------
select * from roms
where parent is null and sample_set is not null;


--List of bootlegs that are not clones
----------------------------------------
select * from roms
where parent is null and (name like '%bootleg%' or manufacturer like '%bootleg%');


--Multiplayer games whose parent is not multiplayer
----------------------------------------
select * from roms R
where parent is not null and nplayers is not null and nplayers != 1 and exists (
    select * from roms where romname = R.parent and (nplayers = 1 or nplayers is null)
);


--The board that has the largest number of roms
----------------------------------------
select board, count(*) from roms
group by board
having count(*) = (
    select max(y) from (
        select count(*) as y from roms group by board
    ) as t
);


--List of boards that does not work
----------------------------------------
with thing as(
    select
        board,
        100*cast(sum(case when works then 1 else 0 end) as float)/count(*) as ratio
    from roms
    group by board
)
select *
from thing
where ratio < 30
order by ratio desc;



--Filtered list of roms
----------------------------------------
select romname
--select count(*), sum(size)
from roms where parent is null and not has_chd
and (
    fba or
    board not in (
        select board from roms
        group by board
        having cast(100 as float)*sum(case when works then 1 else 0 end)/count(*) < 5
    )
)
--BOARD
and board not in (
--Good systems with alternate source (3D and does not work)
'triforce', --Dolphin (Mario Kart GP 2)
'naomi', --naomi + atomiswave (DC emulator)

'namcos11', --PS1
'namcos12', --PS1 (Tekken, Soulcalibur - PS1)
'model1', --Early 3D
'model2', --Nebula
'model3', --Supermodel
'zn', --Zinc, (includes Taito FX), PS1
'stv', --Saturn
'cps3', --FBA version
'kinst', --N64
'midzeus', --N64
'taitotz', --PC

--Ignored systems (3D and does not work)
--Namco 3D
'namcos10',
'namcos21', --Early 3D
'namcos22',
'namcos23',
'namcops2', --PS2

--Konami 3D
'konamigq', --PS1
'konamigv', --PS1
'konamim2',
'viper',
'nwk-tr',
'zr107',
'gticlub',
'hornet',
'pyson', --PS2

--Konami Bemani
'ksys573', --PS1
'twinkle', --PS1
'djmain',
'firebeat',

--Taito 3D
'taitotz',
'taitogn', --PS1
'taitowlf', --PC, DC version
'taitojc',
'taitopjc',

--Other Notable 3D
'atarigt',
'mediagx', --PC
'vegas', --Midway/Atari Vegas
'seattle', --Driver for Atari/Midway Phoenix/Seattle/Flagstaff
'midqslvr', --PC
'midvunit',
'midxunit',
'atlantis',
'3do',
'hng64',

--Other 3D
'ghosteo',
'gaelco3d',
'itech32',
'seta2',
'tetrisp2',
'nexus3d', --Examu AH1
'aleck64', --N64
'hikaru',
'chihiro',
'atvtrack',
'coolridr',
'magictg',


--Bootleg
'multigam', 'famibox', --NES
'snesb', 'sfcbox', 'nss', --SNES
'tourvis', --PC Engine
'megadrvb', --SMD

--Repetition
'39in1',

--Garbage
'gamtor',
'astropc',
'atronic',
'tmmjprd',
'sfbonus',
'multfish',
'usgames',
'meritm',
'amaticmg',
'pcat_nit',
'peplus',
'')
and not( board like 'mpu4%')

--ROMNAME
and romname not in (
    select romname from roms
    where genre = 'Multiplay' and
    (name like '%bootleg%' or manufacturer like '%bootleg%')
)
and romname not in (
--pseudo-clones
'ms5pcb', --mslug5
'svcpcb', --svc
'kf2k3pcb', --kof2003
'samsho5', --samsh5sp
'kov', --kovplus
'kov2', --kov2p
'kovsh', --kovshp
'ibara', --ibarablk
'futari15', --futaribl
'deathsml', --dsmbl

'kbash2', --Clone and bootleg of kbash (Knuckle Bash)
'mstworld', --Clone and bootleg of spang (Super Pang)
'beastrzb', --Clone and bootleg of beastrzr (Beastorizer (USA) ) - Blood Roar

--Naomi
'slasho', --slashout: "Slashout"
'ggx', --ggx15: "Guilty Gear X ver. 1.5"
'ggxx', 'ggxxrl', 'ggxxsla', --ggxxac: "Guilty Gear XX Accent Core (GDL-0041)"
'vf4', 'vf4cart', 'vf4evo', --vf4evoct: "Virtua Fighter 4 Evolution (Cartridge)", vf4tuned: "Virtua Fighter 4 Final Tuned"
'')

--GENRE
and genre not like 'Casino%'
and genre not like 'Quiz%'
and genre not in(
'Tabletop / Mahjong',
'')
;


--Good roms that were excluded with the filter
----------------------------------------
select romname
--select count(*), sum(size)
from roms
where romname in (
--STV
'prikura', --Princess Clara Daisakusen
'diehard', --Die Hard Arcade
'cottonbm', --Cotton Boomerang
'cotton2', --Cotton 2
'grdforce', --Guardian Force
'rsgun', --Radiant Silvergun
'shienryu', --Shienryu
'sokyugrt', --Soukyugurentai / Terra Diver
'astrass', --Astra SuperStars
'suikoenb', --Suikoenbu / Outlaws of the Lost Dynasty
'colmns97', --Columns  97
'bakubaku', --Baku Baku Animal
'elandore', --Touryuu Densetsu Elan-Doree / Elan Doree - Legend of Dragoon
'groovef', --Groove on Fight - Gouketsuji Ichizoku 3

--ZN
'ts2', --Battle Arena Toshinden 2
'starglad', --Star Gladiator Episode:1 Final Crusade 
'plsmaswd', --Star Gladiator 2
'strider2', --Strider 2

--OTHER
'gradius4',
'slrasslt',
'bballoon',
'grdians',
'gundamex',
'penbros',

--NAOMI
'zerogu2', --Zero Gunner 2 (40)
'gwing2', --Gigawing 2 (50)
'hmgeo', --Heavy Metal Geomatrix (70)
'slasho', --Slash Out (110)

--NAOMI CHD
--Ikaruga (60)
--Border Down (240)
--Chaos Field (130)
--Trizeal (150)
--Under Defeat (180)
--Trigger Heart Exelica (120)
--Shikigami No Shiro (25)
--Shikigami No Shiro II (140)

--ATOMISWAVE
'mslug6', --Metal Slug 6
'kov7sprt', --Knights Of Valour : The Seven Spirits
'dolphin', --Dolphin Blue
'ggx15', --Guilty Gear X Plus 1.5
--Samurai Shodown VI (200)(samsptk)
--The King Of Fighters XI (230)(kofxi)
--Neo-Geo Battle Coliseum (300)(ngbc)

--CPS3
'sfiii3', --CHD
'redearth', --CHD
'')
;
