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

static void champions_turn(champion_t **champions, corewar_t *corewar,
    champion_t *node)
{
    int tmp = -1;

    while (node != NULL) {
        if (node->instructions == NULL || node->timeout > 0 ||
        get_memory_cell(corewar, node->head)->id_owner != node->id) {
            node->timeout--;
            node = node->next;
            continue;
        }
        if (node->cycle_live >= CYCLE_TO_DIE ||
        is_champion_dead(corewar, node->id)) {
            tmp = node->id;
            node = node->next;
            destroy_champion_node_by_id(champions, tmp);
            corewar->nb_champions--;
            continue;
        }
        mini_printf("%s : %s\n", node->name, node->instructions->instruction);
        node->timeout = node->instructions->nb_cycles;
        instruction_execution(corewar, node, node->instructions);
        node = node->next;
    }
}

void main_loop(champion_t **champions, corewar_t *corewar)
{
    champion_t *node;

    corewar->turn_nbr = 0;
    while (corewar->nb_champions > 1 && corewar->nb_turns != 0) {
        corewar->turn_nbr++;
        node = *champions;
        node->cycle_live++;
        champions_turn(champions, corewar, node);
        corewar->nb_turns--;
    }
}
