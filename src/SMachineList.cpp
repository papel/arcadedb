# include "SMachineList.hpp"

#include <string.h>
#include <stdio.h>

bool SMachineList::Comp::operator()(const Machine& s1, const Machine& s2) const{
    return strcmp(s1.get_sourcefile(), s2.get_sourcefile()) == 0;
}
size_t SMachineList::Hash::operator()(const Machine& m) const{
    const char* str = m.get_sourcefile();
    size_t mul = 1;
    size_t res = 0;
    for (int i=0; str[i] != 0; i++){
        res += (str[i]-50)*mul;
        mul *= 50;
    }
    return res;
}


Machine* SMachineList::new_machine(const char* name){
    Machine to_insert;
    to_insert.reset();
    to_insert.set_sourcefile(name);
    
    std::pair<MIterator, bool> ins = table.insert(to_insert);
    Machine* inserted = (Machine*)&(*ins.first);
    
    if (!ins.second){
        //update
        //..
    }
    
    return inserted;
}

Machine* SMachineList::get_machine(const char* name){
    Machine to_insert;
    to_insert.reset();
    to_insert.set_sourcefile(name);
    MIterator it = table.find(to_insert);
    if (it == table.end()){
        return nullptr;
    }
    return (Machine*)&(*it);
}

Iterator<Machine>* SMachineList::new_iterator(){
    MIterator a = table.begin();
    MIterator b = table.end();
    return new WIterator<Machine, MIterator>(a, b);
}




void SMachineList::print(){
    for (MIterator it = table.begin(), end = table.end(); it != end; it++){
        Machine& ma = *(Machine*)&(*it);
        const char* bios = ma.get_bios();
        printf("%s (%s) | %d | %d (%d)\n", ma.get_sourcefile(), (bios!=NULL)? bios : "-",  ma.get_first_year(), ma.get_number_games(), ma.get_working_rate() );
        
    }
    
    //create table boards (sourcefile varchar(20) primary key, name varchar(80), first_year integer, last_year integer);
    for (MIterator it = table.begin(), end = table.end(); it != end; it++){
        Machine& ma = *(Machine*)&(*it);
        const char* bios = ma.get_bios();
        printf("insert into boards values (\'%s\', NULL, NULL);\n", ma.get_sourcefile() );
    }
    
}

