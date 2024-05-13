/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** conversion
*/

#include "../include/corewar.h"

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

char *convert_int_in_bin(int nb)
{
    char *ans;
    int tmp;

    if (nb > 255 || nb < 0)
        nb = my_abs(nb) % 255;
    ans = my_strdup("00000000");
    for (int i = 7; i >= 0; i--) {
        tmp = my_compute_power_rec(2, i);
        if (nb - tmp == 0) {
            ans[7 - i] = '1';
            break;
        }
        if (nb - tmp > 0) {
            nb -= tmp;
            ans[7 - i] = '1';
        }
    }
    return ans;
}

static char get_int_value(int nb)
{
    if (nb >= 0 && nb < 10)
        return '0' + nb;
    nb -= 10;
    return 'a' + nb;
}

char *convert_int_in_hex(int nb)
{
    char *ans;

    if (nb > 255 || nb < 0)
        nb = my_abs(nb) % 255;
    ans = my_strdup("00");
    for (int i = 1; i >= 0; i--) {
        ans[i] = get_int_value(nb % 16);
        nb = nb / 16;
    }
    return ans;
}

int convert_bin_in_int(char *bin)
{
    int ans = 0;

    if (bin == NULL)
        return 0;
    for (int i = my_strlen(bin) - 1; i >= 0; i--)
        if (bin[i] == '1')
            ans += my_compute_power_rec(2, my_strlen(bin) - 1 - i);
    return ans;
}
