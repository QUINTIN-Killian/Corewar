/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** lld
*/
/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ld
*/
#include "include/corewar.h"

int set_val(int i)
{
    if (i == 0)
        return 24;
    if (i == 1) {
        return 12;
    if (i == 2) {
        return 8;
    }
    if (i == 3) {
        return -1;
    }
    }
}

void exec_lld(champion_t *champion, corewar_t *corewar)
{
    int value1 = 0;
    int adress = 0;
    int new = 0;
    int val = 0;
    cell_t temp;

    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0) {
        value1 = champion->registers[champion->instructions->parameters[1]];
    } else {
        value1 = champion->instructions->parameters[1];
    }
    adress = champion->PC + value1;
    for (int i = 0 ; i < 4; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp.value);
        val = set_val(i);
        if (val != -1)
            new << val;
    }
    champion->registers[champion->instructions->parameters[1]] = new;
    if (new == 0) {
        champion->carry = 0;
    } else {
        champion->carry = 1;
    }
}