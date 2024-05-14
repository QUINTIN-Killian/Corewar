/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** error_handling
*/

#include "../include/corewar.h"

int is_enough_champions(int ac, char **av)
{
    int res = 0;

    for (int i = 0; i < ac; i++)
        if (is_correct_file(av, i))
            res++;
    if (res < 2 || res > 4) {
        mini_fdprintf(2, "Incorrect number of champions.\n");
        return 0;
    }
    return 1;
}

int is_enough_correct_champions(corewar_t *corewar)
{
    if (corewar->nb_champions < 2 || corewar->nb_champions > 4) {
        mini_fdprintf(2, "Incorrect number of champions.\n");
        return 0;
    }
    return 1;
}
