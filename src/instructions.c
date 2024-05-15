/*
** EPITECH PROJECT, 2024
** B-CPE-200-LYN-2-1-corewar-elie.chardin
** File description:
** instructions
*/

#include "../include/corewar.h"

instructions_t *create_instruction(instructions_t *next)
{
    instructions_t *instruction = malloc(sizeof(instructions_t));

    if (next == NULL)
        instruction->id = 1;
    else
        instruction->id = next->id + 1;
    instruction->mnemonic = 0;
    instruction->nb_bytes = 0;
    instruction->nb_parameters = 0;
    instruction->coding_byte = NULL;
    instruction->instruction = NULL;
    instruction->parameters = NULL;
    instruction->next = next;
    return instruction;
}

static void del_node(instructions_t *node)
{
    if (node->instruction != NULL)
        free(node->instruction);
    if (node->coding_byte != NULL)
        free(node->coding_byte);
    if (node->parameters != NULL)
        free(node->parameters);
    free(node);
}

void delete_instructions_list(instructions_t **instructions)
{
    instructions_t *current = *instructions;
    instructions_t *next;

    while (current != NULL) {
        next = current->next;
        del_node(current);
        current = next;
    }
    *instructions = NULL;
}

instructions_t *rev_instructions(instructions_t **instructions)
{
    instructions_t *p = NULL;
    instructions_t *c = *instructions;
    instructions_t *n;

    while (c != NULL) {
        n = c->next;
        c->next = p;
        p = c;
        c = n;
    }
    return p;
}

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
