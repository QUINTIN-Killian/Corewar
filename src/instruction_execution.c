/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instruction_recognition
*/

#include "../include/corewar.h"

static void instruction_execution4(champion_t *champion,
    instructions_t *instruction)
{
    if (instruction->mnemonic == 13) {
        mini_printf("Instruction LLD\n");
        return;
    }
    if (instruction->mnemonic == 14) {
        mini_printf("Instruction LLDI\n");
        return;
    }
    if (instruction->mnemonic == 15) {
        mini_printf("Instruction LFORK\n");
        return;
    }
    if (instruction->mnemonic == 16) {
        mini_printf("Instruction AFF\n");
        return exec_aff(champion);
    }
}

static void instruction_execution3(champion_t *champion,
    instructions_t *instruction)
{
    if (instruction->mnemonic == 9) {
        mini_printf("Instruction ZJMP\n");
        return;
    }
    if (instruction->mnemonic == 10) {
        mini_printf("Instruction LDI\n");
        return;
    }
    if (instruction->mnemonic == 11) {
        mini_printf("Instruction STI\n");
        return;
    }
    if (instruction->mnemonic == 12) {
        mini_printf("Instruction FORK\n");
        return;
    }
    instruction_execution4(champion, instruction);
}

static void instruction_execution2(champion_t *champion,
    instructions_t *instruction)
{
    if (instruction->mnemonic == 5) {
        mini_printf("Instruction SUB\n");
        return exec_sub(champion);
    }
    if (instruction->mnemonic == 6) {
        mini_printf("Instruction AND\n");
        return exec_and(champion);
    }
    if (instruction->mnemonic == 7) {
        mini_printf("Instruction OR\n");
        return exec_or(champion);
    }
    if (instruction->mnemonic == 8) {
        mini_printf("Instruction XOR\n");
        return exec_xor(champion);
    }
    instruction_execution3(champion, instruction);
}

void instruction_execution(champion_t *champion, instructions_t *instruction)
{
    if (instruction->mnemonic == 1) {
        mini_printf("Instruction LIVE\n");
        return exec_live(champion);
    }
    if (instruction->mnemonic == 2) {
        mini_printf("Instruction LD\n");
        return;
    }
    if (instruction->mnemonic == 3) {
        mini_printf("Instruction ST\n");
        return;
    }
    if (instruction->mnemonic == 4) {
        mini_printf("Instruction ADD\n");
        return exec_add(champion);
    }
    instruction_execution2(champion, instruction);
}
