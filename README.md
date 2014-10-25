arcadedb
========

This is a generator of SQL commands to create a database about Arcade games.

###Compilation
It uses [pugixml](http://pugixml.org/).

There is nothing special about the compilation. Compile everything with `g++ -std=c+11` and include *pugixml* files.

###Execution
`./listing mamelist.xml fbalist.xml Catlist.ini Version.ini nplayers.ini`

###Input files
* **mamelist.xml**: Obtained from MAME by running the command: `./mame -listxml > mamelist.xml`
* **fbalist.xml**: Obtained from FBA GUI.
* **Catlist.ini** and **Version.ini**: Download **cat32en** from [this link](http://www.progettoemma.net/?catlist).
* **nplayers.ini**: Download from [here](http://nplayers.arcadebelgium.be/).

###Output
It will output the results to stdout.

###Database
Using **sqlite3**:  
`cat sql/table.sql | sqlite3 database.db`  
`./listing mamelist.xml fbalist.xml Catlist.ini Version.ini nplayers.ini | sqlite3 database.db`

You can use [sqlitebrowser](http://sourceforge.net/projects/sqlitebrowser/). It is a GUI for sqlite.

See the file `sql/table.sql` to see some queries.
