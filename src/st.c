/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** st
*/
#include "../include/corewar.h"

void exec_st(corewar_t *corewar, champion_t *champion)
{
    int value = champion->registers[get_memory_cell(corewar,
    champion->PC + 2)->value_int];
    char *bin = convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int);

    champion->timeout = 5;
    if (my_strncmp(&(bin[2]), "01", 2) == 0) {
        champion->registers[get_memory_cell(corewar, champion->PC + 3)
        ->value_int] = value;
        champion->PC = cycle_coords(champion->PC + 4);
        free(bin);
        return;
    }
    free(bin);
    set_memory_cell(corewar, create_tmp_cell(champion->owner, value),
    champion->PC + combine_bytes(2, get_memory_cell(corewar, champion->PC + 3)
    ->value_int, get_memory_cell(corewar, champion->PC + 4)->value_int) %
    IDX_MOD, 4);
    champion->PC = cycle_coords(champion->PC + 5);
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

static int check_end(char *pair, int len, char *coding_byte, cell_t *cell)
{
    if (my_strcmp(pair, "01") == 0 &&
    (cell->value_int < 1 || cell->value_int > 16))
        return 1;
    if (check_empty(len, pair, coding_byte))
        return 1;
    return 0;
}

static int check_first_register(corewar_t *corewar, int adresse)
{
    cell_t *cell = get_memory_cell(corewar, adresse);

    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    return 0;
}

int check_st(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    int adresse = champion->PC + 1;

    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (my_strcmp(pair, "01") != 0 ||
    check_first_register(corewar, adresse) == 1)
        return 1;
    pair[0] = coding_byte[2];
    pair[1] = coding_byte[3];
    if (my_strcmp(pair, "01") != 0 && my_strcmp(pair, "10") != 0
        && my_strcmp(pair, "11") != 0)
        return 1;
    return check_end(pair, my_strlen(coding_byte), coding_byte,
    get_memory_cell(corewar, adresse + 1));
}
