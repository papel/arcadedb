#include <stdio.h>


int main(){
    
    FILE* arq = stdin;
    FILE* saida = stdout;
    

    int x = 0;
    const char* str ="filesld6:";
    while (x < 9){
        char ch = fgetc(arq);
        if (ch == str[x]){
            x++;
        }
        else {
            x = 0;
        }
    }

    while(true){
        char ch;
        
        //lengthi
        for (int i=0; i<7; i++){
            ch = fgetc(arq);
            if(i == 0 && ch == 'n'){
                //name4:
                break;
            }
        }
        if (feof(arq))
            break;
        if (ch == 'n')
            break;
        
        char length[20];
        for (int i=0; true; i++){
            ch = fgetc(arq);
            if (ch < '0' || ch > '9' ){
                length[i] = 0;
                break;
            }
            length[i] = ch;
        }
        unsigned int size = 0;
        sscanf(length, "%u",  &size);
        
        int dp = 0;
        while (dp < 2){
            ch = fgetc(arq);
            if (ch == ':') dp ++;
        }
        
        char name[30];
        for (int i=0; true; i++){
            ch = fgetc(arq);
            if (ch == '.' ){
                name[i] = 0;
                break;
            }
            name[i] = ch;
        }
        
        while (true){
            ch = fgetc(arq);
            if (ch == ':') break;
        }
        
        if (feof(arq))
            break;
        
        //fprintf(saida, "%s %u\n", name, size);
        fprintf(saida, "update roms set size = %d where romname = \'%s\';\n", size, name);
    }
    
}
