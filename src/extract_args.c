/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** extract_args
*/

#include "../include/corewar.h"

static int extract_args_aux(int ac, char **av, corewar_t *corewar, int *i)
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
        if (!extract_args_aux(ac, av, corewar, &i))
            return 0;
    }
    return 1;
}
