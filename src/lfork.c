/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** lfork
*/
#include "../include/corewar.h"

void exec_lfork(champion_t *champion, corewar_t *corewar)
{
    int value1 = 0;
    int adress = 0;

    value1 = champion->instructions->parameters[0];
    adress = champion->PC + value1;
    duplicate_champion(corewar, champion->id, adress);
    // move_instruction_head(champion);
}