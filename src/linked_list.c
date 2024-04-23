/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** champions_handling
*/

#include "../include/corewar.h"

champion_t *create_champion(corewar_t *corewar, int id, int start_mem,
    char *filename)
{
    champion_t *champion = malloc(sizeof(champion_t));

    corewar->nb_champions++;
    champion->timeout = 0;
    champion->is_alive = 1;
    champion->id = id;
    champion->start_mem = start_mem;
    champion->fd = fopen(filename, "r");
    champion->next = corewar->champions;
    return champion;
}

static void del_node(champion_t *node)
{
    fclose(node->fd);
    free(node);
}

static void change_cellule(champion_t *previous, champion_t *current,
    champion_t **champions)
{
    if (previous == NULL) {
        *champions = current->next;
    } else {
        previous->next = current->next;
    }
}

void delete_by_id(champion_t **champions, int id)
{
    champion_t *current = *champions;
    champion_t *previous = NULL;

    while (current != NULL) {
        if (current->id == id) {
            change_cellule(previous, current, champions);
            del_node(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void display_champs_infos(champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        mini_printf("ID: %d, Name: %s, Head: %d, Timeout: %d, Statut: %d\n",
        node->id, node->name, node->start_mem, node->timeout, node->is_alive);
        node = node->next;
    }
}

void delete_list(champion_t **champions)
{
    champion_t *current = *champions;
    champion_t *next;

    while (current != NULL) {
        next = current->next;
        del_node(current);
        current = next;
    }
    *champions = NULL;
}

champion_t *rev_champions(champion_t **champions)
{
    champion_t *p = NULL;
    champion_t *c = *champions;
    champion_t *n;

    while (c != NULL) {
        n = c->next;
        c->next = p;
        p = c;
        c = n;
    }
    return p;
}
