#include "SGameList.hpp"
#include "SMachineList.hpp"

#include "SQLGameList.hpp"

#include <stdio.h>

void read_mame_xml(const char* input, GameList* games, MachineList* machines);
void read_fba_xml(const char* input, GameList* games);

void read_lists1(const char* input, GameList* games, int md);
void read_lists2(const char* input, GameList* games, int md);


int main(int argc, char* argv[]){
    if (argc != 6){
        printf("this_file.exec mame.xml fba.xml Catlist.ini Version.ini nplayers.ini\n");
        return -1;
    }
    
    //tabela de bios
    //cat db.sql | sqlite3 database.db
    //0 1 sqlite
    //Lista como hash
    //Lista binário alfabética com a ordem do mame
    //Tamanho somando rom
    
    SQLGameList games;
    SMachineList machines;
    
    /*
    FILE* sourc = execute_mame_xml(argv[1]);
    if (sourc == NULL)
        return -1;
    */
    
    read_mame_xml(argv[1], &games, &machines);
    read_fba_xml(argv[2], &games);
    read_lists1(argv[3], &games, 1);
    read_lists1(argv[4], &games, 2);
    read_lists2(argv[5], &games, 1);
    
    //
    
    return 0;
}
