/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** main_loop
*/

#include "../include/corewar.h"

static int is_champion_dead_aux(corewar_t *corewar, char *id_hex, int i)
{
    for (int j = 0; corewar->memory[i][j] != NULL; j++) {
        if (my_strcmp(corewar->memory[i][j], id_hex) == 0) {
            return 0;
        }
    }
    return 1;
}

int is_champion_dead(corewar_t *corewar, int id)
{
    char *id_hex = convert_int_in_hex(id);

    for (int i = 0; corewar->memory[i] != NULL; i++) {
        if (!is_champion_dead_aux(corewar, id_hex, i)) {
            free(id_hex);
            return 0;
        }
    }
    return 1;
}

static int skip_turn(champion_t **champions, corewar_t *corewar,
    champion_t **node)
{
    int tmp = -1;

    if ((*node)->cycle_live == CYCLE_TO_DIE ||
    is_champion_dead(corewar, (*node)->id)) {
        tmp = (*node)->id;
        *node = (*node)->next;
        destroy_champion_node_by_id(champions, tmp);
        return 1;
    }
    if ((*node)->timeout > 0) {
        (*node)->timeout--;
        *node = (*node)->next;
        return 1;
    }
    return 0;
}

static void champions_turn(champion_t **champions, corewar_t *corewar,
    champion_t *node)
{
    while (node != NULL) {
        if (skip_turn(champions, corewar, &node))
            continue;
        if (node->instructions != NULL) {
            mini_printf("%s : %s\n",
            node->name, node->instructions->instruction);
            node->timeout = node->instructions->nb_cycles;
            node->instructions = move_instruction_head(&node->instructions);
        }
        node = node->next;
    }
}

void main_loop(champion_t **champions, corewar_t *corewar)
{
    champion_t *node;

    while (corewar->nb_champions > 1 && corewar->nb_turns != 0) {
        node = *champions;
        node->cycle_live++;
        champions_turn(champions, corewar, node);
        corewar->nb_turns--;
    }
}
