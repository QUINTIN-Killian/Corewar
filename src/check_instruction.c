/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** check_instruction
*/

#include "../include/corewar.h"

int check_mnemonic(corewar_t *corewar, champion_t *champion)
{
    int value = get_memory_cell(corewar, champion->PC)->value_int;

    return value >= 1 && value <= 16;
}

int check_coding_byte(corewar_t *corewar, champion_t *champion)
{
    int opcode = get_memory_cell(corewar, champion->PC)->value_int;
    int value;
    char *coding_byte;
    int nb_params;

    if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
        return 1;
    value = get_memory_cell(corewar, champion->PC + 1)->value_int;
    if (value <= 0 || value > 252)
        return 0;
    coding_byte = convert_int_in_bin(value);
    nb_params = get_nb_parameters(coding_byte);
    free(coding_byte);
    for (int i = 0; op_tab[i].mnemonique != NULL; i++) {
        if (op_tab[i].code == opcode && op_tab[i].nbr_args != nb_params)
            return 0;
        if (op_tab[i].code == opcode && op_tab[i].nbr_args == nb_params)
            return 1;
    }
    return 0;
}

static int is_correct_register(int value)
{
    return value >= 1 && value <= 16;
}


static void skip_parameter(char *coding_byte, int i, int opcode, int *pc_tmp)
{
    if (my_strncmp(&(coding_byte[i * 2]), "10", 2) == 0) {
        if (opcode == 10 || opcode == 11 || opcode == 14)
            *pc_tmp += 2;
        else
            *pc_tmp += 4;
    }
    if (my_strncmp(&(coding_byte[i * 2]), "11", 2) == 0)
        *pc_tmp += 2;
}

int check_register(corewar_t *corewar, champion_t *champion)
{
    int opcode = get_memory_cell(corewar, champion->PC)->value_int;
    char *coding_byte;
    int pc_tmp = champion->PC + 2;

    if (opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15)
        return 1;
    coding_byte = convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int);
    for (int i = 0; i < get_nb_parameters(coding_byte); i++) {
        if (my_strncmp(&(coding_byte[i * 2]), "01", 2) == 0 &&
        !is_correct_register(get_memory_cell(corewar, pc_tmp)->value_int)) {
            free(coding_byte);
            return 0;
        }
        if (my_strncmp(&(coding_byte[i * 2]), "01", 2) == 0)
            pc_tmp++;
        skip_parameter(coding_byte, i, opcode, &pc_tmp);
    }
    free(coding_byte);
    return 1;
}

int check_instruction(corewar_t *corewar, champion_t *champion)
{
    return check_mnemonic(corewar, champion) && check_coding_byte(corewar,
    champion) && check_register(corewar, champion);

}
