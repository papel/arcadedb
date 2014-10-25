#pragma once

#include "Game.hpp"
#include "Iterator.hpp"

class GameList{
  public:
    virtual ~GameList(){}
    
    virtual Game* new_game(const char* romname) = 0;
    virtual Game* get_game(const char* romname) = 0;
    virtual Iterator<Game>* new_iterator() = 0;
};
