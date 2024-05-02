/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** xor
*/

#include "../include/corewar.h"

void exec_xor(champion_t *champion)
{
    int value1 = 0;
    int value2 = 0;

    if (my_strncmp(champion->instructions->coding_byte, "01", 2) == 0)
        value1 = champion->registers[champion->instructions->parameters[0]];
    else
        value1 = champion->instructions->parameters[0];
    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0)
        value2 = champion->registers[champion->instructions->parameters[1]];
    else
        value2 = champion->instructions->parameters[1];
    champion->registers[champion->instructions->parameters[2]] =
    value1 ^ value2;
}
