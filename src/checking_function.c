/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** checking_function
*/
#include "../include/corewar.h"

int set_adresse(char *pair, champion_t *champion)
{
    if (my_strcmp(pair, "10") == 0) {
        return champion->PC + 5;
    }
    if (my_strcmp(pair, "01") == 0) {
        return champion->PC + 2;
    }
    return champion->PC + 3;
}

int check_empty(int len, char *coding_byte, char *pair, int start)
{
    for (int i = start; i < len; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "00") != 0)
            return 1;
    }
    return 0;
}

int check_register(int coords, corewar_t *corewar)
{
    cell_t *cell = get_memory_cell(corewar, coords);

    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    return 0;
}