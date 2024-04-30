/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** reverse
*/

#include "../include/corewar.h"

unsigned short rev_short(unsigned short nbr)
{
    return (nbr << 8) | ((nbr >> 8) & 0xFF);
}

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
