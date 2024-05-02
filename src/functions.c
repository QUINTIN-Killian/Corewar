/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** functions
*/

#include "../include/corewar.h"

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

static void set_champions_same_id(champion_t **champions, champion_t *node_ref)
{
    champion_t *node = *champions;

    while (node != NULL) {
        if (node != node_ref && node->id == node_ref->id)
            node->id++;
        node = node->next;
    }
}

void set_champions_infos(corewar_t *corewar, champion_t **champions)
{
    champion_t *node = *champions;
    int n = 0;

    while (node != NULL) {
        if (node->id != -1)
            set_champions_same_id(champions, node);
        if (node->id == -1)
            node->id = get_max_champion_id(champions);
        if (node->start_mem == -1)
            node->start_mem = 0 + n * (MEM_SIZE / corewar->nb_champions);
        node->registers[0] = node->start_mem;
        n++;
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

char *convert_int_in_bin(int nb)
{
    char *ans;
    int tmp;

    if (nb > 255 || nb < 0)
        return NULL;
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

static char get_char_value(int nb)
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
        return NULL;
    ans = my_strdup("00");
    for (int i = 1; i >= 0; i--) {
        ans[i] = get_char_value(nb % 16);
        nb = nb / 16;
    }
    return ans;
}
