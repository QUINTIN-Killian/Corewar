/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** extract_args
*/

#include "../include/corewar.h"

int extract_args(int ac, char **av, corewar_t *corewar)
{
    int id = -1;
    int start_mem = -1;

    for (int i = 1; i < ac; i++) {
        if (is_dump_flag(av, i)) {
            corewar->nb_turns = convert_str_in_int(av[i + 1]);
            i += 2;
            continue;
        }
        if (is_a_flag(av, i)) {
            start_mem = convert_hex_in_int(&(av[i + 1][2]));
            i += 2;
            continue;
        }
        if (is_n_flag(av, i)) {
            id = convert_str_in_int(av[i + 1]);
            i += 2;
            continue;
        }
        if (is_correct_file(av, i)) {
            corewar->champions = create_champion(corewar, id, start_mem,
            av[i]);
            continue;
        }
        mini_fdprintf(2, "Incorrect parameter.\n");
        return 0;
    }
    return 1;
}
