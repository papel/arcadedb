#ifndef __GAME_LIST__HEADER__
#define __GAME_LIST__HEADER__

#include "Game.hpp"

class GameList{
  public:
    virtual ~GameList(){}
    
    virtual Game* new_game() = 0;
    virtual void add_game() = 0;
        //add to memory
        //print sql
        //print to filter
    
    virtual void set_fba(const char* romname, bool w) = 0;
    virtual void set_genre(const char* romname, const char* genre) = 0;
    virtual void set_version(const char* romname, int ver) = 0;
    virtual void set_nplayers(const char* romname, int nplayers) = 0;
    virtual void set_mature(const char* romname, bool mat) = 0;
    
};    

#endif
