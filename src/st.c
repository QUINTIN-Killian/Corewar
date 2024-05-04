/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** st
*/
#include "../include/corewar.h"

void exec_st(champion_t *champion, corewar_t *corewar)
{
    int value1 = champion->registers[champion->instructions->parameters[0]];
    int value2 = 0;
    int adress = 0;

    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0) {
        value2 = value1;
        champion->registers[champion->instructions->parameters[1]] = value2;
    } else {
        value2 = champion->instructions->parameters[1];
        adress = champion->PC + value2 % IDX_MOD;
        set_memory_cell(corewar, create_tmp_cell(champion->id, value1),
        adress, 4);
    }
    move_instruction_head(champion);
}

static int check_empty(int len, char *pair, char *coding_byte)
{
    for (int i = 4; i < len; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "00") != 0) {
            return 1;
        }
    }
    return 0;
}

int check_st(char *coding_byte, champion_t *champion)
{
    int len = my_strlen(coding_byte);
    char pair[3];

    if (len % 2 != 0)
        return 1;
    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (my_strcmp(pair, "01") != 0)
        return 1;
    if (champion->registers[champion->instructions->parameters[0]] < 1 ||
        champion->registers[champion->instructions->parameters[0]] > 16)
        return 1;
    pair[0] = coding_byte[2];
    pair[1] = coding_byte[3];
    if (my_strcmp(pair, "01") != 0 && my_strcmp(pair, "10") != 0
        && my_strcmp(pair, "11") != 0)
        return 1;
    if (check_empty(len, pair, coding_byte == 1))
        return 1;
    return 0;
}
