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

void exec_ld(corewar_t *corewar, champion_t *champion)
{
    int adress = champion->PC + 2;
    int value;

    if (my_strncmp(convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int), "01", 2) == 0) {
        value = champion->registers[get_memory_cell(corewar,
        adress)->value_int];
        adress++;
    } else {
        value = get_memory_cell(corewar, adress)->value_int;
        adress = move_pc_general(convert_int_in_bin(get_memory_cell(corewar,
        champion->PC + 1)->value_int), 1);
    }
    champion->registers[get_memory_cell(corewar, adress)->value_int] =
    champion->PC + value % IDX_MOD;
    set_carry(champion, champion->registers[get_memory_cell(corewar, adress)
    ->value_int]);
    champion->PC = cycle_coords(champion->PC + (adress - champion->PC + 1));
}

static int check_empty(int len, char *coding_byte, char *pair)
{
    for (int i = 4; i < len; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "00") != 0)
            return 1;
    }
    return 0;
}

static int check_register(int coords, corewar_t *corewar)
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
    }
    if (my_strcmp(pair, "01") == 0) {
        return champion->PC + 2;
    }
    return champion->PC + 3;
}

static int check_first(char *pair, champion_t *champion, corewar_t *corewar)
{
    if (my_strcmp(pair, "10") != 0 && my_strcmp(pair, "11")
        != 0 && my_strcmp(pair, "01") != 0)
        return 1;
    if (my_strcmp(pair, "01") == 0 &&
        check_register(champion->PC + 2, corewar) == 1) {
        return 1;
    }
    return 0;
}

int check_ld(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    int adresse = 0;
    cell_t *cell;

    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (check_first(pair, champion, corewar) == 1)
        return 1;
    adresse = set_adresse(pair, champion);
    pair[0] = coding_byte[2];
    pair[1] = coding_byte[3];
    if (my_strcmp(pair, "01") != 0)
        return 1;
    cell = get_memory_cell(corewar, adresse);
    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    return check_empty(my_strlen(coding_byte), coding_byte, pair);
}
