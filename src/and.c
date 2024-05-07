/*
** EPITECH PROJECT, 2024
** corewar-private
** File description:
** and
*/

#include "../include/corewar.h"

static int get_param_and(corewar_t *corewar, champion_t *champion, int ind,
    int pc_adding)
{
    char *bin = convert_int_in_bin(get_memory_cell(corewar,
    champion->PC + 1)->value_int);

    if (my_strncmp(&(bin[ind]), "01", 2) == 0) {
        free(bin);
        return champion->registers[get_memory_cell(corewar,
        champion->PC + pc_adding)->value_int];
    } else {
        free(bin);
        return get_memory_cell(corewar, champion->PC + pc_adding)->value_int;
    }
}

void exec_and(corewar_t *corewar, champion_t *champion)
{
    int value1 = get_param_and(corewar, champion, 0, 2);
    int value2 = get_param_and(corewar, champion, 2, 3);

    champion->registers[get_memory_cell(corewar, champion->PC + 4)->value_int]
    = value1 & value2;
    set_carry(champion, champion->registers[get_memory_cell(corewar,
    champion->PC + 4)->value_int]);
    champion->PC += 5;
    champion->timeout = 6;
}

// static int set_adresse(char *pair)
// {
//     if (my_strcmp(pair, "10") == 0) {
//         return 4;
//     }
//     if (my_strcmp(pair, "01") == 0) {
//         return 1;
//     }
//     return 2;
// }

int check_and(char *coding_byte, champion_t *champion, corewar_t *corewar)
{
    char pair[3];
    int adresse = 0;

    for (int i = 0; i < 4; i += 2) {
        pair[0] = coding_byte[i];
        pair[1] = coding_byte[i + 1];
        pair[2] = '\0';
        if (my_strcmp(pair, "10") != 0 && my_strcmp(pair, "11")
        != 0 && my_strcmp(pair, "01") != 0)
            return 1;
        adresse = set_adresse(pair, champion);
    }
    pair[0] = coding_byte[4];
    pair[1] = coding_byte[5];
    pair[2] = '\0';
    if (check_register(adresse + 1, corewar) == 1)
        return 1;
    return check_empty(my_strlen(coding_byte), coding_byte, pair, 6);
}
