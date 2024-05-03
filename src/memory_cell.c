/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** get_memory_cell
*/

#include "../include/corewar.h"

cell_t *get_memory_cell(corewar_t *corewar, int coords)
{
    int x;
    int y;

    if (coords < 0 || coords >= MEM_SIZE)
        coords = my_abs(coords % MEM_SIZE);
    y = coords / 32;
    x = coords % 32;
    return &(corewar->memory[y][x]);
}

int set_memory_cell(corewar_t *corewar, int id_owner, int new_cell, int coords)
{
    int x;
    int y;

    if (coords < 0 || coords >= MEM_SIZE)
        coords = my_abs(coords % MEM_SIZE);
    y = coords / 32;
    x = coords % 32;
    free(corewar->memory[y][x].value);
    corewar->memory[y][x].id_owner = id_owner;
    corewar->memory[y][x].value = convert_int_in_hex(new_cell);
    return 1;
}
