/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instruction_recognition
*/

#include "../include/corewar.h"

const instruction_call_t calls[] = {
    {2, exec_ld},
    {3, exec_st},
    {4, exec_add},
    {5, exec_sub},
    {6, exec_and},
    {7, exec_or},
    {8, exec_xor},
    {9, exec_zjmp},
    {10, exec_ldi},
    {11, exec_sti},
    {12, exec_fork},
    {13, exec_lld},
    {14, exec_lldi},
    {15, exec_lfork},
    {16, exec_aff},
    {-1, NULL}
};

void instruction_execution(corewar_t *corewar, champion_t *champion)
{
    int mnemonic = get_memory_cell(corewar, champion->PC)->value_int;

    if (mnemonic == 1)
        return exec_live(corewar, &corewar->champions, champion);
    for (int i = 0; calls[i].f != NULL; i++)
        if (calls[i].mnemonic == mnemonic)
            return calls[i].f(corewar, champion);
    mini_fdprintf(2, "Erreur instruction !\n");
}
