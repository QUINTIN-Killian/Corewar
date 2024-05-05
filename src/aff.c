/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** aff
*/

#include "../include/corewar.h"

void exec_aff(champion_t *champion)
{
    mini_printf("%c\n", champion->registers[
    champion->instructions->parameters[0]]);
    move_instruction_head(champion);
}

static int check_end_cb(int len, char *pair, char *coding_byte)
{
    for (int i = 2; i < len; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "00") != 0)
            return 1;
    }
    return 0;
}

int check_aff(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    int len = my_strlen(coding_byte);
    char pair[3];
    int adresse = champion->PC + 1;
    cell_t *cell;

    if (len < 8 || len % 2 != 0)
        return 1;
    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (my_strcmp(pair, "01") != 0)
        return 1;
    cell = get_memory_cell(corewar, adresse);
    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    if (check_end_cb(len, pair, coding_byte) == 1)
        return 1;
    return 0;
}
