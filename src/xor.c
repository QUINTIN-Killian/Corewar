/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** xor
*/

#include "../include/corewar.h"

static int get_param_xor(corewar_t *corewar, champion_t *champion, int ind,
    int pc_adding)
{
    char *bin = convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int);

    if (my_strncmp(&(bin[ind]), "01", 2) == 0) {
        free(bin);
        return champion->registers[get_memory_cell(corewar,
        champion->PC + pc_adding)->value_int];
    } else {
        free(bin);
        return get_memory_cell(corewar, champion->PC + pc_adding)->value_int;
    }
}

void exec_xor(corewar_t *corewar, champion_t *champion)
{
    int value1 = get_param_xor(corewar, champion, 0, 2);
    int value2 = get_param_xor(corewar, champion, 2, 3);

    champion->registers[get_memory_cell(corewar, champion->PC + 4)->value_int]
    = value1 ^ value2;
    set_carry(champion, champion->registers[get_memory_cell(corewar,
    champion->PC + 4)->value_int]);
    champion->PC += 5;
    champion->timeout = 6;
}
