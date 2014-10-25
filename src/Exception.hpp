#pragma once

class Exception{
    const char* error;
  public:
    Exception(const char* e){
        error = e;
    }
    const char* get_message(){
        return error;
    }
};
