#include "SGameList.hpp"
#include "SMachineList.hpp"
#include "SQLOutput.hpp"
#include "FileRead.hpp"
#include "Exception.hpp"

#include <stdio.h>


int main(int argc, char* argv[]){
    if (argc != 5){
        fprintf(stderr, "Invalid input files. The correct arguments are:\n");
        fprintf(stderr, " %s mamelist.xml fbalist.xml catlist.ini nplayers.ini > output.sql\n", argv[0]);
        return -1;
    }
    
    try {
        SGameList games(50000);
        SMachineList machines;
        SQLOutput outp;
        
        fprintf(stderr, "Reading: %s\n", argv[1]);
        read_mame_xml(argv[1], &games, &machines);
        
        fprintf(stderr, "Reading: %s\n", argv[2]);
//        read_fba_xml(argv[2], &games);
        
        fprintf(stderr, "Reading: %s\n", argv[3]);
        read_genre(argv[3], &games);
        
        fprintf(stderr, "Reading: %s\n", argv[4]);
        read_numplayers(argv[4], &games);
        
        fprintf(stderr, "Output: ...\n" );
        outp.output(stdout, &games);
    }
    catch (Exception& e){
        fprintf(stderr, "%s\n", e.get_message());
    }
    
    return 0;
}
