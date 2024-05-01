/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** sub
*/

#include "../../include/corewar.h"

void exec_sub(champion_t *champion)
{
    champion->registers[champion->instructions->parameters[2]] =
    champion->registers[champion->instructions->parameters[0]] -
    champion->registers[champion->instructions->parameters[1]];
}
