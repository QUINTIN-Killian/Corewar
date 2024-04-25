/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** functions
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

int get_max_champion_id(champion_t **champions)
{
    int id = 1;
    champion_t *node = *champions;

    while (node != NULL) {
        if (node->id == id) {
            id++;
            node = *champions;
        }
        node = node->next;
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

void give_champions_id(champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        if (node->id == -1)
            node->id = get_max_champion_id(champions);
        node->start_mem = node->id;
        node = node->next;
    }
}

void del_incorrect_magic_number(corewar_t *corewar, champion_t **champions)
{
    champion_t *node = *champions;
    champion_t *tmp;

    while (node != NULL) {
        if (node->magic_number != COREWAR_EXEC_MAGIC) {
            tmp = node;
            node = node->next;
            destroy_champion_node_by_id(champions, tmp->id);
            corewar->nb_champions--;
            continue;
        }
        node = node->next;
    }
}
