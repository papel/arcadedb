#include "GameList.hpp"

#include <stdio.h>
#include <string.h>

class SQLGameList : public GameList {
    Game internal;
    FILE* output;
    
  public:
    SQLGameList(){
        output = stdout;
        //fprintf(output, "create table roms );
    }
    ~SQLGameList(){
    }
    Game* new_game(){
        internal.reset();
        return &internal;
    }
    void add_game(){
        
        char name[100];
        strcpy(name, internal.get_name());
        for(int i=0; name[i] != 0; i++){
            if (name[i] == '\'' || name[i] == '\"'){
                name[i] = ' ';
            }
        }
        
        char parent[30];
        if (internal.get_parent() != NULL){
            strcpy(parent, "\'");
            strcat(parent, internal.get_parent());
            strcat(parent, "\'");
        }
        char sample[30];
        if (internal.get_sample_parent() != NULL){
            strcpy(sample, "\'");
            strcat(sample, internal.get_sample_parent());
            strcat(sample, "\'");
        }
        
        fprintf(output,
            "insert into roms values('%s', '%s', %s, '%s', %d, NULL, %s, %s, %s, NULL, NULL, NULL, NULL, NULL);\n",
            internal.get_romname(),
            name,
            (internal.get_parent() != NULL)? parent : "NULL",
            internal.get_system()->get_sourcefile(),
            internal.get_year(),
            //(internal.get_chd() != NULL)? "true" : "false",
            (internal.get_chd() != NULL)? "1" : "0",

            (internal.get_sample_parent() != NULL)? sample : "NULL",
            //(internal.works())? "true" : "false"
            (internal.works())? "1" : "0"
        );
        
    }
    void set_fba(const char* romname, bool w){
        if (w){
            //fprintf(output, "%s\n", romname);
            //fprintf(output, "update roms set fba = true where romname = \'%s\';\n", romname);
            fprintf(output, "update roms set fba = 1 where romname = \'%s\';\n", romname);
        }
    }
    void set_genre(const char* romname, const char* genre){
        //fprintf(output, "%s %s\n", romname, rdata);
        fprintf(output, "update roms set genre = \'%s\' where romname = \'%s\';\n", genre, romname);
    }
    void set_mature(const char* romname, bool mat){
        //fprintf(output, "update roms set mature = %s where romname = \'%s\';\n", (mat)?"true":"false", romname);
        fprintf(output, "update roms set mature = %s where romname = \'%s\';\n", (mat)?"1":"0", romname);
    }
    void set_version(const char* romname, int ver){
        //fprintf(output, "%s %d\n", romname, ver);
        fprintf(output, "update roms set version = %d where romname = \'%s\';\n", ver, romname);
    }
    void set_nplayers(const char* romname, int nplayers){
        //fprintf(output, "%s %d\n", romname, nplayers);
        fprintf(output, "update roms set nplayers = %d where romname = \'%s\';\n", nplayers, romname);
    }
    
};
