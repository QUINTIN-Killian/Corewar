/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instructions2
*/

#include "../include/corewar.h"

extern op_t op_tab[];

int set_instruction(instructions_t *node)
{
    for (int i = 0; op_tab[i].mnemonique != NULL; i++) {
        if (node->mnemonic == op_tab[i].code) {
            node->instruction = my_strdup(op_tab[i].mnemonique);
            node->nb_cycles = op_tab[i].nbr_cycles;
            node->nb_parameters = op_tab[i].nbr_args;
            return 1;
        }
    }
    return 0;
}
