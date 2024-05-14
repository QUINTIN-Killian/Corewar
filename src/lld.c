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

static int get_param_lld(corewar_t *corewar, champion_t *champion, int *adress,
    char *bin)
{
    int value;

    if (my_strncmp(bin, "01", 2) == 0) {
        value = champion->registers[get_memory_cell(corewar,
        *adress)->value_int];
        *adress += 1;
    } else if (my_strncmp(bin, "10", 2) == 0) {
        value = combine_bytes(4,
        get_memory_cell(corewar, *adress)->value_int,
        get_memory_cell(corewar, *adress + 1)->value_int,
        get_memory_cell(corewar, *adress + 2)->value_int,
        get_memory_cell(corewar, *adress + 3)->value_int);
        *adress += 4;
    } else {
        value = combine_bytes(2,
        get_memory_cell(corewar, *adress)->value_int,
        get_memory_cell(corewar, *adress + 1)->value_int);
        *adress += 2;
    }
    return value;
}

static void set_lld(corewar_t *corewar, champion_t *champion, int adress,
    int value)
{
    char *bin = convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int);

    if (get_parameter_type(bin, 1) == T_IND) {
        champion->registers[get_memory_cell(corewar, adress)->value_int] =
        combine_bytes(REG_SIZE,
        get_memory_cell(corewar, adress + value)->value_int,
        get_memory_cell(corewar, (adress + value) + 1)->value_int,
        get_memory_cell(corewar, (adress + value) + 2)->value_int,
        get_memory_cell(corewar, (adress + value) + 3)->value_int);
    } else {
        champion->registers[get_memory_cell(corewar, adress)->value_int] =
        combine_bytes(REG_SIZE,
        get_memory_cell(corewar, value)->value_int,
        get_memory_cell(corewar, value + 1)->value_int,
        get_memory_cell(corewar, value + 2)->value_int,
        get_memory_cell(corewar, value + 3)->value_int);
    }
    free(bin);
}

void exec_lld(corewar_t *corewar, champion_t *champion)
{
    int adress = champion->PC + 2;
    char *bin = convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int);
    int value = get_param_lld(corewar, champion, &adress, bin);

    free(bin);
    set_lld(corewar, champion, adress, value);
    set_carry(champion, champion->registers[get_memory_cell(corewar, adress)
    ->value_int]);
    champion->PC = cycle_coords(champion->PC + (adress - champion->PC + 1));
    champion->timeout = 10;
}
