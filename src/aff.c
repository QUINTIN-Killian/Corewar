/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** aff
*/

#include "../include/corewar.h"

void exec_aff(champion_t *champion)
{
    mini_printf("%c\n", champion->registers[
    champion->instructions->parameters[0]]);
}
