#include <stdio.h>
#include <string.h>

namespace Avulso {
    
    void strcop(char* dest, const char* orig, size_t size){
        int i = 0;
        do {
            dest[i] = orig[i];
            i++;
        } while (i < size && orig[i-1] != 0);
        dest[size-1] = 0;
    }
    bool str_starts(const char *str, const char *pre){
        return strncmp(pre, str, strlen(pre)) == 0;
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
    
    void read_until(FILE* arq, char* dest, size_t size, char stop){
        size--;
        for (int i=0; i<size; ){
            char ch = fgetc(arq);
            if (feof(arq) || ch == stop){
                dest[i] = 0;
                return;
            }
            if (ch == '\r'){
                continue;
            }
            dest[i] = ch;
            i++;
        }
        dest[size] = 0;
    }
    
}
