/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** main
*/

#include "../include/corewar.h"

void init_struct(corewar_t *corewar)
{
    corewar->id = -1;
    corewar->start_mem = -1;
    corewar->champions = NULL;
    corewar->nb_champions = 0;
    corewar->nb_turns = -1;
}

void destroy_struct(corewar_t *corewar)
{
    delete_list(&corewar->champions);
}

int error_handling(int ac, char **av, corewar_t *corewar)
{
    init_struct(corewar);
    if (ac < 3) {
        mini_fdprintf(2, "Not enough arguments.\n");
        return 1;
    }
    if (!is_enough_champions(ac, av) || !extract_args(ac, av, corewar))
        return 1;
    give_champions_id(&corewar->champions);
    corewar->champions = rev_champions(&corewar->champions);
    if (!unique_champions(&corewar->champions))
        return 1;
    extract_header(&corewar->champions);
    del_incorrect_magic_number(corewar, &corewar->champions);
    if (!is_enough_correct_champions(corewar))
        return 1;
    return 0;
}

int main(int ac, char **av)
{
    corewar_t corewar;

    if (error_handling(ac, av, &corewar)) {
        destroy_struct(&corewar);
        return 84;
    }
    display_champs_infos(&corewar.champions);
    destroy_struct(&corewar);
    return 0;
}
