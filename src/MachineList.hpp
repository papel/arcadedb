#ifndef __MACHINE_LIST__HEADER__
#define __MACHINE_LIST__HEADER__

#include "Machine.hpp"

#include <unordered_set>


class MachineList{
    typedef std::unordered_set<Machine>::iterator Iterator;
    struct Comp{
        bool operator()(const Machine& s1, const Machine& s2) const;
    };
    struct Hash{
        size_t operator()(const Machine& m) const;
    };
    
    std::unordered_set<Machine, Hash, Comp> table;
    Machine to_insert;
    
  public:
    virtual Machine* new_machine() = 0;
    virtual Machine* add_machine() = 0;
    
};

#endif
