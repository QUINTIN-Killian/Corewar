/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** aff
*/

#include "../include/corewar.h"

void exec_aff(corewar_t *corewar, champion_t *champion)
{
    mini_printf("%c\n", champion->registers[get_memory_cell(corewar,
    champion->PC + 1)->value_int]);
    champion->PC += 2;
    champion->timeout = 2;
}

int check_aff(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    int len = my_strlen(coding_byte);
    char pair[3];
    int adresse = champion->PC + 2;
    cell_t *cell;

    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (my_strcmp(pair, "01") != 0)
        return 1;
    cell = get_memory_cell(corewar, adresse);
    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    if (check_empty(len, coding_byte, pair, 2) == 1)
        return 1;
    return 0;
}
