/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ld
*/

#include "../include/corewar.h"

static int get_param_ld(corewar_t *corewar, champion_t *champion, int *adress,
    char *bin)
{
    int value;

    if (my_strncmp(bin, "01", 2) == 0) {
        value = champion->registers[get_memory_cell(corewar,
        *adress)->value_int];
        *adress += 1;
    } else if (my_strncmp(bin, "10", 2) == 0) {
        value = combine_bytes(4,
        get_memory_cell(corewar, *adress)->value_int,
        get_memory_cell(corewar, *adress + 1)->value_int,
        get_memory_cell(corewar, *adress + 2)->value_int,
        get_memory_cell(corewar, *adress + 3)->value_int);
        *adress += 4;
    } else {
        value = combine_bytes(2,
        get_memory_cell(corewar, *adress)->value_int,
        get_memory_cell(corewar, *adress + 1)->value_int);
        *adress += 2;
    }
    return value;
}

void exec_ld(corewar_t *corewar, champion_t *champion)
{
    int adress = champion->PC + 2;
    char *bin = convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int);
    int value = get_param_ld(corewar, champion, &adress, bin);

    free(bin);
    champion->registers[get_memory_cell(corewar, adress)->value_int] =
    champion->PC + value % IDX_MOD;
    set_carry(champion, champion->registers[get_memory_cell(corewar, adress)
    ->value_int]);
    champion->PC = cycle_coords(champion->PC + (adress - champion->PC + 1));
    champion->timeout = 5;
}yy

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
    return check_empty(my_strlen(coding_byte), coding_byte, pair, 4);
}
