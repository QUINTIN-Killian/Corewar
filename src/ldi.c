/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ldi
*/
#include "include/corewar.h"

int ldi_bin(corewar_t *corewar, cell_t temp, int adress)
{
    int val = 0;
    int new = 0;

    for (int i = 0; i < REG_SIZE; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp.value);
        val = set_val(i);
        if (val != -1)
            new << val;
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
    cell_t temp;

    value1 = set_value(champion, 0, 0);
    value2 = set_value(champion, 2, 1);
    value2 = set_value2();
    adress = champion->PC + value1 % IDX_MOD;
    temp = get_memory_cell(corewar, adress);
    s = temp.value + value2;
    adress = champion->PC + s % IDX_MOD;
    new = ldi_bin(corewar, temp, adress);
    champion->registers[champion->instructions->parameters[3]] = new;
    set_carry(champion, new);
}
