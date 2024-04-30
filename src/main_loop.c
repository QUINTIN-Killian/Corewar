/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** main_loop
*/

#include "../include/corewar.h"

void main_loop(champion_t **champions, corewar_t *corewar)
{
    champion_t *node;

    while (corewar->nb_champions > 1 && corewar->nb_turns != 0) {
        node = *champions;
        while (node != NULL) {
            if (node->instructions != NULL) {
                mini_printf("%s : %s\n", node->name, node->instructions->instruction);
                node->instructions = move_instruction_head(&node->instructions);
            }
            node = node->next;
        }
        corewar->nb_turns--;
    }
}
