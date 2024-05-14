/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** writing
*/

#include "../include/corewar.h"

static int write_live(corewar_t *corewar, champion_t *champion,
    instructions_t **node)
{
    if ((*node)->mnemonic == 1) {
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->mnemonic), champion->PC, 1);
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->parameters[0]), champion->PC + 1, 4);
        champion->PC += (*node)->nb_bytes;
        (*node) = (*node)->next;
        return 1;
    }
    return 0;
}

static int write_no_coding_byte(corewar_t *corewar, champion_t *champion,
    instructions_t **node)
{
    if ((*node)->mnemonic == 9 || (*node)->mnemonic == 12 ||
    (*node)->mnemonic == 15) {
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->mnemonic), champion->PC, 1);
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->parameters[0]), champion->PC + 1, 2);
        champion->PC += (*node)->nb_bytes;
        (*node) = (*node)->next;
        return 1;
    }
    return 0;
}

static void write_index_instruction(corewar_t *corewar, champion_t *champion,
    instructions_t **node)
{
    set_memory_cell(corewar, create_tmp_cell(champion->owner,
    (*node)->mnemonic), champion->PC, 1);
    set_memory_cell(corewar, create_tmp_cell(champion->owner,
    convert_bin_in_int((*node)->coding_byte)), champion->PC + 1, 1);
    champion->PC += 2;
    for (int i = 0; i < get_nb_parameters((*node)->coding_byte); i++) {
        if (my_strncmp(&((*node)->coding_byte[i * 2]), "01", 2) == 0) {
            set_memory_cell(corewar, create_tmp_cell(champion->owner,
            (*node)->parameters[i]), champion->PC, 1);
            champion->PC++;
            continue;
        }
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->parameters[i]), champion->PC, 2);
        champion->PC += 2;
    }
    (*node) = (*node)->next;
}

static int write_general_instruction_aux(corewar_t *corewar,
    champion_t *champion, instructions_t **node, int i)
{
    if (my_strncmp(&((*node)->coding_byte[i * 2]), "01", 2) == 0) {
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->parameters[i]), champion->PC, 1);
        champion->PC++;
        return 1;
    }
    if (my_strncmp(&((*node)->coding_byte[i * 2]), "10", 2) == 0) {
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->parameters[i]), champion->PC, 4);
        champion->PC += 4;
        return 1;
    }
    return 0;
}

static void write_general_instruction(corewar_t *corewar, champion_t *champion,
    instructions_t **node)
{
    set_memory_cell(corewar, create_tmp_cell(champion->owner,
    (*node)->mnemonic), champion->PC, 1);
    set_memory_cell(corewar, create_tmp_cell(champion->owner,
    convert_bin_in_int((*node)->coding_byte)), champion->PC + 1, 1);
    champion->PC += 2;
    for (int i = 0; i < get_nb_parameters((*node)->coding_byte); i++) {
        if (write_general_instruction_aux(corewar, champion, node, i))
            continue;
        set_memory_cell(corewar, create_tmp_cell(champion->owner,
        (*node)->parameters[i]), champion->PC, 2);
        champion->PC += 2;
    }
    (*node) = (*node)->next;
}

void write_instructions_in_memory_aux(corewar_t *corewar,
    champion_t *champion, instructions_t **instructions)
{
    instructions_t *node = *instructions;

    while (node != NULL) {
        if (write_live(corewar, champion, &node))
            continue;
        if (write_no_coding_byte(corewar, champion, &node))
            continue;
        if (node->mnemonic == 10 || node->mnemonic == 11 ||
        node->mnemonic == 14) {
            write_index_instruction(corewar, champion, &node);
            continue;
        }
        write_general_instruction(corewar, champion, &node);
    }
}

void write_instructions_in_memory(corewar_t *corewar, champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        write_instructions_in_memory_aux(corewar, node, &node->instructions);
        node->PC = node->registers[0];
        node = node->next;
    }
}
