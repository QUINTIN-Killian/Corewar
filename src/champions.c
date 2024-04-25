/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** champions_handling
*/

#include "../include/corewar.h"

champion_t *create_champion(corewar_t *corewar, char *filename)
{
    champion_t *champion = malloc(sizeof(champion_t));

    corewar->nb_champions++;
    champion->magic_number = 0;
    champion->name[0] = '\0';
    champion->prog_size = 0;
    champion->comment[0] = '\0';
    champion->timeout = 0;
    champion->is_alive = 1;
    champion->id = corewar->id;
    champion->start_mem = corewar->start_mem;
    champion->fd = fopen(filename, "r");
    champion->next = corewar->champions;
    champion->instructions = NULL;
    corewar->id = -1;
    corewar->start_mem = -1;
    return champion;
}

static void del_node(champion_t *node)
{
    fclose(node->fd);
    free(node);
}

void destroy_champion_node_by_id(champion_t **champions, int id)
{
    champion_t *node = *champions;
    champion_t *tmp;

    if (node == NULL)
        return;
    if (node->id == id) {
        *champions = node->next;
        del_node(node);
        return;
    }
    while (node->next != NULL) {
        if (node->next->id == id) {
            tmp = node->next;
            node->next = node->next->next;
            del_node(tmp);
            return;
        }
        node = node->next;
    }
}

void display_champions_infos(champion_t **champions)
{
    champion_t *node = *champions;

    if (node == NULL) {
        mini_printf("\e[33mChampions:\e[0m\n");
        mini_printf("NULL\n");
        return;
    }
    while (node != NULL) {
        mini_printf("\e[33mChampion:\e[0m\n");
        mini_printf("ID: %d, Name: %s, Head: %d, Timeout: %d, Statut: %d\n",
        node->id, node->name, node->start_mem, node->timeout, node->is_alive);
        display_instructions_infos(&node->instructions);
        node = node->next;
    }
}

void delete_champions_list(champion_t **champions)
{
    champion_t *current = *champions;
    champion_t *next;

    while (current != NULL) {
        delete_instructions_list(&current->instructions);
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
