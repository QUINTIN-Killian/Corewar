/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** main
*/

#include "../include/corewar.h"

void init_struct(corewar_t *corewar)
{
    corewar->champions = NULL;
    corewar->nb_champions = 0;
    corewar->nb_turns = -1;
}

int error_handling(int ac, char **av, corewar_t *corewar)
{
    init_struct(corewar);
    if (ac < 3 || !is_enough_champions(ac, av))
        return 1;
    if (!extract_args(ac, av, corewar)) {
        //fonction destroy linked list
        return 1;
    }
}

int main(int ac, char **av)
{
    corewar_t corewar;

    if (error_handling(ac, av, &corewar))
        return 84;
    return 0;
}
