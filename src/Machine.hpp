#pragma once

#include "Avulso.hpp"

class Game;
typedef Game Bios;

class Machine {
    char sourcefile[20];
    char name[40];
    short first_year;
    short last_year;
    Bios* bios;
    int working_games;
    int number_games;
    
  public:
    Machine(){
        reset();
    }
    ~Machine();
    
    void reset(){
        sourcefile[0] = 0;
        name[0] = 0;
        first_year = 0;
        last_year = 0;
        bios = nullptr;
        working_games = 0;
        number_games = 0;
    }
    
    void set_sourcefile(const char* nam){
        int i;
        for (i=0; nam[i] != 0; i++);
        if (i < 2) return;
        Avulso::strcop(sourcefile, nam, (i>=20)? 20 : i+1 );
    }
    const char* get_sourcefile() const{
        return sourcefile;
    }
    
    void set_bios(Bios* nam){
        bios = nam;
    }
    Bios* get_bios() const{
        return bios;
    }
    
    short get_first_year() const{
        return first_year;
    }
    short get_last_year() const{
        return last_year;
    }
    
    short get_number_games() const{
        return number_games;
    }
    short get_working_rate() const{
        if (number_games==0) return 0;
        return (short)(100*((float)working_games/number_games));
    }
    
    void add_game(Game* game);
    
};
