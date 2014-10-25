#ifndef __SMACHINE_LIST__HEADER__
#define __SMACHINE_LIST__HEADER__

#include "MachineList.hpp"

#include <unordered_set>

class SMachineList : public MachineList{
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
    virtual Machine* new_machine();
    virtual Machine* add_machine();
    
    void print();
    
    ~SMachineList(){}
};

#endif
