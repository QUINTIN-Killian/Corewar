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
#include "include/corewar.h"

void exec_lld(champion_t *champion, corewar_t *corewar)
{
    int value1 = 0;
    int adress = 0;
    int new = 0;
    int val = 0;
    cell_t temp;

    value1 = set_value(champion, 2, 1);
    adress = champion->PC + value1;
    for (int i = 0; i < REG_SIZE; i++) {
        temp = get_memory_cell(corewar, adress);
        new += convert_hex_in_int(temp.value);
        val = set_val(i);
        if (val != -1)
            new << val;
    }
    champion->registers[champion->instructions->parameters[1]] = new;
    set_carry(champion, new);
}
