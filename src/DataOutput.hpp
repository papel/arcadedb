#pragma once
#include "GameList.hpp"
#include <stdio.h>

class DataOutput{
  public:
    virtual void output(FILE* output, GameList* gamelist) = 0;
    virtual ~DataOutput(){}
};
