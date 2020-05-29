#pragma once

#include "GameList.hpp"

class SGameList : public GameList {
    Game* gameList; //alphabetical order instead of hash
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
