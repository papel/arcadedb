#include <stdio.h>
#include <string.h>
#include <unordered_set>


struct Name{
    char romname[20];
};
struct Comp{
    bool operator()(const Name& s1, const Name& s2) const{
        return strcmp(s1.romname, s2.romname) == 0;
    }
};
struct Hash{
    size_t operator()(const Name& m) const{
        const char* str = m.romname;
        size_t mul = 1;
        size_t res = 0;
        for (int i=0; str[i] != 0; i++){
            res += (str[i]-50)*mul;
            mul *= 50;
        }
        return res;
    }
};

int main(int argc, char* argv[]){
    
    //torrent list
    //torrent resume
    //selected ones
    
    FILE* tlist = fopen(argv[1], "r");
    FILE* tresume = fopen(argv[2], "r+");
    FILE* tselect = fopen(argv[3], "r");
    
    if (tlist == NULL || tresume == NULL || tselect == NULL){
        printf("Erro abrir arquivo\n");
        return -1;
    }
    
    //Tabela de escolhidos
    std::unordered_set<Name, Hash, Comp> table;
    while (!feof(tselect)){
        Name str;
        for (int i=0; i<20; i++){
            char ch = fgetc(tselect);
            if (feof(tselect) || ch == '\n'){
                str.romname[i] = 0;
                break;
            }
            str.romname[i] = ch;
        }
        if (feof(tselect) || str.romname[0] == 0) break;
        
        table.insert(str);
        
    }
    
    //ir até arquivo "dndl"
    int x = 0;
    const char* str = "dndl";
    while (x < 4){
        char ch = fgetc(tresume);
        if (ch == str[x]){
            x++;
        }
        else {
            x = 0;
        }
    }
    
    unsigned long long tsize = 0;
    
    while(true){
        char ch;
        
        //lengthi
        for (int i=0; i<7; i++){
            fgetc(tlist);
        }
        if (feof(tlist))
            break;
        
        char length[20];
        for (int i=0; true; i++){
            ch = fgetc(tlist);
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
            ch = fgetc(tlist);
            if (ch == ':') dp ++;
        }
        
        Name name;
        for (int i=0; i<20; i++){
            ch = fgetc(tlist);
            if (ch == '.' ){
                name.romname[i] = 0;
                break;
            }
            name.romname[i] = ch;
        }
        
        while (true){
            ch = fgetc(tlist);
            if (ch == ':') break;
        }
        
        if (feof(tlist))
            break;
        
        std::unordered_set<Name>::iterator it = table.find(name);
        unsigned char ma = '0';
        if (it != table.end()){
            ma = '1';
            tsize += size;
        }
        fgetc(tresume);//i
        fputc(ma, tresume);//0-1
        fgetc(tresume);//e
    }
    printf("%u%u\n", (unsigned int)(tsize/1000), (unsigned int)(tsize%1000));
    
    fclose(tlist);
    fclose(tresume);
    fclose(tselect);
    
}