#ifndef __MACHINE__HEADER__
#define __MACHINE__HEADER__

#include "Avulso.hpp"

class Game;

class Machine {
    char name[40];
    char sourcefile[20];
    short first_year;
    short last_year;
    char bios[20];
    int working_games;
    int number_games;
    
  public:
    Machine(){
        reset();
    }
    void reset(){
        name[0] = 0;
        sourcefile[0] = 0;
        first_year = 0;
        last_year = 0;
        bios[0] = 0;
        working_games = 0;
        number_games = 0;
    }
    
    void set_sourcefile(const char* nam){
        int i;
        for (i=0; nam[i] != 0; i++);
        if (i < 2) return;
        if (nam[i-2] == '.' && nam[i-1] == 'c' ){
            i -= 2;
        }
        Avulso::strcop(sourcefile, nam, (i>=20)? 20 : i+1 );
    }
    const char* get_sourcefile() const{
        return sourcefile;
    }
    
    void set_bios(const char* nam){
        Avulso::strcop(bios, nam, 20);
    }
    const char* get_bios() const{
        if (bios[0] == 0) return NULL;
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

#endif
