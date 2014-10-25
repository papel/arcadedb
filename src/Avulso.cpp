#include <stdio.h>
#include <string.h>

namespace Avulso {
    
    void strcop(char* dest, const char* orig, int size){
        int i = 0;
        do {
            dest[i] = orig[i];
            i++;
        } while (i < size && orig[i-1] != 0);
        dest[size-1] = 0;
    }
    
    void goto_after(FILE* arq, const char* str){
        int x = 0;
        int len = strlen(str);
        while (x < len && !feof(arq)){
            char ch = fgetc(arq);
            if (ch == str[x]){
                x++;
            }
            else {
                x = 0;
            }
        }
    }
    
}
