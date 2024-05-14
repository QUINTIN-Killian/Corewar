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
    instruction->prev = NULL;
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

void destroy_instruction_node_by_id(instructions_t **instructions, int id)
{
    instructions_t *node = *instructions;
    instructions_t *tmp;

    if (node == NULL)
        return;
    if (node->id == id) {
        *instructions = node->next;
        del_node(node);
        return;
    }
    while (node->next != NULL) {
        if (node->next->id == id) {
            tmp = node->next;
            node->next = node->next->next;
            del_node(tmp);
            return;
        }
        node = node->next;
    }
}

static void display_instructions_infos_aux(instructions_t *node)
{
    mini_printf("\tID: %d, Mnemonic: %d, Instruction: %s, Cycles: %d, ",
    node->id, node->mnemonic, node->instruction, node->nb_cycles);
    mini_printf("Coding byte: %s, Size: %d, Nb_params: %d\n",
    node->coding_byte, node->nb_bytes, node->nb_parameters);
    mini_printf("\tParameters:\n\t");
    if (node->mnemonic == 1 || node->mnemonic == 9 ||
    node->mnemonic == 12 || node->mnemonic == 15) {
        mini_printf("\t%d\n", node->parameters[0]);
        return;
    }
    for (int i = 0; i < get_nb_parameters(node->coding_byte); i++)
        mini_printf("\t%d", node->parameters[i]);
    mini_printf("\n");
}

void display_instructions_infos(instructions_t **instructions)
{
    instructions_t *node = *instructions;

    mini_printf("Instructions:\n");
    if (node == NULL || node->parameters == NULL) {
        mini_printf("\tNULL\n");
        return;
    }
    while (node != NULL) {
        display_instructions_infos_aux(node);
        node = node->next;
    }
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
