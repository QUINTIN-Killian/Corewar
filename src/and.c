/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** and
*/

#include "../include/corewar.h"

void exec_and(champion_t *champion)
{
    int value1 = 0;
    int value2 = 0;

    if (my_strncmp(champion->instructions->coding_byte, "01", 2) == 0)
        value1 = champion->registers[champion->instructions->parameters[0]];
    else
        value1 = champion->instructions->parameters[0];
    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0)
        value2 = champion->registers[champion->instructions->parameters[1]];
    else
        value2 = champion->instructions->parameters[1];
    champion->registers[champion->instructions->parameters[2]] =
    value1 & value2;
    if (champion->registers[champion->instructions->parameters[2]] == 0)
        champion->carry = 0;
    else
        champion->carry = 1;
    move_instruction_head(champion);
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

static int set_adresse(char *pair, champion_t *champion)
{
    if (my_strcmp(pair, "10") == 0) {
        return 4;
    }
    if (my_strcmp(pair, "01") == 0) {
        return 1;
    }
    return 2;
}

static int check_register(int coords, corewar_t *corewar)
{
    cell_t *cell = get_memory_cell(corewar, coords);

    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    return 0;
}

int check_and(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    int adresse = champion->PC + 1;

    for (int i = 0; i < 4; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "10") != 0 && my_strcmp(pair, "11")
        != 0 && my_strcmp(pair, "01") != 0)
            return 1;
        adresse += set_adresse(pair, champion);
    }
    pair[0] = coding_byte[4];
    pair[1] = coding_byte[5];
    pair[2] = '\0';
    if (check_register(adresse + 1, corewar) == 1)
        return 1;
    return check_empty(my_strlen(coding_byte), coding_byte, pair);
}
