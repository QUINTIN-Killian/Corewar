/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** memory
*/

#include "../include/corewar.h"

void create_memory(corewar_t *corewar)
{
    corewar->memory = malloc(sizeof(cell_t *) * (MEM_SIZE / 32 + 1));
    for (int i = 0; i < MEM_SIZE / 32; i++) {
        corewar->memory[i] = malloc(sizeof(cell_t) * (32 + 1));
        for (int j = 0; j < 32; j++) {
            corewar->memory[i][j].id_owner = -1;
            corewar->memory[i][j].value_int = 0;
            corewar->memory[i][j].value = my_strdup("00");
        }
        corewar->memory[i][32].value = NULL;
    }
    corewar->memory[MEM_SIZE / 32] = NULL;
}

static int print_color(int color, cell_t *cell)
{
    if (color == 0) {
        mini_printf("\e[31m");
        mini_printf("%s ", cell->value);
        return mini_printf("\e[0m");
    }
    if (color == 1) {
        mini_printf("\e[32m");
        mini_printf("%s ", cell->value);
        return mini_printf("\e[0m");
    }
    if (color == 2) {
        mini_printf("\e[33m");
        mini_printf("%s ", cell->value);
        return mini_printf("\e[0m");
    }
    if (color == 3) {
        mini_printf("\e[34m");
        mini_printf("%s ", cell->value);
        return mini_printf("\e[0m");
    }
}

static int print_memory_aux(int *ids, cell_t *cell)
{
    if (ids == NULL)
        return mini_printf("%s ", cell->value);
    for (int i = 0; ids[i] != -1; i++)
        if (cell->id_owner == ids[i])
            return print_color(i, cell);
    return mini_printf("%s ", cell->value);
}

void print_memory(corewar_t *corewar)
{
    int *ids = get_tab_ids_champions(&corewar->champions);

    for (int i = 0; corewar->memory[i] != NULL; i++) {
        for (int j = 0; corewar->memory[i][j].value != NULL; j++) {
            print_memory_aux(ids, &(corewar->memory[i][j]));
        }
        mini_printf("\n");
    }
}

void destroy_memory(corewar_t *corewar)
{
    if (corewar->memory == NULL)
        return;
    for (int i = 0; corewar->memory[i] != NULL; i++) {
        for (int j = 0; corewar->memory[i][j].value != NULL; j++)
            free(corewar->memory[i][j].value);
        free(corewar->memory[i]);
    }
    free(corewar->memory);
}
