/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ldi
*/

#include "../include/corewar.h"

int ldi_bin(corewar_t *corewar, cell_t *temp, int adress)
{
    int val = 0;
    int new = 0;

    for (int i = 0; i < REG_SIZE; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp->value);
        val = set_val(i);
        if (val != -1)
            new = new << val;
    }
    return new;
}

void exec_ldi(corewar_t *corewar, champion_t *champion)
{
    int value1 = 0;
    int value2 = 0;
    int adress = 0;
    int s = 0;
    int new = 0;
    cell_t *temp;

    value1 = set_value(champion, 0, 0);
    value2 = set_value(champion, 2, 1);
    //value2 = set_value2();
    adress = champion->PC + value1 % IDX_MOD;
    temp = get_memory_cell(corewar, adress);
    s = convert_hex_in_int(temp->value) + value2;
    //anciennement <s = temp.value + value2;>
    adress = champion->PC + s % IDX_MOD;
    new = ldi_bin(corewar, temp, adress);
    champion->registers[champion->instructions->parameters[3]] = new;
    set_carry(champion, new);
    move_instruction_head(champion);
}

static int check_registers(champion_t *champion, int i,
    corewar_t *corewar, int adresse)
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
    int j = 0;
    int adresse = champion->PC + 1;

    for (int i = 0; i < 4; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "11") != 0 && my_strcmp(pair, "01") != 0)
            return -1;
        if (my_strcmp(pair, "01") == 0)
            adresse++;
        if (my_strcmp(pair, "11") == 0)
            adresse += 2;
        if (my_strcmp(pair, "01") == 0 &&
            check_registers(champion, j, corewar, adresse) == 1)
            return -1;
        j++;
    }
    return adresse;
}

int check_ldi(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    int adresse = 0;

    if (my_strlen(coding_byte) < 8 || my_strlen(coding_byte) % 2 != 0)
        return 1;
    if (check_firsts_couples(pair, coding_byte, champion, corewar) == -1) {
        return 1;
    } else {
        adresse = check_firsts_couples(pair, coding_byte, champion, corewar);
    }
    pair[0] = coding_byte[4];
    pair[1] = coding_byte[5];
    pair[2] = '\0';
    if (my_strcmp(pair, "01") != 0)
        return 1;
    if (check_registers(champion, 2, corewar, adresse) == 1)
        return 1;
    if (check_empty(my_strlen(coding_byte), coding_byte, pair) == 1)
        return 1;
    return 0;
}
