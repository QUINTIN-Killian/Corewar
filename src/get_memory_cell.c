/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** get_memory_cell
*/
#include "include/corewar.h"

cell_t get_memory_cell(corewar_t *corewar, int coords)
{
    int x;
    int y;

    if (coords < 0 || coords >= MEM_SIZE)
        return;
    y = coords / 32;
    x = coords % 32;
    return corewar->memory[x][y];
}