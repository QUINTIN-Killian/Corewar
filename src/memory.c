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
