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
        if (node->head == -1)
            node->head = 0 + n * (MEM_SIZE / corewar->nb_champions);
        node->registers[0] = node->PC;
        node->registers[1] = node->id;
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

char **tablloc(int nb_elements, ...)
{
    char **tab = malloc(sizeof(char *) * (nb_elements + 1));
    char *element = NULL;
    va_list args;

    va_start(args, nb_elements);
    for (int i = 0; i < nb_elements; i++) {
        element = va_arg(args, char *);
        if (element == NULL)
            tab[i] = my_strdup("");
        else
            tab[i] = my_strdup(element);
    }
    va_end(args);
    tab[nb_elements] = NULL;
    return tab;
}

char **realloc_tab_plus_one(char **tab)
{
    char **ans = malloc(sizeof(char *) * (my_strlen_array(tab) + 2));

    for (int i = 0; i < my_strlen_array(tab); i++)
        ans[i] = my_strdup(tab[i]);
    ans[my_strlen_array(tab) + 1] = NULL;
    free_word_array(tab);
    return ans;
}
