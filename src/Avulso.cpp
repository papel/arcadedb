
namespace Avulso {
    
    void strcop(char* dest, const char* orig, int size){
        int i = 0;
        do {
            dest[i] = orig[i];
            i++;
        } while (i < size && orig[i-1] != 0);
        dest[size-1] = 0;
    }
    
}
