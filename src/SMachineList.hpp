#pragma once

#include "MachineList.hpp"

#include <unordered_set>

class SMachineList : public MachineList{
    struct Comp{
        bool operator()(const Machine& s1, const Machine& s2) const;
    };
    struct Hash{
        size_t operator()(const Machine& m) const;
    };
    typedef std::unordered_set<Machine, Hash, Comp>::iterator MIterator;
    
    std::unordered_set<Machine, Hash, Comp> table;
    
    
  public:
    Machine* new_machine(const char* name);
    Machine* get_machine(const char* name);
    Iterator<Machine>* new_iterator();
    
    ~SMachineList(){}
};
