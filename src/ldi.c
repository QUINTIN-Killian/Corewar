/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ldi
*/

#include "../include/corewar.h"

static int get_param_ldi(corewar_t *corewar, champion_t *champion, int i,
    int *pc)
{
    int res = 0;
    char *bin = convert_int_in_bin(get_memory_cell(
    corewar, champion->PC + 1)->value_int);

    if (my_strncmp(&(bin[i]), "01", 2) == 0) {
        res = champion->registers[get_memory_cell(
        corewar, *pc)->value_int];
        *pc += 1;
    } else {
        res = combine_bytes(2, get_memory_cell(
        corewar, *pc)->value_int, get_memory_cell(
        corewar, *pc + 1)->value_int);
        *pc += 2;
    }
    free(bin);
    return res;
}

void exec_ldi(corewar_t *corewar, champion_t *champion)
{
    int pc = champion->PC + 2;
    int param1 = get_param_ldi(corewar, champion, 0, &pc);
    int param2 = get_param_ldi(corewar, champion, 2, &pc);
    int s = combine_bytes(IND_SIZE,
    get_memory_cell(corewar, champion->PC + param1 % IDX_MOD)->value_int,
    get_memory_cell(corewar, (champion->PC + param1 % IDX_MOD) + 1)->value_int)
    + param2;

    champion->registers[get_memory_cell(corewar, pc)->value_int] =
    combine_bytes(REG_SIZE,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD))->value_int,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD) + 1)->value_int,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD) + 2)->value_int,
    get_memory_cell(corewar, (champion->PC + s % IDX_MOD) + 3)->value_int);
    champion->PC = cycle_coords(champion->PC + (pc - champion->PC + 1));
    set_carry(champion,
    champion->registers[get_memory_cell(corewar, pc)->value_int]);
    champion->timeout = 25;
}

static int check_registers(corewar_t *corewar, int adresse)
{
    cell_t *cell = get_memory_cell(corewar, adresse);

    if (cell->value_int < 1 || cell->value_int > 16)
        return 1;
    return 0;
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

static int check_firsts_couples(char *pair, char *coding_byte,
    champion_t *champion, corewar_t *corewar)
{
    int adresse = champion->PC + 2;

    for (int i = 0; i < 4; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "11") != 0 && my_strcmp(pair, "01") != 0 &&
        my_strcmp(pair, "10") != 0)
            return -1;
        if (my_strcmp(pair, "01") == 0)
            adresse++;
        if (my_strcmp(pair, "11") == 0 || my_strcmp(pair, "10") == 0)
            adresse += 2;
        if (my_strcmp(pair, "01") == 0 &&
            check_registers(corewar, adresse) == 1)
            return -1;
    }
    return adresse;
}

int check_ldi(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    int adresse = check_firsts_couples(pair, coding_byte, champion, corewar);

    if (adresse == -1)
        return 1;
    pair[0] = coding_byte[4];
    pair[1] = coding_byte[5];
    pair[2] = '\0';
    if (my_strcmp(pair, "01") != 0)
        return 1;
    if (check_registers(corewar, adresse + 1) == 1)
        return 1;
    return check_empty(my_strlen(coding_byte), coding_byte, pair);
}
