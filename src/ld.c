/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ld
*/
#include "include/corewar.h"

cell_t get_memory_cell(corewar_t *corewar, int coords)
{
    int x;
    int y;

    if (coords < 0 || coords >= MEM_SIZE)
        return;
    y = coords / 32;
    x = coords % 32;
    return corewar->memory[x][y];
}

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

void exec_ld(champion_t *champion, corewar_t *corewar)
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
    adress = champion->PC + value1 % IDX_MOD;
    for (int i = 0 ; i < 4; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp.value);
        val = set_val(i);
        if (val != -1)
            new << val;
    }
    champion->registers[champion->instructions->parameters[1]] = new;
}