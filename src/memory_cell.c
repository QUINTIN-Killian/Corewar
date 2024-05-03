/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** get_memory_cell
*/

#include "../include/corewar.h"

static int cycle_coords(int coords)
{
    if (coords < 0)
        return MEM_SIZE + (coords % MEM_SIZE);
    if (coords >= MEM_SIZE)
        return coords % MEM_SIZE;
    return coords;
}

cell_t *get_memory_cell(corewar_t *corewar, int coords)
{
    int x;
    int y;

    coords = cycle_coords(coords);
    y = coords / 32;
    x = coords % 32;
    return &(corewar->memory[y][x]);
}

int set_memory_cell(corewar_t *corewar, int id_owner, int new_cell, int coords,
    int nb_bytes)
{
    int x;
    int y;
    unsigned char *nb = (unsigned char *)&new_cell;

    for (int i = nb_bytes - 1; i >= 0; i--) {
        coords = cycle_coords(coords);
        y = coords / 32;
        x = coords % 32;
        free(corewar->memory[y][x].value);
        corewar->memory[y][x].id_owner = id_owner;
        corewar->memory[y][x].value = convert_int_in_hex(nb[i]);
        coords++;
    }
    return 1;
}
