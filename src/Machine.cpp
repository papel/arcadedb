#include "Machine.hpp"
#include "Game.hpp"

void Machine::add_game(Game* game){
    short year = game->get_year();
    bool works = game->works();
    if (first_year == 0 || year < first_year) first_year = year;
    if (last_year == 0 || year > last_year) last_year = year;
    if (works) working_games++;
    number_games++;
}
