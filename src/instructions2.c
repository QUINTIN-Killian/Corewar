/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instructions2
*/

#include "../include/corewar.h"

static int set_instruction4(instructions_t *node)
{
    if (node->mnemonic == 13) {
        node->instruction = my_strdup("lld");
        return 1;
    }
    if (node->mnemonic == 14) {
        node->instruction = my_strdup("lldi");
        return 1;
    }
    if (node->mnemonic == 15) {
        node->instruction = my_strdup("lfork");
        return 1;
    }
    if (node->mnemonic == 16) {
        node->instruction = my_strdup("aff");
        return 1;
    }
    return 0;
}

static int set_instruction3(instructions_t *node)
{
    if (node->mnemonic == 9) {
        node->instruction = my_strdup("zjmp");
        return 1;
    }
    if (node->mnemonic == 10) {
        node->instruction = my_strdup("ldi");
        return 1;
    }
    if (node->mnemonic == 11) {
        node->instruction = my_strdup("sti");
        return 1;
    }
    if (node->mnemonic == 12) {
        node->instruction = my_strdup("fork");
        return 1;
    }
    return set_instruction4(node);
}

static int set_instruction2(instructions_t *node)
{
    if (node->mnemonic == 5) {
        node->instruction = my_strdup("sub");
        return 1;
    }
    if (node->mnemonic == 6) {
        node->instruction = my_strdup("and");
        return 1;
    }
    if (node->mnemonic == 7) {
        node->instruction = my_strdup("or");
        return 1;
    }
    if (node->mnemonic == 8) {
        node->instruction = my_strdup("xor");
        return 1;
    }
    return set_instruction3(node);
}

int set_instruction(instructions_t *node)
{
    if (node->mnemonic == 1) {
        node->instruction = my_strdup("live");
        return 1;
    }
    if (node->mnemonic == 2) {
        node->instruction = my_strdup("ld");
        return 1;
    }
    if (node->mnemonic == 3) {
        node->instruction = my_strdup("st");
        return 1;
    }
    if (node->mnemonic == 4) {
        node->instruction = my_strdup("add");
        return 1;
    }
    return set_instruction2(node);
}
