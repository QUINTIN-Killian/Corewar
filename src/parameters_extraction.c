/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** extraction2
*/

#include "../include/corewar.h"

static int extract_register(FILE *fd)
{
    int nb = 0;

    fread(&nb, 1, 1, fd);
    return nb;
}

static int extract_ind(FILE *fd)
{
    short nb = 0;

    fread(&nb, 2, 1, fd);
    return rev_short(nb);
}

static int extract_direct(FILE *fd)
{
    int nb = 0;

    fread(&nb, 4, 1, fd);
    return rev_int(nb);
}

int get_nb_parameters(char *coding_byte)
{
    int ans = 0;

    for (int i = 0; i < 8; i += 2)
        if (my_strncmp(&(coding_byte[i]), "00", 2) != 0)
            ans++;
    return ans;
}

void extract_indexes_instruction(instructions_t *instruction, FILE *fd)
{
    int nb_parameters = get_nb_parameters(instruction->coding_byte);

    instruction->parameters = malloc(sizeof(int) * nb_parameters);
    for (int i = 0; i < nb_parameters; i++) {
        if (my_strncmp(&(instruction->coding_byte[i * 2]), "01", 2) == 0) {
            instruction->parameters[i] = extract_register(fd);
            continue;
        }
        instruction->parameters[i] = extract_ind(fd);
    }
}

void extract_general(instructions_t *instruction, FILE *fd)
{
    int nb_parameters = get_nb_parameters(instruction->coding_byte);

    instruction->parameters = malloc(sizeof(char *) * nb_parameters);
    for (int i = 0; i < nb_parameters; i++) {
        if (my_strncmp(&(instruction->coding_byte[i * 2]), "01", 2) == 0) {
            instruction->parameters[i] = extract_register(fd);
            continue;
        }
        if (my_strncmp(&(instruction->coding_byte[i * 2]), "10", 2) == 0) {
            instruction->parameters[i] = extract_direct(fd);
            continue;
        }
        instruction->parameters[i] = extract_ind(fd);
    }
}

void extract_parameters(instructions_t *instruction, FILE *fd)
{
    if (instruction->mnemonic == 1) {
        instruction->parameters = malloc(sizeof(int));
        instruction->parameters[0] = extract_direct(fd);
        return;
    }
    if (instruction->mnemonic == 9 || instruction->mnemonic == 12 ||
    instruction->mnemonic == 15) {
        instruction->parameters = malloc(sizeof(int));
        instruction->parameters[0] = extract_ind(fd);
        return;
    }
    if (instruction->mnemonic == 10 || instruction->mnemonic == 11 ||
    instruction->mnemonic == 14)
        return extract_indexes_instruction(instruction, fd);
    extract_general(instruction, fd);
}
