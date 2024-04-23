/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** reverse
*/

#include "../include/corewar.h"

unsigned int rev_int(unsigned int nbr)
{
    return ((nbr << 24) |
    (((nbr >> 16) << 24) >> 16) |
    (((nbr << 16) >> 24) << 16) | (nbr >> 24));
}

unsigned long rev_long(unsigned long nbr)
{
    unsigned long rev_nbr = 0;

    for (unsigned long i = 0; i < sizeof(unsigned long); i++) {
        rev_nbr = (rev_nbr << 8) + (nbr & 0xFF);
        nbr >>= 8;
    }
    return rev_nbr;
}
