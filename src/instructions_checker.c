/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instructions_checker
*/
#include "../include/corewar.h"
extern op_t op_tab[];

void process_instruction(int mnemonic_value)
{
    switch(mnemonic_value) {
        case 1:
            break;
        case 9:
        case 12:
        case 15:
            break;
        case 10:
        case 11:
        case 14:
            break;
        default:
            break;
    }
}

int pc_checker(corewar_t *corewar, champion_t *champion)
{
    cell_t *mnemonic = get_memory_cell(corewar, champion->PC);
    int i = 0;
    int mn = convert_hex_in_int(mnemonic->value);

    while (mn != op_tab[i].mnemonique) {
        process_instruction(op_tab[i].mnemonique);
        i++;
    }
}
