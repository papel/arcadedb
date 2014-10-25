#ifndef __SGAME_LIST__HEADER__
#define __SGAME_LIST__HEADER__

#include "GameList.hpp"

#include <stdio.h>
class SGameList : public GameList {
    Game internal;
    
  public:
    SGameList(){
    }
    ~SGameList(){
    }
    Game* new_game(){
        internal.reset();
        return &internal;
    }
    void add_game(){
        
        if ( internal.get_parent() == NULL && internal.get_chd() == NULL && internal.works()  ) {
            printf("%s | %s | %s | %u\n", internal.get_romname(), internal.get_name(), internal.get_system()->get_sourcefile(), (internal.get_sample_parent() != NULL)?1:0 );
        }

    }

};

#endif
