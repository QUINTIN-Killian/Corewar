/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** print_winner
*/

#include "../include/corewar.h"

void print_winner(corewar_t *corewar)
{
    if (corewar->winner == NULL) {
        mini_printf("The player 0()has won.\n");
        return;
    }
    mini_printf("The player %d(%s)has won.\n", corewar->winner->id,
    corewar->winner->name);
}
