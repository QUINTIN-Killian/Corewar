/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** and
*/

#include "../include/corewar.h"

void exec_add(corewar_t *corewar, champion_t *champion)
{
    champion->registers[get_memory_cell(corewar, champion->PC + 4)->value_int]
    = get_memory_cell(corewar, champion->PC + 2)->value_int +
    get_memory_cell(corewar, champion->PC + 3)->value_int;
    champion->PC += 5;
    champion->timeout = 10;
}

static int check_empty(int len, char *coding_byte, char *pair)
{
    for (int i = 6; i < len; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "00") != 0)
            return 1;
    }
    return 0;
}

int check_add_sub(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    cell_t *cell;

    for (int i = 0; i < 6; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "01") != 0)
            return 1;
        cell = get_memory_cell(corewar, champion->PC + 2 + (i / 2));
        if (cell->value_int < 1 || cell->value_int > 16)
            return 1;
    }
    return check_empty(my_strlen(coding_byte), pair, coding_byte);
}
