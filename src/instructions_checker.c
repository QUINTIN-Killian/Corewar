/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instructions_checker
*/
#include "../include/corewar.h"
extern op_t op_tab[];

static int check_special(char *coding_byte)
{
    int len = my_strlen(coding_byte);
    char pair[3];

    if (len % 2 != 0 || len < 8) {
        return 0;
    }
    pair[0] = coding_byte[0];
    pair[1] = coding_byte[1];
    pair[2] = '\0';
    if (my_strcmp(pair, "11") != 0 && my_strcmp(pair, "10") != 0) {
        return 1;
    }
    for (int i = 2; i < len; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "00") != 0) {
            return 1;
        }
    }
    return 0;
}

void process_instruction(int mnemonic_value, champion_t *champion, corewar_t *corewar)
{
    if (mnemonic_value == 2)
        return check_ld(champion->instructions->coding_byte, champion);
    if (mnemonic_value == 3)
        return check_st(champion->instructions->coding_byte, champion);
    if (mnemonic_value == 4 || mnemonic_value == 5)
        return check_add_sub(champion->instructions->coding_byte, champion);
    if (mnemonic_value == 9 || mnemonic_value == 12 || mnemonic_value == 15)
        return check_special(champion->instructions->coding_byte);
    
}

int pc_checker(corewar_t *corewar, champion_t *champion)
{
    cell_t *mnemonic = get_memory_cell(corewar, champion->PC);
    int i = 0;
    int mn = convert_hex_in_int(mnemonic->value);

    while (mn != op_tab[i].mnemonique) {
        process_instruction(op_tab[i].mnemonique, champion, corewar);
        i++;
    }
}
