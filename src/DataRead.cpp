#include "GameList.hpp"
#include "MachineList.hpp"
#include "Exception.hpp"

#include <stdio.h>
#include <string.h>

static void read_file(const char* input, GameList* games, int md){
    FILE* arq = fopen(input, "r");
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
        
        char info[50];
        for (int i=0; i<50; i++){
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
        
        char rdata[50];
        int ver = 0;
        switch(md){
          case 1:
            strcpy(rdata, info);
            for (int i=0; rdata[i] != 0; i++){
                if (rdata[i] == '*'){
                    ver = 1;
                    rdata[i-1] = 0;
                    break;
                }
            }
            break;
          case 2:
            {
                ver = ( (info[1]-'0')*100 + (info[2]-'0')*10 + (info[3]-'0')*1)*100;
                if (info[4] != 0){
                    ver += ( (info[5]-'0')*10 + (info[6]-'0')*1)*1;
                }
                sprintf(rdata, "%d", ver);
                if (strcmp(rdata, "Fighter / 2.5D") == 0){
                    strcpy(rdata, "Beat em up");
                }
            }
            break;
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
            
            switch(md){
              case 1:
                if (strlen(rdata) > 0){
                    Game* game = games->get_game(romname);
                    if (game != nullptr){
                        game->set_genre(rdata);
                        game->ismature(ver == 1);
                    }
                }
                break;
              case 2:{
                    Game* game = games->get_game(romname);
                    if (game != nullptr){
                        game->set_version(ver);
                    }
                }
                break;
            }
            
        }
        
    }
    fclose(arq);
}


void read_numplayers(const char* input, GameList* games){
    FILE* arq = fopen(input, "r");
    int nl = 0;
    
    Avulso::goto_after(arq, "[NPlayers]");
    Avulso::goto_after(arq, "\n");
    
    while(true){
        char name[30];
        char info[50];
        
        for (int i=0; true; i++){
            char ch = fgetc(arq);
            if (feof(arq) || ch == '='){
                name[i] = 0;
                break;
            }
            name[i] = ch;
        }
        
        for (int i=0; true; i++){
            char ch = fgetc(arq);
            if (ch == '\r'){
                info[i] = 0;
                Avulso::goto_after(arq, "\n");
                break;
            }
            if (feof(arq) || ch == '\n'){
                info[i] = 0;
                break;
            }
            info[i] = ch;
        }
        
        if (feof(arq))
            break;
        
        
        if (info[0] != '?'){
            if (strncmp(info, "LaserDisc", 9) == 0 || strncmp(info, "BIOS", 4) == 0
                || strncmp(info, "Pinball", 7) == 0 || strncmp(info, "Device", 6) == 0
            ){
                
            }
            else {
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
        
    }
    fclose(arq);
}


void read_genre(const char* input, GameList* games){
    read_file(input, games, 1);
}
void read_version(const char* input, GameList* games){
    read_file(input, games, 2);
}
