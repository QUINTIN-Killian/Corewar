/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** live
*/

#include "../include/corewar.h"

void exec_live(corewar_t *corewar, champion_t **champions_list,
    champion_t *champion)
{
    int id = combine_bytes(4,
    get_memory_cell(corewar, champion->PC + 1)->value,
    get_memory_cell(corewar, champion->PC + 2)->value,
    get_memory_cell(corewar, champion->PC + 3)->value,
    get_memory_cell(corewar, champion->PC + 4)->value);
    champion_t *node = *champions_list;

    while (node != NULL) {
        if (node->id == id) {
            node->cycle_live = -1;
            mini_printf("The player %d(%s)is alive.\n", node->id, node->name);
        }
        node = node->next;
    }
    champion->PC += 5;
}
