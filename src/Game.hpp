#pragma once

#include "Machine.hpp"
#include "Avulso.hpp"

class Game {
    char rom_name[20];
    char name[100];
    char clone_of[20];
    Machine* board;
    short year;
    char manufacturer[50];
    int size;
    char chd_file[20];
    char sample_of[20];
    bool _works;
    bool _fba;
    char genre[40];
    bool mature;
    short nplayers;
    int version;
    
  public:
    Game(){
        reset();
    }
    void reset(){
        rom_name[0] = 0;
        name[0] = 0;
        clone_of[0] = 0;
        board = nullptr;
        year = 0;
        manufacturer[0] = 0;
        size = 0;
        chd_file[0] = 0;
        sample_of[0] = 0;
        _works = false;
        _fba = false;
        genre[0] = 0;
        mature = false;
        nplayers = 0;
        version = 0;
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
        Avulso::strcop(manufacturer, nam, 50);
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
    
    void set_board(Machine* sys){
        board = sys;
    }
    Machine* get_board() const{
        return board;
    }
    
    void set_chd(const char* chd){
        Avulso::strcop(chd_file, chd, 20);
    }
    const char* get_chd(){
        if (chd_file[0] == 0) return nullptr;
        return chd_file;
    }
    
    void set_sample_parent(const char* nam){
        Avulso::strcop(sample_of, nam, 20);
    }
    const char* get_sample_parent(){
        if (sample_of[0] == 0) return nullptr;
        return sample_of;
    }
    
    void set_parent(const char* nam){
        Avulso::strcop(clone_of, nam, 20);
    }
    const char* get_parent() const{
        if (clone_of[0] == 0) return nullptr;
        return clone_of;
    }
    
    void set_genre(const char* nam){
        Avulso::strcop(genre, nam, 40);
    }
    const char* get_genre() const{
        if (genre[0] == 0) return nullptr;
        return genre;
    }
    
    void set_nplayers(short y){
        nplayers = y;
    }
    short get_nplayers() const{
        return nplayers;
    }
    
    void set_size(int y){
        size = y;
    }
    int get_size() const{
        return size;
    }
    void set_version(int y){
        version = y;
    }
    int get_version() const{
        return version;
    }
    
    
    void ismature(bool w){
        mature = w;
    }
    bool ismature() const{
        return mature;
    }
    void works(bool w){
        _works = w;
    }
    bool works() const{
        return _works;
    }
    void fba(bool w){
        _fba = w;
    }
    bool fba() const{
        return _fba;
    }
    
};
