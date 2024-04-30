/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** and
*/

#include "../../include/corewar.h"

void exec_and(champion_t *champion)
{
    int value1 = 0;
    int value2 = 0;
    int ind_reg = convert_str_in_int(champion->instructions->parameters[2]);

    if (my_strncmp(champion->instructions->coding_byte, "01", 2) == 0)
        value1 = champion->registers[convert_str_in_int(
        champion->instructions->parameters[0])];
    else
        value1 = convert_str_in_int(champion->instructions->parameters[0]);
    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0)
        value2 = champion->registers[convert_str_in_int(
        champion->instructions->parameters[1])];
    else
        value2 = convert_str_in_int(champion->instructions->parameters[1]);
    free(champion->registers[ind_reg]);
    champion->registers[ind_reg] = convert_int_to_str(value1 & value2);
}
