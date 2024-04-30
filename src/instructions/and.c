/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** and
*/

#include "../../include/corewar.h"

void exec_and(champion_t *champion)
{
    int ind_reg = convert_str_in_int(champion->instructions->parameters[2]);

    free(champion->registers[ind_reg]);
    champion->registers[ind_reg] = convert_int_to_str(convert_str_in_int(
    champion->instructions->parameters[0]) &
    convert_str_in_int(champion->instructions->parameters[1]));
}
