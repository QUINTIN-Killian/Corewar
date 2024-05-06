/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** sti
*/

#include "../include/corewar.h"

void exec_sti(champion_t *champion, corewar_t *corewar)
{
    int value1 = champion->registers[champion->instructions->parameters[0]];
    int value2 = 0;
    int value3 = 0;
    int adress = 0;

    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0) {
        value2 = champion->registers[champion->instructions->parameters[1]];
    } else {
        value2 = champion->instructions->parameters[1];
    }
    if (my_strncmp(&(champion->instructions->coding_byte[4]), "01", 2) == 0) {
        value2 = champion->registers[champion->instructions->parameters[2]];
    } else {
        value2 = champion->instructions->parameters[2];
    }
    adress = champion->PC + (value2 + value3) % IDX_MOD;
    set_memory_cell(corewar, create_tmp_cell(champion->id, value1), adress, 4);
    move_instruction_head(champion);
}

static int check_empty(int len, char *pair, char *coding_byte)
{
    for (int i = 6; i < len; i += 2) {
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
    if (my_strcmp(pair, "01") != 0 &&
        (cell->value_int < 1 || cell->value_int > 16))
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

static int check_register_or(char *pair, char *coding_byte, int adresse, corewar_t *corewar)
{
    if (my_strcmp(pair, "01") != 0 && my_strcmp(pair, "10") != 0
        && my_strcmp(pair, "11") != 0)
        return 1;
    if (check_end(pair, my_strlen(coding_byte), coding_byte,
    get_memory_cell(corewar, adresse + 1)) == 1 && my_strcmp(pair, "01") == 0)
        return 1;
    if (check_empty(my_strlen(coding_byte), pair, coding_byte))
        return 1;
    return 0;
}

int check_sti(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    int adresse = champion->PC + 1;

    if (my_strlen(coding_byte) % 2 != 0 || my_strlen(coding_byte) < 8)
        return 1;
    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (my_strcmp(pair, "01") != 0 ||
    check_first_register(corewar, adresse) == 1)
        return 1;
    pair[0] = coding_byte[2];
    pair[1] = coding_byte[3];
    check_register_or(pair, coding_byte, adresse, corewar);
    pair[0] = coding_byte[4];
    pair[1] = coding_byte[5];
    return check_register_or(pair, coding_byte, adresse, corewar);
}
