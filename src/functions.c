/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** functions
*/

#include "../include/corewar.h"

int convert_hex_in_int(char *hex)
{
    int res = 0;

    if (hex == NULL)
        return res;
    for (int i = my_strlen(hex) - 1; i >= 0; i--) {
        if (hex[i] >= 'A' && hex[i] <= 'F') {
            res += my_compute_power_rec(((hex[i] - 'A') + 10) * 16, i -
            my_strlen(hex) + 1);
            continue;
        }
        if (hex[i] >= 'a' && hex[i] <= 'f') {
            res += my_compute_power_rec(((hex[i] - 'a') + 10) * 16, i -
            my_strlen(hex) + 1);
            continue;
        }
        res += my_compute_power_rec((hex[i] - '0') * 16, i - my_strlen(hex) +
        1);
    }
    return res;
}

int get_max_champion_id(champion_t **champions)
{
    int id = 1;
    champion_t *node = *champions;

    while (node != NULL) {
        if (node->id == id) {
            id++;
            node = *champions;
        }
    }
    return id;
}

int my_str_ishex(char *str)
{
    for (int i = 0; i < my_strlen(str); i++)
        if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <=
        'Z') || (str[i] >= 'a' && str[i] <= 'z')))
            return 0;
    return 1;
}
