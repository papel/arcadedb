#pragma once

void read_mame_xml(const char* input, GameList* games, MachineList* machines);
void read_fba_xml(const char* input, GameList* games);

void read_genre(const char* input, GameList* games);
void read_version(const char* input, GameList* games);
void read_numplayers(const char* input, GameList* games);
