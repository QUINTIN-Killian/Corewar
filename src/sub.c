/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** sub
*/

#include "../include/corewar.h"

void exec_sub(corewar_t *corewar, champion_t *champion)
{
    champion->registers[get_memory_cell(corewar, champion->PC + 4)->value_int]
    = champion->registers[get_memory_cell(corewar,
    champion->PC + 2)->value_int] - champion->registers[get_memory_cell(
    corewar, champion->PC + 3)->value_int];
    set_carry(champion, champion->registers[get_memory_cell(corewar,
    champion->PC + 4)->value_int]);
    champion->PC = cycle_coords(champion->PC + 5);
    champion->timeout = 10;
}
