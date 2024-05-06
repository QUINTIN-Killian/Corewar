/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** move
*/

#include "../include/corewar.h"

void set_carry(champion_t *champion, int value)
{
    if (value == 0)
        champion->carry = 0;
    else
        champion->carry = 1;
}
