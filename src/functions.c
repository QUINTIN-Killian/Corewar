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
            continue;
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
        if (node->head == -1)
            node->head = 0 + n * (MEM_SIZE / corewar->nb_champions);
        node->registers[0] = node->PC;
        node->registers[1] = node->id;
        node->owner = node->id;
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

int get_parameter_type(char *coding_byte, int param)
{
    int i = 0;

    param--;
    for (; i < param; i++);
    if (my_strncmp(&(coding_byte[i * 2]), "01", 2) == 0)
        return T_REG;
    if (my_strncmp(&(coding_byte[i * 2]), "10", 2) == 0)
        return T_DIR;
    if (my_strncmp(&(coding_byte[i * 2]), "11", 2) == 0)
        return T_IND;
    return 0;
}
