/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** xor
*/

#include "../include/corewar.h"

void exec_xor(corewar_t *corewar, champion_t *champion)
{
    int value1 = 0;
    int value2 = 0;

    if (my_strncmp(convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int), "01", 2) == 0)
        value1 = champion->registers[get_memory_cell(corewar,
        champion->PC + 2)->value_int];
    else
        value1 = get_memory_cell(corewar, champion->PC + 2)->value_int;
    if (my_strncmp(&(convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int)[2]), "01", 2) == 0)
        value2 = champion->registers[get_memory_cell(corewar,
        champion->PC + 3)->value_int];
    else
        value2 = get_memory_cell(corewar, champion->PC + 3)->value_int;
    champion->registers[get_memory_cell(corewar, champion->PC + 4)->value_int]
    = value1 ^ value2;
    set_carry(champion, champion->registers[get_memory_cell(corewar,
    champion->PC + 4)->value_int]);
    champion->PC += 5;
    champion->timeout = 6;
}
