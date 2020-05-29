#pragma once

#include <stddef.h>
#include <stdio.h>

namespace Avulso {
    template<typename TType, typename KType>
    static int binary_search(TType* array, int size, KType key, int (*tComparator)(KType, KType), KType (*tGetkey)(TType*) ){
        int imin = 0;
        int imax = size - 1;
        while (imax >= imin){
            int imid = (imin + imax)/2;
            int comp = tComparator( tGetkey( &array[imid] ), key);
            if( comp == 0)
                return imid;
            else if (comp < 0)
                imin = imid + 1;
            else
                imax = imid - 1;
        }
        return -1;
    }
    
    //String
    void strcop(char* dest, const char* orig, size_t size);
    bool str_starts(const char *str, const char *pre);
    
    //File
    void goto_after(FILE* arq, const char* str);
    void read_until(FILE* arq, char* dest, size_t size, char stop);

}
