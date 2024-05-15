/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** aff
*/

#include "../include/corewar.h"

void exec_aff(corewar_t *corewar, champion_t *champion)
{
    mini_printf("%c\n", champion->registers[get_memory_cell(corewar,
    champion->PC + 2)->value_int] % 256);
    champion->PC = cycle_coords(champion->PC + 3);
    champion->timeout = 2;
}
