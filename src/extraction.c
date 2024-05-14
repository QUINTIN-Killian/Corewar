/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** extraction
*/

#include "../include/corewar.h"

static int extract_args_aux(char **av, corewar_t *corewar, int *i)
{
    if (is_n_flag(av, *i)) {
        corewar->id = convert_str_in_int(av[*i + 1]);
        *i += 1;
        return 1;
    }
    if (is_correct_file(av, *i)) {
        corewar->champions = create_champion(corewar, av[*i]);
        return 1;
    }
    mini_fdprintf(2, "Incorrect parameter.\n");
    return 0;
}

int extract_args(int ac, char **av, corewar_t *corewar)
{
    for (int i = 1; i < ac; i++) {
        if (is_dump_flag(av, i)) {
            corewar->nb_turns = convert_str_in_int(av[i + 1]);
            i++;
            continue;
        }
        if (is_a_flag(av, i)) {
            corewar->start_mem = convert_str_in_int(av[i + 1]) % MEM_SIZE;
            i++;
            continue;
        }
        if (!extract_args_aux(av, corewar, &i))
            return 0;
    }
    return 1;
}

void extract_header(champion_t **champions)
{
    champion_t *node = *champions;
    int extra_bytes = 0;

    while (node != NULL) {
        fread(&(node->magic_number), sizeof(unsigned int), 1, node->fd);
        node->magic_number = rev_int(node->magic_number);
        fread(&(node->name), sizeof(char), PROG_NAME_LENGTH, node->fd);
        node->name[PROG_NAME_LENGTH] = '\0';
        fread(&(node->prog_size), sizeof(unsigned long), 1, node->fd);
        node->prog_size = rev_long(node->prog_size);
        fread(&(node->comment), sizeof(char), COMMENT_LENGTH, node->fd);
        node->comment[COMMENT_LENGTH] = '\0';
        fread(&(extra_bytes), 4, 1, node->fd);
        node = node->next;
    }
}

static int extract_coding_byte(int mnemonic, FILE *fd)
{
    int coding_byte = 0;

    if (mnemonic != 1 && mnemonic != 9 && mnemonic != 12 && mnemonic != 15)
        fread(&coding_byte, 1, 1, fd);
    return coding_byte;
}

void extract_body(champion_t **champions)
{
    champion_t *node = *champions;
    int mnemonic = 0;

    while (node != NULL) {
        while (fread(&mnemonic, 1, 1, node->fd) == 1) {
            node->instructions = create_instruction(node->instructions);
            node->instructions->mnemonic = mnemonic;
            node->instructions->coding_byte =
            convert_int_in_bin(extract_coding_byte(mnemonic, node->fd));
            set_instruction(node->instructions);
            extract_parameters(node->instructions, node->fd);
        }
        node->instructions = rev_instructions(&node->instructions);
        node->head_instruction_ref = node->instructions;
        node = node->next;
    }
}

static int extract_live(corewar_t *corewar, champion_t *champion, int pc_tmp)
{
    champion->pc->params = realloc_tab_plus_one(champion->pc->params);
    champion->pc->params[0] = convert_int_to_str(combine_bytes(4,
    get_memory_cell(corewar, pc_tmp)->value_int,
    get_memory_cell(corewar, pc_tmp + 1)->value_int,
    get_memory_cell(corewar, pc_tmp + 2)->value_int,
    get_memory_cell(corewar, pc_tmp + 3)->value_int));
    champion->pc->params[1] = NULL;
    champion->PC = pc_tmp + 4;
    return 1;
}

static int extract_index(corewar_t *corewar, champion_t *champion, int pc_tmp)
{
    for (int i = 0; i < 4; i++) {
        if (my_strcmp(champion->pc->coding_byte[i], "00") == 0)
            break;
        if (my_strcmp(champion->pc->coding_byte[i], "01") == 0) {
            
            pc_tmp++;
        }
    }
    champion->PC = pc_tmp;
    return 1;
}

int extract_instruction(corewar_t *corewar, champion_t *champion)
{
    char *coding_byte;
    int pc_tmp = champion->PC;

    destroy_pc_content(champion);
    champion->pc->mnemonic = get_memory_cell(corewar, pc_tmp)->value_int;
    if (champion->pc->mnemonic < 1 || champion->pc->mnemonic > 16)
        return 0;
    if ((champion->pc->mnemonic >= 2 && champion->pc->mnemonic <= 8) ||
    (champion->pc->mnemonic >= 10 && champion->pc->mnemonic <= 11) ||
    (champion->pc->mnemonic >= 13 && champion->pc->mnemonic <= 14) ||
    champion->pc->mnemonic == 16) {
        pc_tmp++;
        coding_byte = convert_int_in_bin(get_memory_cell(corewar,
        pc_tmp)->value_int);
        champion->pc->coding_byte = malloc(sizeof(char *) * 5);
        for (int i = 0; i < 4; i++) {
            champion->pc->coding_byte[i] =
            my_strndup(&(coding_byte[i * 2]), 2);
        }
        champion->pc->coding_byte[4] = NULL;
        free(coding_byte);
    }
    pc_tmp++;
    champion->pc->params = NULL;
    if (champion->pc->mnemonic == 1)
        return extract_live(corewar, champion, pc_tmp);
    for (int i = 0; i < 4; i++) {
        if (my_strcmp(champion->pc->coding_byte[i], "01") == 0) {
            champion->pc->params[i] = convert_int_to_str(get_memory_cell(corewar, pc_tmp)->value_int);
            continue;
        }
        if ()
    }
    return 1;
}
