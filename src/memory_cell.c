/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** get_memory_cell
*/

#include "../include/corewar.h"

cell_t *create_tmp_cell(int id_owner, int value_int)
{
    cell_t *cell = malloc(sizeof(cell_t));

    cell->id_owner = id_owner;
    cell->value_int = value_int;
    return cell;
}

int combine_bytes(int nb_bytes, ...)
{
    int res = 0;
    va_list args;

    if (nb_bytes < 1 || nb_bytes > 4)
        return 0;
    va_start(args, nb_bytes);
    for (int i = 0; i < nb_bytes; i++) {
        res += va_arg(args, int);
        res = res << (8 * (nb_bytes - 1 - i));
    }
    va_end(args);
    return cycle_nb(res);
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

int set_memory_cell(corewar_t *corewar, cell_t *new_cell, int coords,
    int nb_bytes)
{
    int x;
    int y;
    unsigned char *nb = (unsigned char *)&(new_cell->value_int);

    for (int i = nb_bytes - 1; i >= 0; i--) {
        coords = cycle_coords(coords);
        y = coords / 32;
        x = coords % 32;
        free(corewar->memory[y][x].value);
        corewar->memory[y][x].id_owner = new_cell->id_owner;
        corewar->memory[y][x].value_int = nb[i];
        corewar->memory[y][x].value = convert_int_in_hex(nb[i]);
        coords++;
    }
    free(new_cell);
    return 1;
}
