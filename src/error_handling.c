/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** error_handling
*/

#include "../include/corewar.h"

int is_enough_champions(int ac, char **av)
{
    int res = 0;

    for (int i = 0; i < ac; i++)
        if (is_correct_file(av, i))
            res++;
    if (res < 2 || res > 4) {
        mini_fdprintf(2, "Incorrect number of champions.\n");
        return 0;
    }
    return 1;
}

int is_enough_correct_champions(corewar_t *corewar)
{
    if (corewar->nb_champions < 2 || corewar->nb_champions > 4) {
        mini_fdprintf(2, "Incorrect number of champions.\n");
        return 0;
    }
    return 1;
}

static int champion_already_present(champion_t **champions,
    champion_t *node_ref, int id, int start_mem)
{
    champion_t *node = *champions;

    while (node != NULL) {
        if (node != node_ref && (node->id == id || node->start_mem ==
        start_mem)) {
            mini_fdprintf(2,
            "Several champions have the same id or starting head point.\n");
            return 1;
        }
        node = node->next;
    }
    return 0;
}

int unique_champions(champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        if (champion_already_present(champions, node, node->id,
        node->start_mem))
            return 0;
        node = node->next;
    }
    return 1;
}
