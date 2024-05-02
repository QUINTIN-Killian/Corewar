/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** memory
*/

#include "../include/corewar.h"

void create_memory(corewar_t *corewar)
{
    corewar->memory = malloc(sizeof(char **) * (MEM_SIZE / 32 + 1));
    for (int i = 0; i < MEM_SIZE / 32; i++) {
        corewar->memory[i] = malloc(sizeof(char *) * (32 + 1));
        for (int j = 0; j < 32; j++)
            corewar->memory[i][j] = my_strdup("00");
        corewar->memory[i][32] = NULL;
    }
    corewar->memory[MEM_SIZE / 32] = NULL;
}

void print_memory(corewar_t *corewar)
{
    for (int i = 0; corewar->memory[i] != NULL; i++) {
        for (int j = 0; corewar->memory[i][j] != NULL; j++) {
            mini_printf("%s ", corewar->memory[i][j]);
        }
        mini_printf("\n");
    }
}

void destroy_memory(corewar_t *corewar)
{
    if (corewar->memory != NULL) {
        for (int i = 0; corewar->memory[i] != NULL; i++)
            free_word_array(corewar->memory[i]);
        free(corewar->memory);
    }
}

int set_memory_cell(corewar_t *corewar, int new_cell, int coords)
{
    int x;
    int y;

    if (coords < 0 || coords >= MEM_SIZE)
        return 0;
    y = coords / 32;
    x = coords % 32;
    free(corewar->memory[y][x]);
    corewar->memory[y][x] = convert_int_in_hex(new_cell);
    return 1;
}

void place_champions_head(corewar_t *corewar, champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        set_memory_cell(corewar, node->id, node->head);
        node = node->next;
    }
}
