/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** add
*/

#include "../include/corewar.h"

void exec_add(champion_t *champion)
{
    champion->registers[champion->instructions->parameters[2]] =
    champion->registers[champion->instructions->parameters[0]] +
    champion->registers[champion->instructions->parameters[1]];
}
