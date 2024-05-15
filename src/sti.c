/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** sti
*/

#include "../include/corewar.h"

static void get_param_sti(corewar_t *corewar, champion_t *champion, int *pc,
    int *adress)
{
    char *bin;

    for (int i = 1; i < 3; i++) {
        bin = convert_int_in_bin(get_memory_cell(corewar,
        champion->PC + 1)->value_int);
        if (my_strncmp(&(bin[i * 2]), "01", 2) == 0) {
            *adress += champion->registers[get_memory_cell(corewar,
            *pc)->value_int];
            *pc += 1;
            free(bin);
            continue;
        }
        free(bin);
        *adress += combine_bytes(2, get_memory_cell(corewar, *pc)->value_int,
        get_memory_cell(corewar, *pc + 1)->value_int);
        *pc += 2;
    }
}

void exec_sti(corewar_t *corewar, champion_t *champion)
{
    int value = champion->registers[get_memory_cell(corewar,
    champion->PC + 2)->value_int];
    int pc = champion->PC + 3;
    int adress = 0;

    get_param_sti(corewar, champion, &pc, &adress);
    set_memory_cell(corewar, create_tmp_cell(champion->id, value),
    champion->PC + adress % IDX_MOD, 4);
    champion->PC = cycle_coords(champion->PC + (pc - champion->PC));
    champion->timeout = 25;
}
