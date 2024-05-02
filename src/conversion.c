/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** conversion
*/
#include "include/corewar.h"

static int get_char_value(char c)
{
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    return c - '0';
}

int convert_hex_in_int(char *hex)
{
    int nb;
    int res = 0;

    if (hex == NULL)
        return -1;
    for (int i = my_strlen(hex) - 1; i >= 0; i--) {
        nb = get_char_value(hex[i]);
        if (i == my_strlen(hex) - 1) {
            res += nb;
            continue;
        }
        res += nb * my_compute_power_rec(16, my_strlen(hex) - i - 1);
    }
    return res;
}