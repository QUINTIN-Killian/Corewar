/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** print_memory
*/

#include "../include/corewar.h"

static int get_color(int *ids, int id_owner)
{
    for (int i = 0; ids[i] != -1; i++)
        if (ids[i] == id_owner)
            return i;
    return -1;
}

static void print_color(int color, char *value)
{
    if (color == 0)
        mini_printf("\e[31m");
    if (color == 1)
        mini_printf("\e[32m");
    if (color == 2)
        mini_printf("\e[33m");
    if (color == 3)
        mini_printf("\e[34m");
    mini_printf("%s ", value);
    if (color != -1)
        mini_printf("\e[0m");
}

static void get_champions_ids_aux(corewar_t *corewar, int i, int j, int **ids)
{
    if (corewar->memory[i][j].id_owner != -1 &&
    !is_nb_already_in_tab(*ids, corewar->memory[i][j].id_owner)) {
        *ids = realloc_int_plus_one(*ids);
        (*ids)[0] = corewar->memory[i][j].id_owner;
    }
}

int *get_champions_ids(corewar_t *corewar)
{
    int *ids = malloc(sizeof(int));

    ids[0] = -1;
    for (int i = 0; corewar->memory[i] != NULL; i++) {
        for (int j = 0; corewar->memory[i][j].value != NULL; j++) {
            get_champions_ids_aux(corewar, i, j, &ids);
        }
    }
    return ids;
}

void print_memory(corewar_t *corewar)
{
    int *ids = get_champions_ids(corewar);

    for (int i = 0; corewar->memory[i] != NULL; i++) {
        for (int j = 0; corewar->memory[i][j].value != NULL; j++) {
            print_color(get_color(ids, corewar->memory[i][j].id_owner),
            corewar->memory[i][j].value);
        }
        mini_printf("\n");
    }
    free(ids);
}
