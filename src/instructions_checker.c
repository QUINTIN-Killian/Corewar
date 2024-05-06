/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instructions_checker
*/
#include "../include/corewar.h"
extern op_t op_tab[];

int process_instruction(int mnemonic_value,
    champion_t *champion, corewar_t *corewar)
{
    if (mnemonic_value == 2 || mnemonic_value == 13)
        return check_ld(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
        return check_ld(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
    if (mnemonic_value == 3)
        return check_st(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
        return check_st(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
    if (mnemonic_value == 4 || mnemonic_value == 5)
        return check_add_sub(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
        return check_add_sub(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
    if (mnemonic_value == 6 || mnemonic_value == 7 || mnemonic_value == 8)
        return check_and(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
    if (mnemonic_value == 10 || mnemonic_value == 14)
        return check_ldi(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
    if (mnemonic_value == 16)
        return check_aff(convert_int_in_bin(get_memory_cell(corewar, champion->PC + 1)->value_int), champion, corewar);
    return 0;
}

int pc_checker(corewar_t *corewar, champion_t *champion)
{
    int mnemonic =
    convert_hex_in_int(get_memory_cell(corewar, champion->PC)->value);

    for (int i = 0; op_tab[i].code != 0; i++)
        if (mnemonic == op_tab[i].code)
            return process_instruction(op_tab[i].code, champion, corewar);
    return 1;
}
