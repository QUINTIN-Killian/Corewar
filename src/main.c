/*
** EPITECH PROJECT, 2024
** corewar
** File description:
** main
*/

#include "../include/corewar.h"

static int print_help(void)
{
    mini_printf("USAGE\n");
    mini_printf("./corewar [-dump nbr_cycle] [[-n prog_number] ");
    mini_printf("[-a load_address] prog_name] ...\n");
    mini_printf("DESCRIPTION\n");
    mini_printf("-dump nbr_cycle dumps the memory after the ");
    mini_printf("nbr_cycle execution (if the round isn’t\n");
    mini_printf("already over) with the following format: 32 bytes/line in ");
    mini_printf("hexadecimal (A0BCDEFE1DD3...)\n");
    mini_printf("-n prog_number sets the next program’s number. ");
    mini_printf("By default, the first free number in the\n");
    mini_printf("parameter order\n");
    mini_printf("-a load_address sets the next program’s loading address. ");
    mini_printf("When no address is specified,\n");
    mini_printf("optimize the addresses so that the processes are as far ");
    mini_printf("away from each other as\n");
    mini_printf("possible. The addresses are MEM_SIZE modulo.\n");
    return 0;
}

void init_struct(corewar_t *corewar)
{
    corewar->nb_live = 0;
    corewar->nb_delta = 0;
    corewar->id = -1;
    corewar->start_mem = -1;
    corewar->champions = NULL;
    corewar->nb_champions = 0;
    corewar->nb_turns = -1;
    corewar->memory = NULL;
}

void destroy_struct(corewar_t *corewar)
{
    destroy_memory(corewar);
    delete_champions_list(&corewar->champions);
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
    corewar->champions = rev_champions(&corewar->champions);
    set_champions_infos(corewar, &corewar->champions);
    extract_header(&corewar->champions);
    del_incorrect_magic_number(corewar, &corewar->champions);
    if (!is_enough_correct_champions(corewar))
        return 1;
    return 0;
}

int main(int ac, char **av)
{
    corewar_t corewar;

    if (ac == 2 && my_strcmp(av[1], "-h") == 0)
        return print_help();
    if (error_handling(ac, av, &corewar)) {
        destroy_struct(&corewar);
        return 84;
    }
    extract_body(&corewar.champions);
    create_memory(&corewar);
    write_instructions_in_memory(&corewar, &corewar.champions);
    main_loop(&corewar.champions, &corewar);
    destroy_struct(&corewar);
    return 0;
}
