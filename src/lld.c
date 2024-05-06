/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** lld
*/
/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** ld
*/

#include "../include/corewar.h"

void exec_lld(corewar_t *corewar, champion_t *champion)
{
    int adress = champion->PC + 2;
    int value;

    if (my_strncmp(convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int), "01", 2) == 0) {
        value = champion->registers[get_memory_cell(corewar,
        adress)->value_int];
        adress++;
    } else {
        value = get_memory_cell(corewar, adress)->value_int;
        adress = move_pc_general(convert_int_in_bin(get_memory_cell(corewar,
        champion->PC + 1)->value_int), 1);
    }
    champion->registers[get_memory_cell(corewar, adress)->value_int] =
    champion->PC + value;
    set_carry(champion, champion->registers[get_memory_cell(corewar, adress)
    ->value_int]);
    champion->PC = cycle_coords(champion->PC + (adress - champion->PC + 1));
}
