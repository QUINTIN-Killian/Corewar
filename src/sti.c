/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** sti
*/

#include "../include/corewar.h"

void exec_sti(corewar_t *corewar, champion_t *champion)
{
    int value = champion->registers[get_memory_cell(corewar,
    champion->PC + 2)->value_int];
    int pc = champion->PC + 3;
    int adress = 0;

    for (int i = 1; i < 3; i++) {
        if (my_strncmp(&(convert_int_in_bin(get_memory_cell(corewar,
        champion->PC + 1)->value_int)[i * 2]), "01", 2) == 0) {
            adress += champion->registers[get_memory_cell(corewar,
            pc)->value_int];
            pc++;
            continue;
        }
        adress += combine_bytes(2, get_memory_cell(corewar, pc)->value_int,
        get_memory_cell(corewar, pc + 1)->value_int);
        pc += 2;
    }
    set_memory_cell(corewar, create_tmp_cell(champion->id, value),
    champion->PC + adress % IDX_MOD, 4);
    champion->PC += pc;
}
