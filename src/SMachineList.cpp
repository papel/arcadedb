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


Machine* SMachineList::new_machine(){
    to_insert.reset();
    return &to_insert;
}

Machine* SMachineList::add_machine(){
    
    std::pair<Iterator, bool> ins = table.insert(to_insert);
    Machine* inserted = (Machine*)&(*ins.first);
    
    if (!ins.second){
        //update
        //..
    }
    
    return inserted;
}

void SMachineList::print(){
    for (Iterator it = table.begin(), end = table.end(); it != end; it++){
        Machine& ma = *(Machine*)&(*it);
        const char* bios = ma.get_bios();
        printf("%s (%s) | %d | %d (%d)\n", ma.get_sourcefile(), (bios!=NULL)? bios : "-",  ma.get_first_year(), ma.get_number_games(), ma.get_working_rate() );
        
    }
    
    //create table boards (sourcefile varchar(20) primary key, name varchar(80), first_year integer, last_year integer);
    for (Iterator it = table.begin(), end = table.end(); it != end; it++){
        Machine& ma = *(Machine*)&(*it);
        const char* bios = ma.get_bios();
        printf("insert into boards values (\'%s\', NULL, NULL);\n", ma.get_sourcefile() );
    }
    
}

