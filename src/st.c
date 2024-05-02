/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** st
*/
#include "../include/corewar.h"

void exec_st(champion_t *champion, corewar_t *corewar)
{
    int value1 = champion->registers[champion->instructions->parameters[0]];
    int value2 = 0;
    int adress = 0;

    if (my_strncmp(&(champion->instructions->coding_byte[2]), "01", 2) == 0) {
        value2 = value1;
        champion->registers[champion->instructions->parameters[1]] = value2;
    } else {
        value2 = champion->instructions->parameters[1];
        adress = champion->PC + value2 % IDX_MOD;
        set_memory_cell(corewar, value1, adress);
    }
}