#include "GameList.hpp"
#include "MachineList.hpp"

#include <stdio.h>
#include <string.h>

void read_lists1(const char* input, GameList* games, int md){
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
                    games->set_genre(romname, rdata);
                    games->set_mature(romname, ver == 1);
                }
                break;
              case 2:
                games->set_version(romname, ver);
                break;
            }
            
        }
        
    }
    
}


void read_lists2(const char* input, GameList* games, int md){
    FILE* arq = fopen(input, "r");
    int nl = 0;
    while (nl < 6 && !feof(arq)){
        char ch = fgetc(arq);
        if (ch == '\n') nl++;
    }
    
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
                i--;
            }
            if (feof(arq) || ch == '\n'){
                info[i] = 0;
                break;
            }
            info[i] = ch;
        }
        
        if (feof(arq))
            break;
        
        
        //fprintf(output, "%s %s\n", name, info);
        //fprintf(output, "update roms set genre = \'%s\' where romname = \'%s\';\n", info, name);
        
        
        if (info[0] != '?'){
            if (strcmp(info, "LaserDisc") == 0 || strcmp(info, "BIOS") == 0
                || strcmp(info, "Pinball") == 0 || strcmp(info, "Device") == 0
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
                    printf("Error: %s %s\n", name, info);
                    break;
                }
                games->set_nplayers(name, nump);
            }
        }
        
        
    }
    
}
