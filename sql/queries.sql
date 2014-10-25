
--List of boards
----------------------------------------
select
    board,
    coalesce(sum(size)/1000, 0) as size,
    cast(coalesce(avg(size), 0) as integer) as avg,
    min(case when year > 1950 then year end) as first_year,
    max(case when year > 1950 then year end) as last_year,
    count(*) as num_games,
    100*cast(count(case when works then 1 end) as float)/count(*) as working
from roms where parent is null
group by board
--having min(year) >= 1994
--having avg(size) > 10000000
order by board;
--order by coalesce(sum(size), 0) desc;
--order by coalesce(avg(size), 0) desc;
--order by min(year);


--List of working boards
----------------------------------------
select board, count(case when has_chd then 1 end), count(*), 100*cast(count(case when works then 1 end) as float)/count(*) as working, min(year)
from roms
where parent is null
group by board
having 100*cast(count(case when works then 1 end) as float)/count(*) >= 5;


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
where parent is null and sample_parent is not null;


--List of bootlegs that are not clones
----------------------------------------
select * from roms
where parent is null and name like '%bootleg%';


--Multiplayer games whose parent is not multiplayer
----------------------------------------
select * from roms R
where parent is not null and nplayers is not null and nplayers != 1 and exists (
    select * from roms where romname = R.parent and (nplayers = 1 or nplayers is null)
);


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
        100*cast(count(case when works then 1 end) as float)/count(*) as ratio
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
from roms where parent is null and not has_chd and (
    fba or
    board not in (
        select board from roms
        group by board
        having cast(100 as float)*count(case when works then 1 end)/count(*) < 5
    )
)
and board not in (
--New and does not work
'pgm2',
--Cave CV1000

--Good systems with alternative download
'triforce', --Dolphin (Mario Kart GP 2)
'naomi', --naomi + atomiswave (see list)

'namcos11', --PS1
'namcos12', --PS1 (Tekken, Soulcalibur - PS1)
'model1', --Early 3D
'model2', --Nebula
'model3', --Supermodel
'zn', --Zinc, (include Taito FX), PS1
'stv', --Saturn
'cps3', --FBA version
'kinst', --N64
'midzeus', --N64

--Ignored systems
'namcos10', --Bad
'namcos21', --Early 3D
'namcos22',
'namcos23',

'ksys573', --PS1
'konamigq', --PS1
'konamigv', --PS1
'konamim2',
'viper',
'nwk-tr',
'zr107',
'gticlub',
'hornet',
'pyson', --PS2
'twinkle', --PS1
'djmain',
'firebeat',
--Konami Bemani

'taitogn', --PS1
'taitowlf', --PC, DC version
'taitojc',
'taitopjc',
'taitotz', --PC
--Scorpion

'atarigt',
'atarifb',
'3do',
'mediagx', --PC
'vegas', --Midway/Atari Vegas
'seattle', --Driver for Atari/Midway Phoenix/Seattle/Flagstaff
--Atari Cojag, Atari Denver

'midqslvr', --PC
'midvunit',
'midxunit',
'atlantis',
--Midway Zeus II, Graphite (PC)

'eolith',
'ghosteo',
'gaelco3d',
'itech32',
'seta2',
'tetrisp2',
--seibu spi

--Ignored systems, mostly 3D
'aleck64', --N64
'namcops2', --PS2
'nexus3d', --AH1
'hikaru',
'chihiro',
'hng64',
'atvtrack',
'coolridr',
'magictg',

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
'')
and not( board like 'mpu4%')

and romname not in (
'ms5pcb', --pseudo-clone of mslug5
'svcpcb', --pseudo-clone of svc
'kf2k3pcb', --pseudo-clone of kof2003
'samsho5', --pseudo-clone of samsh5sp
'kbash2', --Clone and bootleg of kbash (Knuckle Bash)
'mstworld', --Clone and bootleg of spang (Super Pang)
'beastrzb', --Clone and bootleg of beastrzr (Beastorizer (USA) ) - Blood Roar
'kov', --kovplus
'kov2', --kov2p
'kovsh', --kovshp

--Naomi
'slasho', --slashout: "Slashout"
'ggx', --ggx15: "Guilty Gear X ver. 1.5"
'ggxx', 'ggxxrl', 'ggxxsla', --ggxxac: "Guilty Gear XX Accent Core (GDL-0041)"
'vf4', 'vf4cart', 'vf4evo', --vf4evoct: "Virtua Fighter 4 Evolution (Cartridge)", vf4tuned: "Virtua Fighter 4 Final Tuned"
'')

and genre not in(
'Fruit Machines',
'Casino',
'') and not (genre like 'Quiz%')
;
--'multigam', 'famibox', --NES
--'snesb', 'sfcbox',
--'tourvis', --PC Engine
--'megadrvb'


--Good roms that were excluded with the filter
----------------------------------------
select romname from roms
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
'salmndr2',
'dragoona',

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
--Neo-Geo Battle Coliseum ()(ngbc)--300

--CPS3
'sfiii3', --CHD
'redearth', --CHD
'')
;
