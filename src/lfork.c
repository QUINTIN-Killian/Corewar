/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** lfork
*/

#include "../include/corewar.h"

void exec_lfork(corewar_t *corewar, champion_t *champion)
{
    int value = combine_bytes(2,
    get_memory_cell(corewar, champion->PC + 1)->value_int,
    get_memory_cell(corewar, champion->PC + 2)->value_int);
    champion_t *new_champion =
    duplicate_champion(&corewar->champions, champion);

    new_champion->PC = cycle_coords(champion->PC + value);
    champion->PC += 3;
}
