/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instruction_recognition
*/

#include "../include/corewar.h"

static void instruction_execution4(corewar_t *corewar, champion_t *champion,
    instructions_t *instruction)
{
    if (instruction->mnemonic == 13)
        return exec_lld(champion, corewar);
    if (instruction->mnemonic == 14)
        return exec_lldi(corewar, champion);
    if (instruction->mnemonic == 15)
        return move_instruction_head(champion);
    if (instruction->mnemonic == 16)
        return exec_aff(champion);
}

static void instruction_execution3(corewar_t *corewar, champion_t *champion,
    instructions_t *instruction)
{
    if (instruction->mnemonic == 9)
        return exec_zjmp(champion);
    if (instruction->mnemonic == 10)
        return exec_ldi(corewar, champion);
    if (instruction->mnemonic == 11)
        return exec_sti(champion, corewar);
    if (instruction->mnemonic == 12)
        return move_instruction_head(champion);
    instruction_execution4(corewar, champion, instruction);
}

static void instruction_execution2(corewar_t *corewar, champion_t *champion,
    instructions_t *instruction)
{
    if (instruction->mnemonic == 5)
        return exec_sub(champion);
    if (instruction->mnemonic == 6)
        return exec_and(champion);
    if (instruction->mnemonic == 7)
        return exec_or(champion);
    if (instruction->mnemonic == 8)
        return exec_xor(champion);
    instruction_execution3(corewar, champion, instruction);
}

void instruction_execution(corewar_t *corewar, champion_t *champion,
    instructions_t *instruction)
{
    if (instruction->mnemonic == 1)
        return exec_live(champion);
    if (instruction->mnemonic == 2)
        return exec_ld(champion, corewar);
    if (instruction->mnemonic == 3)
        return exec_st(champion, corewar);
    if (instruction->mnemonic == 4)
        return exec_add(champion);
    instruction_execution2(corewar, champion, instruction);
}
