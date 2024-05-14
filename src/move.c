/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** move
*/

#include "../include/corewar.h"

int cycle_nb(int nb, int bytes)
{
    if (bytes == 1) {
        if (nb <= 0xff / 2) /*127 ; -128*/
            return nb;
        return (-0xff / 2) + (nb - 1 - 0xff / 2) - 1;
    } else if (bytes == 2) {
        if (nb <= 0xffff / 2) /*32 767 ; -32 768*/
            return nb;
        return (-0xffff / 2) + (nb - 1 - 0xffff / 2) - 1;
    }
    return nb;
}

int cycle_coords(int coords)
{
    while (coords < 0)
        coords += MEM_SIZE;
    if (coords >= MEM_SIZE)
        return coords % MEM_SIZE;
    return coords;
}

void set_carry(champion_t *champion, int value)
{
    if (value == 0)
        champion->carry = 0;
    else
        champion->carry = 1;
}
