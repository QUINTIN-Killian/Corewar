/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** zjmp
*/

#include "../include/corewar.h"

void exec_zjmp(corewar_t *corewar, champion_t *champion)
{
    int value = combine_bytes(2,
    get_memory_cell(corewar, champion->PC + 1)->value_int,
    get_memory_cell(corewar, champion->PC + 2)->value_int);

    champion->timeout = 20;
    if (!champion->carry || value == 0) {
        champion->PC += 3;
        return;
    }
    if (value <= 0xffff / 2)
        champion->PC += value % IDX_MOD;
    else
        champion->PC -= value % IDX_MOD;
    champion->PC = cycle_coords(champion->PC);
}
