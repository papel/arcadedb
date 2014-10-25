#pragma once
#include "DataOutput.hpp"

class SQLOutput : public DataOutput{
  public:
    void output(FILE* output, GameList* gamelist);
    ~SQLOutput(){}
};
