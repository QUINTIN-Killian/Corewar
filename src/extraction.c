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
            corewar->start_mem = convert_hex_in_int(&(av[i + 1][2]));
            i++;
            continue;
        }
        if (!extract_args_aux(av, corewar, &i))
            return 0;
    }
    return 1;
}

int extract_header(champion_t **champions)
{
    champion_t *node = *champions;

    while (node != NULL) {
        if (fread(&(node->magic_number), sizeof(unsigned int), 1,
        node->fd) < 1 || fread(&(node->name), sizeof(char), PROG_NAME_LENGTH,
        node->fd) < PROG_NAME_LENGTH || fread(&(node->prog_size),
        sizeof(unsigned long), 1, node->fd) < 1 || fread(&(node->comment),
        sizeof(char), COMMENT_LENGTH, node->fd) < COMMENT_LENGTH) {
            mini_fdprintf(2, "Incorrect header file.\n");
            return 0;
        }
        node->magic_number = rev_int(node->magic_number);
        node->name[PROG_NAME_LENGTH] = '\0';
        node->prog_size = rev_long(node->prog_size);
        node->comment[COMMENT_LENGTH] = '\0';
        node = node->next;
    }
    return 1;
}
