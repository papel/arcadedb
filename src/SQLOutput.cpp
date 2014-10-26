#include "SQLOutput.hpp"

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
    char manufacturer[60];
    escapeString(manufacturer, game.get_manufacturer() );
    
    char parent[22];
    getOrNull(parent, game.get_parent() );
    char sample_parent[22];
    getOrNull(sample_parent, game.get_sample_parent() );
    char genre[40];
    getOrNull(genre, game.get_genre() );

    
    fprintf(output, 
        "insert into roms values('%s', '%s', %s, '%s', %d, '%s', %d, '%s', %s, '%s', '%s', %s, '%s', %d, %d);\n",
        
        game.get_romname(),
        name,
        parent,
        game.get_board()->get_sourcefile(),
        
        game.get_year(),//int
        manufacturer,
        game.get_size(),//int
        setBool( game.get_chd() != nullptr ),
        
        sample_parent,
        setBool( game.works() ),
        setBool( game.fba() ),
        genre,
        
        setBool( game.ismature() ),
        game.get_nplayers(),//int
        game.get_version() //int
    );
}

void SQLOutput::output(FILE* output, GameList* games){
    Iterator<Game>* it = games->new_iterator();
    std::auto_ptr< Iterator<Game> > ptr(it);
    
    while ( it->hasNext() ){
        Game& game = it->getNext();
        
        //Skip garbage
        const char* genr = game.get_genre();
        if (genr != nullptr ){
            if (strcmp( genr, "Fruit Machines" ) == 0 || strcmp( genr, "System / BIOS" ) == 0) continue;
        }
        
        print_game(output, game);
    }
    
}
