/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** champions
*/

#include "../include/corewar.h"

champion_t *create_champion(corewar_t *corewar, int id, int start_mem,
    char *filename)
{
    champion_t *champion = malloc(sizeof(champion_t));

    corewar->nb_champions++;
    if (id == -1)
        champion->id = get_max_champion_id(&corewar->champions);
    else
        champion->id = id;
    champion->start_mem = start_mem;
    champion->fd = fopen(filename, "r");
    champion->next = corewar->champions;
    return champion;
}
