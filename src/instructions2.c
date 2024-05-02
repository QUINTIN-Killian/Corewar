/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instructions2
*/

#include "../include/corewar.h"

extern op_t op_tab[];

int set_instruction(instructions_t *node)
{
    for (int i = 0; op_tab[i].mnemonique != NULL; i++) {
        if (node->mnemonic == op_tab[i].code) {
            node->instruction = my_strdup(op_tab[i].mnemonique);
            node->nb_cycles = op_tab[i].nbr_cycles;
            node->nb_parameters = op_tab[i].nbr_args;
            return 1;
        }
    }
    return 0;
}

static void set_double_linked_list_aux(instructions_t **instructions)
{
    instructions_t *p = NULL;
    instructions_t *c = *instructions;

    while (c != NULL) {
        c->prev = p;
        p = c;
        c = c->next;
    }
}

void set_double_linked_list(champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        set_double_linked_list_aux(&node->instructions);
        node = node->next;
    }
}

instructions_t *move_instruction_head(instructions_t **instructions)
{
    instructions_t *node = *instructions;

    if (node == NULL)
        return NULL;
    if (node->next != NULL)
        return node->next;
    while (node->prev != NULL)
        node = node->prev;
    return node;
}
