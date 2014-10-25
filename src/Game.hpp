#ifndef __GAME__HEADER__
#define __GAME__HEADER__

#include "Machine.hpp"
#include "Avulso.hpp"

class Game {
    char name[100];
    char rom_name[20];
    char manufacturer[30];
    short year;
    Machine* system;
    char chd_file[20];
    char sample_of[20];
    char clone_of[20];
    bool _works;
    
  public:
    Game(){
        reset();
    }
    void reset(){
        name[0] = 0;
        rom_name[0] = 0;
        manufacturer[0] = 0;
        year = 0;
        system = NULL;
        chd_file[0] = 0;
        sample_of[0] = 0;
        clone_of[0] = 0;
        _works = false;
    }
    
    
    void set_name(const char* nam){
        Avulso::strcop(name, nam, 100);
    }
    const char* get_name() const{
        return name;
    }
    
    void set_romname(const char* nam){
        Avulso::strcop(rom_name, nam, 20);
    }
    const char* get_romname() const{
        return rom_name;
    }
    
    void set_manufacturer(const char* nam){
        Avulso::strcop(manufacturer, nam, 30);
    }
    const char* get_manufacturer() const{
        return manufacturer;
    }
    
    void set_year(short y){
        year = y;
    }
    short get_year() const{
        return year;
    }
    
    void set_system(Machine* sys){
        system = sys;
    }
    Machine* get_system() const{
        return system;
    }
    
    void set_chd(const char* chd){
        Avulso::strcop(chd_file, chd, 20);
    }
    const char* get_chd(){
        if (chd_file[0] == 0) return NULL;
        return chd_file;
    }
    
    void set_sample_parent(const char* nam){
        Avulso::strcop(sample_of, nam, 20);
    }
    const char* get_sample_parent(){
        if (sample_of[0] == 0) return NULL;
        return sample_of;
    }
    
    void set_parent(const char* nam){
        Avulso::strcop(clone_of, nam, 20);
    }
    const char* get_parent() const{
        if (clone_of[0] == 0) return NULL;
        return clone_of;
    }
    
    bool works(bool w){
        _works = w;
    }
    bool works() const{
        return _works;
    }
    
};

#endif
