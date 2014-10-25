#pragma once

#include "Machine.hpp"
#include "Iterator.hpp"

class MachineList{
  public:
    virtual Machine* new_machine(const char* name) = 0;
    virtual Machine* get_machine(const char* name) = 0;
    virtual Iterator<Machine>* new_iterator() = 0;
    virtual ~MachineList(){}
};
