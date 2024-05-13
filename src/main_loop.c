/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** main_loop
*/

#include "../include/corewar.h"

static int is_champion_dead_aux(corewar_t *corewar, int id, int i)
{
    for (int j = 0; corewar->memory[i][j].value != NULL; j++) {
        if (corewar->memory[i][j].id_owner == id) {
            return 0;
        }
    }
    return 1;
}

int is_champion_dead(corewar_t *corewar, int id)
{
    for (int i = 0; corewar->memory[i] != NULL; i++) {
        if (!is_champion_dead_aux(corewar, id, i)) {
            return 0;
        }
    }
    return 1;
}

static int skip_turn_aux(corewar_t *corewar, champion_t **node)
{
    if ((*node)->timeout > 0) {
        (*node)->timeout--;
        (*node) = (*node)->next;
        return 1;
    }
    // if (pc_checker(corewar, *node)) {
    //     (*node) = (*node)->next;
    //     return 1;
    // }
    return 0;
}

static int skip_turn(champion_t **champions, corewar_t *corewar,
    champion_t **node)
{
    int tmp = -1;

    if ((*node)->cycle_live >= CYCLE_TO_DIE ||
    is_champion_dead(corewar, (*node)->id)) {
        tmp = (*node)->id;
        mini_fdprintf(2, "Champion %s is dead !\n", (*node)->name); /*remove*/
        (*node) = (*node)->next;
        destroy_champion_node_by_id(champions, tmp);
        corewar->nb_champions--;
        if (get_nb_champions(champions) == 1) {
            mini_printf("The player %d(%s)has won.\n",
            (*node)->id, (*node)->name);
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
        if (skip == 2)
            break;
        mini_printf("%d) %s : %s, %d\n",
        corewar->turn_id, node->name,
        get_memory_cell(corewar, node->PC)->value, node->PC); /*remove*/
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
    print_memory(corewar); /*bonus*/
    mini_printf("Game terminated at turn %d.\n", corewar->turn_id); /*remove*/
}
