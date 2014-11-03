/*
 * This is used for reducing the size of gamedata.xml by removing fruit machines and clones.
 */

#include <string.h>
#include <stdio.h>
#include <unordered_set>

#include "pugixml.hpp"
using namespace pugi;

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


void gotostr(FILE* arq, const char* str){
    int x = 0;
    while (x < strlen(str) && !feof(arq)){
        char ch = fgetc(arq);
        if (ch == str[x]){
            x++;
        }
        else {
            x = 0;
        }
    }
}

int main(int argc, char* argv[]){
    if (argc != 5){
        fprintf(stderr, "Invalid input files. The correct arguments are:\n");
        fprintf(stderr, " %s (t/f) Catlist input.xml output.xml\n", argv[0]);
        return -1;
    }
    bool includelist = argv[1][0] == 't';
    
    std::unordered_set<Name, Hash, Comp> list;
    
    FILE* cat = fopen(argv[2], "r");
    if (!includelist){
        gotostr(cat, "[Fruit Machines]");
        gotostr(cat, "\n");
    }
    while (!feof(cat)){
        Name str;
        char ch = 0;
        for (int i=0; i<20; i++){
            ch = fgetc(cat);
            if (feof(cat) || ch == '\n'|| ch == '\r' || ch == '\t' || ch == ' '){
                str.romname[i] = 0;
                break;
            }
            str.romname[i] = ch;
        }
        if (ch != '\n'){
            gotostr(cat, "\n");
        }
        if (str.romname[0] == 0) break;
        
        list.insert(str);
    }
    fclose(cat);
    
    
    xml_document doc;
    xml_parse_result loadOkay = doc.load_file(argv[3]);
    if (!loadOkay){
        fprintf(stderr, "Failed to load file: %s\n", loadOkay.description());
        return -1;
    }
    
    xml_node pParent = doc.document_element();
    if (!pParent){
        fprintf(stderr, "Error in the Mame XML file.");
        return -1;
    }
    
    for (xml_node pChild = pParent.first_child(); pChild; ){
        bool ignore_game = false;
        
        for ( xml_attribute pAttrib = pChild.first_attribute(); pAttrib; pAttrib = pAttrib.next_attribute() ){
            //<game name="005" sourcefile="segag80r.c" sampleof="005" isbios="yes" cloneof="" romof="">
            const char* attr = pAttrib.name();
            const char* val = pAttrib.value();
            
            int nume = attr[0] + 26*attr[1];
            switch (nume){
                case 'n'+26*'a':
                    if (strcmp(attr, "name") == 0) {
                        Name name;
                        for (int i=0; i<20; i++){
                            name.romname[i] = val[i];
                            if (val[i] == 0 ){
                                break;
                            }
                        }
                        std::unordered_set<Name, Hash, Comp>::iterator it = list.find(name);
                        if ( includelist == (it == list.end()) ){
                            ignore_game = true;
                        }
                    }
                    break;
                case 'i'+26*'s':
                    if (strcmp(attr, "isbios") == 0) {
                        if (strcmp(val, "yes") == 0) {
                            //ignore_game = true;
                        }
                    }
                    else if (strcmp(attr, "ismechanical") == 0) {
                        if (strcmp(val, "yes") == 0) {
                            ignore_game = true;
                        }
                    }
                    else if (strcmp(attr, "isdevice") == 0) {
                        if (strcmp(val, "yes") == 0) {
                            //ignore_game = true;
                        }
                    }
                    break;
                case 'c'+26*'l':
                    if (strcmp(attr, "cloneof") == 0) {
                        ignore_game = true;
                    }
                    break;
            }
            if (ignore_game) break;
        }
        
        xml_node exclude = pChild;
        pChild = pChild.next_sibling();
        if (ignore_game){
            pParent.remove_child(exclude);
        }
    }
    
    doc.save_file(argv[4]);
}
