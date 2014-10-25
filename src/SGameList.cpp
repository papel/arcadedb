#include "SGameList.hpp"
#include "Exception.hpp"
#include "Avulso.hpp"

#include <string.h>
#include <stdio.h>

Game* SGameList::new_game(const char* romname){
    if (quant == limit){
        throw Exception("The limit of the list has been reached.");
    }
    Game* ret = &gameList[quant];
    quant++;
    ret->reset();
    ret->set_romname(romname);
    return ret;
}


static const char* getKey(Game* game){
    return game->get_romname();
}

Game* SGameList::get_game(const char* romname){
    int pos = Avulso::binary_search<Game, const char*>( gameList, quant, romname, strcmp, getKey);
    if (pos < 0){
        return nullptr;
    }
    return &gameList[pos];
}

Iterator<Game>* SGameList::new_iterator(){
    return new ArrayIterator<Game>(gameList, quant);
}
