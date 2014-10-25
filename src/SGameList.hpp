#pragma once

#include "GameList.hpp"

class SGameList : public GameList {
    Game* gameList; //alfabetical order from mame instead of hash
    int quant;
    int limit;
    
  public:
    SGameList(int lim){
        gameList = new Game[lim];
        quant = 0;
        limit = lim;
    }
    ~SGameList(){
        delete [] gameList;
    }
    
    Game* new_game(const char* romname);
    Game* get_game(const char* romname);
    Iterator<Game>* new_iterator();
    
};
