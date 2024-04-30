/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** add
*/

#include "../../include/corewar.h"

void exec_add(champion_t *champion)
{
    int value1 = convert_str_in_int(champion->registers[
    convert_str_in_int(champion->instructions->parameters[0])]);
    int value2 = convert_str_in_int(champion->registers[
    convert_str_in_int(champion->instructions->parameters[1])]);
    int ind_reg = convert_str_in_int(champion->instructions->parameters[2]);

    free(champion->registers[ind_reg]);
    champion->registers[ind_reg] = convert_int_to_str(value1 + value2);
}
