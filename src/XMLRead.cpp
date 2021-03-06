#include "GameList.hpp"
#include "MachineList.hpp"
#include "Exception.hpp"

#include <string.h>
#include <stdio.h>

#include "pugixml.hpp"
using namespace pugi;


void read_mame_xml(const char* pFilename, GameList* games, MachineList* machines){
    
    xml_document doc;
    xml_parse_result loadOkay = doc.load_file(pFilename);
    if (!loadOkay){
        //throw Exception("Failed to load file: %s\n", loadOkay.description());
        throw Exception(loadOkay.description());
    }
    
    xml_node pParent = doc.document_element();
    if (!pParent){
        throw Exception("Error in the Mame XML file.");
    }
    
    for (xml_node pChild = pParent.first_child(); pChild; pChild = pChild.next_sibling()){
        //Each <game>
        char machine_source[40];
        char rom_romname[20];
        char rom_cloneof[20];
        char rom_sampleof[20];
        char rom_gamename[100];
        char rom_manufacturer[100];
        char rom_chd[20];
        short rom_year = 0;
        uint64_t rom_size = 0;
        bool status = false; //good|imperfect|preliminary
        
        rom_cloneof[0] = 0;
        rom_sampleof[0] = 0;
        machine_source[0] = 0;
        rom_chd[0] = 0;
        
        bool isbios = false;
        bool ignore_game = false;
        
        for ( xml_attribute pAttrib = pChild.first_attribute(); pAttrib; pAttrib = pAttrib.next_attribute() ){
            //<game name="005" sourcefile="segag80r.c" sampleof="005" isbios="yes" cloneof="" romof="">
            const char* attr = pAttrib.name();
            const char* val = pAttrib.value();
            
            int nume = attr[0] + 26*attr[1];
            switch (nume){
                case 'n'+26*'a':
                    if (strcmp(attr, "name") == 0) {
                        Avulso::strcop(rom_romname, val, 20);
                    }
                    break;
                case 's'+26*'o':
                    if (strcmp(attr, "sourcefile") == 0) {
                        Avulso::strcop(machine_source, val, 40);
                        int siz = strlen(machine_source);
                        if (machine_source[siz-2] == '.' && machine_source[siz-1] == 'c' ){
                            machine_source[siz-2] = 0;
                        }
                        else if (machine_source[siz-4] == '.' && machine_source[siz-3] == 'c' && machine_source[siz-2] == 'p' ){
                            machine_source[siz-4] = 0;
                        }
                    }
                    break;
                case 'i'+26*'s':
                    if (strcmp(attr, "isbios") == 0) {
                        if (strcmp(val, "yes") == 0) {
                            isbios = true;
                        }
                    }
                    else if (strcmp(attr, "ismechanical") == 0) {
                        if (strcmp(val, "yes") == 0) {
                            ignore_game = true;
                        }
                    }
                    else if (strcmp(attr, "isdevice") == 0) {
                        if (strcmp(val, "yes") == 0) {
                            ignore_game = true;
                        }
                    }
                    break;
                case 'c'+26*'l':
                    if (strcmp(attr, "cloneof") == 0) {
                        Avulso::strcop(rom_cloneof, val, 20);
                    }
                    break;
                case 'r'+26*'o':
                    if (strcmp(attr, "romof") == 0) {
                        //Show the parent or the bios
                    }
                    break;
                case 's'+26*'a':
                    if (strcmp(attr, "sampleof") == 0) {
                        Avulso::strcop(rom_sampleof, val, 20);
                    }
                    break;
            }
        }
        
        if (ignore_game) continue;
        
        
        for (xml_node pdata = pChild.first_child(); pdata; pdata = pdata.next_sibling()){
            //<description>005</description><year>1981</year><manufacturer>Sega</manufacturer><driver status="imperfect" emulation="good" color="good" sound="imperfect" graphic="good" savestate="unsupported"/>
            
            const char* elem = pdata.name();
            
            int nume = elem[0] + 26*elem[1];
            switch (nume){
                case 'd'+26*'e':
                    if (strcmp(elem, "description") == 0) {
                        const char* val = pdata.child_value();
                        Avulso::strcop(rom_gamename, val, 100);
                    }
                    break;
                case 'y'+26*'e':
                    if (strcmp(elem, "year") == 0) {
                        const char* val = pdata.child_value();
                        int temp = 0;
                        sscanf(val, "%d", &temp );
                        rom_year = (short)temp;
                    }
                    break;
                case 'm'+26*'a':
                    if (strcmp(elem, "manufacturer") == 0) {
                        const char* val = pdata.child_value();
                        Avulso::strcop(rom_manufacturer, val, 100);
                    }
                    break;
                case 'd'+26*'r':
                    if (strcmp(elem, "driver") == 0) {
                        for ( xml_attribute pAttrib = pdata.first_attribute(); pAttrib; pAttrib = pAttrib.next_attribute() ){
                            const char* attr = pAttrib.name();
                            const char* val = pAttrib.value();
                            if (strcmp(attr, "emulation") == 0 && strcmp(val, "good") == 0){
                                status = true;
                                break;
                            }
                        }
                    }
                    break;
                case 'd'+26*'i':
                    if (strcmp(elem, "disk") == 0) {
                        const char* val = pdata.child_value();
                        Avulso::strcop(rom_chd, val, 20);
                    }
                    break;
                case 's'+26*'a':
                    if (strcmp(elem, "sample") == 0) {
                        //A sample file
                    }
                    break;
                case 'r'+26*'o':
                    if (strcmp(elem, "rom") == 0) {
                        //A rom file
                        for ( xml_attribute pAttrib = pdata.first_attribute(); pAttrib; pAttrib = pAttrib.next_attribute() ){
                            const char* attr = pAttrib.name();
                            const char* val = pAttrib.value();
                            
                            if (strcmp(attr, "size") == 0){
                                uint64_t tsize = 0;
                                sscanf(val, "%llu", &tsize );
                                rom_size += tsize;
                            }
                        }
                        
                    }
                    break;
                case 's'+26*'o':
                    if (strcmp(elem, "softwarelist") == 0) {
                        //Mess stuff
                        ignore_game = true;
                    }
                    break;
            }
            if (ignore_game){
                break;
            }
        }
        if (ignore_game){
            continue;
        }
        
        Game* game;
        if (isbios){
            game = new Game;
            game->set_romname(rom_romname);
        }
        else {
            game = games->new_game(rom_romname);
        }
        
        if (rom_cloneof[0] != 0)
            game->set_parent(rom_cloneof);
        if (rom_sampleof[0] != 0)
            game->set_sample_parent(rom_sampleof);
        if (rom_chd[0] != 0)
            game->set_chd(rom_chd);
        
        game->set_name(rom_gamename);
        game->set_year(rom_year);
        game->set_manufacturer(rom_manufacturer);
        game->works(status);
        game->set_size(rom_size);

        
        Machine* machine = machines->new_machine(machine_source);
        game->set_board(machine);
        
        if (isbios){
            if (game->get_parent() == nullptr) {
                if (machine->get_bios() == nullptr){
                    machine->set_bios( (Bios*)game );
                }
                else {
                    delete game;
                }
            }
            else {
                delete game;
            }
        }
        else {
            machine->add_game(game);
        }
        
    }
}

void read_fba_xml(const char* input, GameList* games){
    
    xml_document doc;
    xml_parse_result loadOkay = doc.load_file(input);
    if (!loadOkay){
        //throw Exception("Failed to load file: %s\n", loadOkay.description());
        throw Exception(loadOkay.description());
    }
    
    xml_node pParent = doc.document_element();
    if (!pParent){
        throw Exception("Error in the FBA XML file.");
    }
    
    for (xml_node pChild = pParent.first_child().next_sibling(); pChild; pChild = pChild.next_sibling()){
        //Each <game>
        for ( xml_attribute pAttrib = pChild.first_attribute(); pAttrib; pAttrib = pAttrib.next_attribute() ){
            const char* attr = pAttrib.name();
            const char* val = pAttrib.value();
            
            if (strcmp(attr, "name") == 0) {
                Game* game = games->get_game(val);
                if (game != nullptr){
                    game->fba(true);
                }
                break;
            }
        }
    }
    
}
