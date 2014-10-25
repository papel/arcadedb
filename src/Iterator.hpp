#pragma once

template<typename Type>
class Iterator{
public:
    virtual bool hasNext() = 0;
    virtual Type& getNext() = 0;
    virtual ~Iterator(){}
};

template<typename TType>
class ArrayIterator : public Iterator<TType>{
    TType* ptr;
    int pos;
    int quant;
    
  public:
    ArrayIterator(TType* pt, int quan){
        ptr = pt;
        pos = 0;
        quant = quan;
    }
    
    bool hasNext(){
        return pos < quant;
    }
    TType& getNext(){
        pos++;
        return ptr[pos - 1];
    }
    
};

template<typename TType, typename TIt>
class WIterator : public Iterator<TType>{
    TIt it;
    TIt end;
    
  public:
    WIterator(TIt& i, TIt& e)
    : it(i), end(e){}
    
    bool hasNext(){
        return it != end;
    }
    TType& getNext(){
        TType* temp = (TType*)&(*it);
        it++;
        return *temp;
    }
    
};
