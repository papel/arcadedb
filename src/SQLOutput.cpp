#include "SQLOutput.hpp"

#include <stdio.h>
#include <string.h>
#include <memory>

static const char* getOrNull(const char* str){
    if (str == nullptr){
        return "null";
    }
    return str;
}
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

static void print_game(FILE* output, Game& game){
    char name[110];
    escapeString(name, game.get_name());
    char manufacturer[60];
    escapeString(manufacturer, getOrNull( game.get_manufacturer() ));
    
    fprintf(output, 
        "insert into roms values('%s', '%s', '%s', '%s', %d, '%s', %d, '%s', '%s', '%s', '%s', '%s', '%s', %d, %d);\n",
        
        game.get_romname(),
        name,
        getOrNull( game.get_parent() ),
        game.get_board()->get_sourcefile(),
        
        game.get_year(),//int
        manufacturer,
        game.get_size(),//int
        setBool( game.get_chd() != nullptr ),
        
        getOrNull( game.get_sample_parent() ),
        setBool( game.works() ),
        setBool( game.fba() ),
        getOrNull( game.get_genre() ),
        
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
        
        //Skip fruit machines
        if ( strcmp( getOrNull( game.get_genre() ), "Fruit Machines" ) == 0 ) continue;
        
        print_game(output, game);
    }
    
}
