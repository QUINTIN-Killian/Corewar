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

