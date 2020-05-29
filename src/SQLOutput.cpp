#include "SQLOutput.hpp"
#include "Avulso.hpp"

#include <stdio.h>
#include <string.h>
#include <memory>

static const char* setBool(bool boo){
    /*
    if (boo){
        return "true";
    }
    else {
        return "false";
    }
    */
    //for sqlite
    if (boo){
        return "1";
    }
    else {
        return "0";
    }
}

static void escapeString(char* dest, const char* src){
    while (*src){
        if (*src == '\''){
            *dest = '\'';
            dest++;
            *dest = '\'';
        }
        else {
            *dest = *src;
        }
        dest++;
        src++;
    }
    *dest = *src;
}
static void getOrNull(char* dest, const char* src){
    if (src == nullptr){
        strcpy(dest, "null");
    }
    else {
        strcpy(dest, "'");
        strcat(dest, src);
        strcat(dest, "'");
    }
}

static void print_game(FILE* output, Game& game){
    char name[110];
    escapeString(name, game.get_name());
    char manufacturer[110];
    escapeString(manufacturer, game.get_manufacturer() );
    
    char parent[22];
    getOrNull(parent, game.get_parent() );
    char sample_parent[22];
    getOrNull(sample_parent, game.get_sample_parent() );
    char genre[40];
    getOrNull(genre, game.get_genre() );

    
    fprintf(output, 
        "insert into roms values('%s', '%s', %s, '%s', %d, '%s', %llu, '%s', %s, '%s', '%s', %s, '%s', %d);\n",
        
        game.get_romname(),
        name,
        parent,
        game.get_board()->get_sourcefile(),
        
        (int)game.get_year(),
        manufacturer,
        game.get_size(),//uint64
        setBool( game.get_chd() != nullptr ),
        
        sample_parent,
        setBool( game.works() ),
        setBool( game.fba() ),
        genre,
        
        setBool( game.ismature() ),
        (int)game.get_nplayers()
    );
}

void SQLOutput::output(FILE* output, GameList* games){
    Iterator<Game>* it = games->new_iterator();
    std::auto_ptr< Iterator<Game> > ptr(it);
    
    while ( it->hasNext() ){
        Game& game = it->getNext();
        
        //Skip garbage
        //Bios are separate because they aren't game 
        const char* genr = game.get_genre();
        if (genr != nullptr ){
            if (Avulso::str_starts(genr, "MESS")){
                continue;
            }
        }
        
        print_game(output, game);
    }
    
}
