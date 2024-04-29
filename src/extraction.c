/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** extraction
*/

#include "../include/corewar.h"

static int extract_args_aux(char **av, corewar_t *corewar, int *i)
{
    if (is_n_flag(av, *i)) {
        corewar->id = convert_str_in_int(av[*i + 1]);
        *i += 1;
        return 1;
    }
    if (is_correct_file(av, *i)) {
        corewar->champions = create_champion(corewar, av[*i]);
        return 1;
    }
    mini_fdprintf(2, "Incorrect parameter.\n");
    return 0;
}

int extract_args(int ac, char **av, corewar_t *corewar)
{
    for (int i = 1; i < ac; i++) {
        if (is_dump_flag(av, i)) {
            corewar->nb_turns = convert_str_in_int(av[i + 1]);
            i++;
            continue;
        }
        if (is_a_flag(av, i)) {
            corewar->start_mem = convert_str_in_int(av[i + 1]);
            i++;
            continue;
        }
        if (!extract_args_aux(av, corewar, &i))
            return 0;
    }
    return 1;
}

void extract_header(champion_t **champions)
{
    champion_t *node = *champions;
    int extra_bytes = 0;

    while (node != NULL) {
        fread(&(node->magic_number), sizeof(unsigned int), 1, node->fd);
        node->magic_number = rev_int(node->magic_number);
        fread(&(node->name), sizeof(char), PROG_NAME_LENGTH, node->fd);
        node->name[PROG_NAME_LENGTH] = '\0';
        fread(&(node->prog_size), sizeof(unsigned long), 1, node->fd);
        node->prog_size = rev_long(node->prog_size);
        fread(&(node->comment), sizeof(char), COMMENT_LENGTH, node->fd);
        node->comment[COMMENT_LENGTH] = '\0';
        fread(&(extra_bytes), 4, 1, node->fd);
        node = node->next;
    }
}

void extract_body(champion_t **champions)
{
    champion_t *node = *champions;
    int mnemonic = 0;
    int coding_byte = 0;

    while (node != NULL) { 
        while (fread(&mnemonic, 1, 1, node->fd) == 1) {
            node->instructions = create_instruction(node->instructions);
            node->instructions->mnemonic = mnemonic;
            // fread(&(node->instructions->mnemonic), 1, 1, node->fd);
            if (node->instructions->mnemonic != 1 || node->instructions->mnemonic != 9
            || node->instructions->mnemonic != 12 || node->instructions->mnemonic != 15) {
                fread(&coding_byte, 1, 1, node->fd);
            }
            node->instructions->coding_byte = convert_int_in_bin(coding_byte);
            set_instruction(node->instructions, node);
            node->instructions = node->instructions->next;
        }
        node = node->next;
    }
}