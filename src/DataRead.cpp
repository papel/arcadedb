#include "GameList.hpp"
#include "MachineList.hpp"
#include "Exception.hpp"
#include "Avulso.hpp"

#include <stdio.h>
#include <string.h>

void read_genre(const char* input, GameList* games){
    FILE* arq = fopen(input, "r");
    if (arq == nullptr){
        throw Exception("Failed to open file");
    }
    
    int nl = 0;
    while (nl < 6 && !feof(arq)){
        char ch = fgetc(arq);
        if (ch == '\n') nl++;
    }
    
    //Each genre
    while(true){
        char cha = fgetc(arq);
        if (feof(arq) || cha != '[')
            break;
        
        char info[100];
        for (int i=0; i<100; i++){
            char ch = fgetc(arq);
            if (feof(arq) || ch == ']'){
                info[i] = 0;
                break;
            }
            info[i] = ch;
        }
        
        do {
            char ch = fgetc(arq);
            if (ch == '\n') break;
        } while (!feof(arq));
        
        char rdata[100];
        bool mature = false;

        strcpy(rdata, info);
        for (int i=0; rdata[i] != 0; i++){
            if (rdata[i] == '*'){
                mature = true;
                rdata[i-1] = 0;
                break;
            }
        }
        if (Avulso::str_starts(rdata, "Arcade: ")){
            char* dest = rdata;
            char* src = dest + strlen("Arcade: ");
            do {
                *dest = *src;
                src++; dest++;
            } while (*src != 0);
        }
        else {
            strcpy(rdata, "MESS");
        }
        //Board Game, Tabletop
        if (Avulso::str_starts(rdata, "Electromechanical") || Avulso::str_starts(rdata, "Utilities") || Avulso::str_starts(rdata, "System")){
            strcpy(rdata, "MESS");
        }
        
        if (strcmp(rdata, "Fighter / 2.5D") == 0){
            strcpy(rdata, "Beat em up");
        }

        
        
        //Each game
        while (true){
            char romname[30];
            for (int i=0; i<30; i++){
                char ch = fgetc(arq);
                if (ch == '\r'){
                    i--;
                }
                else if(feof(arq) || ch == '\n'){
                    romname[i] = 0;
                    break;
                }
                else {
                    romname[i] = ch;
                }
            }
            if (romname[0] == 0) //empty line
                break;
            
            
            if (strlen(rdata) > 0){
                Game* game = games->get_game(romname);
                if (game != nullptr){
                    game->set_genre(rdata);
                    game->ismature(mature);
                }
            }
            
        }
        
    }
    fclose(arq);
}


void read_numplayers(const char* input, GameList* games){
    FILE* arq = fopen(input, "r");
    if (arq == nullptr){
        throw Exception("Failed to open file");
    }
    
    Avulso::goto_after(arq, "[NPlayers]");
    Avulso::goto_after(arq, "\n");
    
    while(true){
        char name[30];
        char info[100];

        Avulso::read_until(arq, name, 30, '=');
        Avulso::read_until(arq, info, 100, '\n');
        
        if (feof(arq))
            break;
        
        if (info[0] >= '0' && info[0] <= '9'){
            int nump = info[0] - '0';
            if (nump == 1 || info[3] == 's'){
            }
            else if (info[3] == 'a'){
                nump = -nump;
            }
            else {
                //throw Exception("Error: %s %s\n", name, info);
                throw Exception("Error in numplayers.");
            }
            Game* game = games->get_game(name);
            if (game != nullptr){
                game->set_nplayers(nump);
            }
        }
        
    }
    fclose(arq);
}

