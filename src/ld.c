/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ld
*/

#include "../include/corewar.h"

int set_val(int i)
{
    if (i == 0)
        return 24;
    if (i == 1)
        return 12;
    if (i == 2)
        return 8;
    return -1;
}

void exec_ld(champion_t *champion, corewar_t *corewar)
{
    int value1 = 0;
    int adress = 0;
    int new = 0;
    int val = 0;
    cell_t *temp;

    value1 = set_value(champion, 2, 1);
    adress = champion->PC + value1 % IDX_MOD;
    for (int i = 0; i < 4; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp->value);
        val = set_val(i);
        if (val != -1)
            new = new << val;
    }
    champion->registers[champion->instructions->parameters[1]] = new;
    set_carry(champion, new);
    move_instruction_head(champion);
}

static check_empty(int len, char *coding_byte, char *pair)
{
    for (int i = 4; i < len; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "00") != 0)
            return 1;
    }
}

static check_register(int coords, corewar_t *corewar)
{
    cell_t *cell = get_memory_cell(corewar, coords);

    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    return 0;
}

static int set_adresse(char *pair, champion_t *champion)
{
    if (my_strcmp(pair, "10") == 0) {
        return champion->PC + 5;
    } else if (my_strcmp(pair, "01") == 0) {
        return champion->PC + 3;
    } else if(my_strcmp(pair, "11") == 0) {
        return champion->PC + 3;
    }
}

int check_ld(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    int len = my_strlen(coding_byte);
    char pair[3];
    int adresse = 0;
    cell_t *cell;

    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (my_strcmp(pair, "10") != 0 && my_strcmp(pair, "11") != 0 && my_strcmp(pair, "01") != 0)
        return 1;
    if (adresse == champion->PC + 3 && my_strcmp(pair, "01") == 0 &&
        check_register(champion->PC + 2, corewar) == 1) {
        return 1;
    }
    adresse = set_adresse(pair, champion);
    pair[0] = coding_byte[2];
    pair[1] = coding_byte[3];
    if (my_strcmp(pair, "01") != 0)
        return 1;
    cell = get_memory_cell(corewar, adresse);
    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    if (check_empty(len, coding_byte, pair) == 1)
        return 1;
    return 0;
}

