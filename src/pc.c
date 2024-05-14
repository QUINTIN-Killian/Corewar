/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** pc
*/

#include "../include/corewar.h"

void init_pc_struct(champion_t *champion)
{
    champion->pc->coding_byte = NULL;
    champion->pc->params = NULL;
}

void destroy_pc_content(champion_t *champion)
{
    free_word_array(champion->pc->coding_byte);
    free_word_array(champion->pc->params);
}
