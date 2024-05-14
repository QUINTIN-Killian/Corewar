/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** main_loop
*/

#include "../include/corewar.h"

static int skip_turn_aux(corewar_t *corewar, champion_t **node)
{
    if ((*node)->timeout > 0) {
        (*node)->timeout--;
        (*node) = (*node)->next;
        return 1;
    }
    return 0;
}

static int skip_turn(champion_t **champions, corewar_t *corewar,
    champion_t **node)
{
    int tmp = -1;

    if ((*node)->cycle_live >= CYCLE_TO_DIE) {
        tmp = (*node)->id;
        mini_fdprintf(2, "Champion %s is dead !\n", (*node)->name);
        (*node) = (*node)->next;
        destroy_champion_node_by_id(champions, tmp);
        if (get_nb_champions(champions) == 1) {
            mini_printf("The player %d(%s)has won.\n",
            (*champions)->id, (*champions)->name);
            return 2;
        }
        return 1;
    }
    return skip_turn_aux(corewar, node);
}

static void champions_turn(champion_t **champions, corewar_t *corewar,
    champion_t *node)
{
    int skip = 0;

    while (node != NULL) {
        node->cycle_live++;
        skip = skip_turn(champions, corewar, &node);
        if (skip == 1)
            continue;
        if (skip == 2) {
            corewar->nb_champions = -1;
            break;
        }
        instruction_execution(corewar, node);
        node = node->next;
    }
}

void main_loop(champion_t **champions, corewar_t *corewar)
{
    champion_t *node;

    corewar->turn_id = 0;
    while (corewar->nb_champions > 1 && corewar->nb_turns != 0) {
        corewar->turn_id++;
        node = *champions;
        champions_turn(champions, corewar, node);
        corewar->nb_turns--;
    }
    print_memory(corewar);
    mini_printf("Game terminated at turn %d.\n", corewar->turn_id);
}
