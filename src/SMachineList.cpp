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
