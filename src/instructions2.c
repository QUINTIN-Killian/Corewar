/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** instructions2
*/

#include "../include/corewar.h"

extern op_t op_tab[];

static char *extract_index(char *params, champion_t *node)
{
    short nb = 0;

    fread(&nb, 2, 1, node->fd);
    nb = (nb << 8) | ((nb >> 8) & 0xFF);
    params = convert_int_to_str(nb);
    printf("indirect : %s\n", params);
    return params;
}

static char *extract_register(char *params, champion_t *node)
{
    short nb  = 0;


    fread(&nb, 1, 1, node->fd);
    params = convert_int_to_str(nb);
    printf("register : %s\n", params);
    return params;
}

static char *extract_indirect(char *params, champion_t *node)
{
    short nb = 0;
    fread(&nb, 2, 1, node->fd);
    nb = (nb << 8) | ((nb >> 8) & 0xFF);
    params = convert_int_to_str(nb);
    printf("indirect : %x\n", nb);
    return params;
}

static char *extract_direct(char *params, champion_t *node)
{
    short nb = 0;
    fread(&nb, 4, 1, node->fd);
    nb = (nb << 8) | ((nb >> 8) & 0xFF);
    params = convert_int_to_str(nb);
    printf("indirect : %x\n", nb);
    return params;
}

static char *extract_sti(const char *pair, char *params, champion_t *node)
{
    if (strcmp(pair, "10") == 0 ) {
        params = extract_index(params, node);
        printf("params : %s\n", params);
        return params;
    }
    if (strcmp(pair, "01") == 0) {
        params = extract_register(params, node);
        return params;
    }
    if (strcmp(pair, "11") == 0) {
        params = extract_index(params, node);
        return params;
    }
    return NULL;
}

char *extract_gen(const char *pair, char *params, champion_t *node)
{
    if (strcmp(pair, "10") == 0 ) {
        params = extract_direct(params, node);
        return params;
    }
    if (strcmp(pair, "01") == 0) {
        params = extract_register(params, node);
        return params;
    }
    if (strcmp(pair, "11") == 0) {
        params = extract_indirect(params, node);
        return params;
    }
    return NULL;
}

void other_extract(instructions_t *node, champion_t *champ, int q, char *pair)
{
    if (strcmp(node->instruction, "add") == 0 || strcmp(node->instruction, "sub") == 0
    || strcmp(node->instruction, "st") == 0 || strcmp(node->instruction, "and") == 0
    || strcmp(node->instruction, "or") == 0 || strcmp(node->instruction, "xor") == 0
    || strcmp(node->instruction, "ld") == 0 || strcmp(node->instruction, "zjmp") == 0
    || strcmp(node->instruction, "fork") == 0 || strcmp(node->instruction, "lld") == 0
    || strcmp(node->instruction, "lfork") == 0 || strcmp(node->instruction, "aff") == 0) {
        for (int i = 0; i < 8; i += 2, q++) {
            my_strncpy(pair, node->coding_byte + i, 2);
            pair[2] = '\0';
            node->parameters[q] = extract_gen(pair, node->parameters[q], champ);
        }
    }
}

void extracts_methods(instructions_t *node, champion_t *champ, int q)
{
    char pair[3];

    if (strcmp(node->instruction, "sti") == 0 || strcmp(node->instruction, "ldi") == 0
    || strcmp(node->instruction, "lldi") == 0) {
        for (int i = 0; i < 8; i += 2, q++) {
            my_strncpy(pair, node->coding_byte + i, 2);
            pair[2] = '\0';
            node->parameters[q] =  extract_sti(pair, node->parameters[q], champ);
        }
    }
    other_extract(node, champ, q, pair);
}

void extract_parameters(instructions_t *node, champion_t *champ)
{
    char pair[3];
    int init = 0;
    int q = 0;

    for (int i = 0; i < 8; i += 2) {
        my_strncpy(pair, node->coding_byte + i, 2);
        pair[2] = '\0';
        if (my_strcmp(pair, "00") == 0)
            init++;
    }
    node->parameters = malloc(sizeof(char * ) * init);
    extracts_methods(node, champ, q);
}

int set_instruction(instructions_t *node, champion_t *champ)
{
    for (int i = 0; op_tab[i].mnemonique != NULL; i++) {
        if (node->mnemonic == op_tab[i].code) {
            node->instruction = my_strdup(op_tab[i].mnemonique);
            node->nb_cycles = op_tab[i].nbr_cycles;
            node->nb_parameters = op_tab[i].nbr_args;
            extract_parameters(node, champ);
            return 1;
        }
    }
    return 0;
}
