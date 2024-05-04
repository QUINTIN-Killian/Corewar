/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** add
*/

#include "../include/corewar.h"

void exec_add(champion_t *champion)
{
    champion->registers[champion->instructions->parameters[2]] =
    champion->registers[champion->instructions->parameters[0]] +
    champion->registers[champion->instructions->parameters[1]];
    if (champion->registers[champion->instructions->parameters[2]] == 0)
        champion->carry = 0;
    else
        champion->carry = 1;
    move_instruction_head(champion);
}

static int check_empty(int len, char *pair, char *coding_byte)
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

static int register_checker(champion_t *champion)
{
    if (champion->registers[champion->instructions->parameters[0]] < 1 ||
    champion->registers[champion->instructions->parameters[0]] > 16 ||
    champion->registers[champion->instructions->parameters[1]] < 1 ||
    champion->registers[champion->instructions->parameters[1]] > 16 ||
    champion->registers[champion->instructions->parameters[2]] < 1 ||
    champion->registers[champion->instructions->parameters[2]] > 16)
        return 1;
    return 0;
}

int check_add_sub(char *coding_byte, champion_t *champion)
{
    int len = my_strlen(coding_byte);
    char pair[3];

    if (len < 8 || len % 2 != 0)
        return 1;
    for (int i = 0; i < 6; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "01") != 0)
            return 1;
    }
    if (check_empty(len, pair, coding_byte) == 1)
        return 1;
    if (register_checker(champion) == 1)
        return 1;
    return 0;
}
