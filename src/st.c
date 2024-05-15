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
    set_memory_cell(corewar, create_tmp_cell(champion->id, value),
    champion->PC + combine_bytes(2, get_memory_cell(corewar, champion->PC + 3)
    ->value_int, get_memory_cell(corewar, champion->PC + 4)->value_int) %
    IDX_MOD, 4);
    champion->PC = cycle_coords(champion->PC + 5);
}
